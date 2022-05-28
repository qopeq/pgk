#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QPainter>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QImage *img;

    int start_szer;
    int start_wys;
    int koniec_szer;
    int koniec_wys;
    int szer;
    int wys;
    int r, g, b;
    std::vector <QPoint> points;

private slots:
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent*);
    void drawLine(int x1, int y1, int x2, int y2);
    void drawPixel(int x, int y);
    //void mouseReleaseEvent(QMouseEvent *event);
    void drawEllipse(int x1, int y1, int x2, int y2);
    void drawCircle(int x1, int y1, int x2, int y2);

};
#endif // MAINWINDOW_H
