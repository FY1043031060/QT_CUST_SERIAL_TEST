#include "CAN.h"
#include <QDebug>
#include <stdlib.h>     // Include file for various functions
#include <stdio.h>      // Include file for printf
#include <conio.h>      // Include file for _getch/kbhit
#include <windows.h>    // Include file for Win32 time functions
CAN::CAN(QWidget *parent) :
    QWidget(parent)
{
    ui.setupUi(this);
    initComponent();
    initConnection();
}

CAN::~CAN()
{
    nxStatus_t l_Status = 0;
    // Clear the XNET sessions
    l_Status = nxClear(m_OutputSessionRef);
    if (nxSuccess != l_Status)
    {
        DisplayErrorAndExit(l_Status, (char*)"nxClear");
    }

    l_Status = nxClear(m_InputSessionRef);
    if (nxSuccess != l_Status)
    {
        DisplayErrorAndExit(l_Status, (char*)"nxClear");
    }
}

int CAN::writeData(const unsigned char *pBuff, int length)
{
    nxStatus_t l_Status = 0;
    f64 l_OutputValueBuffer;
    memcpy(&l_OutputValueBuffer, pBuff, length);

    // Update the signal values
    l_Status = nxWriteSignalSinglePoint(m_OutputSessionRef,
                                        &l_OutputValueBuffer, sizeof(length));
    if (nxSuccess == l_Status)
    {
        qDebug() <<("Signals sent:\n");
        qDebug() <<("Signal 1: %f\n", l_OutputValueBuffer);
    }
    else
    {
        DisplayErrorAndExit(l_Status, (char*)"nxWriteSignalSinglePoint");
    }
    return 0;
}

int CAN::readData(unsigned char *pBuff, int length)
{
    nxStatus_t l_Status = 0;
    f64 l_InputValueBuffer;
    nxTimestamp_t l_TimestampBuffer;
    // Read the latest signal values
    l_Status = nxReadSignalSinglePoint(m_InputSessionRef,
                                       &l_InputValueBuffer, sizeof(l_InputValueBuffer),
                                       &l_TimestampBuffer, sizeof(l_TimestampBuffer));
    if (nxSuccess == l_Status)
    {
        // Print the values ignoring timestamps
        qDebug() <<("Signals received:\n");
        qDebug() <<("Signal 1: %f\n", l_InputValueBuffer);
        qDebug() <<QString("time: %1").arg(l_TimestampBuffer);
    }
    else
    {
        DisplayErrorAndExit(l_Status, (char*)"nxReadSignalSinglePoint");
    }
    memcpy(pBuff, &l_InputValueBuffer, sizeof(l_InputValueBuffer));
    return sizeof(l_InputValueBuffer);
}

void CAN::initComponent()
{
    const char *l_pSelectedInterface1 = "CAN1";
    const char *l_pSelectedInterface2 = "CAN2";
    const char *l_pSelectedDatabase = "./NIXNET_example.xml";
    const char *l_pSelectedCluster = "CAN_Cluster";
    const char *l_pSelectedInputSignalList = "CANEventSignal1";
    const char *l_pSelectedOutputSignalList = "CANEventSignal1";
    nxStatus_t l_Status = 0;


    // Create an XNET session in SignalInSinglePoint mode
    l_Status = nxCreateSession(l_pSelectedDatabase, l_pSelectedCluster,
                               l_pSelectedInputSignalList, l_pSelectedInterface1,
                               nxMode_SignalInSinglePoint, &m_InputSessionRef);
    if (nxSuccess == l_Status)
    {
        qDebug() <<("Input session created successfully.\n");
    }
    else
    {
        DisplayErrorAndExit(l_Status, (char*)"nxCreateSession");
    }

    // Create an XNET session in SignalOutSinglePoint mode
    l_Status = nxCreateSession(l_pSelectedDatabase, l_pSelectedCluster,
                               l_pSelectedOutputSignalList, l_pSelectedInterface2,
                               nxMode_SignalOutSinglePoint, &m_OutputSessionRef);
    if (nxSuccess == l_Status)
    {
        qDebug() <<("Output session created successfully.\n");
    }
    else
    {
        DisplayErrorAndExit(l_Status, (char*)"nxCreateSession");
    }

    if (nxSuccess == l_Status)
    {
        qDebug() <<("Input session started manually.\n");
    }
    else
    {
        DisplayErrorAndExit(l_Status, (char*)"nxStart");
    }

    qDebug() <<("Press any key to transmit or q to quit\n");
    qDebug() <<("The same values should be received.\n");



}

//=============================================================================
// Display Error Function
//=============================================================================
void CAN::DisplayErrorAndExit(nxStatus_t Status, char *Source)
{
    char l_StatusString[1024];
    nxStatusToString(Status, sizeof(l_StatusString), l_StatusString);

    qDebug() << ("\n\nERROR at %s!\n%s\n", Source, l_StatusString);
    qDebug() << ("\nExecution stopped.\nPress any key to quit\n");

    nxClear(m_OutputSessionRef);
    nxClear(m_InputSessionRef);

    _getch();
    exit(1);
}

void CAN::initConnection()
{
    connect(ui.pushButtonSend,&QPushButton::clicked,[&](){
        bool ok = false;
        double temp = ui.lineEditSend->text().toDouble(&ok);
        if(ok)
        {
            writeData((unsigned char*)&temp,sizeof(temp));
        }
    });
    connect(&m_recvTimer,&QTimer::timeout,[&](){
        double temp = 0;
        readData((unsigned char*)&temp,sizeof(temp));
        ui.textEditRecv->setText(ui.textEditRecv->toPlainText()+QString::number(temp));
    });
    connect(&m_sendTimer,&QTimer::timeout,[&](){
      emit  ui.pushButtonSend->clicked();
    });
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
    connect(ui.pushButtonClear, &QPushButton::clicked, [&]()
    {
        ui.labelRecvLength->setText("0");
        ui.labelSendLength->setText("0");
        ui.textEditRecv->setText("");
        ui.lineEditSend->setText("");
    });
}
