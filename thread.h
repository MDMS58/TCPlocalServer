/**
 * @file mythread.h
 * @brief Contiene la declaración de la clase MyThread
 */

#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include "localserver.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPointF>
#include <QGraphicsRectItem>
#include <bulletlist.h>
#include <QLabel>

/**
 * @brief La clase MyThread representa un hilo que ejecuta un bucle de juego
 */
class MyThread : public QThread
{
    Q_OBJECT

public:
    LocalServer *server; /**< El servidor local utilizado para multijugador */
    QGraphicsScene *scene ; /**< La escena del juego */
    QGraphicsView *view ; /**< La vista del juego */
    QLabel *label ; /**< La etiqueta de puntuación del jugador */
    QVariant condition=0; /**< La variable de condición utilizada para la sincronización */
    bulletList enemiesList; /**< La lista de balas enemigas */
    bulletList list; /**< La lista de balas del jugador */
    QGraphicsPixmapItem* item ; /**< La nave espacial del jugador */

    /**
     * @brief Mueve las naves enemigas
     */
    void move();

    /**
     * @brief Mueve el elemento de la nave espacial del jugador
     */
    void itemMove();

    /**
     * @brief Crea las balas y las mueve
     */
    void widget_1();

    /**
     * @brief Comprueba las colisiones de balas
     */
    void checkCollision();

    /**
     * @brief Comprueba las colisiones del jugador
     */
    void PlayerCollision();

    /**
     * @brief Analiza lo que sucede tras cada choque
     */
    void pause();

    /**
     * @brief Define la posición de las naves espaciales enemigas y las balas tras cada ronda
     */
    void definePos();

    /**
     * @brief Cambia al otro poder en caso de no estar en memoria
     * @param file el nombre de archivo del poder
     */
    void waitPower(QString file);

    /**
     * @brief Lee el poder presente
     */
    void powers();

    /**
     * @brief Reduce la velocidad de los enemigos
     * @param localSpeed la velocidad local del juego
     */
    void reduceSpeed(int localSpeed);

    /**
     * @brief Aumenta la velocidad del juego
     * @param localSpeed la velocidad local del juego
     */
    void increaseSpeed(int localSpeed);

    /**
     * @brief Aplica la mitad del daño a la nave espacial del jugador
     */
    void halfDamage();

    /**
     * @brief Muestra la puntuación y la salud del jugador
     */
    void showInformation();

    /**
     * @brief Duplica el daño del jugador
     */
    void DoubleDamage();

    /**
     * @brief Construye un nuevo objeto MyThread
     * @param parent el objeto padre
     */
    explicit MyThread(QObject *parent = nullptr);

    /**
     * @brief revisa si el jugador ya perdio
     */
    void lose();

    void potentiometer();

protected:
    /**
     * @brief El método de ejecución del hilo
     */
    void run() override;
};

#endif // MYTHREAD_H
