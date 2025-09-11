#include <bits/stdc++.h>
using namespace std;

class Numbers {
private:
  int number1;
  int number2;
  string operation;

public:
  int getNumber1() const { return number1; }
  int getNumber2() const { return number2; }
  string getOperation() const { return operation; }
};

class Chain {
protected:
  Chain *next = nullptr;

public:
  Chain(const Chain &) = default;
  Chain(Chain &&) = delete;
  virtual void setNext(Chain *next) = 0;
  virtual void handleRequest(Numbers numbers) {
    cout << "No handler found for the operation." << endl;
  }
  virtual ~Chain() {}
};

class Add : public Chain {
public:
  void handleRequest(Numbers &numbers) override {
    if (numbers.getOperation() == "add") {
      cout << "Addition: ";
      cout << numbers.getNumber1() + numbers.getNumber2() << endl;
    } else {
      if (next != nullptr) {
        next->handleRequest(numbers);
      } else
        Chain::handleRequest(numbers);
    }
  }
  void setNext(Chain *next) override { this->next = next; };
};
