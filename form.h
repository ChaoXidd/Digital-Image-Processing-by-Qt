#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QImage>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);

    void receiveImg(QImage img);



   void wheelEvent(QWheelEvent *ev);


    QImage m_img;

    ~Form();

private:
    Ui::Form *ui;
};

#endif // FORM_H
