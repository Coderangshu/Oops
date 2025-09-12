#include <bits/stdc++.h>
using namespace std;

// Implmentation Hierarchy: Engine Interface (LLL)
class Engine {
  public:
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual ~Engine() {}
};

// Concrete Implementation: Petrol Engine
class PetrolEngine : public Engine {
  public:
    void start() override { cout << "Petrol Engine Started" << endl; }
    void stop() override { cout << "Petrol Engine Stopped" << endl; }
};

// Concrete Implementation: Diesel Engine
class DieselEngine : public Engine {
  public:
    void start() override { cout << "Diesel Engine Started" << endl; }
    void stop() override { cout << "Diesel Engine Stopped" << endl; }
};

// Concrete Implementation: Electric Engine
class ElectricEngine : public Engine {
  public:
    void start() override { cout << "Electric Engine Started" << endl; }
    void stop() override { cout << "Electric Engine Stopped" << endl; }
};

// Abstraction Hierarchy: Vehicle Interface (HHL)
class Car {
  protected:
    Engine *engine; // Composition: Car has an Engine
  public:
    Car(Engine *e) : engine(e) {}
    virtual void drive() = 0;
    virtual ~Car() { delete engine; }
};

// Refined Abstraction: Sedan
class Sedan : public Car {
  public:
    Sedan(Engine *e) : Car(e) {}

    void drive() override {
        engine->start();
        cout << "Driving a Sedan" << endl;
        engine->stop();
    }
};

// Refined Abstraction: SUV
class SUV : public Car {
  public:
    SUV(Engine *e) : Car(e) {}

    void drive() override {
        engine->start();
        cout << "Driving an SUV" << endl;
        engine->stop();
    }
};

int main() {
    // Create Engine implementations on the heap
    Engine *petrolEngine = new PetrolEngine();
    Engine *dieselEngine = new DieselEngine();
    Engine *electricEngine = new ElectricEngine();

    // Create Car, injecting Engine implementations
    Car *sedanWithPetrol = new Sedan(petrolEngine);
    Car *suvWithDiesel = new SUV(dieselEngine);
    Car *sedanWithElectric = new Sedan(electricEngine);

    // Use the Car
    sedanWithPetrol->drive();
    suvWithDiesel->drive();
    sedanWithElectric->drive();

    // Clean up
    delete sedanWithPetrol;
    delete suvWithDiesel;
    delete sedanWithElectric;

    return 0;
}
