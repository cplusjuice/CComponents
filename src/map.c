#include <stdlib.h>

#include "ccomponents.h"

typedef struct _map_value_private {
    List *values;
    List *keys;
} MapValuePrivate;

typedef struct _map_size_private {
    int mapSize;
} MapSizePrivate;

int indexOfKey(List *keys, char *key) {
    for (int index = 0; index < keys->length(keys); index++) {
        String *currentKey = (String *) keys->get(keys, index);
        if (currentKey->equalsChr(currentKey, key))
            return index;
    } return -1;
}

void _removeElement(struct _sys_unsafe_map *this, char *key) {
    MapValuePrivate *pValue = (MapValuePrivate *) this->_value;
    MapSizePrivate  *mapSize  = (MapSizePrivate  *) this->_size;

    int index = indexOfKey(pValue->keys, key);

    deleteString(pValue->keys->get(pValue->keys, index));
    pValue->keys->remove(pValue->keys, index);
    pValue->values->remove(pValue->values, index);

    mapSize->mapSize--;
}

void _set_map_value(struct _sys_unsafe_map *this, char *key, void *value) {
    MapValuePrivate *pValue = (MapValuePrivate *) this->_value;
    int index = indexOfKey(pValue->keys, key);

    if (index == -1) {
        String *newKey = newString(key);
        pValue->keys->push(pValue->keys, newKey);

        void *randomMemory = malloc(this->elementSize);
        pValue->values->push(pValue->values, randomMemory);
        free(randomMemory);

        MapSizePrivate *pSize = (MapSizePrivate *) this->_size;
        pSize->mapSize++;

        // More fast then call indexOfKey() again
        index = pValue->keys->length(pValue->keys) - 1;
    }

    pValue->values->set(pValue->values, index, value);
}

void *_get_map_value(struct _sys_unsafe_map *this, char *key) {
    MapValuePrivate *pValue = (MapValuePrivate *) this->_value;
    int index = indexOfKey(pValue->keys, key);

    if (index == -1)
        return NULL;

    return pValue->values->get(pValue->values, index);
}

int _mapLength(struct _sys_unsafe_map *this) {
    MapSizePrivate *mapSize = (MapSizePrivate *) this->_size;

    return mapSize->mapSize;
}

Map *newMap(int elementSize) {
    Map *new = (Map *) malloc(sizeof(Map));

    MapValuePrivate *mapValue = malloc(sizeof(MapValuePrivate));
    mapValue->keys   = newList(sizeof(char *));
    mapValue->values = newList(elementSize);

    MapSizePrivate *mapSize = (MapSizePrivate *) malloc(sizeof(MapSizePrivate));
    mapSize->mapSize = 0;

    new->_value      = mapValue;
    new->_size       = (void *) mapSize;
    new->elementSize = elementSize;
    new->remove      = &_removeElement;
    new->set         = &_set_map_value;
    new->get         = &_get_map_value;
    new->length      = &_mapLength;

    return new;
}

void deleteMap(Map *this) {
    MapSizePrivate  *mapSize  = (MapSizePrivate  *) this->_size;
    MapValuePrivate *mapValue = (MapValuePrivate *) this->_value;

    free(mapSize);
    deleteList(mapValue->keys);
    deleteList(mapValue->values);
    free(mapValue);
    free(this);
}