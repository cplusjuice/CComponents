#ifndef __C_COMPONENTS_H__
#define __C_COMPONENTS_H__

#define CCOMP_V_MA 0
#define CCOMP_V_MI 0
#define CCOMP_V_PA 1

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdbool.h>

#include "foreach.h"

#ifdef delete
#error Macro delete already defined
#endif /* delete */
#define delete(object) (object->_class->delete(object))

typedef enum _ccomp_classtype {
    INTERFACE_CCOBJECT,
    INTERFACE_LIST,
    INTERFACE_MAP,
    CLASS_ARRAY_LIST,
    CLASS_LINKED_LIST,
    CLASS_ARRAY_MAP,
    CLASS_STRING,
} ClassType;

typedef struct _ccomp_class {
    ClassType classType;
    void (*delete)(void *instance);
} Class;

typedef void * v_private;

/**
 * Interfaces pre-declaration
 */

typedef struct _ccomp_object CCObject; // For case library user will reserves name Object
typedef struct _ccomp_list List;
typedef struct _ccomp_map Map;

/**
 * Classes pre-declaration
 */

typedef struct _ccomp_array_list_class ClassArrayListType;
typedef struct _ccomp_array_list ArrayList;
typedef struct _ccomp_linked_list_class ClassLinkedListType;
typedef struct _ccomp_linked_list LinkedList;
typedef struct _ccomp_array_map_class ClassArrayMapType;
typedef struct _ccomp_array_map ArrayMap;
typedef struct _ccomp_string_class ClassStringType;
typedef struct _ccomp_string String;

struct _ccomp_object {
    ClassType interfaceType;
    String *(*toString)(void *this);
    void *(*copy)(void *this);
};

struct _ccomp_list {
    ClassType interfaceType;
    void (*add)(void *this, void *value);
    void (*remove)(void *this, unsigned long int index);
    void (*set)(void *this, unsigned long int index, void *value);
    void *(*get)(void *this, unsigned long int index);
    unsigned long int (*length)(void *this);

    CCObject _impl_CCObject;
};

struct _ccomp_map {
    ClassType interfaceType;
    void (*remove)(void *this, char *key);
    void (*set)(void *this, char *key, void *value);
    void *(*get)(void *this, char *_value);
    unsigned long int (*length)(void *this);

    CCObject _impl_CCObject;
};

/** 
 * ArrayList
 */

extern Class classArrayList;
extern ClassArrayListType ClassArrayList;

struct _ccomp_array_list_class {
    void (*include)(void *this, void **, unsigned long int);

    List _impl_List;
};

struct _ccomp_array_list {
    Class *_class;
    ClassArrayListType *class;
    v_private _private;
};

extern ArrayList *createArrayList();

#ifdef CreateArrayList
#error Macro CreateArrayList already defined
#endif /* CreateArrayList */
#define CreateArrayList createArrayList

/**
 * LinkedList
 */

extern Class classLinkedList;
extern ClassLinkedListType ClassLinkedList;

struct _ccomp_linked_list_class {
    void (*addFirst)(void *this, void *);
    void *(*getFirst)(void *this);
    void *(*getLast)(void *this);
    void (*removeFirst)(void *this);
    void (*removeLast)(void *this);

    List _impl_List;
};

struct _ccomp_linked_list {
    Class *_class;
    ClassLinkedListType *class;
    v_private _private;
};

extern LinkedList *createLinkedList();

#ifdef CreateLinkedList
#error Macro CreateLinkedList already defined
#endif /* CreateLinkedList */
#define CreateLinkedList createLinkedList

/**
 * ArrayMap
 */

extern Class classArrayMap;
extern ClassArrayMapType ClassArrayMap;

struct _ccomp_array_map_class {
    Map _impl_Map;
};

struct _ccomp_array_map {
    Class *_class;
    ClassArrayMapType *class;
    v_private _private;
};

extern ArrayMap *createArrayMap();

#ifdef CreateArrayMap
#error Macro CreateArrayMap already defined
#endif /* CreateArrayMap */
#define CreateArrayMap createArrayMap

/**
 * String
 */

/**
 * The structure that stores the match (for the match method of String).
 * Released in all cases through free();
 */
typedef struct _sys_string_match {
    int begin;
    int end;
} StringMatch;

extern Class classString;
extern ClassStringType ClassString;

struct _ccomp_string_class {
    char *(*getValue)(void *this);
    void (*setValue)(void *this, char *);
    void (*add)(void *this, char *);
    String *(*sub)(void *this, int, int);
#ifndef _WIN32
    void (*replace)(void *this, char *, char *);
    void (*replaceFirst)(void *this, char *, char *);
    StringMatch *(*match)(void *this, char *, int);
    ArrayList *(*split)(void *this, char *);
#endif
    void (*addLong)(void *this, long int);
    void (*addULong)(void *this, unsigned long int);
    int (*toInt)(void *this);
    char (*charAt)(void *this, int);
    int (*length)(void *this);
    bool (*equals)(void *this, String *);
    bool (*equalsChr)(void *this, char *);
    
    CCObject _impl_CCObject;
};

struct _ccomp_string {
    Class *_class;
    ClassStringType *class;
    v_private _private;
};

extern String *createStringChar(char *);
extern String *createStringLong(long int);
extern String *createStringULong(unsigned long int);

#ifdef CreateString
#error Macro CreateString already defined
#endif /* CreateString */
#define CreateString(X)      \
    _Generic((X),         \
    char *   : createStringChar,\
    int      : createStringLong,\
    long int : createStringLong,\
    unsigned long int : createStringULong,\
    unsigned int      : createStringULong\
    ) (X)

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __C_COMPONENTS_H__ */
