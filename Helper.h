#ifndef HELPER_H
#define HELPER_H

#include <QObject>
#include <QSettings>

class Helper : public QObject
{
    Q_OBJECT
public:
    enum REMOTE_STYLE{
        REMOTE_POLL = 0,
        REMOTE_INTERRUPT = 1
    };

public:
    static Helper& getInstance()
    {
        static Helper instance;
        return instance;
    }
    QString getASL232VisaDes();
    QString getASL422VisaDes();
    int getASL232RemoteType();
    int getASL422RemoteType();
signals:

public slots:

private:
    explicit Helper(QObject *parent = nullptr);
    void initINI();

    QSettings* m_cfgINI;
};

#endif // HELPER_H
