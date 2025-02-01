#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QSerialPort>
QT_BEGIN_NAMESPACE
namespace Ui {
class MCU_PC_COMMUNICATION;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void onConnectButtonClicked();
    void handleReadyRead();
    void onDisconnectButtonCliked();
    void stateLed1RadioButton();
private slots:
    void dataSendButtonCliked();
private:
    Ui::MCU_PC_COMMUNICATION *ui;
    QSerialPort *mserial;
    uint8_t calculateLEDState(QWidget* parent);
};
#endif // MAINWINDOW_H
