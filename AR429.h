#ifndef AR429_H
#define AR429_H

#include "ui_AR429.h"
#include "QtResource.h"
#include "Function429.h"
#include <QTimer>

class AR429 : public QtResource
{
    Q_OBJECT

public:
    explicit AR429(QWidget *parent = 0);
    ~AR429();
    int initAR429(AR429_INFO *info, char *dstPC);
    int uninitAR429();
    int configAR429(short channel ,func type,unsigned int value);
    int sendAR429Data(short channel, short length ,unsigned int * pValue);
    int recvAR429Data(short channel, short length ,unsigned int * pValue,int *pActalLength);

    QByteArray translateToHex(QByteArray hexData);
    QByteArray trimToUINT(QByteArray hexData);
    QString formatToHex(QByteArray hexData);
private:
    void initCompoent();
    void sendData();
    void sendFixData();
    void sendCustData();

    Ui::AR429 ui;
    QTimer m_recvTiemr;
    QTimer m_sendTimer;
};

#endif // AR429_H
