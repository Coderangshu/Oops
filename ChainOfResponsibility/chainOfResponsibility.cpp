#include <bits/stdc++.h>
using namespace std;

// Abstract Handler (Base Class)
class MoneyHandler {
protected:
  MoneyHandler *nextHandler;

public:
  MoneyHandler() : nextHandler(nullptr) {}

  void setNextHandler(MoneyHandler *next) { nextHandler = next; }

  virtual void dispense(int amount) = 0;
};

// Concrete Handler for Rs 1000 notes
class ThousandHandler : public MoneyHandler {
private:
  int numNotes;

public:
  ThousandHandler(int numNotes) : numNotes(numNotes) {}

  void dispense(int amount) override {
    int notesNeeded = amount / 1000;

    if (notesNeeded > numNotes) {
      notesNeeded = numNotes;
      numNotes = 0;
    } else {
      numNotes -= notesNeeded;
    }

    if (notesNeeded > 0)
      cout << "Dispensing " << notesNeeded << " x 1000 notes." << endl;

    int remainingAmt = amount - (notesNeeded * 1000);
    if (remainingAmt > 0) {
      if (nextHandler != nullptr)
        nextHandler->dispense(remainingAmt);
      else
        cout << "Remaining amount of " << remainingAmt
             << " cannot be fulfilled." << endl;
    }
  }
};

// Concrete Handler for Rs 500 notes
class FiveHundredHandler : public MoneyHandler {
private:
  int numNotes;

public:
  FiveHundredHandler(int numNotes) : numNotes(numNotes) {}

  void dispense(int amount) override {
    int notesNeeded = amount / 500;

    if (notesNeeded > numNotes) {
      notesNeeded = numNotes;
      numNotes = 0;
    } else {
      numNotes -= notesNeeded;
    }

    if (notesNeeded > 0)
      cout << "Dispensing " << notesNeeded << " x 500 notes." << endl;

    int remainingAmt = amount - (notesNeeded * 500);
    if (remainingAmt > 0) {
      if (nextHandler != nullptr)
        nextHandler->dispense(remainingAmt);
      else
        cout << "Remaining amount of " << remainingAmt
             << " cannot be fulfilled." << endl;
    }
  }
};

// Concrete Handler for Rs 200 notes
class TwoHundredHandler : public MoneyHandler {
private:
  int numNotes;

public:
  TwoHundredHandler(int numNotes) : numNotes(numNotes) {}

  void dispense(int amount) override {
    int notesNeeded = amount / 200;

    if (notesNeeded > numNotes) {
      notesNeeded = numNotes;
      numNotes = 0;
    } else {
      numNotes -= notesNeeded;
    }

    if (notesNeeded > 0)
      cout << "Dispensing " << notesNeeded << " x 200 notes." << endl;

    int remainingAmt = amount - (notesNeeded * 200);
    if (remainingAmt > 0) {
      if (nextHandler != nullptr)
        nextHandler->dispense(remainingAmt);
      else
        cout << "Remaining amount of " << remainingAmt
             << " cannot be fulfilled." << endl;
    }
  }
};

// Concrete Handler for Rs 100 notes
class OneHundredHandler : public MoneyHandler {
private:
  int numNotes;

public:
  OneHundredHandler(int numNotes) : numNotes(numNotes) {}

  void dispense(int amount) override {
    int notesNeeded = amount / 100;

    if (notesNeeded > numNotes) {
      notesNeeded = numNotes;
      numNotes = 0;
    } else {
      numNotes -= notesNeeded;
    }

    if (notesNeeded > 0)
      cout << "Dispensing " << notesNeeded << " x 100 notes." << endl;

    int remainingAmt = amount - (notesNeeded * 100);
    if (remainingAmt > 0) {
      if (nextHandler != nullptr)
        nextHandler->dispense(remainingAmt);
      else
        cout << "Remaining amount of " << remainingAmt
             << " cannot be fulfilled." << endl;
    }
  }
};

// Concrete Handler for Rs 50 notes
class FiftyHandler : public MoneyHandler {
private:
  int numNotes;

public:
  FiftyHandler(int numNotes) : numNotes(numNotes) {}

  void dispense(int amount) override {
    int notesNeeded = amount / 50;

    if (notesNeeded > numNotes) {
      notesNeeded = numNotes;
      numNotes = 0;
    } else {
      numNotes -= notesNeeded;
    }

    if (notesNeeded > 0)
      cout << "Dispensing " << notesNeeded << " x 50 notes." << endl;

    int remainingAmt = amount - (notesNeeded * 50);
    if (remainingAmt > 0) {
      if (nextHandler != nullptr)
        nextHandler->dispense(remainingAmt);
      else
        cout << "Remaining amount of " << remainingAmt
             << " cannot be fulfilled." << endl;
    }
  }
};

// Concrete Handler for Rs 50 notes
class TwentyHandler : public MoneyHandler {
private:
  int numNotes;

public:
  TwentyHandler(int numNotes) : numNotes(numNotes) {}

  void dispense(int amount) override {
    int notesNeeded = amount / 20;

    if (notesNeeded > numNotes) {
      notesNeeded = numNotes;
      numNotes = 0;
    } else {
      numNotes -= notesNeeded;
    }

    if (notesNeeded > 0)
      cout << "Dispensing " << notesNeeded << " x 20 notes." << endl;

    int remainingAmt = amount - (notesNeeded * 20);
    if (remainingAmt > 0) {
      if (nextHandler != nullptr)
        nextHandler->dispense(remainingAmt);
      else
        cout << "Remaining amount of " << remainingAmt
             << " cannot be fulfilled." << endl;
    }
  }
};

// Concrete Handler for Rs 10 notes
class TenHandler : public MoneyHandler {
private:
  int numNotes;

public:
  TenHandler(int numNotes) : numNotes(numNotes) {}

  void dispense(int amount) override {
    int notesNeeded = amount / 10;

    if (notesNeeded > numNotes) {
      notesNeeded = numNotes;
      numNotes = 0;
    } else {
      numNotes -= notesNeeded;
    }

    if (notesNeeded > 0)
      cout << "Dispensing " << notesNeeded << " x 10 notes." << endl;

    int remainingAmt = amount - (notesNeeded * 10);
    if (remainingAmt > 0) {
      if (nextHandler != nullptr)
        nextHandler->dispense(remainingAmt);
      else
        cout << "Remaining amount of " << remainingAmt
             << " cannot be fulfilled." << endl;
    }
  }
};

// Client Code
int main() {
  // Creating handlers for each note type
  MoneyHandler *thousandHandler = new ThousandHandler(3);
  MoneyHandler *fiveHundredHandler = new FiveHundredHandler(5);
  MoneyHandler *twoHundredHandler = new TwoHundredHandler(10);
  MoneyHandler *oneHundredHandler = new OneHundredHandler(20);
  MoneyHandler *fiftyHandler = new FiftyHandler(30);
  MoneyHandler *twentyHandler = new TwentyHandler(50);
  MoneyHandler *tenHandler = new TenHandler(100);

  // Setting up the chain of responsibility
  thousandHandler->setNextHandler(fiveHundredHandler);
  fiveHundredHandler->setNextHandler(twoHundredHandler);
  twoHundredHandler->setNextHandler(oneHundredHandler);
  oneHundredHandler->setNextHandler(fiftyHandler);
  fiftyHandler->setNextHandler(twentyHandler);
  twentyHandler->setNextHandler(tenHandler);

  int amountToWithdraw = 3760;

  // Initiating the chain
  cout << "\nDiespensing amount: " << amountToWithdraw << endl;
  thousandHandler->dispense(amountToWithdraw);

  return 0;
}
