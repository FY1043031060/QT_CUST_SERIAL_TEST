#include "QtResource.h"

#include <QDebug>
QtResource::QtResource(QString strDevice, ViSession viResourceRM, QWidget *parent)
    :QWidget(parent), m_strDev(strDevice)
{
    ViStatus status = viOpen(viResourceRM,
                             strDevice.trimmed().toLatin1().data(),
                             VI_NULL,
                             VI_NULL,
                             &m_session);
    if(VI_SUCCESS > status)
    {
        ViChar errInfo[VI_FIND_BUFLEN] = {0};
        viStatusDesc(viResourceRM,status,errInfo);
        qDebug() << __FUNCTION__ << QString::fromLocal8Bit(errInfo);
    }
    setObjectName(strDevice.trimmed());
}

QtResource::~QtResource()
{
    if(m_session != NULL)
    {
        viClose(m_session);
        m_session = NULL;
    }
}
