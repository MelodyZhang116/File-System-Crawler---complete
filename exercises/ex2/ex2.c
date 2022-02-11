// Copyright 2022 <Melody Zhang> [legal/copyright]
#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
void DumpBytes(void* pData, int32_t byteLen);

void CopyAndSort(uint8_t array1[], uint8_t array2[], int32_t byteLen);
//void printArray(uint8_t arr[],int n);
int main(int argc, char* argv[]) {
  int32_t int_val = 1;
  float   float_val = 1.0f;
  uint8_t arr_unsorted[] = {3, 2, 0, 8, 17, 6, 10, 7, 8, 1, 12};
  uint8_t arr_sorted[]   = {0, 0, 0, 0,  0, 0,  0, 0, 0, 0,  0};

  DumpBytes(&int_val, sizeof(int_val));
  DumpBytes(&float_val, sizeof(float_val));
  DumpBytes(arr_unsorted, sizeof(arr_unsorted));
  CopyAndSort(arr_unsorted, arr_sorted, sizeof(arr_unsorted));
  DumpBytes(arr_sorted, sizeof(arr_sorted));
  return EXIT_SUCCESS;
}

void DumpBytes(void* pData, int32_t byteLen) {
  printf("The %i bytes starting at %p are:",byteLen, pData);
  for ( int i = 0 ; i < byteLen ; i++){
      uint8_t hex_value = *((char*)pData+i);
      printf(" %02"PRIx8,hex_value);
      
  }
  printf("\n");
}
void CopyAndSort(uint8_t array1[], uint8_t array2[], int32_t byteLen){
  int j;
  uint8_t key;
  uint8_t *end_ptr;
  end_ptr = &array1[byteLen-1];
  uint8_t *array1_ptr = array1;
  uint8_t *array2_ptr = array2;
  while(array1_ptr <= end_ptr){
    *array2_ptr = *array1_ptr;
    array1_ptr++;
    array2_ptr++;
  }
  
  DumpBytes(array2, byteLen);
  for(int i = 1; i < byteLen; i++){
    key = array2[i];
    j = i - 1;
    while (j>=0 && array2[j] > key){
      array2[j + 1] = array2[j];
      j = j - 1;
    }
    array2[j+1] = key;
  }
}
/*
void printArray(uint8_t arr[],int n){
  int i;
  for (i = 0; i < n; i++){
    printf("%d", arr[i]);
  }
  printf("\n");
}
*/
