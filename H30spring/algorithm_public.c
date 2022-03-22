#include <stdio.h>

#define DATA_SIZE 7
#define lchild(i) (2*(i)+1)
#define rchild(i) (2*(i)+2)
#define parent(i) ((int)(((i)-1)/2))

/* 関数のプロトタイプ宣言 */
// ヒープの作成
void makeHeap(int data[], int heap[], int hnum);
// 値の交換
void swap(int heap[], int i, int j);
// ソート
void heapSort(int heap[], int sort[], int hnum);
// ヒープの再構築
void downHeap(int heap[], int hlast);


int main(void){
  int i;
  int data[DATA_SIZE] = {30, 45, 5, 60, 10, 20, 15};
  int heap[DATA_SIZE];
  int sort[DATA_SIZE];

  // ヒープの作成
  makeHeap(data, heap, DATA_SIZE);
  // 表示
  for(i = 0; i < DATA_SIZE; i++){
    printf("data[%d] = %d\n", i, heap[i]);
  }

  // ソートの作成
  heapSort(heap, sort, DATA_SIZE);
  // 表示
  for(i = 0; i < DATA_SIZE; i++){
    printf("sort[%d] = %d\n", i, sort[i]);
  }
  
  return 0;
}

// ヒープの作成
void makeHeap(int data[], int heap[], int hnum){
  int i, k;
  for(i = 0; i < hnum; i++){
    heap[i] = data[i];
    k = i;
    while(k > 0){
      if(heap[k] > heap[parent(k)]){
        swap(heap, k, parent(k));
        k = parent(k);
      }else{
        break;
      }
    }
  }
}

// 値の交換
void swap(int heap[], int i, int j){
  int tmp;
  tmp = heap[i];
  heap[i] = heap[j];
  heap[j] = tmp;
}

// ソート
void heapSort(int heap[], int sort[], int hnum){
  int i, last;
  for(i = 0; i < hnum; i++){
    sort[i] = heap[i];
  }
  for(last = hnum - 1; last > 0; last--){
    swap(sort, 0, last);
    downHeap(sort, last-1);
  }
}

// ヒープの再構築
void downHeap(int heap[], int hlast){
  int n, tmp;
  n = 0;
  while(lchild(n) <= hlast){
    tmp = lchild(n);
    if(rchild(n) <= hlast){
      if(heap[tmp] <= heap[rchild(n)]){
        tmp = rchild(n);
      }
    }
    if(heap[tmp] > heap[n]){
      swap(heap, n, tmp);
    }else{
      return;
    }
    n = tmp;
  }
}
