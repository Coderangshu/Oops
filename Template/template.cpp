#include <bits/stdc++.h>
using namespace std;

// ---------------------------------------------
// 1. Base class defining the template method
// ---------------------------------------------
class ModelTrainer {
  public:
    // The template medho - final so subclasses can't changethe sequence
    void trainPipeline(const string &dataPath) {
        loadData(dataPath);
        preprocessData();
        trainModel();
        evaluateModel();
        saveModel();
    }

  protected:
    void loadData(const string &dataPath) {
        cout << "[Common] Loading data from: " << dataPath << endl;
        // Simulate data loading
    }

    virtual void preprocessData() {
        cout << "[Common] Splitting into train/test and normalizing data"
             << endl;
        // Common preprocessing steps
    }
    // Pure virtual - must be implemented by subclasses
    virtual void trainModel() = 0;
    // Pure virtual - must be implemented by subclasses
    virtual void evaluateModel() = 0;

    // Provide a default save, but subclasses can override if needed
    virtual void saveModel() {
        cout << "[Common] Saving model to disk" << endl;
        // Simulate model saving
    }
};

// ---------------------------------------------
// 2. Concreate subclass for Neural Network
// ---------------------------------------------
class NeuralNetworkTrainer : public ModelTrainer {
  protected:
    void trainModel() override {
        cout << "[NeuralNetwork] Training neural network model" << endl;
        // Simulate NN training
    }

    void evaluateModel() override {
        cout << "[NeuralNetwork] Evaluating neural network model" << endl;
        // Simulate NN evaluation
    }

    void saveModel() override {
        cout << "[NeuralNetwork] Saving neural network model with custom format"
             << endl;
        // Simulate custom NN model saving
    }
};

// ---------------------------------------------
// 3. Concreate subclass for Decision Tree
// ---------------------------------------------
class DecisionTreeTrainer : public ModelTrainer {
  protected:
    void trainModel() override {
        cout << "[DecisionTree] Training decision tree model" << endl;
        // Simulate DT training
    }

    void evaluateModel() override {
        cout << "[DecisionTree] Evaluating decision tree model" << endl;
        // Simulate DT evaluation
    }
};

// ---------------------------------------------
// 4. Usage
// ---------------------------------------------
int main() {
    cout << "=== Neural Network Training ===" << endl;
    ModelTrainer *nnTrainer = new NeuralNetworkTrainer();
    nnTrainer->trainPipeline("data/neural_network_data.csv");
    delete nnTrainer;

    cout << "\n=== Decision Tree Training ===" << endl;
    ModelTrainer *dtTrainer = new DecisionTreeTrainer();
    dtTrainer->trainPipeline("data/decision_tree_data.csv");
    delete dtTrainer;

    return 0;
}
