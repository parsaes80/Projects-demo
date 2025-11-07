#include <complex>
#include <iostream>
#include <iomanip>
#include <SDL2/SDL.h>
#include <omp.h>
#include <chrono>
#include <immintrin.h>
#include <boost/multiprecision/cpp_bin_float.hpp>

//CUSTOMIZATION:
constexpr int RESOLUTION = 1440;
constexpr int DEPTH = 2;
constexpr int SCREEN_SIZE = 1;
constexpr int THREAD_COUNT = 16;

using namespace std;

int currDepth = DEPTH;
int zoom = 1;

//void computeMandelbrot(int** dots, int rows, int cols, long double startx, long double endx, long double starty, long double endy) {
//    long double stepx = (endx - startx) / (cols - 1); // will become zero if zoomed too much
//    long double stepy = (endy - starty) / (rows - 1); //causing pixelation
//
//    currDepth = DEPTH + (zoom / 4);
//    #pragma omp parallel for schedule(dynamic)
//    for (int i = 0; i < rows; i++) {
//        for (int j = 0; j < cols; j++) {
//            long double real = startx + j * stepx;
//            long double imag = starty + i * stepy;
//            complex<long double> c(real, imag);
//            complex<long double> z(0, 0);
//            dots[i][j] = 0;
//            int color = 0;
//            for (int n = 0; n < 255 * currDepth; n++) {
//                z = z * z + c;
//                color++;
//                if ((z.imag()*z.imag()) + (z.real()* z.real())  > 4) {
//                    dots[i][j] = color;
//                    break;
//                }
//            }
//        }
//    }
//}
void computeMandelbrot(int** dots, int rows, int cols, double startx, double endx, double starty, double endy) {
    double stepx = (endx - startx) / cols;
    double stepy = (endy - starty) / rows;
    currDepth = DEPTH + (zoom / 4);
    int max_iterations = 255 * currDepth;

#pragma omp parallel for schedule(dynamic)
    for (int i = 0; i < rows; i++) {
        // We process 8 pixels at a time, so the inner loop steps by 8.
        for (int j = 0; j < cols; j += 8) {

            // --- Step 1: Initialize vectors for 8 pixels ---

            // c_real = startx + (j + [0,1,2,3,4,5,6,7]) * stepx
            __m512d v_j_offset = _mm512_set_pd(7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0, 0.0);
            __m512d v_c_real = _mm512_fmadd_pd(v_j_offset, _mm512_set1_pd(stepx), _mm512_set1_pd(startx + j * stepx));

            // c_imag is constant for the entire row
            __m512d v_c_imag = _mm512_set1_pd(starty + i * stepy);

            // z starts at 0
            __m512d v_z_real = _mm512_setzero_pd();
            __m512d v_z_imag = _mm512_setzero_pd();

            // Vector to store the iteration count for each of the 8 pixels
            __m256i v_iterations = _mm256_setzero_si256();

            // Mask to track which of the 8 pixels are still iterating (1 = active, 0 = escaped)
            __mmask8 active_mask = 0xFF; // Start with all 8 lanes active

            // --- Step 2: The Main Mandelbrot Loop ---
            for (int n = 0; n < max_iterations; n++) {
                if (active_mask == 0) {
                    break; // All 8 pixels have escaped, exit early
                }

                // The Mandelbrot calculation: z = z*z + c
                // z_real_new = z_real^2 - z_imag^2 + c_real
                // z_imag_new = 2*z_real*z_imag + c_imag

                __m512d zr_sq = _mm512_mul_pd(v_z_real, v_z_real);
                __m512d zi_sq = _mm512_mul_pd(v_z_imag, v_z_imag);
                __m512d zrzi = _mm512_mul_pd(v_z_real, v_z_imag);

                // Update z, but only for the active lanes
                v_z_real = _mm512_mask_add_pd(v_z_real, active_mask, _mm512_sub_pd(zr_sq, zi_sq), v_c_real);
                v_z_imag = _mm512_mask_add_pd(v_z_imag, active_mask, _mm512_add_pd(zrzi, zrzi), v_c_imag);

                // --- Step 3: Check for escapees ---
                // Condition: z_real^2 + z_imag^2 > 4
                zr_sq = _mm512_mul_pd(v_z_real, v_z_real);
                zi_sq = _mm512_mul_pd(v_z_imag, v_z_imag);
                __m512d mag_sq = _mm512_add_pd(zr_sq, zi_sq);
                __m512d v_four = _mm512_set1_pd(4.0);

                // Compare magnitudes with 4. Result is a mask.
                __mmask8 escape_mask = _mm512_cmp_pd_mask(mag_sq, v_four, _CMP_GT_OQ);

                // --- Step 4: Update state based on escapees ---
                // Increment iteration count only for active lanes
                v_iterations = _mm256_mask_add_epi32(v_iterations, active_mask, v_iterations, _mm256_set1_epi32(1));

                // Turn off the bit in the active_mask for any pixel that has escaped
                active_mask = _kandn_mask8(escape_mask, active_mask);
            }

            // --- Step 5: Store the results ---
            // Check if we have enough columns left to write 8 pixels
            v_iterations = _mm256_mask_mov_epi32(v_iterations, active_mask, _mm256_setzero_si256());

            // Check if we have enough columns left to write 8 pixels
            if (j + 8 <= cols) {
                _mm256_storeu_si256(reinterpret_cast<__m256i*>(&dots[i][j]), v_iterations);
            }
            else {
                // Handle the edge case where there are fewer than 8 pixels left in the row
                alignas(32) int temp[8];
                _mm256_store_si256(reinterpret_cast<__m256i*>(temp), v_iterations);
                for (int k = 0; k < cols - j; ++k) {
                    dots[i][j + k] = temp[k];
                }
            }
        }
    }
}

void render(int** dots, int rows, int cols, SDL_Renderer* renderer, SDL_Rect& rect, int screenWidth, int screenHeight) {
    // Render Mandelbrot set
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            SDL_SetRenderDrawColor(renderer, 0, dots[i][j] / currDepth, dots[i][j] / currDepth, 255);
            rect.x = j * (screenWidth / cols);
            rect.y = i * (screenHeight / rows);
            SDL_RenderFillRect(renderer, &rect);
        }
    }
    SDL_RenderPresent(renderer);
}
int main(int argc, char** argv) {
    const int res = RESOLUTION;
    const int rows = res;
    const int cols = res;

    int** dots = new int* [rows];
    for (int i = 0; i < rows; i++) {
        dots[i] = new int[cols]();
    }

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
        return 1;
    }

    const int screenWidth = cols * SCREEN_SIZE;
    const int screenHeight = rows * SCREEN_SIZE;
    SDL_Window* window = SDL_CreateWindow("Mandelbrot set Visualization", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Rect rect = { 0, 0, screenWidth / cols, screenHeight / rows };

    long double startx = -2, endx = 2, starty = 2, endy = -2;

    cout << setprecision(20);
    omp_set_num_threads(THREAD_COUNT);

    cout << "CONTROLS: \n ZOOM IN/OUT(E/Q) \n UP/DOWN/LEFT/RIGHT (W/S/A/D) \n EXIT(R)\n";

    // Initial rendering
    computeMandelbrot(dots, rows, cols, startx, endx, starty, endy);
    render(dots, rows, cols, renderer, rect, screenWidth, screenHeight);

    bool quit = false;
    SDL_Event event;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            else if (event.type == SDL_KEYDOWN) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderClear(renderer);

                long double decreaseAmountx = abs(endx - startx) / 4;
                long double decreaseAmounty = abs(starty - endy) / 4;

                switch (event.key.keysym.sym) {
                case SDLK_e:
                    zoom++;
                    endx -= decreaseAmountx; startx += decreaseAmountx;
                    endy += decreaseAmounty; starty -= decreaseAmounty;
                    break;
                case SDLK_q:
                    zoom--;
                    endx += decreaseAmountx; startx -= decreaseAmountx;
                    endy -= decreaseAmounty; starty += decreaseAmounty;
                    break;
                case SDLK_a:
                    endx -= decreaseAmountx; startx -= decreaseAmountx;
                    break;
                case SDLK_d:
                    endx += decreaseAmountx; startx += decreaseAmountx;
                    break;
                case SDLK_w:
                    endy += decreaseAmounty; starty += decreaseAmounty;
                    break;
                case SDLK_s:
                    endy -= decreaseAmounty; starty -= decreaseAmounty;
                    break;
                case SDLK_r:
                    SDL_Event quitEvent;
                    quitEvent.type = SDL_QUIT;
                    SDL_PushEvent(&quitEvent);
                    continue;
                }
                auto start = chrono::high_resolution_clock::now();
                computeMandelbrot(dots, rows, cols, startx, endx, starty, endy);
                auto stop = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
                cout << "Time taken by function: "<< duration.count() << " microseconds" << endl;
                render(dots, rows, cols, renderer, rect, screenWidth, screenHeight);
                cout << "x range: " << startx << " to " << endx << endl;
                cout << "y range: " << endy << " to " << starty << endl << endl;
                cout << currDepth<<endl;
            }
        }
    }
    // Cleanup
    for (int i = 0; i < rows; i++) {
        delete[] dots[i];
    }
    delete[] dots;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
