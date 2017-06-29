#include "MainWindow.h"
#include "visa.h"
#include <QDebug>
#include "Helper.h"

static ViSession s_DefaultRM = NULL;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),m_hostName("visa://USER-20170518HA/?*") ////USER-20170518HA  ////R3ZH522P0MBEX0Y
{
    ui.setupUi(this);
    m_layout = new QVBoxLayout(this->centralWidget());

    if(VI_SUCCESS > viOpenDefaultRM(&s_DefaultRM))
    {
        return;
    }
    Q_ASSERT(VI_SUCCESS == scanForResources());
    createWid();
//    testConcurrence();
}

MainWindow::~MainWindow()
{
    viClose(s_DefaultRM);
}

int MainWindow::scanForResources()
{
    int status = VI_SUCCESS;
    ViFindList session;
    ViChar strDesc[FILENAME_MAX];
    ViChar strErr[FILENAME_MAX];
    ViChar strSession[] = "visa://?*";
    ViUInt16 intfType;
    ViUInt16 intfNum;
    ViChar rsrcClass[FILENAME_MAX];
    ViChar expandedUnaliasedName[FILENAME_MAX];
    ViChar aliasIfExists[FILENAME_MAX]; //USER DEFINE NAME
    m_mapResourceAlias.clear();
    ViUInt32 retCnt;
    //根据默认资源管理器获取资源描述符
    status = viFindRsrc(s_DefaultRM,
                        m_hostName.trimmed().toUtf8().data(),
                        &session,
                        &retCnt,
                        strDesc);
    if(status != VI_SUCCESS)
    {
        viStatusDesc(s_DefaultRM,status,strErr);
        qDebug() <<QString::fromLocal8Bit(strErr);
        return status;
    }
    //根据默认资源管理器以及资源描述符获取设备其他信息
    status = viParseRsrcEx(s_DefaultRM,
                           strDesc,
                           &intfType,
                           &intfNum,
                           rsrcClass,
                           expandedUnaliasedName,
                           aliasIfExists);
    if(status != VI_SUCCESS)
    {
        viStatusDesc(s_DefaultRM,status,strErr);
        qDebug() <<QString::fromLocal8Bit(strErr);
        return status;
    }
    qDebug() <<__FUNCTION__ << "strDesc"<< strDesc
            <<"aliasIfExists"<< aliasIfExists;
    m_mapResourceAlias.insert(strDesc,aliasIfExists);

    for(unsigned long index = 0; index < retCnt - 1; index++)
    {
        status = viFindNext(session, strDesc);
        viParseRsrcEx(s_DefaultRM,
                      strDesc,
                      &intfType,
                      &intfNum,
                      rsrcClass,
                      expandedUnaliasedName,
                      aliasIfExists);

        qDebug() <<__FUNCTION__ << "strDesc"<< strDesc
                <<"aliasIfExists"<< aliasIfExists;
        m_mapResourceAlias.insert(strDesc,aliasIfExists);

    }
    return status;
}
#define _SERIAL_
void MainWindow::createWid()
{
#ifdef _SERIAL_
    foreach(QString val, m_mapResourceAlias.keys())
    {
        if(val.contains(Helper::getInstance().getASL232VisaDes()))//NOTE::232有变更
        {
            m_layout->addWidget(new ASL232(val,s_DefaultRM,this));
        }
        else if(val.contains(Helper::getInstance().getASL422VisaDes()))//NOTE::422
        {
            m_layout->addWidget(new ASL422(val,s_DefaultRM,this));
        }

    }
////NOTE:: access CAN1 and CAN2 with RPC server.
//    m_layout->addWidget(new CAN(this));
#else
//    m_layout->addWidget(new AR429(this));
#endif
}

#include <QTimer>
#include <QLabel>
#include <QFile>
void MainWindow::testConcurrence()
{
    QWidget* widMain = new QWidget(this);
    widMain->setObjectName(QString("widMain"));
    widMain->setWindowFlag(Qt::Window);

    static ASL232* pwid = this->findChild<ASL232*>(QString("ASL232"));
    conUi.setupUi(widMain);
    auto listCombos =widMain->findChildren<QComboBox*>();
    for(int index = 0;index <listCombos.size();index++)
    {
        listCombos[index]->addItem(QString("%1").arg(index));
    }
    ////配置波特率
    [&](){
        for(int index = 0;index < 18;index++)
            pwid->configRS232Format(index,115200,0,2,0);
    }();
    ////数据定时发送
    QTimer* sendTimer = new QTimer(widMain);
    QTimer* recvTimer = new QTimer(this);
    connect(sendTimer,&QTimer::timeout,[&](){
        unsigned char arr[] = {"12345678"};
        unsigned int numAct = 0;
        for(int index = 0;index < 18;index++)
        {
            numAct = 0;
            pwid->sendRS232Data(index,8,arr, &numAct);
            setSendLabelDis(index,numAct);
        }
    });
    connect(recvTimer,&QTimer::timeout,[&](){
        unsigned char arr[1000] = {0};
        int numAct = 0;
        double timeLab = 0;
        for(int index = 0;index < 18;index++)
        {
            numAct = 0;
            pwid->recvRS232Data(index, 1000, arr, &numAct, &timeLab);
            setRecvLabelDis(index, numAct);
        }
    });
    connect(conUi.pushButtonStop,&QPushButton::clicked,[&](){
         this->findChild<QWidget*>(QString("widMain"))->findChild<QTimer*>()->stop();
    });
    connect(conUi.pushButtonClear,&QPushButton::clicked,[&](){
        foreach (auto val, this->findChild<QWidget*>(QString("widMain"))->findChildren<QLabel*>()) {
            val->setText(QString("0"));
        } ;
    });
    sendTimer->start(100);
    recvTimer->start(0);
    widMain->show();
}

void MainWindow::setSendLabelDis(int index, int strNum)
{
    switch (index) {
    case 0:
        conUi.labelSend_0->setText(QString::number((conUi.labelSend_0->text().toInt() + strNum),10));
        break;
    case 1:
        conUi.labelSend_1->setText(QString::number((conUi.labelSend_1->text().toInt() + strNum),10));
        break;
    case 2:
        conUi.labelSend_2->setText(QString::number((conUi.labelSend_2->text().toInt() + strNum),10));
        break;
    case 3:
        conUi.labelSend_3->setText(QString::number((conUi.labelSend_3->text().toInt() + strNum),10));
        break;
    case 4:
        conUi.labelSend_4->setText(QString::number((conUi.labelSend_4->text().toInt() + strNum),10));
        break;
    case 5:
        conUi.labelSend_5->setText(QString::number((conUi.labelSend_5->text().toInt() + strNum),10));
        break;
    case 6:
        conUi.labelSend_6->setText(QString::number((conUi.labelSend_6->text().toInt() + strNum),10));
        break;
    case 7:
        conUi.labelSend_7->setText(QString::number((conUi.labelSend_7->text().toInt() + strNum),10));
        break;
    case 8:
        conUi.labelSend_8->setText(QString::number((conUi.labelSend_8->text().toInt() + strNum),10));
        break;
    case 9:
        conUi.labelSend_9->setText(QString::number((conUi.labelSend_9->text().toInt() + strNum),10));
        break;
    case 10:
        conUi.labelSend_10->setText(QString::number((conUi.labelSend_10->text().toInt() + strNum),10));
        break;
    case 11:
        conUi.labelSend_11->setText(QString::number((conUi.labelSend_11->text().toInt() + strNum),10));
        break;
    case 12:
        conUi.labelSend_12->setText(QString::number((conUi.labelSend_12->text().toInt() + strNum),10));
        break;
    case 13:
        conUi.labelSend_13->setText(QString::number((conUi.labelSend_13->text().toInt() + strNum),10));
        break;
    case 14:
        conUi.labelSend_14->setText(QString::number((conUi.labelSend_14->text().toInt() + strNum),10));
        break;
    case 15:
        conUi.labelSend_15->setText(QString::number((conUi.labelSend_15->text().toInt() + strNum),10));
        break;
    case 16:
        conUi.labelSend_16->setText(QString::number((conUi.labelSend_16->text().toInt() + strNum),10));
        break;
    case 17:
        conUi.labelSend_17->setText(QString::number((conUi.labelSend_17->text().toInt() + strNum),10));
        break;
    default:
        break;
    }
}

void MainWindow::setRecvLabelDis(int index, int strNum)
{
    switch (index) {
    case 0:
        conUi.labelRecv_0->setText(QString::number((conUi.labelRecv_0->text().toInt() + strNum),10));
        break;
    case 1:
        conUi.labelRecv_1->setText(QString::number((conUi.labelRecv_1->text().toInt() + strNum),10));
        break;
    case 2:
        conUi.labelRecv_2->setText(QString::number((conUi.labelRecv_2->text().toInt() + strNum),10));
        break;
    case 3:
        conUi.labelRecv_3->setText(QString::number((conUi.labelRecv_3->text().toInt() + strNum),10));
        break;
    case 4:
        conUi.labelRecv_4->setText(QString::number((conUi.labelRecv_4->text().toInt() + strNum),10));
        break;
    case 5:
        conUi.labelRecv_5->setText(QString::number((conUi.labelRecv_5->text().toInt() + strNum),10));
        break;
    case 6:
        conUi.labelRecv_6->setText(QString::number((conUi.labelRecv_6->text().toInt() + strNum),10));
        break;
    case 7:
        conUi.labelRecv_7->setText(QString::number((conUi.labelRecv_7->text().toInt() + strNum),10));
        break;
    case 8:
        conUi.labelRecv_8->setText(QString::number((conUi.labelRecv_8->text().toInt() + strNum),10));
        break;
    case 9:
        conUi.labelRecv_9->setText(QString::number((conUi.labelRecv_9->text().toInt() + strNum),10));
        break;
    case 10:
        conUi.labelRecv_10->setText(QString::number((conUi.labelRecv_10->text().toInt() + strNum),10));
        break;
    case 11:
        conUi.labelRecv_11->setText(QString::number((conUi.labelRecv_11->text().toInt() + strNum),10));
        break;
    case 12:
        conUi.labelRecv_12->setText(QString::number((conUi.labelRecv_12->text().toInt() + strNum),10));
        break;
    case 13:
        conUi.labelRecv_13->setText(QString::number((conUi.labelRecv_13->text().toInt() + strNum),10));
        break;
    case 14:
        conUi.labelRecv_14->setText(QString::number((conUi.labelRecv_14->text().toInt() + strNum),10));
        break;
    case 15:
        conUi.labelRecv_15->setText(QString::number((conUi.labelRecv_15->text().toInt() + strNum),10));
        break;
    case 16:
        conUi.labelRecv_16->setText(QString::number((conUi.labelRecv_16->text().toInt() + strNum),10));
        break;
    case 17:
        conUi.labelRecv_17->setText(QString::number((conUi.labelRecv_17->text().toInt() + strNum),10));
        break;
    default:
        break;
    }
}


