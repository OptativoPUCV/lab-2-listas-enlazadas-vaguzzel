#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
    List *list = (List *)malloc(sizeof(List));  // Reserva memoria para la estructura de la lista
    if (list == NULL) exit(EXIT_FAILURE);  // Verifica que la memoria fue correctamente reservada

    list->head = NULL;   // Inicializa el puntero al primer nodo como NULL
    list->tail = NULL;   // Inicializa el puntero al último nodo como NULL
    list->current = NULL; // Inicializa el puntero 'current' como NULL

    return list;  // Retorna el puntero a la lista recién creada
}


void * firstList(List *list) {
    if (list == NULL || list->head == NULL) return NULL;  // Verifica si la lista está vacía
    list->current = list->head;  // Apunta al primer nodo
    return list->current->data;  // Retorna el dato del primer nodo
}

void * nextList(List *list) {
    if (list == NULL || list->current == NULL || list->current->next == NULL) return NULL;  // Si no hay siguiente nodo
    list->current = list->current->next;  // Avanza al siguiente nodo
    return list->current->data;  // Retorna el dato del siguiente nodo
}

void * lastList(List *list) {
    if (list == NULL || list->tail == NULL) return NULL;  // Verifica si la lista está vacía
    list->current = list->tail;  // Apunta al último nodo
    return list->current->data;  // Retorna el dato del último nodo
}

void * prevList(List *list) {
    if (list == NULL || list->current == NULL || list->current->prev == NULL) return NULL;  // Si no hay nodo anterior
    list->current = list->current->prev;  // Retrocede al nodo anterior
    return list->current->data;  // Retorna el dato del nodo anterior
}

void pushFront(List *list, void *data) {
    Node *newNode = createNode(data);  // Crea un nuevo nodo

    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
        list->current = newNode;
    } else {
        newNode->next = list->head;  // Enlaza el nuevo nodo al principio
        list->head->prev = newNode;
        list->head = newNode;  // Actualiza el head de la lista
    }
}


void pushCurrent(List *list, void *data) {
    if (list == NULL || list->current == NULL) return;  // Si la lista o current son NULL, no hace nada
    Node *newNode = createNode(data);  // Crea un nuevo nodo
    newNode->next = list->current->next;  // Enlaza el siguiente nodo
    if (list->current->next != NULL) {
        list->current->next->prev = newNode;  // Si hay un siguiente nodo, ajusta su anterior
    }
    list->current->next = newNode;  // Enlaza el nuevo nodo al nodo actual
    newNode->prev = list->current;  // Enlaza el nuevo nodo al nodo anterior
    if (list->current == list->tail) {
        list->tail = newNode;  // Si el current es el último nodo, actualiza el tail
    }
}

void pushBack(List *list, void *data) {
    list->current = list->tail;
    pushCurrent(list, data);
}

void * popFront(List *list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List *list) {
    list->current = list->tail;
    return popCurrent(list);
}


void * popCurrent(List *list) {
    if (list == NULL || list->current == NULL) return NULL;  // Verifica si la lista o current son NULL
    Node *temp = list->current;
    void *data = temp->data;  // Guarda el dato del nodo que se va a eliminar
    
    // Ajuste de los enlaces
    if (temp->prev != NULL) {
        temp->prev->next = temp->next;
    } else {
        list->head = temp->next;  // Si el nodo a eliminar es el head, actualiza el head
    }
    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    } else {
        list->tail = temp->prev;  // Si el nodo a eliminar es el tail, actualiza el tail
    }
    
    list->current = temp->next;  // Mueve el current al siguiente nodo
    free(temp);  // Libera la memoria del nodo eliminado
    return data;  // Retorna el dato del nodo eliminado
}


void cleanList(List *list) {
    while (list->head != NULL) {
        popFront(list);
    }
}
