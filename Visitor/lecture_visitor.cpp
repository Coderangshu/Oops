#include <bits/stdc++.h>
using namespace std;

class Node {
public:
  int data;
  Node *next;
  Node(int d) : data(d), next(nullptr) {}
};

class Q {
  Node *head = nullptr;

public:
  void insert(int x) {
    Node *newNode = new Node(x);
    auto cur = head;
    while (cur->next)
      cur = cur->next;
    cur = newNode;
  }

  int fetch() {
    if (!head)
      throw runtime_error("Queue is empty");
    int val = head->data;
    Node *temp = head;
    head = head->next;
    delete temp;
    return val;
  }

  void visitMe(class QVisitor *v);
};

// QVisitor : multiple variations
// 1. Finds highest entry
// 2. Sums up all numbers
// 3. Appends another Q into the visited one

class QVisitor {
public:
  virtual void visit(Q *q) = 0;
  virtual ~QVisitor() {}
};

class HighestVisitor : public QVisitor {
  int highest = INT_MIN;

public:
  void visit(Q *q) override {
    try {
      while (true) {
        int x = q->fetch();
        highest = max(highest, x);
      }
    } catch (runtime_error &) {
      // queue is empty
      cout << "HighestVisitor finished visiting." << endl;
    }
  }
  int getHighest() const { return highest; }
};

// class SumVisitor : public QVisitor {
//   int sum = 0;
//
// public:
//   void visit(Q *q) override {
//     try {
//       while (true) {
//         int x = q->fetch();
//         sum += x;
//       }
//     } catch (runtime_error &) {
//       // queue is empty
//     }
//   }
//   int getSum() const { return sum; }
// };

// class AppendVisitor : public QVisitor {
//   Q *toAppend;
//
// public:
//   AppendVisitor(Q *q) : toAppend(q1) {}
//   void visit(Q *q) override {
//     try {
//       while (true) {
//         int x = toAppend->fetch();
//         q->insert(x);
//       }
//     } catch (runtime_error &) {
//       // toAppend is empty
//     }
//   }
// };

void Q::visitMe(QVisitor *v) { v->visit(this); }

int main() {
  Q q1;
  for (int i = 1; i <= 5; ++i)
    q1.insert(i);

  HighestVisitor hv;
  q1.visitMe(&hv);
  cout << "Highest in q1: " << hv.getHighest() << endl;

  // for (int i = 1; i <= 5; ++i)
  //   q1.insert(i);
  //
  // SumVisitor sv;
  // q1.visitMe(&sv);
  // cout << "Sum of q1: " << sv.getSum() << endl;
  //
  // for (int i = 1; i <= 5; ++i)
  //   q1.insert(i);
  // Q q2;
  // for (int i = 6; i <= 10; ++i)
  //   q2.insert(i);
  //
  // AppendVisitor av(&q2);
  // q1.visitMe(&av);
  // cout << "After appending q2 to q1, q1 contains: ";
  // try {
  //   while (true) {
  //     cout << q1.fetch() << " ";
  //   }
  // } catch (runtime_error &) {
  //   // queue is empty
  // }
  // cout << endl;

  return 0;
}
