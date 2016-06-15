#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int powers_2[] = {1,2,4,8,16,32,64,128,256,512};

class Reading {
  private:
    int reading;
    int precision;
    int hash;
  public:
    int get_hash() {
      return hash;
    }
  
    friend ostream& operator<<(ostream& os, const Reading& r);
    friend istream& operator>>(istream& os, Reading& r);
};

ostream& operator<<(ostream& os, const Reading& r) {
  os << r.reading << " " << r.precision;
  return os;
}

istream& operator>>(istream& is, Reading& r) {
  is >> r.reading >> r.precision;
  r.hash = (1024*powers_2[10-r.precision] + 1)*r.reading;
  return is;
}

bool sortOrder(Reading a, Reading b) {
  return a.get_hash() < b.get_hash();
}

int main() {
  int n;
  cin >> n;
  vector<Reading> readings(n);
  while(n--) {
    cin >> readings[n];
  }
  sort(readings.begin(), readings.end(), sortOrder);
  for(vector<Reading>::iterator i = readings.begin(); i != readings.end(); i++) {
    cout << *i << endl;
  }
  return 0;
}
