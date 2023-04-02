#include <QTcpServer>
#include <QTcpSocket>
#include <QThread>
#include <QDebug>
 QTcpServer server;
 server.listen(QHostAddress::Any, 1290
class ServerThread : public QThread {
public:
    void run() override {
        QTcpServer server;
        if (!server.listen(QHostAddress::Any, 1290)) {
            qDebug() << "Error: could not start server";
            return;
        }
        qDebug() << "Server started, listening on port 1234";

        while (true) {
            // Esperar por una nueva conexión
            if (!server.waitForNewConnection(-1)) {
                qDebug() << "Error: could not accept incoming connection";
                continue;
            }
            // Manejar la nueva conexión
            QTcpSocket *socket = server.nextPendingConnection();
            qDebug() << "New connection from:" << socket->peerAddress().toString();
            // Hacer algo con el socket...
            QString data=socket->readAll();
            qDebug()<<data;
            socket->flush();
            socket->close();
            delete socket;
        }
    }
};
