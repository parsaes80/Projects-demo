#include "QTMandelbrot.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QTMandelbrot window;
    window.show();
    return app.exec();
}
