/*
 * rpn-stack.c --
 */

/** @file */

#include "rpn-stack.h"
#include <stdio.h>
#include <stdlib.h>

typedef unsigned char byte;

/*
 * Prefixing all global symbols with rpn_ to avoid clashes with
 * symbols defined in the C library (e.g., signal stack definitions)
 * since we use this stack for building an RPN calculator.
 */
typedef struct _rpn_stack
{
    int top;
    byte *storage;
    int elemSize;
    int maxElements;
}rpn_stack_t;

/**
 * \brief Create a new empty stack.
 *
 * \return A pointer acting as a handle for the new stack.
 */
rpn_stack_t* rpn_stack_new()
{
    rpn_stack_t *s = malloc(sizeof(rpn_stack_t));
    byte *storage;

    storage = (byte *)malloc(8 * 100);
    if(storage == NULL) 
    {
        fprintf(stderr, "Insufficient memory to initialize stack.\n");
        exit(1);
    }

    s->top = 0;
    s->maxElements = 100;
    s->elemSize = 8;
    s->storage = storage;
    return s;
}


/**
 * \brief Push data (allocated by the caller) on the stack.
 *
 * \param s The stack to push data on.
 * \param data The pointer to data to be pushed on the stack.
 */
void rpn_stack_push(rpn_stack_t *s, void *data)
{
    if(s->top == s->maxElements) 
    {
        fprintf(stderr, "Element can not be pushed: Stack is full.\n");
        exit(1);
    }

    int start = s->top * s->elemSize, i;

    for(i = 0; i < s->elemSize; i++) 
    {
        *(s->storage + start + i) = *((byte *)(data + i));
    }

    s->top = s->top + 1;
}

/**
 * \brief Pop data from the top of the stack.
 *
 * \param s The stack to pop data from.
 * \return The data or NULL if the stack is empty.
 */
void* rpn_stack_pop(rpn_stack_t *s)
{
    if(rpn_stack_empty(s)) 
    {
        fprintf(stderr, "Can not pop from an empty stack.\n");
        exit(1);
    }

    void *elem = rpn_stack_peek(s);
    s->top = s->top - 1;

    return elem;
}

/**
 * \brief Peek on the data at the top of the stack.
 *
 * \param s The stack to peek on.
 * \return The data or NULL if the stack is empty.
 */
void* rpn_stack_peek(rpn_stack_t *s)
{
    if(rpn_stack_empty(s)) 
    {
        fprintf(stderr, "Can not pop from an empty stack.\n");
        exit(1);
    }

    int start = (s -> top - 1) * s -> elemSize, i;
    byte *elem;
    elem = (byte *)malloc(s -> elemSize);

    for(i = 0; i < s-> elemSize; i++) 
    {
        *(elem + i) = *(s->storage + start + i);
    }

    return (void *)elem;
}

/**
 * \brief Test whether a stack is empty.
 *
 * \param s The stack to test.
 * \return A non-zero value if the stack is empty, 0 otherwise.
 */
int rpn_stack_empty(rpn_stack_t *s)
{
    return (s->top == 0);
}

/**
 * \brief Delete a stack.
 *
 * \param s The stack to delete.
 */
void rpn_stack_del(rpn_stack_t *s)
{
    free(s->storage);
    s->top = 0;
}