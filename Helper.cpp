#include "Helper.h"
#include <QDebug>
Helper::Helper(QObject *parent) : QObject(parent)
{
    initINI();
}

QString Helper::getASL232VisaDes()
{
    QString str = m_cfgINI->value(QString("ASL232/VisaResource")).toString();
    qDebug() << __FUNCTION__ << str;
    return str;
}

QString Helper::getASL422VisaDes()
{
    return m_cfgINI->value(QString("ASL422/VisaResource")).toString();
}

int Helper::getASL232RemoteType()
{
    return m_cfgINI->value(QString("ASL422/RemoteType"),0).toInt();
}

int Helper::getASL422RemoteType()
{
    return m_cfgINI->value(QString("ASL422/RemoteType"),0).toInt();
}

void Helper::initINI()
{
    m_cfgINI = new QSettings("./config.ini",QSettings::IniFormat,this);
    QStringList listGroup = m_cfgINI->childGroups();
}

