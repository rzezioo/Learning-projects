#include <iostream>
#include <cstdio>
#include <string>
#include <cstdlib>
using namespace std;

int power_of_2(int n) {
  if(n == 0) {
    return 1;
  } else {
    switch (n%4) {
      case 0: return 6; break;
      case 1: return 2; break;
      case 2: return 4; break;
      case 3: return 8; break;
    }
  }
}

int parse_last_three_digits(string s) {
  bool truncated = false;
  if(s.length() > 3) {
    s = s.substr(s.length() - 3);
    truncated = true;
  }
  int res = atoi(s.c_str());
  if(truncated) {
    res += 1000;
  }
  return res;
}

int main() {
  string input;
  cin >> input;
  int x = parse_last_three_digits(input);
  cout << power_of_2(x) << endl;
  return 0;
}
