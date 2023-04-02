#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE
class LocalServer;
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    LocalServer *server;

private slots:
    void on_start_clicked();

    void on_read_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
