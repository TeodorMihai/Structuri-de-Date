#include <cmath>
#include <unordered_set>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main(int argc, char* argv[]) {
  if (argc < 6) {
    return 1;
  }
  stringstream ss;

  double score;
  ss << argv[5] << endl;
  ss >> score;

  ifstream test(argv[2], ios::in);
  ifstream student(argv[3], ios::in);
  ifstream correct(argv[4], ios::in);

  string file_name;
  test >> file_name;

  // Check for first task
  bool is_correct = true;
  int m;
  test >> m;
  for (int i = 0; i < m; i++) {
    string word1;
    string word2;
    test >> word1;
    test >> word2;
    double score1, score2;
    student >> score1;
    correct >> score2;
    if (abs(score1 - score2) > 0.01) {
      cout << word1 << " -> " << word2 << " :: "
           << score1 << " != " << score2 << endl;
      is_correct = false;
      break;
    }
  }

  if (!is_correct) {
    cout << "-" << score << "p : Testul " << argv[1] << endl;
    return 0;
  }

  // Check for second task
  int n;
  test >> n;
  for (int i = 0; i < n; i++) {
    string word1;
    string word2;
    test >> word1;
    test >> word2;
    string line1;
    string line2;
    getline(student, line1);
    getline(correct, line2);
    if (line1 != line2) {
      cout << "From " << word1 << " to " << word2 << ":" << endl
           << line1 << endl << " vs. " << line2 << endl;
      is_correct = false;
      break;
    }
  }
  if (!is_correct) {
    cout << "-" << score << "p : Testul " << argv[1] << endl;
    return 0;
  }
  // BONUS
  int b;
  test >> b;
  for (int i = 0; i < b; i++) {
    int n;
    string word;
    test >> n;
    test >> word;
    unordered_set<string> solutions;
    int n1;
    string line1;
    correct >> n1;
    for (int j = 0; j < n1; j++) {
      getline(correct, line1);
      solutions.insert(line1);
    }
    int n2;
    student >> n2;
    if (n1 != n2) {
      cout << "Different number of solutions: " << n1 << "!=" << n2 << endl;
      is_correct = false;
      break;
    }
    string line2;
    for (int j = 0; j < n2; j ++) {
      getline(student, line2);
      if (solutions.find(line2) == solutions.end()) {
        cout << n << " words phrase ending with \"" << word << "\":" << endl
             << line2 << endl
             << "is not a solution!" << endl;
        is_correct = false;
        break;
      }
    }
    if (is_correct == false) {
      break;
    }
  }
  if (!is_correct) {
    cout << "-" << score << "p : Testul " << argv[1] << endl;
    return 0;
  } else {
    cout << "Testul " << argv[1] << " trecut!" << endl;
  }
  test.close();
  student.close();
  correct.close();
  return 0;
}
