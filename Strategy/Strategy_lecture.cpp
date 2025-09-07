#include <bits/stdc++.h>
using namespace std;

class Sorter {

public:
  virtual int sort(int *arr, int sz) = 0;
};

class Sorter1 : public Sorter {
  // implement bubble sort
  // return number of swaps
public:
  int sort(int *arr, int sz) override {
    int swaps = 0;
    for (int i = 0; i < sz - 1; i++) {
      for (int j = 0; j < sz - i - 1; j++) {
        if (arr[j] > arr[j + 1]) {
          swap(arr[j], arr[j + 1]);
          swaps++;
        }
      }
    }
    return swaps; // returning number of swaps as an example
  }
};

class Sorter2 : public Sorter {
  // implement quicksort
  // return number of swaps
public:
  int sort(int *arr, int sz) override {
    // QuickSort implementation
    function<int(int, int)> quickSort = [&](int low, int high) {
      if (low >= high)
        return 0;
      int pivot = arr[high];
      int i = low - 1;
      int swaps = 0;

      for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
          i++;
          swap(arr[i], arr[j]);
          swaps++;
        }
      }
      swap(arr[i + 1], arr[high]);
      swaps++;

      swaps += quickSort(low, i);
      swaps += quickSort(i + 2, high);
      return swaps;
    };
    return quickSort(0, sz - 1);
  }
};

class Sorter3 : public Sorter {
  // implement mergesort
  // return number of swaps
public:
  int sort(int *arr, int sz) override {
    // MergeSort implementation
    function<int(int, int)> mergeSort = [&](int left, int right) {
      if (left >= right)
        return 0;
      int mid = left + (right - left) / 2;
      int swaps = 0;

      swaps += mergeSort(left, mid);
      swaps += mergeSort(mid + 1, right);

      vector<int> temp(right - left + 1);
      int i = left, j = mid + 1, k = 0;

      while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
          temp[k++] = arr[i++];
        } else {
          temp[k++] = arr[j++];
          swaps += (mid - i + 1); // Count inversions
        }
      }
      while (i <= mid)
        temp[k++] = arr[i++];
      while (j <= right)
        temp[k++] = arr[j++];

      for (int p = 0; p < temp.size(); p++) {
        arr[left + p] = temp[p];
      }
      return swaps;
    };
    return mergeSort(0, sz - 1);
  }
};

int main() {

  Sorter *s;
  int *arr = new int[10]{5, 2, 9, 1, 5, 6, 3, 8, 7, 4};

  int choice;

  cin >> choice;
  switch (choice) {

  case 0:
    s = new Sorter1();
    int ns = s->sort(arr, 10);
    cout << ns << endl;
    break;
  case 1:
    s = new Sorter2();
    ns = s->sort(arr, 10);
    cout << ns << endl;
    break;
  case 2:
    s = new Sorter3();
    ns = s->sort(arr, 10);
    cout << ns << endl;
    break;
  }

  for (int i = 0; i < 10; i++) {
    cout << arr[i] << " ";
  }
}
