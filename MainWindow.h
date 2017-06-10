#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_MainWindow.h"
#include "ui_Concurrence.h"
#include "QtResource.h"
#include "ASL232.h"
#include "ASL422.h"
#include <QMap>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    int scanForResources();
    void createWid();
    void testConcurrence();
    void setSendLabelDis(int index, int strNum);
    void setRecvLabelDis(int index, int strNum);

private:
    Ui::MainWindow ui;
    unsigned long m_numResources;       //资源计数
    QString m_hostName;    //"visa://NT-G6000/?*";    //VISA远程访问域名
    QMap<QString, QString> m_mapResourceAlias;
    QVBoxLayout* m_layout;
    Ui::Concurrence conUi;
};

#endif // MAINWINDOW_H
