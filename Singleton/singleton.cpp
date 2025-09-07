#include <bits/stdc++.h>
using namespace std;

class Singleton {
private:
  static Singleton *instance;
  Singleton() { cout << "Singleton Constructor Called" << endl; }
  Singleton(const Singleton &) = delete; // Delete copy constructor
  Singleton &
  operator=(const Singleton &) = delete; // Delete assignment operator
public:
  static Singleton *getInstance() {
    if (instance == nullptr) {
      instance = new Singleton();
    }
    return instance;
  }
};

Singleton *Singleton::instance = nullptr;

int main() {
  Singleton *s1 = Singleton::getInstance();
  Singleton *s2 = Singleton::getInstance();

  if (s1 == s2) {
    cout << "Both are same instances" << endl;
  } else {
    cout << "Different instances" << endl;
  }
}
