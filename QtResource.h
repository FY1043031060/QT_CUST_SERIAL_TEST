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
    ViSession m_session;    //��Դ���
    QString m_strDev;   //��Դ������
};

#endif // QTRESOURCE_H
