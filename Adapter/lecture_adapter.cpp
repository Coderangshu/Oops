#include <bits/stdc++.h>
using namespace std;

class Collection {
public:
  virtual void insert(int) = 0;
  virtual int fetch() = 0;
};

class Stack { // implement this
  vector<int> stk;

public:
  void push(int x) { stk.push_back(x); }
  int pop() {
    if (stk.empty()) {
      throw runtime_error("Stack is empty");
    }
    int x = stk.back();
    stk.pop_back();
    return x;
  }
  bool empty() const { return stk.empty(); }
};

class FIFO : public Collection {
  Stack s1, s2;

public:
  void insert(int x) { s1.push(x); }

  int fetch() {
    if (s2.empty()) {
      while (!s1.empty()) {
        s2.push(s1.pop());
      }
    }
    if (s2.empty()) {
      throw runtime_error("Queue is empty");
    }
    return s2.pop();
  }
};

class LIFO : public Collection {
  Stack s;

public:
  void insert(int x) { s.push(x); }

  int fetch() {
    if (s.empty()) {
      throw runtime_error("Stack is empty");
    }
    return s.pop();
  }
};

int main() {

  Collection *cp;
  cp = new FIFO();
  cp->insert(10);
  cp->insert(20);
  cout << cp->fetch() << endl;
  cp = new LIFO();
  cp->insert(10);
  cp->insert(20);
  cout << cp->fetch() << endl;
};
