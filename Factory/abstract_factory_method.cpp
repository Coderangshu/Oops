#include <bits/stdc++.h>
using namespace std;

class Burger {
public:
  virtual void prepare() = 0;
  virtual ~Burger() {}
};

class BasicBurger : public Burger {
public:
  void prepare() override {
    cout << "Preparing Basic Burger with bun, patty, and ketchup!" << endl;
  }
};

class StandardBurger : public Burger {
public:
  void prepare() override {
    cout << "Preparing Standard Burger with bun, patty, cheese, and lettuce!"
         << endl;
  }
};

class PremiumBurger : public Burger {
public:
  void prepare() override {
    cout << "Preparing Premium Burger with gourmet bun, premium patty, cheese, "
            "lettuce, and secret sauce!"
         << endl;
  }
};

class BasicWheatBurger : public Burger {
public:
  void prepare() override {
    cout << "Preparing Basic Wheat Burger with bun, patty, and ketchup!"
         << endl;
  }
};

class StandardWheatBurger : public Burger {
public:
  void prepare() override {
    cout << "Preparing Standard Wheat Burger with bun, patty, cheese, and "
            "lettuce!"
         << endl;
  }
};

class PremiumWheatBurger : public Burger {
public:
  void prepare() override {
    cout << "Preparing Premium Wheat Burger with gourmet bun, premium patty, "
            "cheese, "
            "lettuce, and secret sauce!"
         << endl;
  }
};

class GarlicBread {
public:
  virtual void prepare() = 0;
};

class BasicGarlicBread : public GarlicBread {
public:
  void prepare() override {
    cout << "Preparing Basic Garlic Bread with butter and garlic!" << endl;
  }
};

class CheeseGarlicBread : public GarlicBread {
public:
  void prepare() override {
    cout << "Preparing Cheese Garlic Bread with with extra chees, butter and "
            "garlic!"
         << endl;
  }
};

class BasicWheatGarlicBread : public GarlicBread {
public:
  void prepare() override {
    cout << "Preparing Basic Wheat Garlic Bread with butter and garlic!"
         << endl;
  }
};

class CheeseWheatGarlicBread : public GarlicBread {
public:
  void prepare() override {
    cout << "Preparing Cheese Wheat Garlic Bread with with extra chees, butter "
            "and "
            "garlic!"
         << endl;
  }
};

class MealFactory {
public:
  virtual Burger *createBurger(string &type) = 0;
  virtual GarlicBread *createGarlicBread(string &type) = 0;
};

class SinghMeal : public MealFactory {
public:
  Burger *createBurger(string &type) override {
    if (type == "basic") {
      return new BasicBurger();
    } else if (type == "standard") {
      return new StandardBurger();
    } else if (type == "premium") {
      return new PremiumBurger();
    } else {
      cout << "Invalid burger type!" << endl;
      return nullptr;
    }
  }

  GarlicBread *createGarlicBread(string &type) override {
    if (type == "basic")
      return new BasicGarlicBread();
    else if (type == "cheese")
      return new CheeseGarlicBread();
    else {
      cout << "Invalid Garlic Bread type" << endl;
      return nullptr;
    }
  }
};

class KingMeal : public MealFactory {
public:
  Burger *createBurger(string &type) {
    if (type == "basic") {
      return new BasicWheatBurger();
    } else if (type == "standard") {
      return new StandardWheatBurger();
    } else if (type == "premium") {
      return new PremiumWheatBurger();
    } else {
      cout << "Invalid burger type!" << endl;
      return nullptr;
    }
  }

  GarlicBread *createGarlicBread(string &type) override {
    if (type == "basic")
      return new BasicWheatGarlicBread();
    else if (type == "cheese")
      return new CheeseWheatGarlicBread();
    else {
      cout << "Invalid Garlic Bread type" << endl;
      return nullptr;
    }
  }
};

int main() {
  string burgerType = "basic";
  string garlicBreadType = "cheese";

  MealFactory *mf = new KingMeal();

  Burger *b = mf->createBurger(burgerType);
  GarlicBread *gb = mf->createGarlicBread(garlicBreadType);

  b->prepare();
  gb->prepare();
  // mybf = new SinghBurger();
  // type = "premium";
  // b = mybf->createBurger(type);
  // b->prepare();
  return 0;
}
