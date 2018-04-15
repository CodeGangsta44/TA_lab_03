#include <fstream>
#include <iostream>

using namespace std;

void swap(int* a, int* b){ // функція для обміну елементів масиву місцями
  int swap = *a;
  *a = *b;
  *b = swap;
}

void sort_without_decompose(int* arr, int f, int l, int* count){ // викликаємо, коли у підмасиві менше 4 елементів
  if ((l - f) == 1){
    (*count)++;
    if (arr[f] > arr[l]){
      swap(&arr[l], &arr[f]);
    }
    return;
  }
  if ((l - f) == 2){
    int i = f - 1;
    int x = arr[l];
    for (int j = f; j < l; j++){
      (*count)++;
      if (arr[j] <= x){
        i++;
        swap(&arr[i], &arr[j]);
      }
    }
    arr[l] = arr[i + 1];
    arr[i + 1] = x;
    if (i == -1){
      (*count)++;
      if (arr[f + 1] > arr[f + 2]) swap(&arr[f + 1], &arr[f + 2]);
      return;
    }
    if (i == l - 1){
      (*count)++;
      if (arr[f] > arr[f + 1]) swap(&arr[f], &arr[f + 1]);
      return;
    }
    return;
  }
}

void prepare(int* arr_to_prepare, int* original_arr, int len, int* count){
  /* викликаємо, щоб скопіювати
  вихідний масив у масив, який
  передаватимемо у функію сортування
  та обнулити лічильник порівнянь */
  *count = 0;
  for (int k = 0; k < len; k++) arr_to_prepare[k] = original_arr[k];
}

  /* функції 'partition' викликаються для
  розбивання вхідного масива на підмасиви
  відносно опорного елемента */

int partition_first(int* arr, int f, int l, int* count){
  int i = f - 1;
  int x = arr[l];
  for (int j = f; j < l; j++){
    (*count)++;
    if (arr[j] <= x){
      i++;
      swap(&arr[i], &arr[j]);
    }
  }
  arr[l] = arr[i + 1];
  arr[i + 1] = x;
  return i + 1;
}

int partition_second(int* arr, int f, int l, int* count){
  if ((arr[f] < arr[(f + l) / 2] && arr[(f + l)/2] < arr[l]) ||
      (arr[f] > arr[(f + l) / 2] && arr[(f + l)/2] > arr[l])){
    swap(&arr[(f + l) / 2], &arr[l]);
  } else if ((arr[(f + l) / 2] < arr[f] && arr[f] < arr[l]) ||
             (arr[(f + l) / 2] > arr[f] && arr[f] > arr[l])){
    swap(&arr[f], &arr[l]);
  }
  if (arr[f] > arr[(f + l) / 2]){
    swap(&arr[f], &arr[l - 1]);
    swap(&arr[(f + l) / 2], &arr[f]);
  } else if (arr[f] < arr[(f + l) / 2]){
    swap(&arr[(f + l) / 2], &arr[l - 1]);
  }
  int i = f;
  int x = arr[l];
  for (int j = f + 1; j < l - 1; j++){
    (*count)++;
    if (arr[j] <= x){
      i++;
      swap(&arr[i], &arr[j]);
    }
  }
  arr[l] = arr[i + 1];
  arr[i + 1] = x;
  return i + 1;
}
void partition_third(int* arr, int f, int l, int* count, int* i1, int* i2, int* i3){
  swap(&arr[l - 1], &arr[f + 1]);
  swap(&arr[l - 2], &arr[f]);
  int i = l - 3;
  int x = arr[l];
  for (int j = l - 2; j < l; j++){
    if (arr[j] <= x){
      i++;
      swap(&arr[i], &arr[j]);
    }
  }
  arr[l] = arr[i + 1];
  arr[i + 1] = x;
  if (arr[l - 2] > arr[l - 1]) swap(&arr[l - 2], &arr[l - 1]);
  if (arr[l - 1] > arr[l]) swap(&arr[l], &arr[l - 1]);
  i = f - 1;
  int j = f - 1;
  int k = l - 3;
  for (int n = f; n <= k; n++){
    (*count)++;
    if (arr[n] > arr[l - 1]){
      (*count)++;
      if (arr[n] > arr[l]){
        swap(&arr[n], &arr[k]);
        k--;
        n--;
        continue;
      }
    } else {
      j++;
      (*count)++;
      if (arr[n] < arr[l - 2]){
          swap(&arr[j], &arr[n]);
          swap(&arr[j], &arr[i + 1]);
          i++;
        continue;
      } else {
        swap(&arr[n], &arr[j]);
        continue;
      }
    }
  }
  int sw = arr[l - 2];
  swap(&arr[k + 1], &arr[l - 2]);
  swap(&arr[j + 1], &arr[k + 1]);
  swap(&arr[i + 1], &arr[j + 1]);
  arr[i + 1] = sw;
  j++;
  k++;
  sw = arr[l - 1];
  swap(&arr[k + 1], &arr[l - 1]);
  swap(&arr[j + 1], &arr[k + 1]);
  arr[j + 1] = sw;
  k++;
  swap(&arr[l], &arr[k + 1]);
  *i1 = i + 1;
  *i2 = j + 1;
  *i3 = k + 1;
  return;
}

  /* функції 'quick_sort' викликаються для
  кожного з підмасивів, що утворилися після
  виклику 'partition', рекурсивно, якщо
  розмір цього підмасиву більше 3, у
  іншому ж випадку викликається функція
  сортування без декомпозиції(без розділення
  на підмасиви) */

void quick_sort_first(int* arr, int f, int l, int* count){
  if (f >= l) return;
  int c = partition_first(arr, f, l, count);
  quick_sort_first(arr, f, c - 1, count);
  quick_sort_first(arr, c + 1, l, count);
}

void quick_sort_second(int* arr, int f, int l, int* count){
  if (f >= l) return;
  if ((l - f) < 3){
    sort_without_decompose(arr, f, l, count);
    return;
  }
  int c = partition_second(arr, f, l, count);
  quick_sort_second(arr, f, c - 1, count);
  quick_sort_second(arr, c + 1, l, count);
}

void quick_sort_third(int* arr, int f, int l, int* count, int* i1, int* i2, int* i3){
  if (f >= l) return;
  if ((l - f) < 3){
    sort_without_decompose(arr, f, l, count);
    return;
  }
  partition_third(arr, f, l, count, i1, i2, i3);
  int a = *i1;
  int b = *i2;
  int c = *i3;
  quick_sort_third(arr, f, a - 1, count, i1, i2, i3);
  quick_sort_third(arr, a + 1, b - 1, count, i1, i2, i3);
  quick_sort_third(arr, b + 1, c - 1, count, i1, i2, i3);
  quick_sort_third(arr, c + 1, l, count, i1, i2, i3);
}

int main(int argc, char* argv[]){
  ifstream fin(argv[1]);
  ofstream fout("ip71_dovhopoliuk_03_output.txt");
  int N;
  fin >> N;
  int* true_array = new int[N];
  int* array = new int[N];
  for (int i = 0; i < N; i++) fin >> true_array[i];
  int* count = new int;
  int* i1 = new int;
  int* i2 = new int;
  int* i3 = new int;
  cout << endl;
  cout << "Масив вхідний: ";
  for (int k = 0; k < N; k++){
    cout << true_array[k] << " ";
  }
  cout << endl << endl;
  prepare(array, true_array, N, count);
  quick_sort_first(array, 0, N - 1, count);
  fout << *count << " ";
  cout << "Кількість порівнянь для звичайної модифікації: \t " << *count << endl;
  cout << "Масив: ";
  for (int k = 0; k < N; k++){
    cout << array[k] << " ";
  }
  cout << endl << endl;
  prepare(array, true_array, N, count);
  quick_sort_second(array, 0, N - 1, count);
  fout << *count << " ";
  cout << "Кількість порівнянь для \"медіани\": \t\t " << *count << endl;
  cout << "Масив: ";
  for (int k = 0; k < N; k++){
    cout << array[k] << " ";
  }
  cout << endl << endl;
  prepare(array, true_array, N, count);
  quick_sort_third(array, 0, N - 1, count, i1, i2, i3);
  fout << *count;
  cout << "Кількість порівнянь для трьох опорних елементів: " << *count << endl;
  cout << "Масив: ";
  for (int k = 0; k < N; k++){
    cout << array[k] << " ";
  }
  cout << endl << endl;
}
