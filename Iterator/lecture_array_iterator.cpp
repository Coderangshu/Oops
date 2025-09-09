#include <bits/stdc++.h>
using namespace std;

class MyArr {
  int *arr;
  int size;

public:
  MyArr(int s) {
    size = s;
    arr = new int[size];
    for (int i = 0; i < size; i++) {
      arr[i] = i + 1;
    }
  }
};

class Iterator {
  MyArr &myArr;
  int index;

public:
  Iterator(MyArr &arr) : myArr(arr), index(0) {}
  bool hasNext() { return index < myArr.size; }
  int next() { return myArr.arr[index++]; }
};
