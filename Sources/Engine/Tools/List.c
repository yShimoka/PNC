#include "Engine/Tools/List.h"

struct USG_Node* _USG_LIST_createNode(struct USG_Node* last, struct USG_Node* next, void* contents) {
    struct USG_Node* node = (struct USG_Node*)malloc(sizeof(struct USG_Node));

    node->pLast = last;
    node->pNext = next;
    node->pContents = contents;

    return node;
}

struct USG_Node* _USG_LIST_safeNext(struct USG_Node* node) {
    if (node == NULL) return NULL;
    else return node->pNext;
}

struct USG_Node* _USG_LIST_safeLast(struct USG_Node* node) {
    if (node == NULL) return NULL;
    else return node->pLast;
}

struct USG_Node* USG_LIST_findFirst(struct USG_Node* node) {
    if (node == NULL) return NULL;

    struct USG_Node* current = node;

    while (_USG_LIST_safeLast(current) != NULL) current = _USG_LIST_safeLast(current);

    return current;
}

struct USG_Node* USG_LIST_findLast(struct USG_Node* node) {
    if (node == NULL) return NULL;

    struct USG_Node* current = node;

    while (_USG_LIST_safeNext(current) != NULL) current = _USG_LIST_safeNext(current);

    return current;
}

void USG_LIST_append(USG_List list, void* element) {
    // Check if the list is empty.
    if (*list == NULL) {
        *list = _USG_LIST_createNode(NULL, NULL, element);
    } else {
        // Get the end of the list.
        struct USG_Node* tail = USG_LIST_findLast(*list);

        // Create the new node.
        struct USG_Node* node = _USG_LIST_createNode(tail, NULL, element);

        // Set the new tail.
        tail->pNext = node;
    }
}

void USG_LIST_clear(USG_List list) {
    struct USG_Node* head = USG_LIST_findFirst(*list);
    struct USG_Node* next = _USG_LIST_safeNext(head);

    while (head != NULL) {
        free(head);
        head = next;
        next = head != NULL ? head->pNext : NULL;
    }
}

USG_List USG_LIST_create() {
    USG_List source = (USG_List)malloc(sizeof(struct USG_Node*));
    *source = NULL;

    return source;
}

void USG_LIST_forEach(USG_List list, void (*iterable)(void *)) {
    struct USG_Node* current = *list;

    // Loop.
    while (current != NULL) {
        iterable(current->pContents);

        current = _USG_LIST_safeNext(current);
    }
}