#ifndef ASL422_H
#define ASL422_H
#include "QtResource.h"
#include "ui_ASL232.h"
#include <QTimer>


class ASL422 : public QtResource
{
    Q_OBJECT
public:
    enum RELAY_CONFIG{
        RS422MODE = 0,
        RS485MODE = 1
    };

    explicit ASL422(QString strDevice, ViSession viResourceRM, QWidget *parent = nullptr);
    ~ASL422();

    int configRS422Format(short channelNum ,unsigned long baudrate,int wordlength,int parity,int stopBit);
    int sendRS422Data(short channelNum, short length ,unsigned char * pValue, unsigned int *pActualLength);
    int recvRS422Data(short channelNum, short length, unsigned char * pValue, int *pActalLength,double *timeLab);
    int switch485VS422(int channel,RELAY_CONFIG eMode);
private:
    int initRS422();
    int uninitRS422();
    QByteArray translateToHex(QByteArray hexData);
    QByteArray trimToUINT(QByteArray hexData);
    QString formatToHex(QByteArray hexData);
private:
    void initCompoent();
    void sendData();
    void sendFixData();
    void sendCustData();
    Ui::ASL232 ui;
    QTimer m_recvTiemr;
    QTimer m_sendTimer;
};

#endif // ASL422_H
