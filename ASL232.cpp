#include "ASL232.h"
#include "Function422.h"
#include <QStringList>
#include <QDebug>
#include <QTime>

ASL232::ASL232(QString strDevice, ViSession viResourceRM, QWidget *parent)
    : QtResource(strDevice, viResourceRM, parent)
{
    ui.setupUi(this);
    initRS232();
    initCompoent();
}

int ASL232::initRS232()
{
    int status = NT_H1040_Rs232Init(m_session);
    qDebug() << __FUNCTION__ << status;
    return status;
}

int ASL232::uninitRS232()
{
    int status = NT_H1040_Rs232UnInit(m_session);
    qDebug() << __FUNCTION__ << status;
    return status;
}

int ASL232::configRS232Format(short channel, unsigned long baudrate, int wordlength, int parity, int stopBit)
{
    int status = NT_H1040_RS232_DataFormatConfig(m_session, channel ,  baudrate, wordlength, parity, stopBit);
    qDebug() << __FUNCTION__ << status;
    return status;
}

int ASL232::sendRS232Data(short channel, short length, unsigned char *pValue, unsigned int *pActualLength)
{
    int status = NT_H1040_RS232_SendString(m_session, channel,  length ,   pValue,  pActualLength);
    qDebug() << __FUNCTION__ << "status" << status << "ActualLength" << *pActualLength;
    return status;
}

int ASL232::recvRS232Data(short channel, short length, unsigned char *pValue,  int *pActalLength, float *timeLab)
{
    int status = NT_H1040_RS232_GetString(m_session, channel, length, pValue, pActalLength, timeLab) ;
    if(*pActalLength > 0)
        qDebug() << __FUNCTION__ << status << *pActalLength;
    return status;

}

ASL232::~ASL232()
{
    uninitRS232();
}

void ASL232::initCompoent()
{
    m_recvTiemr.start(0);
    QStringList arrChannel;
    for(int index = 0; index < 18; index ++)
    {
        arrChannel << QString("%1").arg(index);
    }

    //    arrChannel << "0" << "1" << "2" << "3";
    ui.comboBoxChannelSend->addItems(arrChannel);
    ui.comboBoxChannelRecv->addItems(arrChannel);

    QStringList strBaudrate;
    strBaudrate << "300" << "600" << "1200" << "2400"\
                << "4800" << "9600" << "19200" << "38400"\
                << "43000" << "56000" << "57600" << "115200";
    ui.comboBoxBaudrate->addItems(strBaudrate);

    QStringList strDataBit;
    strDataBit << "0" << "1";
    ui.comboBoxDataBit->addItems(strDataBit);


    QStringList strParityBit;
    strParityBit << "0" << "1" << "2";
    ui.comboBoxParityBit->addItems(strParityBit);

    QStringList strStopBit;
    strStopBit << "0" << "1";
    ui.comboBoxStopBit->addItems(strStopBit);
    ////串口配置
    connect(ui.pushButtonConfig, &QPushButton::clicked, [&]()
    {
        int channelSend =  ui.comboBoxChannelSend->currentText().trimmed().toInt();
        int channelRecv = ui.comboBoxChannelRecv->currentText().trimmed().toInt();
        unsigned long baudrate = ui.comboBoxBaudrate->currentText().trimmed().toULong();
        int wordlength = ui.comboBoxDataBit->currentText().trimmed().toInt();
        int parity = ui.comboBoxParityBit->currentText().trimmed().toInt();
        int stopBit = ui.comboBoxStopBit->currentText().trimmed().toInt();
        configRS232Format(channelSend,
                          baudrate,
                          wordlength,
                          parity,
                          stopBit);
        configRS232Format(channelRecv,
                          baudrate,
                          wordlength,
                          parity,
                          stopBit);
    });
    ////串口发数
    connect(ui.pushButtonSend, &QPushButton::clicked, this, &ASL232::sendData);
    ////定时循环接收数据
    connect(&m_recvTiemr, &QTimer::timeout, [&]()
    {

        int channel =  ui.comboBoxChannelRecv->currentText().trimmed().toInt();
        unsigned int tempAct = 0;

        unsigned char arrTemp[1000];
        memset(arrTemp, 0, 1000);

        int iActLength = 0;
        float ftimeLab = 0.0;
        recvRS232Data(channel, 1000, arrTemp, &iActLength, &ftimeLab);

        if(iActLength > 0)
        {
            qDebug() << __FUNCTION__ <<"Recv Time:" << QTime::currentTime() << "end";
            qDebug() << __FUNCTION__ << QStringLiteral("#实际接收数据量#:") << iActLength;

            QString temp;

            temp += QString::fromLatin1((char*)arrTemp, iActLength);
            for(int index = 0; index < iActLength; index++);
            //QString::number(((int)arrTemp[index]), 16);

            ui.textEditRecv->setPlainText(temp);
            int currSize = ui.labelRecvLength->text().toInt();
            ui.labelRecvLength->setText(QString("%1").arg(iActLength + currSize));
        }
    });
    ////定时循环发数
    connect(ui.checkBoxTimerSet, &QCheckBox::stateChanged, [&](int state)
    {
        int interval = 0;
        switch(state)
        {
            case Qt::Unchecked:
                m_sendTimer.stop();
                break;
            case Qt::Checked:
                interval = ui.lineEditTimerSet->text().trimmed().toInt();
                m_sendTimer.start(interval);
                break;
            default:
                break;
        }

    });
    connect(&m_sendTimer, &QTimer::timeout, [&]()
    {

        this->sendData();
    });
    connect(ui.pushButtonClear, &QPushButton::clicked, [&]()
    {
        ui.labelRecvLength->setText("0");
        ui.labelSendLength->setText("0");
        ui.textEditRecv->setText("");
        ui.textEditSend->setText("");
    });
}

void ASL232::sendData()
{
    switch(ui.checkBoxFixData->checkState())
    {
        case Qt::Checked:
            sendFixData();
            break;
        case Qt::Unchecked:
            sendCustData();
            break;
        default:
            break;
    }
}

void ASL232::sendFixData()
{
    QString strSend = ui.textEditSend->toPlainText();
    std::string strTemp = strSend.toStdString();
    int channel =  ui.comboBoxChannelSend->currentText().trimmed().toInt();
    unsigned int tempAct = 0;
    int sizeLength = strTemp.size();
    if(sizeLength > 500)
    {
        qDebug() << __FUNCTION__ << "size is out of array.";
        return;
    }
    //       char arr[500];
    //       strTemp.c_str();
    //       memcpy(arr, strTemp.c_str(),strTemp.size());

#define ARRAY_SIZE 5
    volatile int arr[ARRAY_SIZE] = {0};
    for(int index = 0; index < ARRAY_SIZE; index++)
        arr[index] = 9;

    qDebug() << __FUNCTION__ <<"Send FixData Time:" << QTime::currentTime() << "start";
    sendRS232Data(channel, ARRAY_SIZE, (unsigned char*)arr, &tempAct);
    qDebug() << __FUNCTION__ <<"Send FixData Time:" << QTime::currentTime() << "end";
    int temp = ui.labelSendLength->text().toInt();
    ui.labelSendLength->setText(QString("%1").arg(tempAct + temp));
    qDebug() << __FUNCTION__ << QStringLiteral("实际发送数据量:") << tempAct;

}

void ASL232::sendCustData()
{
    QString strSend = ui.textEditSend->toPlainText();
    QByteArray arrSend = strSend.toLatin1();

    QByteArray arrData = arrSend;//= translateToHex(arrSend);

    int channel =  ui.comboBoxChannelSend->currentText().trimmed().toInt();
    unsigned int tempAct = 0;
    int sizeLength = arrData.size();
    qDebug() << __FUNCTION__ << QString("size :%1").arg(sizeLength);

    unsigned int* arrTemp = new unsigned int[sizeLength];
    for(int index = 0; index < arrData.size(); index++)
    {
        arrTemp[index] = arrData.at(index);
        arrTemp[index] &= 0x000000FF;
    }
    //发送数据
    qDebug() << __FUNCTION__ <<"Send CustData Time:" << QTime::currentTime() << "start";
    sendRS232Data(channel, arrData.size(), (unsigned char*)arrData.data(), &tempAct);
    qDebug() << __FUNCTION__ <<"Send CustData Time:" << QTime::currentTime() << "end";
    //界面显示发送信息
    int temp = ui.labelSendLength->text().toInt();
    ui.labelSendLength->setText(QString("%1").arg(tempAct + temp));

    qDebug() << __FUNCTION__ << QStringLiteral("实际发送数据量:") << tempAct;
    delete[] arrTemp;
}

QByteArray ASL232::translateToHex(QByteArray hexData)
{
    if(hexData.size() < 2)
    {
        return QByteArray();
    }

    if(hexData.size() % 2 != 0)
    {
        hexData.remove(hexData.size() - 1, 1);
    }

    for(int i = 0; i < hexData.size(); i++)
    {
        char hex = hexData[i];
        if(!((hex >= '0' && hex <= '9') || (hex >= 'A' && hex <= 'F') || (hex >= 'a' && hex <= 'f')))
        {
            hexData[i] = 'F';
        }
    }

    QByteArray result;
    for(int i = 0; i < hexData.size() - 1; i = i + 2)
    {
        QByteArray hexWord = hexData.mid(i, 2);
        bool ok;
        int hex = hexWord.toInt(&ok, 16);
        result.append(hex);
        qDebug() << __FUNCTION__ << "ok?" << ok;
    }
    qDebug() << __FUNCTION__ << "result array" << result;
    return result;
}

QString ASL232::formatToHex(QByteArray hexData)
{
    QString hexString;
    for(int i = 0; i < hexData.size() - 1; i += 2)
    {
        hexString.append(hexData.mid(i, 2)).append(" ");
    }

    return hexString.trimmed();
}

QByteArray ASL232::trimToUINT(QByteArray hexData)
{
    if(hexData.size() < 4)
    {
        return QByteArray();
    }
    if(hexData.size() % 4 != 0)
    {
        hexData.remove(hexData.size() - 1, 1);
    }
    QByteArray result = hexData;
    return result;
}
