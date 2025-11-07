#include "QTMandelbrot.h"
#include <complex>
#include <execution>
#include <algorithm>
#include <numeric>
#include <vector>
#include <cmath>
#include <QKeyEvent>
#include <print>
// Color gradient function
QRgb getGradientColor(int iterations, int maxIterations) {
    if (iterations == 0) {
        return qRgb(0, 0, 0); // Black for points in the set
    }
    
    // Normalize the iteration count to 0-1
    double t = static_cast<double>(iterations) / maxIterations;
    
    // Apply smooth coloring with multiple gradients
    double r, g, b;
    
    if (t < 0.16) {
        // Dark blue to blue
        r = 0;
        g = 0;
        b = 0.5 + 0.5 * (t / 0.16);
    } else if (t < 0.33) {
        // Blue to cyan
        double local_t = (t - 0.16) / 0.17;
        r = 0;
        g = local_t;
        b = 1.0;
    } else if (t < 0.5) {
        // Cyan to green
        double local_t = (t - 0.33) / 0.17;
        r = 0;
        g = 1.0;
        b = 1.0 - local_t;
    } else if (t < 0.66) {
        // Green to yellow
        double local_t = (t - 0.5) / 0.16;
        r = local_t;
        g = 1.0;
        b = 0;
    } else if (t < 0.83) {
        // Yellow to orange
        double local_t = (t - 0.66) / 0.17;
        r = 1.0;
        g = 1.0 - 0.5 * local_t;
        b = 0;
    } else {
        // Orange to red
        double local_t = (t - 0.83) / 0.17;
        r = 1.0;
        g = 0.5 - 0.5 * local_t;
        b = 0;
    }
    
    // Convert to 0-255 range
    return qRgb(
        static_cast<int>(r * 255),
        static_cast<int>(g * 255),
        static_cast<int>(b * 255)
    );
}

QTMandelbrot::QTMandelbrot(QWidget *parent): QMainWindow(parent)
{
    ui.setupUi(this);
    
    ui.Z_i->setMinimum(-200);ui.Z_i->setMaximum(200);ui.Z_i->setValue(0);
    ui.Z_r->setMinimum(-200);ui.Z_r->setMaximum(200);ui.Z_r->setValue(0);

    renderMandelbrot();
    displayMandelbrot();
}

QTMandelbrot::~QTMandelbrot()
{}

void QTMandelbrot::updateImageAndGrid() {
    int w = this->width();
    int h = this->height();
    
    image = QImage(w, h, QImage::Format_RGB32);
    colorGrid.clear();
    colorGrid.resize(w, std::vector<int>(h, 0));
}

void QTMandelbrot::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);

    ui.mandelbrotLabel->resize(this->width(), this->height());

    updateImageAndGrid();
    renderMandelbrot();
    displayMandelbrot();
}

void QTMandelbrot::renderMandelbrot(){
    const int width = image.width();
    const int height = image.height();

    // Smooth gradual increase in iterations based on zoom level
    const double Depth = 1.0 + (zoom / 16.0); // More gradual than /30
    const int maxIterations = static_cast<int>(255 * Depth);
    
    // Update currDepth for color consistency (keep it as integer for color calculations)
    currDepth = static_cast<int>(Depth);

    const long double step = (endx - startx) / (width - 1);

    // Create a vector of row indices to parallelize over
    std::vector<int> rows(height);
    std::iota(rows.begin(), rows.end(), 0);

    // Parallelize the outer loop using std::execution
    std::for_each(std::execution::par_unseq, rows.begin(), rows.end(), 
        [this, width, height, step,maxIterations](int j) {
            for (int i = 0; i < width; i++) {
                std::complex<long double> c(startx + i * step, starty - j * step);
                std::complex<long double> z(Z_r, Z_i);
                colorGrid[i][j] = 0;
                int color = 0;
                
                // Optimized escape condition check
                for (int n = 0; n <maxIterations; n++) {
                    z= z*z +c;
                    color++;
                    long double z_real = z.real(),z_imag = z.imag();

                    // Fast escape condition check
                    if (z_real * z_real + z_imag * z_imag > 4.0) {
                        colorGrid[i][j] = color;
                        break;
                    }
                }
            }
        });
}
void QTMandelbrot::displayMandelbrot(){
    int width = image.width();
    int height = image.height();
    
    // Use the same calculation as in renderMandelbrot for consistency
    const double Depth = 1.0 + (zoom / 10.0);
    int maxIterations = static_cast<int>(255 * Depth);
    
    for (int x=0; x<width ; x++){
        for(int y=0; y<height ;y++){
            QRgb color = getGradientColor(colorGrid[x][y], maxIterations);
            image.setPixel(x, y, color);
        }
    }
    ui.mandelbrotLabel->setPixmap(QPixmap::fromImage(image));
}

void QTMandelbrot::keyPressEvent(QKeyEvent *event)
{
    long double decreaseAmountx = abs(endx - startx) / 4;
    long double decreaseAmounty = abs(starty - endy) / 4;

    switch (event->key()){
    case Qt::Key_E:
        // Zoom in
        zoom++;
        endx -= decreaseAmountx; startx += decreaseAmountx;
        endy += decreaseAmounty; starty -= decreaseAmounty;
        break;
    case Qt::Key_Q:
        // Zoom out
        zoom--;
        endx += decreaseAmountx; startx -= decreaseAmountx;
        endy -= decreaseAmounty; starty += decreaseAmounty;
        break;
    case Qt::Key_A:
        // Move left
        endx -= decreaseAmountx; startx -= decreaseAmountx;
        break;
    case Qt::Key_D:
        // Move right
        endx += decreaseAmountx; startx += decreaseAmountx;
        break;
    case Qt::Key_W:
        // Move up
        endy += decreaseAmounty; starty += decreaseAmounty;
        break;
    case Qt::Key_S:
        // Move down
        endy -= decreaseAmounty; starty -= decreaseAmounty;
        break;
    default:
        // Call parent class handler for unhandled keys
        QMainWindow::keyPressEvent(event);
        return;
    }

    renderMandelbrot();
    displayMandelbrot();
}

void QTMandelbrot::on_Z_r_sliderMoved(int position)
{
    Z_r = static_cast<long double>(position)/100;
    renderMandelbrot();
    displayMandelbrot();
}


void QTMandelbrot::on_Z_i_sliderMoved(int position)
{
    Z_i = static_cast<long double>(position)/100;
    renderMandelbrot();
    displayMandelbrot();
}

void QTMandelbrot::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        isDragging = true;
        lastMousePos = event->pos();
        setCursor(Qt::ClosedHandCursor);
    }
    QMainWindow::mousePressEvent(event);
}

void QTMandelbrot::mouseMoveEvent(QMouseEvent *event)
{
    if (isDragging && (event->buttons() & Qt::LeftButton)) {
        QPoint delta = event->pos() - lastMousePos;
        
        // Convert pixel movement to complex plane movement
        long double rangex = endx - startx;
        long double rangey = starty - endy;
        long double dx = -static_cast<long double>(delta.x()) * rangex / image.width();
        long double dy = static_cast<long double>(delta.y()) * rangey / image.height();
        
        // Update the view bounds
        startx += dx;
        endx += dx;
        starty += dy;
        endy += dy;
        
        lastMousePos = event->pos();
        
        // Re-render the fractal
        renderMandelbrot();
        displayMandelbrot();
    }
    QMainWindow::mouseMoveEvent(event);
}

void QTMandelbrot::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        isDragging = false;
        setCursor(Qt::ArrowCursor);
    }
    QMainWindow::mouseReleaseEvent(event);
}

void QTMandelbrot::wheelEvent(QWheelEvent *event)
{
    // Get mouse position relative to the image
    QPoint mousePos = event->position().toPoint();
    
    // Convert mouse position to complex plane coordinates
    long double mouseReal = startx + static_cast<long double>(mousePos.x()) * (endx - startx) / image.width();
    long double mouseImag = starty - static_cast<long double>(mousePos.y()) * (starty - endy) / image.height();
    
    // Zoom factor
    long double zoomFactor = (event->angleDelta().y() > 0) ? 0.8 : 1.25; // Zoom in or out
    
    // Update zoom level for depth calculation
    if (event->angleDelta().y() > 0) {
        zoom++;
    } else {
        zoom--;
    }
    //std::println("{}",zoom);
    // Calculate new bounds centered on mouse position
    long double rangex = (endx - startx) * zoomFactor;
    long double rangey = (starty - endy) * zoomFactor;

    startx = mouseReal - rangex * (static_cast<long double>(mousePos.x()) / image.width());
    endx = startx + rangex;
    starty = mouseImag + rangey * (static_cast<long double>(mousePos.y()) / image.height());
    endy = starty - rangey;

    // Re-render the fractal
    auto start = std::chrono::high_resolution_clock::now();
    renderMandelbrot();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::println("time: {}",  duration.count());
    
    displayMandelbrot();
    QMainWindow::wheelEvent(event);
}


void QTMandelbrot::on_resetButton_pressed()
{
    startx= -2;  endx=2;  starty= 2; endy= -2;
    currDepth =1; zoom=0;
    Z_r=0; Z_i=0;
    renderMandelbrot();
    displayMandelbrot();
}

