#include <map>
#include <set>
#include <cmath>
#include <string>
#include <fstream>
#include <iostream>
#include "csvstream.hpp"
using namespace std;

class Classifier {
  private:
  int testing_post;
  int training_post;     
  set<string> word_list;   
  map<pair<string, string>, double> likelihood_predict;
  map<string, int> label_count;
  map<string, int> word_count;
  map<string, map<string, int>> word_label;
  map<string, int> label_examples;
  string training_file;
  string testing_file;
  bool debug;

  public:
  //default constructor
  Classifier() 
  : testing_post(0), training_post(0) {}
 //need overloaded constructor with files passed in and debug mode
  Classifier(string file_trained, string file_tested, 
  bool mode_debugged)
   : testing_post(0), training_post(0), 
   training_file(file_trained), 
   testing_file(file_tested), debug(mode_debugged) {}

    // Destructor
  ~Classifier() {}

   // EFFECTS: Return a set of unique whitespace delimited words.x
  //From specs
  set<string> unique_words(const string &str) {
    istringstream source(str);
    set<string> words;
    string word;
    while (source >> word) {
        words.insert(word);
    }
    return words;
  }

  //Training Section
  void training( ){
        csvstream csvin(training_file);
        map<string, string> row;
        string word_bank;

        if(debug){
            cout << "training data:" << "\n";
        }
        while (csvin >> row) {
            ++label_count[row["tag"]];
            set<string> words = unique_words(row["content"]);
            for(auto it = words.begin(); it != words.end(); ++it){
                ++word_count[*it];
                ++word_label[row["tag"]][*it];
            }

            if(debug) {
                cout << "  label = " << row["tag"] 
                << ", content = " << row["content"] << "\n";
            }

            ++training_post;
            word_bank = word_bank + " " + row["content"];
        }

        word_list = unique_words(word_bank);
        cout << "trained on " << training_post 
        << " examples" << endl;
        cout << endl;
        if(debug) {
         cout << "vocabulary size = " << 
         word_list.size() << endl;
         cout << endl;
        //execute debugging func
        debugging();
        cout << endl;
        }
        testing_data();
    }

  double prior(const string &labeled) {
      double label_c = label_count[labeled] / 
      static_cast<double>(training_post);
      return log(label_c);
  }

  double prediction_likelihood(const string &word, 
  const string &label) {
    double W_label_C = 0;

    //Use when w does not occur anywhere at all in the training set.
    if(word_count[word] == 0) { 
        W_label_C = 1.0 / static_cast<double>(training_post);
    } 
    //Use when w does not occur in posts labeled 
 // but C does occur in the training data overall
    else if(word_label[label][word] == 0) {  
        W_label_C = static_cast<double>(word_count[word]) /
         static_cast<double>(training_post);
    } 
    //if neither the regular formula
    else {
      W_label_C = static_cast<double>(word_label[label][word]) / 
    static_cast<double>(label_count[label]);
    }
    return log(W_label_C);

  }

  double probability_score(const string &label, 
  set<string> words){
    double log_probability;
    for(auto i = words.begin(); i != words.end(); ++i){
        log_probability += prediction_likelihood(*i, label);
    }
    return prior(label) + log_probability;
  }

  pair<string, double> highest_probability_score(set<string> 
  data){
    map<string, double> label_score;
    for(const auto &kv : label_count){
       label_score[kv.first] = 
       probability_score(kv.first, data);
    }
    double max = (*label_score.begin()).second;
    string best_label = (*label_score.begin()).first;
    for(const auto &kv : label_score){
        if(label_score[kv.first] > max){
            max = label_score[kv.first];
            best_label = kv.first;
        }
    }
    return {best_label, max};
  }
  void debugging(){
    cout << "classes:" << "\n";
    for (const auto &kv : label_count) {    
        const auto &labeled = kv.first;
        const auto &examples = kv.second;
        cout << "  " << labeled << ", " << examples << 
        " examples, " 
        << "log-prior = " << prior(labeled) << endl;
    }
    cout << "classifier parameters:" << endl;  
    for (const auto &kv : word_label) {
        const auto &label = kv.first;
        for(const auto &second_kv : kv.second){
            const auto &word = second_kv.first;
            const auto &count = second_kv.second;
            cout << "  " << label << ":" << word << 
            ", count = " << count 
            << ", log-likelihood = " 
            << prediction_likelihood(word, label) << endl;
        }
    }
  }

  //Testing Data
  void testing_data(){
    int correct_predictions = 0;

    cout << "test data:" << endl;
    csvstream test(testing_file);
    map<string, string> row;
    while(test >> row){
        set<string> data = unique_words(row["content"]);
        cout << "  correct = " << row["tag"] << ", predicted = " 
        << highest_probability_score(data).first
         << ", log-probability score = " <<
          highest_probability_score(data).second << endl;
        cout << "  content = " << row["content"] << endl;
        cout << endl;
        if(row["tag"] == 
        highest_probability_score(data).first){
            ++correct_predictions;
        }
    ++testing_post;
    }
    cout << "performance: " << correct_predictions << " / " << 
    testing_post << " posts predicted correctly" << endl;
  }
};
//main
int main(int argc, char *argv[]){
    cout.precision(3);

    string first_file = argv[1];
    string second_file = argv[2];
    string debug = "--debug";    

    csvstream csvin_first(first_file);
    csvstream csvin_second(second_file);

    ifstream first;
    ifstream second;
    first.open(first_file);
    second.open(second_file);

    //check command line arguments

    if(argc != 3 && argc != 4){
      cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" 
      << "\n";
      return 1;
    }
    if(argc == 4 && (argv[3] != debug)){
        cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]"
         << "\n";
        return 1;
    }
     //files dont open
    if (first.fail()) {
       cout << "Error opening file: " << first_file << "\n";
    }
    if (second.fail()) {
       cout << "Error opening file: " << second_file << "\n";
    }

    //for debugging
    if (argc == 3) {
      Classifier c(first_file, second_file, 1);
      c.training();
    }
    if (argc == 4) {
      Classifier c (first_file, second_file, 1);
      c.training();
    }
    first.close();
    second.close();
return 1;
}
