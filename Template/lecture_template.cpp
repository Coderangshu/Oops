// Tax Calculator: Tax = total earning X x - total investments X y
//
// 3 Types of TaxCalculators : Salaried, IndividualSellers, Companies
//
//
// x and y change for each taxpayer

#include <bits/stdc++.h>
using namespace std;

class TaxCalculator {
  public:
    void calculateTax(double totalEarnings, double totalInvestments) {
        double tax = (totalEarnings * getX()) - (totalInvestments * getY());
        cout << "Total Tax: " << tax << endl;
    }
    virtual double getX() const = 0;
    virtual double getY() const = 0;
};

class SalariedTaxCalculator : public TaxCalculator {
  public:
    double getX() const override { return 0.1; }
    double getY() const override { return 0.05; }
};

class IndividualSellerTaxCalculator : public TaxCalculator {
  public:
    double getX() const override { return 0.15; }
    double getY() const override { return 0.1; }
};

class CompanyTaxCalculator : public TaxCalculator {
  public:
    double getX() const override { return 0.25; }
    double getY() const override { return 0.2; }
};

int main() {
    vector<TaxCalculator *> taxCalculators = {
        new SalariedTaxCalculator(), new IndividualSellerTaxCalculator(),
        new CompanyTaxCalculator()};

    for (auto taxCalculator : taxCalculators) {
        taxCalculator->calculateTax(100000, 20000);
    }

    return 0;
}
