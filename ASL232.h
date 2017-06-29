#ifndef ASL232_H
#define ASL232_H
#include "QtResource.h"
#include "ui_ASL232.h"
#include <QTimer>
class ASL232 : public QtResource
{
public:
    explicit ASL232(QString strDevice, ViSession viResourceRM, QWidget *parent = Q_NULLPTR);
    int initRS232();
    int uninitRS232();
    int configRS232Format(short channelNum ,unsigned long baudrate,int wordlength,int parity,int stopBit);
    int sendRS232Data(short channelNum, short length ,unsigned char * pValue,unsigned int *pActualLength);
    int recvRS232Data(short channelNum, short length, unsigned char * pValue, int *pActalLength, double *timeLab);
    ~ASL232();

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

#endif // ASL232_H
