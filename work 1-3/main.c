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
    //
}
//left_child of i = i * k - (k - 2)
//parent index of l = (l + k - 2) / k

void insert_max_heap(HeapType *h, element item, int k) {
    //k-max-heap(자식이 k개인 완전 k-nary tree를 이용한 heap))이 되도록 자료를
    //입력
}

element delete_max_heap(HeapType *h, int k) {
    //k-max-heap에서 가장 key가 큰 원소를 반환한다. 반환 후 k-max-heap을 유지 //한다
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
        printf("< %d >\n", h -> heap[i].key);
    }
    printf("\n");
}
    
int main(void) {
        // k=3일 때 배열에 3진 최대히프에 { 10,8,8,9,5,4,3, 2,1,3, 6,7,4} 대하여 삭제 연산이 맞 //게 되는지 테스트해 보시오
        //사이즈 10이상인 정렬 되지 않은 정수형 배열을 위의 heap_sort를 이용하여
        //정렬하시오. k값을 여러 가지 경우로 해서 test해 보시오.
}
