#include <iostream>
#include <cstdio>
using namespace std;

int factorial(int n) {
  if(n <= 1) {
    return 1;
  } else {
    return (n*factorial(n-1)) %10;
  }
}

int main() {
  int x;
  cin >> x;
  cout << factorial(x) << endl;
  return 0;
}
