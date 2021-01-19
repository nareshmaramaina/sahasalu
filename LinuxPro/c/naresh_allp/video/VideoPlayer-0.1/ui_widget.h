/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created: Sat May 5 15:07:38 2018
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QPushButton *play_Button;
    QComboBox *comboBox;
    QPushButton *close_Button;
    QLabel *label;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(320, 240);
        Widget->setBaseSize(QSize(0, 0));
        QFont font;
        font.setFamily(QString::fromUtf8("Symbol"));
        Widget->setFont(font);
        Widget->setFocusPolicy(Qt::WheelFocus);
        Widget->setContextMenuPolicy(Qt::CustomContextMenu);
        Widget->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 170, 127);"));
        play_Button = new QPushButton(Widget);
        play_Button->setObjectName(QString::fromUtf8("play_Button"));
        play_Button->setGeometry(QRect(100, 130, 80, 31));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setItalic(true);
        font1.setWeight(75);
        play_Button->setFont(font1);
        comboBox = new QComboBox(Widget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(60, 60, 181, 31));
        close_Button = new QPushButton(Widget);
        close_Button->setObjectName(QString::fromUtf8("close_Button"));
        close_Button->setGeometry(QRect(0, 210, 321, 25));
        QFont font2;
        font2.setPointSize(10);
        font2.setBold(true);
        font2.setItalic(true);
        font2.setWeight(75);
        close_Button->setFont(font2);
        close_Button->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 0, 0);"));
        label = new QLabel(Widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 0, 321, 41));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Sans Serif"));
        font3.setPointSize(18);
        font3.setBold(false);
        font3.setItalic(true);
        font3.setUnderline(true);
        font3.setWeight(50);
        label->setFont(font3);
        label->setStyleSheet(QString::fromUtf8("font: italic 18pt \"Sans Serif\";\n"
"text-decoration: underline;\n"
"color: rgb(255, 255, 255);"));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", 0, QApplication::UnicodeUTF8));
        play_Button->setText(QApplication::translate("Widget", "Play", 0, QApplication::UnicodeUTF8));
        close_Button->setText(QApplication::translate("Widget", "CLOSE", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Widget", "         Video Player                                                     ", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
