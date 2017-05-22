#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_MainWindow.h"
#include "QtResource.h"
#include "ASL232.h"
#include <QMap>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int scanForResources();
    void createWid();
private:
    Ui::MainWindow ui;
    unsigned long m_numResources;       //资源计数
    QString m_hostName;    //"visa://NT-G6000/?*";    //VISA远程访问域名
    QMap<QString, QString> m_mapResourceAlias;
    QHBoxLayout* m_layout;
};

#endif // MAINWINDOW_H
