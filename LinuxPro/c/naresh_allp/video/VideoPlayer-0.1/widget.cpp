#include "widget.h"
#include "ui_widget.h"
#include <QStringList>
#include <QDir>
#include <QDebug>
#include <QProcess>
#include <QIcon>
#include <QMessageBox>

char* play_char;
char  str[300],str1[300];
pid_t pid;
QString com_Text1;

Widget::Widget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::Widget)
{
	ui->setupUi(this);
	setGeometry(0,0,320,240);
	setWindowFlags(Qt::FramelessWindowHint);

	//    system("insmod /vision/audio_ctrl.ko");
	sleep (2);

	system("/root/lcd_always_on &");
	ui->comboBox->addItem("---Select--");

	   QDir directory("/mnt/jffs2/");
	   QStringList files = directory.entryList(QStringList() << "*.mp4",QDir::Files);

	   if(files.isEmpty())
	   {
		   QMessageBox msg;
		   msg.setText("No Videos");
		   msg.exec();
	   }

	   else
	   {
		   while(!files.isEmpty())
			   ui->comboBox->addItem(files.takeFirst());
	   }



}



Widget::~Widget()
{

	delete ui;

}

void Widget::postKeyEvent()
{


	//        if(e->type()==QEvent::KeyRelease){
	//            QKeyEvent *ke = static_cast<QKeyEvent *>(e);
	//            int keyVal = ke->key();
	//            qDebug()<<"THe Key Value is---------->"<<ke->key();


	//QKeyEvent(QEvent::KeyPress,Qt::Key_P,Qt::NoModifier);
}


void Widget::APPClose()
{

	qDebug()<<"Inisde Player Close";
	sleep(1);
	system("killall mplayer");

	system("matchbox-desktop --icon-size 60 --icon-padding 36 &");
	system("killall  lcd_always_on");
	close();

}

int Widget::on_play_Button_clicked()
{


	ui->play_Button->hide();
	ui->comboBox->hide();

	com_Text1=ui->comboBox->currentText();
	play_char = strdup(qPrintable(com_Text1));
	memset(str,0,300);

	int n=0;
	pid = fork();
	switch(pid)
	{
		case -1:
			qDebug()<<"fork creation failed";
			break;

		case 0:
			{

				system("amixer cset numid=4 192");
				sleep(1);
				int ret=system("kill -9 $(pidof matchbox-desktop)");
				qDebug()<<"str1 value is"<<ret;
				sleep(1);

				sprintf(str,"mplayer -ao alsa:device=hw=0.0 /mnt/jffs2/'%s' -fs ",play_char);
				qDebug()<<"------->>>>>"<<str;
				system(str);
				system("killall mplayer");
				system("matchbox-desktop --icon-size 60 --icon-padding 36 &");
				system("killall  lcd_always_on");
				goto select;
				n = 1;
				break;

			}
		default :
			{
				connect(ui->close_Button,SIGNAL(clicked(bool)),this,SLOT(APPClose()));
				n=1;
				break;

			}
			n--;
			if(n==0)
			{
				return 0;
			}

	}
}


void Widget::on_close_Button_clicked()
{
	close();
}
#if 0
void Widget::on_pause_Button_clicked()
{
	qDebug()<<"inside pause ";
	//    QPalette Palet = ui->pause_Button->palette();
	//    QPixmap pix(":/play.jpg");
	//    QPixmap pix_scaled(pix.scaled(80,31,  Qt::IgnoreAspectRatio, Qt::SmoothTransformation ));

	//    Palet.setBrush(QPalette::Window, QBrush(pix_scaled));
	//    ui->pause_Button->setPalette(Palet);
	//    ui->pause_Button->setAutoFillBackground(true);
	// ui->pause_Button->setIcon(QIcon(":/play.jpg"));
	//    mplayer input.mp4

	//    QString com_Text1=ui->comboBox->currentText();
	//    mychar = strdup(qPrintable(com_Text1));
	//    memset(str,0,300);
	//    //  system("amixer cset numid=4 192");
	//    sleep(2);

	QKeyEvent key1(QKeyEvent::KeyPress, Qt::Key_P, Qt::NoModifier, "Tab", false, 0 );
	qDebug()<<"-----key avlue---"<<&key1;
	QApplication::sendEvent(this, &key1);

	qDebug()<<"my char value is %s"<<com_Text1;
	char* pause_text;
	pause_text=strdup(qPrintable(com_Text1));
	memset(str1,0,300);

	// sprintf(str1,"mplayer -ao alsa:device=hw=0.0 -vo -pause /mnt/jffs2/'%s'",pause_text);
	sprintf(str1,"mplayer /mnt/jffs2/'%s'",pause_text);
	system(str1);

	QKeyEvent key(QKeyEvent::KeyPress, Qt::Key_Space, Qt::NoModifier, "Space", false, 0 );
	QApplication::sendEvent(this, &key);
	//  postKeyEvent();
	//QKeySequence(tr("p"));
	//keyPressEvent(QKeyEvent *event);
	//    unsigned char buff[4];
	//    buff[0]=0x1a;


	//    sprintf(str,"mplayer -ao alsa:device=hw=0.0 -p /mnt/jffs2/'%s' -seek 10",mychar);
	//    qDebug()<<"------->>>>>"<<str;
	//    system(str);
	//}

#endif
