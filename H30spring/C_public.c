#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define recSize 1002
#define listLen 32

/**
 *@brief 入力されたファイルから集計ファイルを作成
 *@param dataFile 入力ファイル名
 *@param listFile 出力ファイル名
 *@param keyPos キー項目開始桁位置
 *@param keyLen キー項目桁数
 *@param valuePos 数値項目開始桁位置
 *@param valueLen 数値項目桁数
 */
void outList(char *dataFile, char *listFile, int keyPos, int keyLen, int valuePos, int valueLen);

/**
 *@brief リストファイルから棒グラフを作成
 *@param listFile リストファイル名
 */
void outListG(char *listFile);

int main(void){
  /* 設問1テストケース */
  outList("C_test1.txt", "output1", 14, 6, 24, 6);

  /* 設問2テストケース */
  outList("C_test2.txt", "output2", 8, 2, 24, 6);
  outListG("output2");

  return 0;
}

void outList(char *dataFile, char *listFile, int keyPos, int keyLen, int valuePos, int valueLen){
  FILE *inFile, *outFile;
  char inBuf[recSize], inKey[10], key[10], temp[10];
  long count, inValue, value;
  char format[] = " %9s %9ld %9ld\n";

  key[keyLen] = '\0';
  inKey[keyLen] = '\0';
  temp[valueLen] = '\0';
  outFile = fopen(listFile, "w");
  inFile = fopen(dataFile, "r");

  if(fgets(inBuf, recSize, inFile) != NULL){
    // 入力ファイル1行目取得 変数のリセット
    strncpy(key, inBuf + keyPos, keyLen);
    count = 1;
    value = atol(strncpy(temp, inBuf + valuePos, valueLen));
    while(fgets(inBuf, recSize, inFile) != NULL){
      strncpy(inKey, inBuf + keyPos, keyLen);
      inValue = atol(strncpy(temp, inBuf + valuePos, valueLen));
      if(strcmp(key, inKey) != 0){
        // キー項目別テーブル出力 変数のリセット
        fprintf(outFile, format, key, count, value);
        count = 1;
        strcpy(key, inKey);
        value = inValue;
      }else{
        // キー項目カウント
        count++;
        value += inValue;
      }
    }
    fprintf(outFile, format, key, count, value);
  }
  fclose(inFile);
  fclose(outFile);
}

void outListG(char *listFile){
  FILE *inFile;
  char inBuf[listLen];
  long value, valueMax;
  char graph[] = "*************************";

  inFile = fopen(listFile, "r");
  valueMax = 0;
  while(fgets(inBuf, listLen, inFile) != NULL){
    value = atol(inBuf + 21);
    if(value > valueMax){
      valueMax = value;
    }
  }
  fclose(inFile);

  // 標準出力
  inFile = fopen(listFile, "r");
  while(fgets(inBuf, listLen, inFile) != NULL){
    value = atol(inBuf + 21);
    printf("%.30s  |%s\n", inBuf, &graph[25 - 25 * value / valueMax]);
  }
  fclose(inFile);
}