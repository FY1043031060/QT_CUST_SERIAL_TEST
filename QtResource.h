#ifndef QTRESOURCE_H
#define QTRESOURCE_H

#include <QWidget>
#include "visa.h"

class QtResource : public QWidget
{
    Q_OBJECT
public:
    explicit QtResource(QString strDevice, ViSession viResourceRM, QWidget *parent = Q_NULLPTR);
    ~QtResource();
signals:

public slots:
public:
    ViSession m_session;    //资源句柄
    QString m_strDev;   //资源描述符
};

#endif // QTRESOURCE_H
