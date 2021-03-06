/**
 *	(C) Copyright 2007-2008, Magnus Gal�en
 *
 *	dlist.h: List-container.
 */

#ifndef _DLIST_H_
#define _DLIST_H_

#include <stdarg.h>

#include "dcontainer.h"


#define list_val(_var) (((_list_node_*)(_var).node)->val)


/*
typedef struct list_iterator list_iterator;

struct list_iterator
{
    value		val;
    list_iterator	*previous, *next;
};
*/
typedef struct _list_node_ _list_node_;

struct _list_node_
{
    value		val;
    _list_node_		*previous, *next;
};


container* list_container( container *C );

//extern inline int list_size( container *C );

extern inline void list_pushback( container *C, ... );
extern inline void list_pushfront( container *C, ... );
extern inline void list_insert( container *C, const iterator it, ... );

extern inline void list_pushback_value( container *C, value v );

extern inline void list_erase( container *C, const iterator it );
extern inline void list_empty( container *C );
/*
extern inline iterator list_begin( container *C );
extern inline iterator list_end( container *C );
extern inline iterator list_next( const iterator old_it );
extern inline iterator list_previous( const iterator old_it );
*/


typedef struct
{
    container		*C;
    _list_node_		*head, *tail;
    int			size;
} list_container_priv;


static inline iterator list_begin( container *C )
{
    iterator	it;

    it.node = ((list_container_priv*)C->priv)->head;
    it.valid = (it.node==NULL ? 0 : 1);

    return it;
}

static inline iterator list_end( container *C )
{
    iterator	it;

    it.node = ((list_container_priv*)C->priv)->tail;
    it.valid = (it.node==NULL ? 0 : 1);

    return it;
}


static inline iterator list_next( const iterator old_it )
{
    iterator	it;

    it.node = ((_list_node_*)old_it.node)->next;
    if (it.node == NULL) it.valid = 0;
    else it.valid = 1;

    return it;
}


static inline iterator list_previous( const iterator old_it )
{
    iterator	it;

    it.node = ((_list_node_*)old_it.node)->previous;
    if (it.node == NULL) it.valid = 0;
    else it.valid = 1;

    return it;
}


static inline int list_size( container *C )
{
    return ((list_container_priv*)C->priv)->size;
}



#endif	// _DLIST_H_
