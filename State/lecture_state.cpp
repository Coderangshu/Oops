// States: Partial, Full, Empty
// Object following states: Stack

#include <bits/stdc++.h>
using namespace std;

class Stack;

// ----------------- State Interface -----------------
class State {
  public:
    virtual State *push(Stack *stk, int val) = 0;
    virtual State *pop(Stack *stk) = 0;
    virtual State *peek(Stack *stk) = 0;
    virtual string getStateName() = 0;
    virtual ~State() = default;
};

// ----------------- Concrete States Declarations -----------------
class EmptyState : public State {
  public:
    State *push(Stack *stk, int value) override;
    State *pop(Stack *stk) override;
    State *peek(Stack *stk) override;
    string getStateName() override { return "EmptyState"; }
};

class PartialState : public State {
  public:
    State *push(Stack *stk, int value) override;
    State *pop(Stack *stk) override;
    State *peek(Stack *stk) override;
    string getStateName() override { return "PartialState"; }
};

class FullState : public State {
  public:
    State *push(Stack *stk, int value) override;
    State *pop(Stack *stk) override;
    State *peek(Stack *stk) override;
    string getStateName() override { return "FullState"; }
};

// ----------------- Stack Class -----------------
class Stack {
  private:
    vector<int> data;
    int capacity;
    State *currentState;

    // Possible states
    State *emptyState;
    State *partialState;
    State *fullState;

  public:
    Stack(int cap) {
        this->capacity = cap;
        emptyState = new EmptyState();
        partialState = new PartialState();
        fullState = new FullState();
        currentState = emptyState;
    }

    ~Stack() {
        delete emptyState;
        delete partialState;
        delete fullState;
    }

    void push(int value) { currentState = currentState->push(this, value); }
    void pop() { currentState = currentState->pop(this); }
    void peek() { currentState = currentState->peek(this); }
    string getCurrentStateName() { return currentState->getStateName(); }

    State *getEmptyState() { return emptyState; }
    State *getPartialState() { return partialState; }
    State *getFullState() { return fullState; }

    bool isEmpty() const { return data.empty(); }
    bool isFull() const { return data.size() == capacity; }
    int getCurrentSize() { return data.size(); }
    int getCapacity() const { return capacity; }
    void setCapacity(int cap) { capacity = cap; }
    void pushData(int value) { data.push_back(value); }
    int popData() {
        int val = data.back();
        data.pop_back();
        return val;
    }
    int topData() const { return data.back(); }
};

// ----------------- Concrete States Implementations -----------------
State *EmptyState::push(Stack *stk, int value) {
    stk->pushData(value);
    cout << "Pushed " << value << " to stack." << endl;
    if (stk->isFull()) {
        return stk->getFullState();
    } else {
        return stk->getPartialState();
    }
}

State *EmptyState::pop(Stack *stk) {
    cout << "Stack is empty. Cannot pop." << endl;
    return this;
}

State *EmptyState::peek(Stack *stk) {
    cout << "Stack is empty. Cannot peek." << endl;
    return this;
}

State *PartialState::push(Stack *stk, int value) {
    stk->pushData(value);
    cout << "Pushed " << value << " to stack." << endl;
    if (stk->isFull()) {
        return stk->getFullState();
    } else {
        return this;
    }
}

State *PartialState::pop(Stack *stk) {
    int top = stk->popData();
    cout << "Popped " << top << " from stack." << endl;
    if (stk->isEmpty())
        return stk->getEmptyState();
    return this;
}

State *PartialState::peek(Stack *stk) {
    cout << "Top element is " << stk->topData() << endl;
    return this;
}

State *FullState::push(Stack *stk, int value) {
    cout << "Stack is full. Cannot push " << value << "." << endl;
    return this;
}

State *FullState::pop(Stack *stk) {
    int top = stk->popData();
    cout << "Popped " << top << " from stack." << endl;
    if (stk->isEmpty())
        return stk->getEmptyState();
    return stk->getPartialState();
}

State *FullState::peek(Stack *stk) {
    cout << "Top element is " << stk->topData() << endl;
    return this;
}

// ----------------- Main -----------------
int main() {
    Stack stk(3);                              // Stack with capacity 3
    stk.pop();                                 // Should indicate stack is empty
    stk.peek();                                // Should indicate stack is empty
    cout << stk.getCurrentStateName() << endl; // Should be EmptyState

    stk.push(10);
    cout << stk.getCurrentStateName() << endl; // Should be PartialState

    stk.push(20);
    cout << stk.getCurrentStateName() << endl; // Should be PartialState

    stk.peek();                                // Should show top element 20
    stk.push(30);                              // Stack is now full
    cout << stk.getCurrentStateName() << endl; // Should be FullState

    stk.push(40);                              // Should indicate stack is full
    cout << stk.getCurrentStateName() << endl; // Should be FullState

    stk.pop();                                 // Should pop 30
    cout << stk.getCurrentStateName() << endl; // Should be PartialState
    stk.peek();                                // Should show top element 20

    stk.pop();                                 // Should pop 20
    cout << stk.getCurrentStateName() << endl; // Should be PartialState

    stk.pop(); // Should pop 10 and stack becomes empty
    cout << stk.getCurrentStateName() << endl; // Should be PartialState

    stk.pop();                                 // Should indicate stack is empty
    cout << stk.getCurrentStateName() << endl; // Should be EmptyState

    return 0;
}
