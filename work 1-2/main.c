#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 100

typedef struct {
    int key;
} element;

typedef struct {
    element heap[MAX_ELEMENT];
    int heap_size;
} HeapType;

void init(HeapType *h) {
    h -> heap_size = 0;
}

void insert_max_heap(HeapType *h, element item) {
    int i;
    i = ++(h -> heap_size);
    
    while ((i != 1) && (item.key > h -> heap[i / 2].key)) {
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
        if ((child < h -> heap_size) && (h -> heap[child].key) < (h -> heap[child + 1].key)) {
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
        printf("< %d > ",h -> heap[i].key);
    }
    printf("\n");
}

void delete_element(HeapType *h, int number) {
    int parent, child;
    element item, temp;
    
    for (int i = 1; i <= h -> heap_size; i++) {
        if ((h -> heap[i].key) == number) {
            parent = i;
            child = i * 2;
            break;
        }
    }
    
    item = h -> heap[parent];
    temp = h -> heap[(h -> heap_size)--];
    
    while (child <= h -> heap_size) {
        if ((child < h -> heap_size) && (h -> heap[child].key) < (h -> heap[child + 1].key)) {
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
}
// 처음에는 기존 max_heap에서 사용하는 delete_max_heap 함수를 참고해 문제 해결하려 하여 1차원적인 생각으로 item = h -> heap[parent]; 부분에 parent대신 number를 넣어버렸습니다. 그러나 40이라는 값이 아닌 40이 있는 index를 찾아야 한다는 것을 깨달았고, 반복문으로 히프트리를 돌며 if문을 이용해 40이 있는 곳의 index를 찾고 그 index를 부모 노드로 하여 문제를 해결했습니다.

int main(void) {
    element e[9]={{10},{40},{30},{5},{12},{6},{15},{9},{60}};
    HeapType heap1;
    int i;
        
    init(&heap1);
    for (i = 0; i < 9; i++) {
        insert_max_heap(&heap1, e[i]);
    }
    print_heap(&heap1);
    
    int num = 40;
    delete_element(&heap1, num);        //40이 삭제되었는지 체크한다
    print_heap(&heap1);
    
    //max heap인지 체크하는 과정
    for(i = 0; i < 8; i++){
        element a = delete_max_heap(&heap1);
        printf("%d ", a.key);
    }
    return 0;
}
