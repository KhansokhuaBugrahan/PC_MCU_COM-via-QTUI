#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QResizeEvent>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MCU_PC_COMMUNICATION)
    , mserial(new QSerialPort(this))



{

    ui->setupUi(this);

    setWindowTitle("MCU PC COMMUNICATION");
    ui->connectionstate->setStyleSheet("QLabel { color: rgb(255, 0, 0); }");
    connect(ui->Connect, &QPushButton::clicked, this, &MainWindow::onConnectButtonClicked);
    connect(ui->Disconnect, &QPushButton::clicked, this, &MainWindow::onDisconnectButtonCliked);

    connect(ui->DATA_SEND_BUTTON, &QPushButton::clicked, this, &MainWindow::dataSendButtonCliked);
    connect(mserial, &QSerialPort::readyRead, this, &MainWindow::handleReadyRead);

}


MainWindow::~MainWindow()
{
    delete ui;

}
uint8_t MainWindow:: calculateLEDState(QWidget* parent) {
    uint8_t ledState = 0;  // 8-bit value to represent the state of all LEDs

    for (int i = 0; i < 8; ++i) {
        // Dynamically find the group box and radio buttons
        QGroupBox* groupBox = parent->findChild<QGroupBox*>(QString("LED%1").arg(i + 1));
        if (groupBox) {
            QRadioButton* radioButtonON = groupBox->findChild<QRadioButton*>(QString("ON_Button_%1").arg(i + 1));

            // If the "ON" button is checked, set the corresponding bit to 1
            if (radioButtonON && radioButtonON->isChecked()) {
                ledState |= (1 << i);  // Set the ith bit
            }
        } else {
            qDebug() << "GroupBox for LED" << (i + 1) << "not found!";
        }
    }

    return ledState;
}
void MainWindow::onConnectButtonClicked()
{
    mserial->setPortName("COM3");
    mserial->setBaudRate(QSerialPort::Baud115200);
    mserial->setParity(QSerialPort::NoParity);
    mserial->setDataBits(QSerialPort::Data8);
    mserial->setStopBits(QSerialPort::OneStop);
    if(mserial->open(QIODeviceBase::ReadWrite))
    {
        ui->connectionstate->setText("  CONNECTED");
        ui->connectionstate->setStyleSheet("QLabel { color: rgb(0, 255, 0); }");
    }

}
void MainWindow::handleReadyRead() {
    QByteArray receivedData = mserial->readAll();
    qDebug() << "Received data:" << receivedData;
    ui->Display_Received_Data->display(receivedData);
    //ui->lcdNumber->display(123);
}

void MainWindow::onDisconnectButtonCliked()
{

    if(mserial->isOpen())
    {
        mserial->close();
        ui->connectionstate->setText("DISCONNECTED");
        ui->connectionstate->setStyleSheet("QLabel { color: rgb(255, 0, 0); }");
    }
}
void MainWindow::stateLed1RadioButton()
{
     qDebug()<<"radio";
}
void MainWindow::dataSendButtonCliked()
{
     uint8_t ledState = calculateLEDState(this);
   // QPushButton *sendButton = qobject_cast<QPushButton*>(sender());
    qDebug() << "LED State (Decimal):" << ledState;
     QByteArray data;
     data.append(static_cast<char>(ledState));  // Convert uint8_t to char
     mserial->write(data);

}

