#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

/* Notice: sometimes, Cppcheck would find the potential NULL pointer bugs,
 * but some of them cannot occur. You can suppress them by adding the
 * following line.
 *   cppcheck-suppress nullPointer
 */


/* Create an empty queue */
struct list_head *q_new()
{
    struct list_head *q = malloc(sizeof(struct list_head));

    /* If q didn't  allocate space. */
    if (!q)
        return NULL;

    /* Initialize a list_head structure from Linux Kernel API.*/
    INIT_LIST_HEAD(q);
    return q;
}

/* Free all storage used by queue */
void q_free(struct list_head *head)
{
    if (!head)
        return;

    struct list_head *current = head->next;
    while (head != current) {
        element_t *e = container_of(current, element_t, list);
        current = current->next;
        q_release_element(e);
    }

    free(container_of(head, element_t, list));
}

/* Insert an element at head of queue */
bool q_insert_head(struct list_head *head, char *s)
{
    if (!head)
        return false;

    element_t *el = malloc(sizeof(element_t));
    if (!el)
        return false;

    char *c = strdup(s);
    if (!c) {
        free(el);
        return false;
    }

    el->value = c;
    list_add(&el->list, head);
    return true;
}

/* Insert an element at tail of queue */
bool q_insert_tail(struct list_head *head, char *s)
{
    if (!head)
        return false;

    element_t *el = malloc(sizeof(element_t));
    if (!el)
        return false;

    char *c = strdup(s);
    if (!c) {
        free(el);
        return false;
    }

    el->value = c;
    list_add_tail(&el->list, head);
    return true;
}

/* Remove an element from head of queue */
element_t *q_remove_head(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head || list_empty(head))
        return NULL;

    element_t *target = list_first_entry(head, element_t, list);
    strncpy(sp, target->value, bufsize - 1);
    sp[bufsize - 1] = '\0';

    list_del(head->next);

    return target;
}

/* Remove an element from tail of queue */
element_t *q_remove_tail(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head || list_empty(head))
        return NULL;

    element_t *target = list_last_entry(head, element_t, list);
    strncpy(sp, target->value, bufsize - 1);
    sp[bufsize - 1] = '\0';

    list_del(head->prev);

    return target;
}

/* Return number of elements in queue */
int q_size(struct list_head *head)
{
    if (!head || list_empty(head))
        return 0;

    int len = 0;
    struct list_head *li;
    list_for_each (li, head)
        len++;

    return len;
}

/* Delete the middle node in queue */
bool q_delete_mid(struct list_head *head)
{
    // https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/
    if (!head || list_empty(head))
        return false;

    struct list_head *fast = head->next, *slow = head->next;
    while (fast != head && fast->next != head) {
        fast = fast->next->next;
        slow = slow->next;
    }

    list_del(slow);
    q_release_element(list_entry(slow, element_t, list));
    return true;
}

/* Delete all nodes that have duplicate string */
bool q_delete_dup(struct list_head *head)
{
    // https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
    if (!head || list_empty(head))
        return false;

    struct list_head *left, *right;
    list_for_each_safe (left, right, head) {
        element_t *l_el = list_entry(left, element_t, list),
                  *r_el = list_entry(right, element_t, list);
        if (left->next != head && strcmp(l_el->value, r_el->value) == 0) {
            list_del(left);
            q_release_element(l_el);
        }
    }
    return true;
}

/* Swap every two adjacent nodes */
void q_swap(struct list_head *head)
{
    // https://leetcode.com/problems/swap-nodes-in-pairs/
}

/* Reverse elements in queue */
void q_reverse(struct list_head *head)
{
    if (!head || list_empty(head))
        return;

    struct list_head *left, *right;
    list_for_each_safe (left, right, head) {
        left->next = left->prev;
        left->prev = right;
    }
    left->next = left->prev;
    left->prev = right;
}

/* Reverse the nodes of the list k at a time */
void q_reverseK(struct list_head *head, int k)
{
    // https://leetcode.com/problems/reverse-nodes-in-k-group/
}

/* Sort elements of queue in ascending/descending order */
void q_sort(struct list_head *head, bool descend) {}

/* Remove every node which has a node with a strictly less value anywhere to
 * the right side of it */
int q_ascend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Remove every node which has a node with a strictly greater value anywhere to
 * the right side of it */
int q_descend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Merge all the queues into one sorted queue, which is in ascending/descending
 * order */
int q_merge(struct list_head *head, bool descend)
{
    // https://leetcode.com/problems/merge-k-sorted-lists/
    return 0;
}
