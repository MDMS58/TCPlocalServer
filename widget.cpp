#include "widget.h"
#include "ui_widget.h"
#include "localserver.h"
#include <QMessageBox>
#include <QThread>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    server=new LocalServer();
    server->listen(QHostAddress::Any, 1400);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_read_clicked()
{
    QByteArray data = server->socket->readAll();
    qDebug()<<data;

}


void Widget::on_start_clicked()
{

}

