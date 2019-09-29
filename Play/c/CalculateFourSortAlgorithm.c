#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#define MAX 100000

void bubblesort(int array[], int n); 
void insertsort(int array[], int n );
void quicksort(int arrat[], int first, int last);
void comb_sort(int array[], int size);
void init(int array[]);

// バブルソート、挿入ソート、クイックソート、コムソートの実行時間を計測する
int main()
{
  int i, a[MAX];
  clock_t start, end;
  double bub, inser, quick, comb; // 各種ソートアルゴリズムにかかった時間を合計する変数
  bub = 0;
  inser = 0;
  quick = 0;
  comb = 0;
  for (int k = 1; k < 11; k++)
  {
    // ソートするリストの初期化
    init(a);

    // バブルソートの時間を計測
    start = clock();
    bubblesort(a, MAX); 
    end = clock();
    bub = bub + (end - start);


    // ソートするリストの初期化
    init(a);

    // 挿入ソートの時間を計測
    start = clock();
    insertsort(a, MAX);
    end = clock();
    inser = inser + (end - start);


    // ソートするリストの初期化
    init(a);

    // クイックソートの時間を計測
    start = clock();
    quicksort(a, 0, MAX - 1);
    end = clock();
    quick = quick + (end - start);
    
    // ソートするリストの初期化
    init(a);

    // コムソートの時間を計測
    start = clock();
    comb_sort(a, MAX);
    end = clock();
    comb = comb + (end - start);
  }

  printf("buble %f\n", (bub/10) / CLOCKS_PER_SEC);
  printf("insert %f\n", (inser/10) / CLOCKS_PER_SEC);
  printf("quick %f\n", (quick/10) / CLOCKS_PER_SEC);
  printf("comb %f\n", (comb/10) / CLOCKS_PER_SEC);

  return 0;
}

// リスト初期化する
void init(int array[])
{
  srand(4); // 同一乱数を用いて計測する
  for (int i = 0; i < MAX; i++)
    array[i] = rand() % MAX;
}

void bubblesort(int array[], int n)
{
  int i, j, t, sw = 1;
  for( i = 1 ; sw && i < n ; i++ ){
    sw = 0;
    for( j = n - 1 ; j >= i ; j-- ){
      if( array[j-1] > array[j] ){
	t = array[j-1];
	array[j-1] = array[j];
	array[j] = t;
	sw = 1;
      }
    }
  }
  return;
}

void comb_sort(int array[], int size) 
{
  int h = size;
  bool is_swapped = false;

  while (h > 1 || is_swapped) {
    if (h > 1) {
      h = (h * 10) / 13;
    }

    is_swapped = false;
    for (int i = 0; i < size - h; ++i) {
      if (array[i] > array[i + h]) {
        // swap
        int temp = array[i];
        array[i] = array[i + h];
        array[i + h] = temp;
        is_swapped = true;
      }
    }
  }
}

void insertsort( int array[], int n )
{
  int i, j, k, t;

  for( i=1 ; i < n ; i++ ){
    for( j=i-1 ; j >= 0 ; j-- ){
      if( array[j+1] < array[j] ){
	t = array[j+1];
	array[j+1] = array[j];
	array[j] = t;
      }else{
	break;
      }
    }
  }
  return;
}

void quicksort(int array[], int first, int last)
{
  int i, j, x, t;
  x = array[(first+last)/2];
  i = first;
  j = last;
  while(1){
    while( array[i] < x ) i++;
    while( x < array[j] ) j--;
    if( i >= j ) break;
    t = array[i]; 
    array[i] = array[j]; 
    array[j] = t;
    i++;
    j--;
  }
  if( first < i-1 )
    quicksort(array,first,i-1); 
  if( j+1 < last )
    quicksort(array,j+1,last);
}
