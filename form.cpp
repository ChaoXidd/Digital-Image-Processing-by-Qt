#include "form.h"
#include "ui_form.h"
#include<QLabel>
#include <QGraphicsView>
#include<QWheelEvent>

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);






}

 void Form::receiveImg(QImage img)
 {
     m_img=img;

//     QLabel * label=new QLabel;
//     label->setPixmap(QPixmap::fromImage(m_img));
//     ui->sa->setWidget(label);
//     ui->sa->resize(800,800);








     QGraphicsScene *scene = new QGraphicsScene;
     scene->addPixmap(QPixmap::fromImage(m_img));

     ui->graphicsView->setScene(scene);









 }

 void Form::wheelEvent(QWheelEvent *ev)
 {
         int wheelValue =ev->angleDelta().y();
         double ratio = (double)wheelValue / (double)1200 + 1;
         ui->graphicsView->scale(ratio, ratio);

 }

Form::~Form()
{
    delete ui;
}
