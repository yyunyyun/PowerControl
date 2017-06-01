#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "GPIO/GPIOClass.h"

#include <QThread>
#include <QProcess>
#include <QMessageBox>
#include <QDebug>
#include <QTime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), counter_success(0), counter_fail(0),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //output
    initOutput();
    initLED();
    ui->info->setText(tr("init finished"));

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(start_clicked()));
    connect(ui->pushButton_2, SIGNAL(clicked()),this, SLOT(stop_clicked()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(exit_clicked()));

    //timer
    connect(&timer_1, SIGNAL(timeout()), this, SLOT(on_timer_1()));

    ui->Counter_Success->setText(QString::number(counter_success));
    ui->Counter_fail->setText(QString::number(counter_fail));
}

MainWindow::~MainWindow()
{
    unInitOutput();
    uninitLED();

    delete ui;
}

void MainWindow::initOutput()
{
    gpioOutput1 = new GPIOClass("20");

    gpioOutput1->export_gpio();

    gpioOutput1->setdir_gpio("out");

    output1State = false;

    gpioOutput1->setval_gpio("1");

}

void MainWindow::unInitOutput()
{
    gpioOutput1->unexport_gpio();

    if (!gpioOutput1) delete gpioOutput1;
}


void MainWindow::initLED()
{
    ui->status_led->setPixmap(QPixmap(":/images/ball_gray.png"));
}

void MainWindow::uninitLED()
{
    ui->status_led->setPixmap(QPixmap(":/images/ball_gray.png"));
}

void MainWindow::setLED(bool state)
{
    QString img;

    if (state){
        img = ":/images/ball_green.png";
    }
    else
    {
        img = ":images/ball_red.png";
    }

    ui->status_led->setPixmap(QPixmap(img));
}


void MainWindow::start_clicked()
{
    QString text = ui->textEdit->toPlainText();

    if (text == "")
    {
        QMessageBox msgBox;
        msgBox.setText(tr("Please enter IP"));
        msgBox.exec();
        return;
    }

    timer_1.setInterval(200);
    timer_1.start();
}

void MainWindow::on_timer_1()
{
    ui->info->setText(tr("Turn on output"));

    gpioOutput1->setval_gpio("1");

    qApp->processEvents();

    QString text = ui->textEdit->toPlainText();

    delay();

    QProcess p;

    QString cmd;

    QString result;

    cmd = QString("ping -c 1 %1")
            .arg(text);

    qDebug()<<cmd;

    qApp->processEvents();

    for (int i=0; i<3; i++){
        p.start(cmd);
        p.waitForFinished(-1);

        result = QString(p.readAll());

        qDebug()<<result;

        if (result.contains("0%"))
        {
            break;
        }
    }

//    p.start(cmd);
//    p.waitForFinished(-1);

//    QString result(p.readAll());

//    qDebug()<<result;

    if (result.contains("100%"))
    {
        ui->info->setText(p.readAllStandardError());
        setLED(false);
        counter_fail += 1;
        ui->Counter_fail->setText(QString::number(counter_fail));
        //timer_1.stop();

        gpioOutput1->setval_gpio("0");

        qApp->processEvents();

        ui->info->setText(tr("Turn off"));

        timer_1.setInterval(28000);
        timer_1.start();

        return;
    }

    setLED(true);
    counter_success += 1;
    ui->Counter_Success->setText(QString::number(counter_success));

    gpioOutput1->setval_gpio("0");

    qApp->processEvents();

    ui->info->setText(tr("Turn off"));

    timer_1.setInterval(28000);
    timer_1.start();

}

void MainWindow::stop_clicked()
{
    timer_1.stop();
    uninitLED();
    ui->info->setText(tr("Stop"));
}

void MainWindow::exit_clicked()
{
    close();
}


void MainWindow::delay()
{
    QTime dieTime= QTime::currentTime().addSecs(24);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}


















