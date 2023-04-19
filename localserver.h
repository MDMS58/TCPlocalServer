#ifndef LOCALSERVER_H
#define LOCALSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class QTcpServer;

/**
 * @brief The LocalServer class
 * Esta clase representa el servidor local. Hereda de QTcpServer.
 * Permite establecer una conexión TCP local y recibir datos del cliente.
 */
class LocalServer : public QTcpServer{
    Q_OBJECT
public:
    /**
     * @brief LocalServer
     * Constructor de la clase.
     * @param parent Puntero al objeto padre.
     */
    explicit LocalServer(QObject *parent = nullptr);

    QTcpSocket *socket; /**< Socket para recibir datos del cliente. */

};

#endif // LOCALSERVER_H
