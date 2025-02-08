#include <complex>
#include <iostream>
#include <iomanip>
#include <SDL.h>
#include <omp.h>

//CUSTOMIZATION:
constexpr int RESOLUTION = 1000;
constexpr int DEPTH = 1;
constexpr int SCREEN_SIZE = 1;
constexpr int THREAD_COUNT = 16;

using namespace std;


void computeAndRenderMandelbrot(int** dots, int rows, int cols, long double startx, long double endx, long double starty, long double endy, SDL_Renderer* renderer, SDL_Rect& rect, int screenWidth, int screenHeight) {
    long double stepx = (endx - startx) / (cols - 1);
    long double stepy = (endy - starty) / (rows - 1);

#pragma omp parallel for schedule(dynamic)
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            long double real = startx + j * stepx;
            long double imag = starty + i * stepy;
            complex<long double> position(real, imag);
            complex<long double> iterate(0, 0);
            dots[i][j] = 0;
            int color = 0;
            for (int n = 0; n < 255 * DEPTH; n++) {
                iterate = iterate * iterate + position;
                color++;
                if (abs(iterate) > 2) {
                    dots[i][j] = color;
                    break;
                }
            }
        }
    }

    // Render Mandelbrot set
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            SDL_SetRenderDrawColor(renderer, 0, dots[i][j] / DEPTH, dots[i][j] / DEPTH, 255);
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
    computeAndRenderMandelbrot(dots, rows, cols, startx, endx, starty, endy, renderer, rect, screenWidth, screenHeight);

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
                    endx -= decreaseAmountx; startx += decreaseAmountx;
                    endy += decreaseAmounty; starty -= decreaseAmounty;
                    break;
                case SDLK_q:
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

                computeAndRenderMandelbrot(dots, rows, cols, startx, endx, starty, endy, renderer, rect, screenWidth, screenHeight);

                cout << "x range: " << startx << " to " << endx << endl;
                cout << "y range: " << endy << " to " << starty << endl << endl;
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
