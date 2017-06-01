#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class GPIOClass;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //output
    void initOutput();
    void unInitOutput();

    //led
    void initLED();
    void uninitLED();
    void setLED(bool state);

private slots:
    void on_timer_1();
    void start_clicked();
    void stop_clicked();
    void exit_clicked();

private:
    Ui::MainWindow *ui;

    GPIOClass* gpioOutput1;

    bool output1State;

    QTimer timer_1;

    void delay();

    qint64 counter_success;
    qint64 counter_fail;
};

#endif // MAINWINDOW_H
