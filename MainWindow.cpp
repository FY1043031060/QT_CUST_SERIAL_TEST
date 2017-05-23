#include "MainWindow.h"
#include "visa.h"
#include <QDebug>

static ViSession s_DefaultRM = NULL;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),m_hostName("visa://R3ZH522P0MBEX0Y/?*")
{
    ui.setupUi(this);
    m_layout = new QHBoxLayout(this->centralWidget());

    if(VI_SUCCESS > viOpenDefaultRM(&s_DefaultRM))
    {
        return;
    }
    Q_ASSERT(VI_SUCCESS == scanForResources());
    createWid();
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
                        m_hostName.trimmed().toLatin1().data(),
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

void MainWindow::createWid()
{
    foreach(QString val, m_mapResourceAlias.keys())
    {
        if(val.contains(QString("PXI24::11::INSTR")))//NOTE::有变更
        {
            m_layout->addWidget(new ASL232(val,s_DefaultRM,this));
        }
    }
}
