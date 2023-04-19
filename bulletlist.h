#ifndef BULLETLIST_H
#define BULLETLIST_H

#include "bulletNode.h"

/**
 * @brief Clase que implementa una lista enlazada de balas.
 *
 * Esta clase almacena una lista enlazada de balas que se utilizan en un juego. La clase
 * es responsable de insertar, eliminar y mostrar balas, así como de mantener un contador
 * de cuántas balas hay en la lista.
 */

class bulletList
{
public:
    /**
     * @brief Constructor de la clase.
     *
     * Crea una lista enlazada de balas vacía.
     */
    bulletList();

    /**
     * @brief Puntero al primer nodo de la lista.
     */
    bulletNode *head;


    /**
     * @brief Puntero al último nodo de la lista.
     */
    bulletNode *last;

    /**
         * @brief Contador de elementos en la lista.
         */
    int elements=0;

    /**
     * @brief Inserta una cantidad dada de balas en la lista.
     *
     * Crea nuevos nodos de bala y los inserta en la lista enlazada.
     *
     * @param bulletAmount La cantidad de balas que se deben insertar.
     */
    void insert(int bulletAmount);

    /**
        * @brief Muestra los datos de cada nodo en la lista.
        *
        * Recorre cada nodo de la lista y muestra sus datos por consola.
        */
    void show();

    /**
         * @brief Elimina todos los nodos de la lista.
         */
    void deleteNodes();

    /**
     * @brief Reinicia la lista de balas.
     *
     * @param list La lista que se debe reiniciar.
     * @return La lista reiniciada.
     */
    bulletList resetList (bulletList list);

    /**
         * @brief Elimina un nodo de la lista dada su ID de bala.
         *
         * Busca el nodo con el ID de bala dado en la lista y lo elimina.
         *
         * @param bullet_id El ID de la bala que se debe eliminar.
         */
    void deleteNode(int bullet_id);

    /**
        * @brief Cuenta la cantidad de nodos en la lista.
        *
        * Recorre la lista y cuenta la cantidad de nodos que hay en ella.
        *
        * @return La cantidad de nodos en la lista.
        */
    int counter();

    /**
        * @brief Sobrecarga del operador delete.
        *
        * Se utiliza para liberar la memoria ocupada por un objeto de la clase `bulletList`.
        *
        * @param ptr El puntero al objeto que se debe eliminar.
        */
    void operator delete(void* ptr); //Autores: Michael Marcia e Isaac Solis, Marco no, porque no hizo una basura

};

#endif // BULLETLIST_H
