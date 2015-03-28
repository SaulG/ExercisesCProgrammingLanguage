#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
#define SIZE 100000
#define MAXIMUM RAND_MAX
#define REPET 30

int binsearchV1(int x, int v[], int n) {
  int low, mid, high;
  low = 0;
  high = n - 1;
  while (low <= high) {
    mid = (low + high) / 2;
    if (x < v[mid])
      high = mid - 1;
    else if (x > v[mid])
      low = mid + 1;
    else
      return mid;
  }
  return -1;
}

int binsearchV2(int x, int v[], int n) {
  int low, mid, high;
  low = 0;
  high = n - 1;
  while (high - low > 1) {
    mid = (low + high) / 2;
    if (x <= v[mid]) {
      high = mid;
    } else {
      low = mid;
    }
  }  
  // printf("%d mid: %d %d low: %d %d high: %d %d\n", x, mid, v[mid], low, v[low], high, v[high]);
  return (v[low] != x && v[high] != x) ? -1 : ((v[low] == x) ? low : high);
}

int comp(const void *arg1, const void *arg2) {
  if (*(int *)arg1 < *(int *)arg2) {
    return -1;
  } else if (*(int *)arg1 > *(int *)arg2) {
    return 1;
  } else {
    return 0;
  }
}

double original(int* v, int n) {
  int i;
  clock_t begin, end;
  double time_spent;

  begin = clock();  
  for (i = 0; i < n; i++) {
    assert(binsearchV1(v[i], v, n) == i);
  }
  for (i = MAXIMUM; i < MAXIMUM + n; i++) {
    assert(binsearchV1(i, v, n) == -1);
  }
  for (i = -1; i > -n; i--) {
    assert(binsearchV1(i, v, n) == -1);
  }
  end = clock();

  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  return time_spent * 1000;
}

double modified(int* v, int n) {
  int i;
  clock_t begin, end;
  double time_spent;

  begin = clock();  
  for (i = 0; i < n; i++) {
    assert(binsearchV2(v[i], v, n) == i);
  }  
  for (i = MAXIMUM; i < MAXIMUM + n; i++) {
    assert(binsearchV2(i, v, n) == -1);
  }
  for (i = -1; i > -n; i--) {
    assert(binsearchV2(i, v, n) == -1);
  }
  end = clock();

  time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  return time_spent * 1000;
}

int main() {
  int n = SIZE;
  int v[SIZE];
  int i, j, x, mod = n / 20;
  
  fprintf(stderr, "Creating a random array of integers\n");
  for (i = 0; i < SIZE;) {
    x = rand() % MAXIMUM;
    for (j = 0; j < i; j++) {
      if (x == v[j]) {
	break;
      }
    }
    if (i == j) {  
      v[i] = x;
      i++;
      if (i % mod == 0) {
	fprintf(stderr, "Array is %.0f percent full\n", 100.0 * i / SIZE);
      }
    }
  }

  fprintf(stderr, "Sorting the array\n");
  qsort(v, SIZE, sizeof(int), comp);

  fprintf(stderr, "Running the comparison\n");
  for (i = 0; i < REPET; i++) {
    if (rand() % 2) {
      printf("V1 %.3f ms \n", original(v, SIZE));
      printf("V2 %.3f ms \n", modified(v, SIZE));
    } else {
      printf("V2 %.3f ms \n", modified(v, SIZE));
      printf("V1 %.3f ms \n", original(v, SIZE));
    }
  }
  return 0;
}
