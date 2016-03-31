#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void applyGamma(QString value);
    QString getXRandRCurrentOutput();
private slots:
    void on_gammaSlider_valueChanged(int value);

    void on_actionAbout_triggered();

    void on_mouseAccelerationCheckBox_toggled(bool checked);

private:
    Ui::MainWindow *ui;
    QString device;
};

#endif // MAINWINDOW_H
