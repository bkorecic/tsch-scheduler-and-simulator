#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"
#include "defs.h"

/*
 * ListLength
 *
 * Returns the number of elements in the list.
 *
 */
int  ListLength(List* list)
{
    /* Just return the num_members value */
    return (list->num_members);
}

/*
 * ListEmpty
 *
 * Returns true if the list is empty. Returns false otherwise.
 *
 */
int  ListEmpty(List* list)
{
    /* Just call ListLength function to decide if it is empty or not */
    return ((ListLength(list) == 0) ? true : false);
}

/*
 * ListAppend
 *
 * Add obj after Last(). This function returns true if the operation is performed successfully and returns false otherwise.
 *
 */
int  ListAppend(List* list, void* obj)
{
    /* Lets allocate a new ListElem for the new element */
    ListElem* newElem = (ListElem *)malloc(sizeof(ListElem));

    /* Check whether malloc succeeded or not */
    if (newElem != NULL)
    {
        /* Clean the memory */
        memset(newElem, '\0', sizeof(ListElem));

        /* Store obj pointer */
        newElem->obj = obj;

        /* Get the last element */
        ListElem* lastElem = ListLast(list);

        /* Increment the number of elements */
        list->num_members++;

        /* The pointer "prev" of anchor will point to the new element */
        list->anchor.prev = newElem;

        /* The pointer "next" of the new element will point to the anchor */
        newElem->next = &(list->anchor);

        /* List is not empty */
        if ( lastElem != NULL)
        {
            /* The pointer "next" of the last element will point to the new element */
            lastElem->next = newElem;

            /* The pointer "prev" of the new element will point to the last element */
            newElem->prev = lastElem;
        }
        /* List is empty */
        else
        {
            /* The pointer "next" of anchor will point to the new element */
            list->anchor.next = newElem;

            /* The pointer "prev" of the new element will point to the anchor */
            newElem->prev = &(list->anchor);
        }

        return (true);
    }
    /* Well, no memory for you! */
    else
    {
        return (false);
    }
}

/*
 * ListPrepend
 *
 * Add obj before First(). This function returns true if the operation is performed successfully and returns false otherwise.
 *
 */
int  ListPrepend(List* list, void* obj)
{
    /* Lets allocate a new ListElem for the new element */
    ListElem* newElem = (ListElem *)malloc(sizeof(ListElem));

    /* Check whether malloc succeeded or not */
    if (newElem != NULL)
    {
        /* Clean the memory */
        memset(newElem, '\0', sizeof(ListElem));

        /* Store obj pointer */
        newElem->obj = obj;

        /* Get the first element */
        ListElem* firstElem = ListFirst(list);

        /* Increment the number of elements */
        list->num_members++;

        /* The pointer "next" of anchor will point to the new element */
        list->anchor.next = newElem;

        /* The pointer "prev" of the new element will point to the anchor */
        newElem->prev = &(list->anchor);

        /* List is not empty */
        if ( firstElem != NULL)
        {
            /* The pointer "prev" of the first element will point to the new element */
            firstElem->prev = newElem;

            /* The pointer "next" of the new element will point to the first element */
            newElem->next = firstElem;
        }
        /* List is empty */
        else
        {
            /* The pointer "prev" of anchor will point to the new element */
            list->anchor.prev = newElem;

            /* The pointers "next" of the new element will point to the anchor */
            newElem->next = &(list->anchor);
        }

        return (true);
    }
    /* Well, no memory for you! */
    else
    {
        return (false);
    }
}

/*
 * ListUnlink
 *
 * Unlink and delete elem from the list. Please do not delete the object pointed to by elem and do not check if elem is on the list.
 *
 */
void ListUnlink(List* list, ListElem* elem)
{
    /* Obtain the previous and the next elements in the list */
    ListElem* prevElem = ListPrev(list, elem);
    ListElem* nextElem = ListNext(list, elem);

    /* Check if the element is the last one in the list */
    if ((prevElem == NULL) && (nextElem == NULL))
    {
        /* Lets update the anchor, our list is empty */
        list->anchor.next = &(list->anchor);
        list->anchor.prev = &(list->anchor);
    }
    /* Check is the element is the last element in the list (but not the last one) */
    else if ((prevElem != NULL) && (nextElem == NULL))
    {
        prevElem->next = &(list->anchor);
        list->anchor.prev = prevElem;
    }
    /* Check is the element is the first element in the list (but not the last one) */
    else if ((prevElem == NULL) && (nextElem != NULL))
    {
        nextElem->prev = &(list->anchor);
        list->anchor.next = nextElem;
    }
    /* OK, we have at least 3 elements in the list, so lets connect the prevElem and the nextElem */
    else
    {
        nextElem->prev = prevElem;
        prevElem->next = nextElem;
    }

    /* Decrease the number of elements in the list */
    list->num_members--;

    /* Free the memory pointed by elem */
    free(elem);
}

/*
 * ListUnlinkAll
 *
 * Unlink and delete all elements from the list and make the list empty. Please do not delete the objects pointed to be the list elements.
 *
 */
void ListUnlinkAll(List* list)
{
    int i = 0;

    /* Find out the size of the list */
    int size = ListLength(list);

    /* Traverse the list unlink always the first element */
    for(i = 0; i < size; i++)
    {
        /* Get the first element */
        ListElem* firstElem = ListFirst(list);

        /* Unlink it! */
        ListUnlink(list, firstElem);
    }
}

/*
 * ListInsertAfter
 *
 * Insert obj between elem and elem->next. If elem is NULL, then this is the same as Append().
 * This function returns true if the operation is performed successfully and returns false otherwise. Please do not check if elem is on the list.
 *
 */
int  ListInsertAfter(List* list, void* obj, ListElem* elem)
{
    /* If elem is NULL let's Append it */
    if (elem == NULL)
    {
        return (ListAppend(list, obj));
    }
    else
    {
        /* Lets allocate a new ListElem for the new element */
        ListElem* newElem = (ListElem *)malloc(sizeof(ListElem));

        /* Check whether malloc succeeded or not */
        if (newElem != NULL)
        {
            /* Clean the memory */
            memset(newElem, '\0', sizeof(ListElem));

            /* Store obj pointer */
            newElem->obj = obj;

            /* Get the next element */
            ListElem* nextElem = ListNext(list, elem);

            /* Increment the number of elements */
            list->num_members++;

            /* The pointer "next" of elem will point to the newElem */
            elem->next = newElem;

            /* The pointer "prev" of the newElem will point to the elem */
            newElem->prev = elem;

            /* If elem is not the last one */
            if ( nextElem != NULL)
            {
                /* The pointer "prev" of nextElement will point to the newElem */
                nextElem->prev = newElem;

                /* The pointer "next" of the newElem will point to the nextElem */
                newElem->next = nextElem;
            }
            else
            {
                /* The pointer "prev" of anchor will point to the newElem */
                list->anchor.prev = newElem;

                /* The pointers "next" of the newElem will point to the anchor */
                newElem->next = &(list->anchor);
            }

            return (true);
        }
        /* Well, no memory for you! */
        else
        {
            return (false);
        }
    }
}

/*
 * ListInsertBefore
 *
 * Insert obj between elem and elem->prev. If elem is NULL, then this is the same as Prepend().
 * This function returns true if the operation is performed successfully and returns false otherwise. Please do not check if elem is on the list.
 *
 */
int  ListInsertBefore(List* list, void* obj, ListElem* elem)
{
    /* If elem is NULL lets Prepend it */
    if (elem == NULL)
    {
        return (ListPrepend(list, obj));
    }
    else
    {
        /* Lets allocate a new ListElem for the new element */
        ListElem* newElem = (ListElem *)malloc(sizeof(ListElem));

        /* Check whether malloc succeeded or not */
        if (newElem != NULL)
        {
            /* Store obj pointer */
            newElem->obj = obj;

            /* Get the prev element */
            ListElem* prevElem = ListPrev(list, elem);

            /* Increment the number of elements */
            list->num_members++;

            /* The pointer "prev" of elem will point to the newElem */
            elem->prev = newElem;

            /* The pointer "next" of the newElem will point to the elem */
            newElem->next = elem;

            /* If elem is not the first one */
            if ( prevElem != NULL)
            {
                /* The pointer "next" of prevElem will point to the newElem */
                prevElem->next = newElem;

                /* The pointer "prev" of the newElem will point to the prevElem */
                newElem->prev = prevElem;
            }
            else
            {
                /* The pointer "next" of anchor will point to the newElem */
                list->anchor.next = newElem;

                /* The pointers "prev" of the newElem will point to the anchor */
                newElem->prev = &(list->anchor);
            }

            return (true);
        }
        /* Well, no memory for you! */
        else
        {
            return (false);
        }
    }
}

/*
 * ListFirst
 *
 * Returns the first list element.
 *
 */
ListElem *ListFirst(List* list)
{
    /* The first element is the next element pointed by the anchor. But we need to check if the link is not empty. In this case, return NULL */
    return ((ListEmpty(list) == true) ? NULL : (list->anchor.next));
}

/*
 * ListLast
 *
 * Returns the last list element.
 *
 */
ListElem *ListLast(List* list)
{
    /* The last element is the previous element pointed by the anchor. But we need to check if the link is not empty. In this case, return NULL */
    return ((ListEmpty(list) == true) ? NULL : (list->anchor.prev));
}

/*
 * ListNext
 *
 * Returns elem->next. Please do not check if elem is on the list.
 *
 */
ListElem *ListNext(List* list, ListElem* elem)
{
    /* If elem is the last element in the list, it must return NULL. Otherwise, the pointer "next" of elem */
    return ((ListLast(list) == elem) ? NULL : (elem->next));
}

/*
 * ListPrev
 *
 * Returns elem->prev. Please do not check if elem is on the list.
 *
 */
ListElem *ListPrev(List* list, ListElem* elem)
{
    /* If elem is the first element in the list, it must return NULL. Otherwise, the pointer "prev" of elem */
    return ((ListFirst(list) == elem) ? NULL : (elem->prev));
}

/*
 * ListFind
 *
 * Returns the list element elem such that elem->Obj() == obj. Returns NULL if no such element can be found.
 *
 */
ListElem *ListFind(List* list, void* obj)
{
    int i = 0;

    /* Get the first element in the list */
    ListElem *elem = ListFirst(list);

    /* Check if list is not empty */
    if (elem != NULL)
    {
        /* Traverse the list */
        while(i < ListLength(list))
        {
            /* If obj was found, return it! */
            if (elem->obj == obj)
            {
                return (elem);
            }

            /* Get the next element */
            elem = elem->next;
            i++;
        }
    }

    /* Has not found element or list is empty */
    return (NULL);
}

/*
 * ListInit
 *
 * Initialize the list into an empty list. Returns true if all is well and returns false if there is an error initializing the list.
 *
 */
void ListInit(List* list)
{
    /* First, let zero the number of elements in the list */
    list->num_members = 0;

    /* Now lets initialize of pointers (next and prev) of the anchor. They should point to the anchor itself, since we have no element present in the list */
    list->anchor.next = &(list->anchor);
    list->anchor.prev = &(list->anchor);

    /* Obj of anchor must be initialized as NULL */
    list->anchor.obj = NULL;
}
