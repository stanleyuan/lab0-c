/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (!q)
        return q;
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    if (q) {
        if (q->head) {
            while (q->head) {
                list_ele_t *counter = q->head;
                q->head = q->head->next;
                free(counter->value);
                free(counter);
            }
        }
        free(q);
    }
    return;
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    /* What should you do if the q is NULL? */
    if (q) {
        list_ele_t *newh;
        char *news;
        int s_len = strlen(s) + 1;
        newh = malloc(sizeof(list_ele_t));
        /* Don't forget to allocate space for the string and copy it */
        /* What if either call to malloc returns NULL? */
        if (newh) {
            news = malloc(s_len * sizeof(char));
            if (news) {
                // test later
                memset(news, '\0', s_len);
                strcpy(news, s);
                newh->next = q->head;
                newh->value = news;

                if (!q->head)
                    q->tail = newh;
                q->head = newh;
                q->size += 1;
                return true;
            }
            free(newh);
        }
    }
    return false;
}

/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */

    if (q) {
        list_ele_t *tmp = malloc(sizeof(list_ele_t));
        char *news;
        int s_len = strlen(s) + 1;

        if (tmp) {
            news = malloc(s_len * sizeof(char));
            if (news) {
                memset(news, '\0', s_len);
                strcpy(news, s);
                tmp->value = news;
                tmp->next = NULL;

                q->size += 1;
                if (!q->tail) {
                    q->head = tmp;
                    q->tail = tmp;
                } else {
                    q->tail->next = tmp;
                    q->tail = tmp;
                }
                return true;
            }
            free(tmp);
        }
    }

    return false;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* You need to fix up this code. */
    if (q && q->head) {
        list_ele_t *tmp = q->head;
        memset(sp, '\0', bufsize);
        if (sp)
            strncpy(sp, tmp->value, bufsize - 1);
        q->head = q->head->next;
        if (!q->head)
            q->tail = q->head;
        free(tmp->value);
        free(tmp);
        q->size -= 1;
        return true;
    }
    return false;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if (q)
        return q->size;
    return 0;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* You need to write the code for this function */

    if (q && q->head && q->head->next) {
        list_ele_t *left, *right;

        right = q->head->next;
        left = q->head;
        q->tail = q->head;
        q->tail->next = NULL;
        while (right) {
            q->head = right;
            right = q->head->next;
            q->head->next = left;
            left = q->head;
        }
    }
}
