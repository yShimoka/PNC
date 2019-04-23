#include "Engine/Tools/List.h"

#include "Engine/Tools/Allocator.h"

struct USG_Node* _USG_LIST_createNode(struct USG_Node* last, struct USG_Node* next, void* contents) {
    struct USG_Node* node = (struct USG_Node*)USG_allocate(sizeof(struct USG_Node));

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

void USG_LIST_prepend(USG_List list, void* element) {
    // Check if the list is empty.
    if (*list == NULL) {
        *list = _USG_LIST_createNode(NULL, NULL, element);
    } else {
        // Get the head of the list.
        struct USG_Node* head = USG_LIST_findFirst(*list);

        // Create the new node.
        struct USG_Node* node = _USG_LIST_createNode(NULL, head, element);

        // Set the new head.
        head->pLast = node;
    }
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

int USG_LIST_insert(USG_List list, void* element, int index) {
    // Check if the list is empty.
    if (*list == NULL) {
        *list = _USG_LIST_createNode(NULL, NULL, element);
        return 0;
    } else {
        // Get the head of the list.
        struct USG_Node* head = USG_LIST_findFirst(*list);

        // Loop until the index.
        int counter = 1;
        while ((_USG_LIST_safeNext(head) != NULL) && (counter < index)) {
            head = _USG_LIST_safeNext(head);
            counter++;
        }

        // Get the elements around the new one.
        struct USG_Node *last, *next;
        last = head;
        next = head->pNext;

        // Create the new node.
        struct USG_Node* node = _USG_LIST_createNode(last, next, element);

        // Update the neighbours.
        last->pNext = node;
        if (next != NULL) next->pLast = node;

        return counter;
    }
}

int USG_LIST_size(USG_List list) {
    // Check if the list is empty.
    if (*list == NULL) {
        return 0;
    } else {
        // Get the head of the list.
        struct USG_Node* head = USG_LIST_findFirst(*list);

        // Loop until the end.
        int counter = 0;
        while (head != NULL) {
            head = _USG_LIST_safeNext(head);
            counter++;
        }

        return counter;
    }
}

int USG_LIST_find(USG_List list, void* data) {
    // Check if the list is empty.
    if (*list == NULL) {
        return -1;
    } else {
        // Get the head of the list.
        struct USG_Node* head = USG_LIST_findFirst(*list);

        // Loop until the end.
        int counter = 0;
        while ((head != NULL) && (head->pContents != data)) {
            head = _USG_LIST_safeNext(head);
            counter++;
        }

        // If we reached the end, return -1.
        if (head == NULL) counter = -1;

        return counter;
    }
}

void USG_LIST_remove(USG_List list, int index) {
    // Check if the list is empty.
    if (*list != NULL) {
        // If the list has a single item.
        if (USG_LIST_size(list) == 1) {
            // Free the last element.
            USG_deallocate(*list);
            list = NULL;
        } else {
            // Get the head of the list.
            struct USG_Node* head = USG_LIST_findFirst(*list);

            // Loop until the index.
            int counter = 0;
            while ((_USG_LIST_safeNext(head) != NULL) && (counter < index)) {
                head = _USG_LIST_safeNext(head);
                counter++;
            }

            // If the head is not null.
            if (head != NULL) {
                // Get the elements around the head.
                struct USG_Node *last, *next;
                last = head->pLast;
                next = head->pNext;

                // Free the node.
                USG_deallocate(head);

                // Update the pointers.
                last->pNext = next;
                if (next != NULL) next->pLast = last;
            }
        }
    }
}

void USG_LIST_clear(USG_List list) {
    struct USG_Node* head = USG_LIST_findFirst(*list);
    struct USG_Node* next = _USG_LIST_safeNext(head);

    while (head != NULL) {
        USG_deallocate(head);
        head = next;
        next = head != NULL ? head->pNext : NULL;
    }

    USG_deallocate(list);
}

USG_List USG_LIST_create() {
    USG_List source = (USG_List)USG_allocate(sizeof(struct USG_Node*));
    *source = NULL;

    return source;
}

void USG_LIST_forEach(USG_List list, void (*iterable)(void *)) {
    struct USG_Node* current = USG_LIST_findFirst(*list);

    // Loop.
    while (current != NULL) {
        iterable(current->pContents);

        current = _USG_LIST_safeNext(current);
    }
}

void USG_LIST_sort(USG_List list, int (*comparison)(void* a, void* b)) {
    if (*list == NULL) return;

    int swapped = 0;
    int length = USG_LIST_size(list);
    do {
        swapped = 0;
        struct USG_Node* last = USG_LIST_findFirst(*list);
        struct USG_Node* curr = last->pNext;

        for (int i = 1; i < length; i++) {
            int res = comparison(curr->pContents, last->pContents);
            if (res > 0) {
                void* tmp = curr->pContents;
                curr->pContents = last->pContents;
                last->pContents = tmp;

                swapped = 1;
            }

            last = curr;
            curr = last->pNext;
        }

    } while (swapped);
}