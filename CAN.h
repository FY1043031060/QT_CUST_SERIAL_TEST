#ifndef CAN_H
#define CAN_H

#include "ui_CAN.h"
#include "nixnet.h"
#include <QTimer>

class CAN : public QWidget
{
    Q_OBJECT

public:
    explicit CAN(QWidget *parent = nullptr);
    ~CAN();
    int writeData(const unsigned char *pBuff, int length);
    int readData(unsigned char *pBuff, int length);

private:
    void initComponent();
    void DisplayErrorAndExit(nxStatus_t Status, char *Source);
    void initConnection();
    Ui::CAN ui;
    QTimer m_recvTimer;
    QTimer m_sendTimer;
    nxSessionRef_t m_InputSessionRef = 0;
    nxSessionRef_t m_OutputSessionRef = 0;
};

#endif // CAN_H
