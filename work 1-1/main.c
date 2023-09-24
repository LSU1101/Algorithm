#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_ELEMENT 200

typedef struct {
    char key[20];
    int id;
} element;

typedef struct {
    element heap[MAX_ELEMENT];
    int heap_size;
} HeapType;

HeapType *create(void) {
    return (HeapType*)malloc(sizeof(HeapType));
}

void init(HeapType *h) {
    h -> heap_size = 0;
}

void insert_max_heap(HeapType *h, element item) {
    int i;
    i = ++(h -> heap_size);
    
    while ((i != 1) && (strcmp(item.key, h -> heap[i / 2].key)) > 0) {
        h -> heap[i] = h -> heap[i / 2];
        i /= 2;
    }
    h -> heap[i] = item;
}

element delete_max_heap(HeapType *h) {
    int parent, child;
    element item, temp;
    
    item = h -> heap[1];
    temp = h -> heap[(h -> heap_size)--];
    parent = 1;
    child = 2;
    
    while (child <= h -> heap_size) {
        if ((child < h -> heap_size) && (strcmp(h -> heap[child].key, h -> heap[child + 1].key)) < 0) {
            child++;
        }
        if (temp.key >= h -> heap[child].key) {
            break;
        }
        
        h -> heap[parent] = h -> heap[child];
        parent = child;
        child *= 2;
    }
    h -> heap[parent] = temp;
    return item;
}

void print_heap(HeapType *h) {
    for(int i = 1; i <= h -> heap_size; i++) {
        printf("< %s > ",h -> heap[i].key);
    }
    printf("\n");
}

int main(void) {
    element e1 = { "egg", 1234 }, e2 = { "structure", 321 }, e3 = { "sand", 456 };
    element e4, e5, e6;
    HeapType *heap;
    
    heap = create();
    init(heap);
    
    printf("insert\n");
    insert_max_heap(heap, e1);
    print_heap(heap);
    
    insert_max_heap(heap, e2);
    print_heap(heap);
    
    insert_max_heap(heap, e3);
    print_heap(heap);
    printf("\n");
    
    
    printf("delete\n");
    e4 = delete_max_heap(heap);
    printf("< %s > ", e4.key);
    e5 = delete_max_heap(heap);
    printf("< %s > ", e5.key);
    e6 = delete_max_heap(heap);
    printf("< %s > \n", e6.key);
    
    free(heap);
    return 0;
}

