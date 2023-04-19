#ifndef NODEID_H
#define NODEID_H

/**
 * @brief La clase nodeid representa un ID de nodo en una lista enlazada
 */
class nodeid
{
public:
    /**
     * @brief Constructor que crea un nuevo objeto nodeid
     * @param id el ID del nodo
     */
    nodeid(int id);

    /**
     * @brief El siguiente nodo en la lista enlazada
     */
    nodeid *next;

    /**
     * @brief El ID del nodo
     */
    int id;
};

#endif // NODEID_H
