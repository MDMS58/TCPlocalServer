#ifndef LOCALSERVER_H
#define LOCALSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class QTcpServer;
class LocalServer : public QTcpServer{
    Q_OBJECT
public:
    explicit LocalServer(QObject *parent = nullptr);

    QTcpSocket *socket;

signals:
};

#endif // LOCALSERVER_H
