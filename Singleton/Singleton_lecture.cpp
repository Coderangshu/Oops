#include <bits/stdc++.h>
using namespace std;

class A {
  int x;
  A() : x(10) {}
  A(const A &) = delete;
  A &operator=(const A &) = delete;

public:
  static A &getInstance() {
    static A obj;
    return obj;
  }

  void inc() { x++; }
  int val() { return x; }
};

int main() {
  A &ap1 = A::getInstance();
  A &ap2 = A::getInstance();

  ap1.inc();
  ap2.inc();

  cout << ap1.val() << endl;
  cout << ap2.val() << endl;
};
