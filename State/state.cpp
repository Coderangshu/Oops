#include <bits/stdc++.h>
using namespace std;

// Forward declaration
class VendingMachine;

// Abstract State Interface
class VendingState {
public:
  virtual VendingState *insertCoin(VendingMachine *machine, int coin) = 0;
  virtual VendingState *selectItem(VendingMachine *machine) = 0;
  virtual VendingState *dispense(VendingMachine *machine) = 0;
  virtual VendingState *returnCoin(VendingMachine *machine) = 0;
  virtual VendingState *refill(VendingMachine *machine, int quantity) = 0;
  virtual string getStateName() = 0;
};

// Forward declaration of concrete States
class NoCoinState;
class HasCoinState;
class DispenseState;
class SoldOutState;

// Context Class - Vending machine
class VendingMachine {
private:
  VendingState *currentState;
  int itemCount;
  int itemPrice;
  int insertedCoins;

  // State objects (we'll initialize these)
  VendingState *noCoinState;
  VendingState *hasCoinState;
  VendingState *dispenseState;
  VendingState *soldOutState;

public:
  VendingMachine(int itemCount, int itemPrice) {
    this->itemCount = itemCount;
    this->itemPrice = itemPrice;

    // Create state instances
    noCoinState = new NoCoinState();
    hasCoinState = new HasCoinState();
    dispenseState = new DispenseState();
    soldOutState = new SoldOutState();

    // Set initial state
    if (itemCount > 0)
      currentState = noCoinState;
    else
      currentState = soldOutState;
  }

  // Delegate to current state and update state based on return value
  void insertCoin(int coin) {
    currentState = currentState->insertCoin(this, coin);
  }

  void selectItem() { currentState = currentState->selectItem(this); }
  void dispense() { currentState = currentState->dispense(this); }
  void returnCoin() { currentState = currentState->returnCoin(this); }

  void refill(int quantity) {
    currentState = currentState->refill(this, quantity);
  }

  // Print the status of Vending machine
  void printStatus() {
    cout << "\n--- Vending Machine Status ---" << endl;
    cout << "Item Remaining: " << itemCount << endl;
    cout << "Inserted Coins: Rs " << insertedCoins << endl;
    cout << "Current State: " << currentState->getStateName() << endl;
    cout << "-----------------------------" << endl;
  }

  // Getter for states
  VendingState *getNoCoinState() { return noCoinState; }
  VendingState *getHasCoinState() { return hasCoinState; }
  VendingState *getDispenseState() { return dispenseState; }
  VendingState *getSoldOutState() { return soldOutState; }

  // Data access methods
  int getItemCount() { return itemCount; }
  void decreaseItemCount() {
    if (itemCount > 0)
      itemCount--;
  }
  void increaseItemCount(int quantity) { itemCount += quantity; }
  int getItemPrice() { return itemPrice; }
  int getInsertedCoins() { return insertedCoins; }
  void addCoins(int coin) { insertedCoins += coin; }
  int getPrice() { return itemPrice; }
  void setPrice(int price) { itemPrice = price; }
  void setInsertedCoins(int coins) { insertedCoins = coins; }
};

// Concrete States
class NoCoinState : public VendingState {
public:
  VendingState *insertCoin(VendingMachine *machine, int coin) override {
    machine->addCoins(coin);
    cout << "Inserted Rs " << coin << ", current balance: Rs "
         << machine->getInsertedCoins() << endl;
    return machine->getHasCoinState();
  }

  VendingState *selectItem(VendingMachine *machine) override {
    cout << "Please insert coins first." << endl;
    // Stay in the same state
    return this;
  }

  VendingState *dispense(VendingMachine *machine) override {
    cout << "Please insert coins first." << endl;
    // Stay in the same state
    return this;
  }

  VendingState *returnCoin(VendingMachine *machine) override {
    cout << "No coins to return." << endl;
    // Stay in the same state
    return this;
  }

  VendingState *refill(VendingMachine *machine, int quantity) override {
    machine->increaseItemCount(quantity);
    cout << "Machine refilled with " << quantity << " items." << endl;
    // Stay in the same state
    return this;
  }

  string getStateName() override { return "NoCoinState"; }
};

class HasCoinState : public VendingState {
public:
  VendingState *insertCoin(VendingMachine *machine, int coin) override {
    machine->addCoins(coin);
    cout << "Inserted Rs " << coin << ", current balance: Rs "
         << machine->getInsertedCoins() << endl;
    // Stay in the same state
    return this;
  }

  VendingState *selectItem(VendingMachine *machine) override {
    if (machine->getInsertedCoins() >= machine->getItemPrice()) {
      cout << "Item selected." << endl;
      return machine->getDispenseState();
    }

    int change = machine->getItemPrice() - machine->getInsertedCoins();
    cout << "Insufficient balance. Please insert Rs " << change << " more."
         << endl;
    // Stay in the same state
    return this;
  }

  VendingState *dispense(VendingMachine *machine) override {
    cout << "Please select an item first." << endl;
    // Stay in the same state
    return this;
  }

  VendingState *returnCoin(VendingMachine *machine) override {
    int returnedAmount = machine->getInsertedCoins();
    machine->setInsertedCoins(0);
    cout << "Returned Rs " << returnedAmount << endl;
    return machine->getNoCoinState();
  }

  VendingState *refill(VendingMachine *machine, int quantity) override {
    machine->increaseItemCount(quantity);
    cout << "Machine refilled with " << quantity << " items." << endl;
    // Stay in the same state
    return this;
  }

  string getStateName() override { return "HasCoinState"; }
};

class DispenseState : public VendingState {
public:
  VendingState *insertCoin(VendingMachine *machine, int coin) override {
    cout << "Please wait, dispensing item." << endl;
    // Stay in the same state
    return this;
  }

  VendingState *selectItem(VendingMachine *machine) override {
    cout << "Already dispensing item." << endl;
    // Stay in the same state
    return this;
  }

  VendingState *dispense(VendingMachine *machine) override {
    machine->decreaseItemCount();
    int change = machine->getInsertedCoins() - machine->getItemPrice();
    if (change > 0) {
      cout << "Dispensed item. Returning change: Rs " << change << endl;
    } else {
      cout << "Dispensed item." << endl;
    }
    machine->setInsertedCoins(0);
    if (machine->getItemCount() == 0) {
      cout << "Machine is now sold out." << endl;
      return machine->getSoldOutState();
    }
    return machine->getNoCoinState();
  }

  VendingState *returnCoin(VendingMachine *machine) override {
    cout << "Cannot return coins while dispensing." << endl;
    // Stay in the same state
    return this;
  }

  VendingState *refill(VendingMachine *machine, int quantity) override {
    cout << " Cannot refill while dispensing." << endl;
    // Stay in the same state
    return this;
  }

  string getStateName() override { return "DispenseState"; }
};

class SoldOutState : public VendingState {
public:
  VendingState *insertCoin(VendingMachine *machine, int coin) override {
    cout << "Item is sold out. Coin is returned: Rs " << coin << endl;
    this->returnCoin(machine);
    // Stay in the same state
    return this;
  }

  VendingState *selectItem(VendingMachine *machine) override {
    cout << "Item is sold out." << endl;
    // Stay in the same state
    return this;
  }

  VendingState *dispense(VendingMachine *machine) override {
    cout << "Item is sold out." << endl;
    // Stay in the same state
    return this;
  }

  VendingState *returnCoin(VendingMachine *machine) override {
    if (machine->getInsertedCoins() > 0) {
      int returnedAmount = machine->getInsertedCoins();
      machine->setInsertedCoins(0);
      cout << "Returned Rs " << returnedAmount << endl;
    } else {
      cout << "No coins to return." << endl;
    }
    // Stay in the same state
    return this;
  }

  VendingState *refill(VendingMachine *machine, int quantity) override {
    machine->increaseItemCount(quantity);
    cout << "Machine refilled with " << quantity << " items." << endl;
    return machine->getNoCoinState();
  }

  string getStateName() override { return "SoldOutState"; }
};

int main() {
  cout << "=== Water Bottle Vending Machine ===" << endl;

  int itemCount = 2;  // Initial number of items
  int itemPrice = 20; // Price per item in Rs
  VendingMachine machine(itemCount, itemPrice);
  machine.printStatus();

  // Test scenarios - each operation potentially changes the state
  cout << "1. Trying to select item without inserting coin" << endl;
  machine.selectItem();  // Should prompt to insert Coins
  machine.printStatus(); // Stays in NoCoinState

  cout << "2. Inserting Rs 10" << endl;
  machine.insertCoin(10); // Insert Rs 10
  machine.printStatus();  // Moves to HasCoinState

  cout << "3. Selecting item with insufficient balance" << endl;
  machine.selectItem();  // Should prompt for more Coins
  machine.printStatus(); // Stays in HasCoinState

  cout << "4. Inserting Rs 10 more" << endl;
  machine.insertCoin(10); // Insert Rs 10 more
  machine.printStatus();  // Stays in hasCoinState

  cout << "5. Selecting item with sufficient balance" << endl;
  machine.selectItem();  // Should move to DispenseState
  machine.printStatus(); // Moves to dispenseState

  cout << "6. Dispensing item" << endl;
  machine.dispense();    // Dispense item
  machine.printStatus(); // Moves to noCoinState

  cout << "7. Bying last item" << endl;
  machine.insertCoin(20); // Insert Rs 20
  machine.selectItem();   // Select item
  machine.dispense();     // Dispense item
  machine.printStatus();  // Moves to SoldOutState

  cout << "8. Trying to insert coin when sold out" << endl;
  machine.insertCoin(20); // Insert Rs 20
  machine.printStatus();  // Stays in SoldOutState

  cout << "9. Refilling machine with 2 items" << endl;
  machine.refill(2);     // Refill with 2 items
  machine.printStatus(); // Moves to NoCoinState

  return 0;
}
