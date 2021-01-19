#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QKeyEvent>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
protected:
    void postKeyEvent();

signals:
private slots:


    void APPClose();

    int on_play_Button_clicked();

    void on_close_Button_clicked();
private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
