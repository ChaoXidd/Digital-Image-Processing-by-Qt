#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QBarSet>
#include<QBarSeries>
#include<QBarCategoryAxis>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initData();

    void(Form::*b)(QImage)=&Form::receiveImg;
    void(MainWindow::*a)(QImage)=&MainWindow::sendImg;
    connect(this,a,m_form,b);





}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::initData()
{
    string n;
    ifstream ifs;
    ifs.open("F:\\Qtcode\\QtGIS\\1.txt",ios::in);
    if (!ifs) //判断打开文件是否成功
    {

        qDebug() << "文件打开失败";//若打开文件失败直接输出打开文件失败

    }
    data.resize(5000);
    for(int j=0;j<data.size();j++)
    {
        data[j].resize(4000);
    }

    for(int i = 0; i < data.size(); i++)
    {
        for (int  j= 0; j < data[0].size();j++)
        {
            ifs>>n;
            data[i][j] = atoi(n.c_str());
        }
    }

    ifs.close();

}

void MainWindow::drawImage()
{

    // 创建颜色映射
    QMap<int, QColor> colorMap;
    colorMap[1] = m_color1; //      林地
    colorMap[2] = m_color2; //      亮屋顶
    colorMap[3] = m_color3; //     道路
    colorMap[4] = m_color4; //     草地
    colorMap[5] = m_color5; //     暗屋顶
    colorMap[6] = m_color6; //    裸地
    colorMap[7] = m_color7; //    水体

     //创建QImage对象
        QImage img(data[0].size(), data.size(), QImage::Format_ARGB32);

         //遍历二维数组，并设置像素点的颜色
        for (int i = 0; i < data.size(); i++) {
            for (int j = 0; j < data[i].size(); j++) {
                QColor color = colorMap[data[i][j]];
                img.setPixelColor(j, i, color);
               // qDebug()<<data[i][j];
            }
        }


        double w_scale=0.1;
        double h_scale=0.1;

        w_scale=ui->w_lineEdit->text().toDouble();
        h_scale=ui->h_lineEdit->text().toDouble();


        m_img=img.scaled(data[0].size()*w_scale,data.size()*h_scale);
        //img.save("F:\\img\\img.png");



//    QWidget *widget=new QWidget;
//    QLabel * label=new QLabel;
//    label->setPixmap(QPixmap::fromImage(img));
//    QScrollArea *sa=new QScrollArea(widget);
//        sa->setWidget(label);
//        sa->resize(800,800);
//        widget->show();







}

void MainWindow::createChartFunc()
{
    for(int i = 0; i < data.size(); i++)
    {
        for (int  j= 0; j < data[0].size();j++)
        {
            switch (data[i][j])
            {
            case 1:
                num1++;
                break;
            case 2:
                num2++;
                break;
            case 3:
                num3++;
                break;
            case 4:
                num4++;
                break;
            case 5:
                num5++;
                break;
            case 6:
                num6++;
                break;
            default:
                num7++;
                break;
            }

        }
    }
    //qDebug()<<num1<<" "<<num2<<" "<<num3;
    QBarSet *set=new QBarSet("数量");
    *set<<num1<<num2<<num3<<num4<<num5<<num6<<num7;
    QBarSeries *series=new QBarSeries();
    series->append(set);
    //设置标签显示位置
    series->setLabelsPosition(QAbstractBarSeries::LabelsPosition::LabelsCenter);
    // 显示标签
    series->setLabelsVisible(true);

    chartView=new QChartView;
    chart=new QChart();
    chart->addSeries(series);
    chart->setTitle("条形统计图");
    chartView->setChart(chart);

    QStringList categories;
    categories<< "林地" <<" 亮屋顶" << "道路" <<"草地"<<"暗屋顶"<<"祼地"<<"水体";
    QBarCategoryAxis *axis=new QBarCategoryAxis();
    axis->append(categories);
    axis->setTitleText("地物类型");

    chart->setAxisX(axis,series);
    //chart->createDefaultAxes();
    QValueAxis *axisY=new QValueAxis;

    axisY->setTitleText("数量");//标题
    chart->setAxisY(axisY,series);
    chart->setBackgroundBrush(QColor(0, 0, 100));//设置背景颜色


    chartView->resize(500,500);
    chartView->show();




}

void MainWindow::Search()
{
    int r =ui->row->text().toInt();
    int c=ui->column->text().toInt();
    QString str;
    int n=data[r][c];
    switch (n)
    {
    case 1:
        str="林地";
        break;
    case 2:
        str="亮屋顶";
        break;
    case 3:
        str="道路";
        break;
    case 4:
        str="草地";
        break;
    case 5:
        str="暗屋顶";
        break;
    case 6:
        str="裸地";
        break;
    default:
        str="水体";
        break;
    }

    ui->result1->setText(QString::number(n));
    ui->result2->setText(str);


}

void MainWindow::paintEvent(QPaintEvent*event)
{
    QPainter p(this);

    QPen pen1;
    pen1.setColor(m_color1);
    p.setPen(pen1);
    QBrush brush1;
    brush1.setColor(m_color1);
    brush1.setStyle(Qt::SolidPattern);
    p.setBrush(brush1);
    p.drawRect(ui->clr_btn1->pos().x()+30,ui->clr_btn1->pos().y()+30,20,20);

    QPen pen2;
    pen2.setColor(m_color2);
    p.setPen(pen2);
    QBrush brush2;
    brush2.setColor(m_color2);
    brush2.setStyle(Qt::SolidPattern);
    p.setBrush(brush2);
    p.drawRect(ui->clr_btn2->pos().x()+30,ui->clr_btn2->pos().y()+30,20,20);

    QPen pen3;
    pen3.setColor(m_color3);
    p.setPen(pen3);
    QBrush brush3;
    brush3.setColor(m_color3);
    brush3.setStyle(Qt::SolidPattern);
    p.setBrush(brush3);
    p.drawRect(ui->clr_btn3->pos().x()+30,ui->clr_btn3->pos().y()+30,20,20);

    QPen pen4;
    pen4.setColor(m_color4);
    p.setPen(pen4);
    QBrush brush4;
    brush4.setColor(m_color4);
    brush4.setStyle(Qt::SolidPattern);
    p.setBrush(brush4);
    p.drawRect(ui->clr_btn4->pos().x()+30,ui->clr_btn4->pos().y()+30,20,20);

    QPen pen5;
    pen5.setColor(m_color5);
    p.setPen(pen5);
    QBrush brush5;
    brush5.setColor(m_color5);
    brush5.setStyle(Qt::SolidPattern);
    p.setBrush(brush5);
    p.drawRect(ui->clr_btn5->pos().x()+30,ui->clr_btn5->pos().y()+30,20,20);

    QPen pen6;
    pen6.setColor(m_color6);
    p.setPen(pen6);
    QBrush brush6;
    brush6.setColor(m_color6);
    brush6.setStyle(Qt::SolidPattern);
    p.setBrush(brush6);
    p.drawRect(ui->clr_btn6->pos().x()+30,ui->clr_btn6->pos().y()+30,20,20);

    QPen pen7;
    pen7.setColor(m_color7);
    p.setPen(pen7);
    QBrush brush7;
    brush7.setColor(m_color7);
    brush7.setStyle(Qt::SolidPattern);
    p.setBrush(brush7);
    p.drawRect(ui->clr_btn7->pos().x()+30,ui->clr_btn7->pos().y()+30,20,20);

}













void MainWindow::on_clr_btn1_clicked()
{
    m_color1=QColorDialog::getColor(Qt::black);
    this->update();
    //qDebug()<<m_color1;
}


void MainWindow::on_clr_btn2_clicked()
{
    m_color2=QColorDialog::getColor(Qt::black);
    this->update();
}


void MainWindow::on_clr_btn3_clicked()
{
    m_color3=QColorDialog::getColor(Qt::black);
    this->update();
}


void MainWindow::on_clr_btn4_clicked()
{
    m_color4=QColorDialog::getColor(Qt::black);
    this->update();
}


void MainWindow::on_clr_btn5_clicked()
{
    m_color5=QColorDialog::getColor(Qt::black);
    this->update();
}


void MainWindow::on_clr_btn6_clicked()
{
    m_color6=QColorDialog::getColor(Qt::black);
    this->update();
}


void MainWindow::on_clr_btn7_clicked()
{
    m_color7=QColorDialog::getColor(Qt::black);
    this->update();
    //qDebug()<<m_color7;
}


void MainWindow::on_ok_btn_clicked()
{
    this->drawImage();
    emit this->sendImg(m_img);
    m_form->show();
}


void MainWindow::on_pushButton_clicked()
{
    createChartFunc();
}


void MainWindow::on_searchBtn_clicked()
{
    Search();
}

