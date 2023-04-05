#include "widget.h"
#include "ui_widget.h"
#include "scene.h"

widget::widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widget)
{
    ui->setupUi(this);
    Scene=new scene();
    ui->graphicsView->setScene(Scene);
}

widget::~widget()
{
    delete ui;
}
