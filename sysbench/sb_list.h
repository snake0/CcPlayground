#ifndef SB_LIST_H
#define SB_LIST_H

/* linked list only for statically allocated struct */

typedef struct _list_item {
  struct _list_item *next;
} sb_list_item_t;

typedef struct _list {
  sb_list_item_t *head, *tail;
} sb_list_t;

#ifndef offsetof
# define offsetof(type, member) ((size_t) &((type *)0)->member)
#endif

#define sb_list_init(l)  do { (l).head = (l).tail = NULL;} while(0)

#define sb_list_add(l, entry) do {\
    if ((l).head ==  NULL) {\
        (l).head = (l).tail = &((entry).listitem); \
        (entry).listitem.next = NULL; \
    } \
    else { \
        (l).tail->next = &((entry).listitem); \
        (l).tail = &((entry).listitem); \
    } \
} while(0)

#define sb_list_for_each(list)  \
    sb_list_item_t *pos; \
    for ((pos) = (list).head; (pos); (pos) = (pos)->next)

#define sb_list_entry(pos, type) \
    ((type *)(void *)(((char *)(pos) - offsetof(type, listitem))))

#endif //SB_LIST_H