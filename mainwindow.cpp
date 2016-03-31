#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QProcess>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    on_gammaSlider_valueChanged(10);

    //setting current output device
    this->device = getXRandRCurrentOutput();
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::getXRandRCurrentOutput()
{
    //spawning process
    QProcess xrandr;
    xrandr.start("bash", QStringList() << "-c" << "xrandr | grep primary");

    //synchronous execution and output collection
    if (!xrandr.waitForStarted()){}
    if (!xrandr.waitForFinished()){}
    QString result = QString(xrandr.readAll());

    //getting first string before whitespace
    QString device = result.split(" ").at(0);

    return device;
}

void MainWindow::applyGamma(QString value)
{
    //spawning process
    QProcess xrandr;
    xrandr.start("bash", QStringList() << "-c" << "xrandr --output "+this->device+" --gamma "+value+":"+value+":"+value);

    //synchronous execution and output collection
    if (!xrandr.waitForStarted()){}
    if (!xrandr.waitForFinished()){}
}


void MainWindow::on_gammaSlider_valueChanged(int value)
{
    QString output = QString::number((double) value / 10);

    //adding .0 decimal part if not present
    if(!output.contains(".")){
        output += ".0";
    }

    ui->statusLabel->setText("Gamma value: "+output);
    applyGamma(output);
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this,"About","<h1>Gamma Corrector</h1><br>Claudio Desideri (c) 2016<br><a href=\"mailto:happy.snizzo@gmail.com\">happy.snizzo@gmail.com</a>");
}

void MainWindow::on_mouseAccelerationCheckBox_toggled(bool checked)
{
    if(checked){
        //spawning process
        QProcess xrandr;
        xrandr.start("bash", QStringList() << "-c" << "xset m 00");

        //synchronous execution and output collection
        if (!xrandr.waitForStarted()){}
        if (!xrandr.waitForFinished()){}
    } else {
        //spawning process
        QProcess xrandr;
        xrandr.start("bash", QStringList() << "-c" << "xset m default");

        //synchronous execution and output collection
        if (!xrandr.waitForStarted()){}
        if (!xrandr.waitForFinished()){}
    }
}
