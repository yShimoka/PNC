#ifndef __USAGI_LIST_H__
#define __USAGI_LIST_H__

#include <stdlib.h>

/**
 * Chained list.
 */
struct USG_Node {
    // Elements next to this node.
    struct USG_Node* pLast;
    struct USG_Node* pNext;

    // Contents of the node.
    void* pContents;
};

typedef struct USG_Node** USG_List;

struct USG_Node* USG_LIST_findFirst(struct USG_Node* node);

struct USG_Node* USG_LIST_findLast(struct USG_Node* node);

void USG_LIST_append(USG_List list, void* element);

void USG_LIST_clear(USG_List list);

USG_List USG_LIST_create();

void USG_LIST_forEach(USG_List list, void (*iterable)(void *));

#endif /* __USAGI_LIST_H__ */