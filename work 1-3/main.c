#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 200 

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

//left_child of i = i * k - (k - 2)
//parent index of l = (l + k - 2) / k

// insert 하는 부분은 교수님께서 제공해 주신 식을 이용해 기존 max_heap 코드에서 간단한 수정으로 해결하였지만, delete 부분은 머리속에 잘 그려지지 않아 직접 노트에 구조를 그려보며 알고리즘을 생각했습니다. 직접 그리며 생각해 보니 정리가 더 잘 되었고, 따라서 for 문을 통해 자식을 모두 확인해 크기를 비교하고 제일 큰 자식을 찾아 그 자식의 index를 child에 넣었습니다.

void insert_max_heap(HeapType *h, element item, int k) {
    //k-max-heap(자식이 k개인 완전 k-nary tree를 이용한 heap))이 되도록 자료를 입력
    int i;
    i = ++(h -> heap_size);
    
    while ((i != 1) && (item.key > h -> heap[(i + k - 2) / k].key)) {
        h -> heap[i] = h -> heap[(i + k - 2) / k];
        i = (i + k - 2) / k;
    }
    h -> heap[i] = item;
}

element delete_max_heap(HeapType *h, int k) {
    //k-max-heap에서 가장 key가 큰 원소를 반환한다. 반환 후 k-max-heap을 유지한다.
    int parent, child;
    element item, temp;
    
    item = h -> heap[1];
    temp = h -> heap[(h -> heap_size)--];
    parent = 1;
    child = 2;
    
    while (child <= h -> heap_size) {
        int max = h->heap[child].key;
        int count = 1;
        
        for (int i = 1; i < k ; i++) {
           if (child + count > h->heap_size) {
              break;
           }
           if (max < h->heap[child + count].key) {
              max = h->heap[child + count].key;
              child += count;
              count = 1;
           }
           else {
           count++;
           }
        }

        if (temp.key >= h -> heap[child].key) {
            break;
        }
        
        h -> heap[parent] = h -> heap[child];
        parent = child;
        child = child * k - (k - 2);
    }
    h -> heap[parent] = temp;
    
    return item;
}

void heap_sort(element a[], int n, int k) { //k-max-heap을 이용하여 정렬한다.
    int i;
    HeapType h;
    init(&h);
    
    for (i = 0; i < n; i++) {
        insert_max_heap(&h, a[i], k);
    }
    
    for (i = n-1; i >= 0; i--) {
        a[i] = delete_max_heap(&h, k);
    }
}

void print_heap(HeapType *h) {
    for (int i = 1; i <= h -> heap_size; i++) {
        printf("< %d > ", h -> heap[i].key);
    }
    printf("\n");
}
    
int main(void) {
    
    // k=3일 때 배열에 3진 최대히프에 { 10,8,8,9,5,4,3, 2,1,3, 6,7,4} 대하여 삭제 연산이 맞게 되는지 테스트해 보시오
    element e[MAX_ELEMENT] = { 10, 8, 8, 9, 5, 4, 3, 2, 1, 3, 6, 7, 4 };
    HeapType heap;
    init(&heap);
    int num = 13;
    int k = 3;
    
    printf("insert\n");
    for (int i = 0; i < num; i++) {
        insert_max_heap(&heap, e[i], k);
    }
    print_heap(&heap);
    printf("\n");
    
    
    printf("delete\n");
    for (int i = 0; i < num; i++) {
        delete_max_heap(&heap, k);
        print_heap(&heap);
    }
    
    // 사이즈 10이상인 정렬 되지 않은 정수형 배열을 위의 heap_sort를 이용하여정렬하시오.
    printf("sort\n");
    heap_sort(e, num, k);
    for (int i = 0; i < num; i++) {
        printf("%d ", e[i].key);
    }
    
    // k값을 여러 가지 경우로 해서 test해 보시오.
    element e2[MAX_ELEMENT] = { 4, 6, 2, 10, 9, 3, 5, 8, 1, 2, 3 };
    HeapType heap2;
    init(&heap2);
    num = 11;
    k = 4;
    
    printf("\n\ninsert\n");
    for (int i = 0; i < num; i++) {
        insert_max_heap(&heap2, e2[i], k);
    }
    print_heap(&heap2);
    printf("\n");
    
    
    printf("delete\n");
    for (int i = 0; i < num; i++) {
        delete_max_heap(&heap2, k);
        print_heap(&heap2);
    }
    
    printf("sort\n");
    heap_sort(e2, num, k);
    for (int i = 0; i < num; i++) {
        printf("%d ", e2[i].key);
    }
    printf("\n");
    
    return 0;
}
