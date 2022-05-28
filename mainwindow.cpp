#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent>
#include <QPainter>
#include <string>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    szer = ui->myFrame->width();
    wys = ui->myFrame->height();

    img = new QImage(szer,wys,QImage::Format_RGB32);
    r=255;
    g=200;
    b=100;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        points.push_back(QPoint(event->x(), event->y()));

        int p_size = points.size();

        if(ui->liniaButton->isChecked() && p_size % 2 == 0){
            drawLine(points[p_size-2].x(), points[p_size-2].y(), points[p_size-1].x(), points[p_size-1].y());
        }else if(ui->okregButton->isChecked() && p_size % 2 == 0){
            drawCircle(points[p_size-2].x(), points[p_size-2].y(), points[p_size-1].x(), points[p_size-1].y());
        }else if(ui->elipsaButton->isChecked() && p_size % 2 == 0){
            drawCircle(points[p_size-2].x(), points[p_size-2].y(), points[p_size-1].x(), points[p_size-1].y());
        }else if(ui->bezierButton->isChecked() && p_size % 2 == 0){
            drawCircle(points[p_size-2].x(), points[p_size-2].y(), points[p_size-1].x(), points[p_size-1].y());
        }else{
            drawPixel(event->x(), event->y());
        }


    }
}


void MainWindow::paintEvent(QPaintEvent*)
{
    // Obiekt klasy QPainter pozwala nam rysowac na komponentach
    QPainter p(this);

    // Rysuje obrazek "img" w punkcie (poczX,poczY)
    // (tu bedzie lewy gorny naroznik)
    p.drawImage(0,0,*img);
}

void MainWindow::drawPixel(int x, int y)
{
    if(x < img->width() and y < img->height() and x >= 0 and y >= 0){
        uchar *pix_line = img->scanLine(y);
        int adr2 = 4*x;
        pix_line[adr2] = b;
        pix_line[adr2+1] = g;
        pix_line[adr2+2] = r;
        pix_line[adr2+3] = 255;
    }
}

void MainWindow::drawLine(int x1, int y1, int x2, int y2)
{
    //swap
    if(x2 < x1){
        int temp = x1;
        x1 = x2;
        x2 = temp;

        temp = y1;
        y1 = y2;
        y2 = temp;
    }
    //rysuj linie lub kropke
    if(x1 == x2){
        //jesli x1 = x2 i y1=y2 narysuj kropke w jednym miejscu
        if(y1 == y2){
            drawPixel(x1, x2);
        }else{
        //jesli x1=x2 a y1!=y2 wtedy rysuj linie prostą od y1 do y2
        if(y1>y2) std::swap(y1,y2);
            for(int y = y1; y < y2; y++){
                drawPixel(x1, y);
            }
        }
    }else{
        //wzor na tworzenie linii z slajdow
        float m = (float)(y2-y1)/(x2-x1);
        float y = y1;

        if(std::abs(m) >= 1){

            if(x2 > x1 && m < 0){//swap
                int temp = x1;
                x1 = x2;
                x2 = temp;

                temp = y1;
                y1 = y2;
                y2 = temp;
            }

            m = (float)(x2-x1)/(y2-y1);
            float x = x1;

            for (int y = y1; y<=y2; y++){
                drawPixel((int)floor(x+0.5), y);
                x = x + m;
            }

        }else{

            if(x2 < x1){
                int temp = x1;
                x1 = x2;
                x2 = temp;

                temp = y1;
                y1 = y2;
                y2 = temp;
            }

            for (int x = x1; x<=x2; x++){
                drawPixel(x, (int)floor(y+0.5));
                y = y + m;
            }
        }

    }

    update();
}


void MainWindow::drawCircle(int x1, int y1, int x2, int y2){

    double r1 = sqrt((x2 - x1)*(x2 - x1) - (y2 - y1)*(y2 - y1));
    int x, y;
    double d;
    x = 0;
    y = r1;
    d = 1 - r1;
    drawPixel(x + x1, y + y1);
    drawPixel(y + x1, x +y1);
    drawPixel(-x + x1, -y +y1);
    drawPixel(-x + x1, y +y1);
    drawPixel(y +x1, -x +y1);
    drawPixel(-y +x1, -x +y1);
    drawPixel(x + x1, -y +y1);
    drawPixel(-y +x1, x +y1);
    while(y > x){
        if(d < 0){
            d = d + 2 * x + 3;
            x++;
        }else{
            d = d+2 *(x - y) + 5;
            x++;
            y--;
        }
        drawPixel(x + x1, y + y1);
        drawPixel(y + x1, x +y1);
        drawPixel(-x + x1, -y +y1);
        drawPixel(-x + x1, y +y1);
        drawPixel(y +x1, -x +y1);
        drawPixel(-y +x1, -x +y1);
        drawPixel(x + x1, -y +y1);
        drawPixel(-y +x1, x +y1);
    }
    update();
}

void MainWindow::drawEllipse(int x1, int y1, int x2, int y2){
    int ilosc_wierzcholkow = ui->wierzBox->value();



}
