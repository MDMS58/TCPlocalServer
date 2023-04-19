#ifndef BULLETNODE_H
#define BULLETNODE_H

#include <QGraphicsItem>

/**
 * @brief The bulletNode class
 *
 * Esta clase implementa un nodo para almacenar información de una bala en una lista enlazada.
 */
class bulletNode
{
public:
    QGraphicsPixmapItem *item; /**< Puntero a un objeto gráfico que representa la bala. */
    bulletNode *nextBullet; /**< Puntero al siguiente nodo en la lista enlazada. */
    bool erasable; /**< Indica si la bala puede ser eliminada. */
    int health; /**< Cantidad de puntos de salud de la bala. */
    int damage; /**< Cantidad de puntos de daño que inflige la bala. */
    int id; /**< Identificador único de la bala. */

    /**
     * @brief Constructor de la clase `bulletNode`.
     *
     * Inicializa los atributos de la clase a sus valores por defecto.
     */
    bulletNode();
};

#endif // BULLETNODE_H
