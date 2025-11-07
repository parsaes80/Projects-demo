#pragma once

#include <QtWidgets/QMainWindow>
#include <QResizeEvent>
#include <QMouseEvent>
#include <QWheelEvent>
#include "ui_QTMandelbrot.h"
#include <vector>

using Matrix = std::vector<std::vector<int>>;
class QTMandelbrot : public QMainWindow
{
    Q_OBJECT

public:
    QTMandelbrot(QWidget *parent = nullptr);
    ~QTMandelbrot();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private slots:
    void on_Z_r_sliderMoved(int position);

    void on_Z_i_sliderMoved(int position);

    void on_resetButton_pressed();

private:
    Ui::QTMandelbrotClass ui;
    QImage image;

    long double startx= -2,  endx=2,  starty= 2, endy= -2;
    Matrix colorGrid;
    int currDepth =1, zoom=0;
    long double Z_r=0, Z_i=0;
    
    // Mouse interaction variables
    bool isDragging = false;
    QPoint lastMousePos;

    void updateImageAndGrid();
    void renderMandelbrot();
    void displayMandelbrot();
};

