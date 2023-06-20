#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QImage>
#include <QColor>
#include <QFile>
#include <QTextStream>
#include <QColorDialog>
#include<fstream>
#include <QScrollArea>
#include<QtCharts>
#include<QDebug>
#include<form.h>


using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initData();
    void drawImage();
    void createChartFunc();
    void Search();
    void paintEvent(QPaintEvent*event);



    QVector<QVector<int>> data;
    QColor m_color1=QColor(0,0,0);
    QColor m_color2=QColor(0,0,0);
    QColor m_color3=QColor(0,0,0);
    QColor m_color4=QColor(0,0,0);
    QColor m_color5=QColor(0,0,0);
    QColor m_color6=QColor(0,0,0);
    QColor m_color7=QColor(0,0,0);


    int num1=0;
    int num2=0;
    int num3=0;
    int num4=0;
    int num5=0;
    int num6=0;
    int num7=0;






    Form *m_form=new Form;
    QImage m_img;



private slots:
    void on_clr_btn1_clicked();

    void on_clr_btn2_clicked();

    void on_clr_btn3_clicked();

    void on_clr_btn4_clicked();

    void on_clr_btn5_clicked();

    void on_clr_btn6_clicked();

    void on_clr_btn7_clicked();

    void on_ok_btn_clicked();

    void on_pushButton_clicked();

    void on_searchBtn_clicked();


signals:
    void sendImg(QImage img);

private:
    Ui::MainWindow *ui;
    QChartView * chartView;
    QChart*chart;
};
#endif // MAINWINDOW_H
