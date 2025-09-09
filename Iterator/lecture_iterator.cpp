#include <bits/stdc++.h>
using namespace std;

int main() {
  vector<int> v = {1, 2, 3, 4, 5};
  vector<int>::iterator it = v.begin();
  int sum = 0;
  for (; it != v.end(); it++) {
    sum += *it;
  }
  cout << "Sum: " << sum << endl;

  set<int> s = {1, 2, 3, 4, 5};
  set<int>::iterator sit = s.begin();
  for (; sit != s.end(); sit++) {
    cout << *sit << " ";
  }
  cout << endl;
}
