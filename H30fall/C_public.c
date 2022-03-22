#include <stdio.h>
#define RED 0
#define GREEN 1
#define BLOCK_COUNT 9
#define TRAIN_COUNT 5

/* 
  宣言
 */
/* 構造体 */
// 鉄道模型の区間
struct block_info {
  struct train_info* train;
  struct block_info* next[2];
  int signal;
};

// 鉄道模型の列車
struct train_info{
  int number;
  struct block_info* dest;
};


/* 関数 */
// シュミレーション統合管理
void start(struct block_info[], int);
// 信号機管理
void set_signals(struct block_info[], int);
// シュミレーション表示
void print_all(int, struct block_info[]);
// 列車進行
void proceed(struct block_info[], int);
// 列車経路確認
int find_block(struct block_info*, struct block_info*);
// シュミレーション終了確認
int finish(struct block_info[], int);

int main(void){
  struct train_info trains[5] = {
    {0, NULL},
    {1, NULL},
    {2, NULL},
    {3, NULL},
    {4, NULL},
  };
  struct block_info blocks[BLOCK_COUNT] = {
    {&trains[4],  {&blocks[2],  NULL},        },
    {&trains[3],  {&blocks[2],  NULL},        },
    {NULL,        {&blocks[3],  NULL},        },
    {&trains[2],  {&blocks[4],  &blocks[7]},  },
    {&trains[1],  {&blocks[5],  &blocks[6]},  },
    {NULL,        {NULL,        NULL},        },
    {NULL,        {NULL,        NULL},        },
    {NULL,        {&blocks[8],  NULL},        },
    {&trains[0],  {NULL,        NULL},        },
  };
  trains[0].dest = &blocks[8];
  trains[1].dest = &blocks[5];
  trains[2].dest = &blocks[6];
  trains[3].dest = &blocks[5];
  trains[4].dest = &blocks[8];

  start(blocks, BLOCK_COUNT);

  return 0;
}

// シュミレーション統合管理
void start(struct block_info blocks[], int nblocks){
  int i;
  
  printf("simulation_start\n");
  set_signals(blocks, BLOCK_COUNT);
  print_all(0, blocks);
  for(i = 0; finish(blocks, BLOCK_COUNT); i++){
    proceed(blocks, BLOCK_COUNT);
    set_signals(blocks, BLOCK_COUNT);
    print_all(i+1, blocks);
  }
  printf("simulation_exit\n");
}

// シュミレーション終了確認
int finish(struct block_info blocks[], int nblocks){
  int i;
  for(i = 0; i < nblocks; i++){
    if(blocks[i].train != NULL){
      // シュミレーション続行
      return 1;
    }
  }
  // シュミレーション終了
  return 0;
}

// 信号機管理
void set_signals(struct block_info blocks[], int nblocks){
  int i;
  struct block_info *block;
  for(i = 0; i < nblocks; i++){
    block = &blocks[i];
    if(block->train == NULL){
      block->signal = GREEN;
    }else{
      block->signal = RED;
    }
  }
}

// シュミレーション表示
void print_all(int test_number, struct block_info blocks[BLOCK_COUNT]){
  int i;
  printf("%03d*********************************************************\n",test_number);
  printf("block_num\ttrain_num\tsignals(RED=0,GRE=1)\n");
  for(i = 0; i <BLOCK_COUNT; i++){
    if(blocks[i].train == NULL){
      printf("%03d\t\tNULL\t\t%d\n", i, blocks[i].signal);
    }else{
      printf("%03d\t\t%2d\t\t%d\n", i, (blocks[i].train)->number, blocks[i].signal);

    }
  }
  printf("************************************************************\n");
}

// 列車進行
void proceed(struct block_info blocks[], int nblocks){
  int i, j;
  struct block_info *block;
  for(i = nblocks - 1; i >= 0; i--){
    block = &blocks[i];
    if(block->train == NULL){
      // 区間内に列車がいない場合
      continue;
    }
    if(block == block->train->dest){
      // 列車が最終駅の手前の区間にいる場合
      block->train = NULL;
      continue;
    }
    for(j = 0; j < 2; j++){
      if(block->next[j] == NULL){
        // 次の駅が存在しない
        continue;
      }
      if(block->next[j]->signal == RED){
        // 次の区間の信号が赤
        continue;
      }
      if(find_block(block->next[j], block->train->dest) == 1){
        // 列車が進行できる場合
        block->next[j]->train = block->train;
        block->next[j]->signal = RED;
        block->train = NULL;
        break;
      }
    }
  }
};

// 列車経路確認
int find_block(struct block_info *block, struct block_info *dest){
  int i;
  if(block == dest){
    // 終着駅を出口とする区間
    return 1;
  }
  for(i = 0; i < 2; i++){
    if(block->next[i] == NULL){
      // 次の駅が存在しない
      continue;
    }
    if(find_block(block->next[i], dest) == 1){
      // 再帰的に呼び出す
      return 1;
    }
  }
  return 0;
}
