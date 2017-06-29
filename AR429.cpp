#include "AR429.h"
#include <QDebug>
#include <QTime>

AR429::AR429(QWidget *parent) :
    QtResource(QString(),NULL,parent)
{
    ui.setupUi(this);
    AR429_INFO stInfo;
    initAR429(&stInfo,(char*)"");
    initCompoent();
}

AR429::~AR429()
{
    uninitAR429();
}

int AR429::initAR429(AR429_INFO *info, char *dstPC)
{
    int status = 0;
    status = InitAR429(info, dstPC);
    return status;
}

int AR429::uninitAR429()
{
    int status = 0;
    status = UnInitAR429();
    return status;
}

int AR429::configAR429(short channel, func type, unsigned int value)
{
    int status = 0 ;
    status = A429_ConfigReg(channel, type, value);
    return status;
}

int AR429::sendAR429Data(short channel, short length, unsigned int *pValue)
{
    int status = 0 ;
    status = A429_DmaSendString(channel, length, pValue);
    status = A429_ConfigReg(channel, A429_TxEnable, 1);
    qDebug() << __FUNCTION__ << "status" << status;
    return status;
}

int AR429::recvAR429Data(short channel, short length, unsigned int *pValue, int *pActalLength)
{
    int status = 0 ;
    status = A429_DmaGetString(channel, length, pValue, pActalLength);
    qDebug() << __FUNCTION__ << "actal Length :" << *pActalLength;
    return status;
}


QByteArray AR429::translateToHex(QByteArray hexData)
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

QString AR429::formatToHex(QByteArray hexData)
{
    QString hexString;
    for(int i = 0; i < hexData.size() - 1; i += 2)
    {
        hexString.append(hexData.mid(i, 2)).append(" ");
    }

    return hexString.trimmed();
}

QByteArray AR429::trimToUINT(QByteArray hexData)
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


void AR429::initCompoent()
{
    m_recvTiemr.start(0);
    QStringList arrChannel;
    for (int index = 0; index < 8; index++)
    {
        arrChannel << QString("%1").arg(index);
    }

    ui.comboBoxChannelSend->addItems(arrChannel);
    ui.comboBoxChannelRecv->addItems(arrChannel);

    connect(ui.checkBoxChannelEn,&QCheckBox::stateChanged,[&](int state){
        int iChannelNum = ui.comboBoxChannelSend->currentText().toInt();
        int value = 0;
        switch (state) {
        case 0:
            value = 0;
            break;
        case 2:
            value = 1;
            break;
        default:
            value = 0;
            break;
        }
        configAR429(iChannelNum,A429_TxEnable,value);
    });


    connect(ui.checkBoxOutWrap,&QCheckBox::stateChanged,[&](int state){
        int iChannelNum = ui.comboBoxChannelSend->currentText().toInt();
        int value = 0;
        switch (state) {
        case 0:
            value = 0;
            break;
        case 2:
            value = 1;
            break;
        default:
            value = 0;
            break;
        }
        configAR429(iChannelNum,A429_OutWrap,value);
    });

    connect(ui.checkBoxWrap,&QCheckBox::stateChanged,[&](int state){
        int iChannelNum = ui.comboBoxChannelSend->currentText().toInt();
        int value = 0;
        switch (state) {
        case 0:
            value = 0;
            break;
        case 2:
            value = 1;
            break;
        default:
            value = 0;
            break;
        }
        configAR429(iChannelNum,A429_Wrap,value);
    });

    connect(ui.checkBoxSpeedChoice,&QCheckBox::stateChanged,[&](int state){
        int iChannelNum = ui.comboBoxChannelSend->currentText().toInt();
        int value = 0;
        switch (state) {
        case 0:
            value = 0;
            break;
        case 2:
            value = 1;
            break;
        default:
            value = 0;
            break;
        }
        configAR429(iChannelNum,A429_BaudRate,value);
        configAR429(iChannelNum,A429_Speed,value);
    });

    connect(ui.pushbuttonReset,&QPushButton::clicked,[&](){
        int iChannelNum = ui.comboBoxChannelSend->currentText().toInt();
        configAR429(iChannelNum,A429_Reset,1);
    });
    connect(ui.pushButtonConfig,&QPushButton::clicked,[&](){
        emit ui.checkBoxChannelEn->stateChanged(ui.checkBoxChannelEn->checkState());
        emit ui.checkBoxOutWrap->stateChanged(ui.checkBoxOutWrap->checkState());
        emit ui.checkBoxWrap->stateChanged(ui.checkBoxWrap->checkState());
        emit ui.checkBoxSpeedChoice->stateChanged(ui.checkBoxSpeedChoice->checkState());
    });

    ////串口发数
    connect(ui.pushButtonSend, &QPushButton::clicked, this, &AR429::sendData);
    ////定时循环接收数据
    connect(&m_recvTiemr, &QTimer::timeout, [&]()
    {
        int channel = ui.comboBoxChannelRecv->currentText().trimmed().toInt();
        unsigned int tempAct = 0;

        unsigned char arrTemp[1000];
        memset(arrTemp, 0, 1000);

        int iActLength = 0;
        float ftimeLab = 0.0;
//        recvRS422Data(channel, 1000, arrTemp, &iActLength, &ftimeLab);
        recvAR429Data(channel,1000,(unsigned int*)arrTemp, &iActLength);
        if (iActLength > 0)
        {
            qDebug() << __FUNCTION__ << "Recv Time:" << QTime::currentTime() << "end";
            qDebug() << __FUNCTION__ << QStringLiteral("#实际接收数据量#:") << iActLength;

            QString temp;

            temp += QString::fromLatin1((char*)arrTemp, iActLength);
            for (int index = 0; index < iActLength; index++);
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
        switch (state)
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

void AR429::sendData()
{
    switch (ui.checkBoxFixData->checkState())
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

void AR429::sendFixData()
{
    QString strSend = ui.textEditSend->toPlainText();
    std::string strTemp = strSend.toStdString();
    int channel = ui.comboBoxChannelSend->currentText().trimmed().toInt();
    unsigned int tempAct = 0;
    int sizeLength = strTemp.size();
    if (sizeLength > 500)
    {
        qDebug() << __FUNCTION__ << "size is out of array.";
        return;
    }
    //       char arr[500];
    //       strTemp.c_str();
    //       memcpy(arr, strTemp.c_str(),strTemp.size());

#define ARRAY_SIZE 5
    volatile int arr[ARRAY_SIZE] = { 0 };
    for (int index = 0; index < ARRAY_SIZE; index++)
        arr[index] = 9;

    qDebug() << __FUNCTION__ << "Send FixData Time:" << QTime::currentTime() << "start";
//    sendRS422Data(channel, ARRAY_SIZE, (unsigned char*)arr, &tempAct);
    sendAR429Data(channel,ARRAY_SIZE/4,(unsigned int*)arr);
    qDebug() << __FUNCTION__ << "Send FixData Time:" << QTime::currentTime() << "end";
    int temp = ui.labelSendLength->text().toInt();
    ui.labelSendLength->setText(QString("%1").arg(tempAct + temp));
    qDebug() << __FUNCTION__ << QStringLiteral("实际发送数据量:") << tempAct;

}

void AR429::sendCustData()
{
    QString strSend = ui.textEditSend->toPlainText();
    QByteArray arrSend = strSend.toLatin1();

    QByteArray arrData = arrSend;//= translateToHex(arrSend);

    int channel = ui.comboBoxChannelSend->currentText().trimmed().toInt();
    unsigned int tempAct = 0;
    int sizeLength = arrData.size();
    qDebug() << __FUNCTION__ << QString("size :%1").arg(sizeLength);

    unsigned int* arrTemp = new unsigned int[sizeLength];
    for (int index = 0; index < arrData.size(); index++)
    {
        arrTemp[index] = arrData.at(index);
        arrTemp[index] &= 0x000000FF;
    }
    //发送数据
    qDebug() << __FUNCTION__ << "Send CustData Time:" << QTime::currentTime() << "start";
//    sendRS422Data(channel, arrData.size(), (unsigned char*)arrData.data(), &tempAct);
    sendAR429Data(channel, arrData.size()/4, (unsigned int*)arrData.data());
    qDebug() << __FUNCTION__ << "Send CustData Time:" << QTime::currentTime() << "end";
    //界面显示发送信息
    int temp = ui.labelSendLength->text().toInt();
    ui.labelSendLength->setText(QString("%1").arg(tempAct + temp));

    qDebug() << __FUNCTION__ << QStringLiteral("实际发送数据量:") << tempAct;
    delete[] arrTemp;
}
