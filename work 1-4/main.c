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
        for (int i = 1; i <= k; i++) {
            if ((child < h -> heap_size) && (h -> heap[child].key) < (h -> heap[child + i].key)) {
                child += i;
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

int kSmallNumber(element e[], int k, int num) {
    HeapType heap;
    init(&heap);
    int answer = 0;
    element kSmallNumber;
        
    printf("\n\ninsert\n");
    for (int i = 0; i < k; i++) {
        insert_max_heap(&heap, e[i], k - 1);
    }
    print_heap(&heap);
    printf("\n");
    
    kSmallNumber = delete_max_heap(&heap, k - 1);
    answer = kSmallNumber.key;
    
    for (int i = k; i < num; i++) {
        if (answer > e[i].key) {
            insert_max_heap(&heap, e[i], k - 1);
            kSmallNumber = delete_max_heap(&heap, k - 1);
            answer = kSmallNumber.key;
        }
    }
    
    return answer;
}
    
int main(void) {
    
    element e[MAX_ELEMENT] = { 2, 5, 4, 7, 6, 9};
    int k;
    int num = 6;
    while (1) {
        printf("몇 번째로 작은 수를 찾고 싶나요?>> ");
        scanf("%d", &k);
        
        if (k < num) {
            break;
        }
        printf("현재 배열에 %d개의 숫자가 있습니다. %d이하의 수를 입력해주세요.\n", num, num);
    }
    
    
    printf("%d번 째로 작은 숫자는 %d\n", k, kSmallNumber(e, k, num));
    
    
    return 0;
}

// 3번에서 해결한 코드를 활용해 문제를 풀었습니다. 설명 동영상에서 알려주신 알고리즘대로 k번 째로 작은 수를 찾고자 하면 배열에서 k번 째 까지 max_heap으로 만든 후, 그 다음 index의 숫자와 비교해 heap에서 delete된 수가 더 클 경우 heap에 insert하고 다시 delete하는 과정을 반복했습니다. 몇 번째로 작은 수를 찾고 싶은지 입력 받는 과정에서 배열에 있는 숫자의 개수보다 큰 수를 입력했을 경우 if문을 통해 검사하여 다시 입력받도록 하였습니다.
