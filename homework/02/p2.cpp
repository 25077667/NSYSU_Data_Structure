#include <algorithm>
#include <iostream>
#include <set>
using namespace std;

class TSet {
public:
  TSet() { this->_set.clear(); }
  TSet(const TSet &);
  TSet(const set<char> &);
  const set<char> &getSet() const;
  friend const TSet operator+(const TSet &, const TSet &);
  friend const TSet operator-(const TSet &, const TSet &);
  friend const TSet operator*(const TSet &, const TSet &);
  const TSet operator=(const set<char> &);
  const TSet operator=(const TSet &);
  friend const bool operator>=(const TSet &, const TSet &);
  const bool have(const char);
  friend ostream &operator<<(ostream &, const TSet &);
  friend istream &operator>>(istream &, TSet &);

private:
  set<char> _set;
};

int main() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    TSet A, B;
    char element;

    cin.ignore();
    cin >> A >> B >> element;

    TSet C, D;
    C = A + B;
    D = A * B;

    cout << "Test Case " << (i + 1) << ":" << endl;
    cout << "A: " << A << endl
         << "B: " << B << endl
         << "A+B: " << C << endl
         << "A*B: " << D << endl
         << "A-B: " << (A - B) << endl
         << "B-A: " << (B - A) << endl;
    // is contain?
    cout << "A " << ((A >= B) ? "contains " : "does not contain ") << "B"
         << endl;
    cout << "B " << ((B >= A) ? "contains " : "does not contain ") << "A"
         << endl;
    // is in?
    cout << "\'" << element << "\' is " << ((A.have(element)) ? "" : "not ")
         << "in A" << endl;
    cout << "\'" << element << "\' is " << ((B.have(element)) ? "" : "not ")
         << "in B" << endl;
  }

  return 0;
}

TSet::TSet(const TSet &source) {
  this->_set.clear();
  set<char> sourceSet = source.getSet();
  for (set<char>::iterator iter = sourceSet.begin(); iter != sourceSet.end();
       iter++)
    this->_set.insert(*iter);
}

TSet::TSet(const set<char> &source) { this->_set = source; }

const set<char> &TSet::getSet() const { return this->_set; }

const TSet operator+(const TSet &A, const TSet &B) {
  TSet result(A);
  set<char> sourceSet = B.getSet();
  for (set<char>::iterator iter = sourceSet.begin(); iter != sourceSet.end();
       iter++) {
    result._set.insert(*iter);
  }
  return TSet(result);
}

const TSet operator*(const TSet &A, const TSet &B) {
  set<char> intersect;
  set<char> s1 = A.getSet();
  set<char> s2 = B.getSet();
  set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(),
                   std::inserter(intersect, intersect.begin()));
  return TSet(intersect);
}

const TSet operator-(const TSet &A, const TSet &B) {
  set<char> difference;
  set<char> s1 = A.getSet();
  set<char> s2 = B.getSet();
  set_difference(s1.begin(), s1.end(), s2.begin(), s2.end(),
                 std::inserter(difference, difference.begin()));
  return TSet(difference);
}

const TSet TSet::operator=(const set<char> &source) {
  this->_set = source;
  return TSet(source);
}

const TSet TSet::operator=(const TSet &source) {
  this->_set = source.getSet();
  return TSet(source.getSet());
}

const bool operator>=(const TSet &A, const TSet &B) {
  TSet difference(B - A);
  set<char> deffSet = difference.getSet();
  return (deffSet.size() == 0);
}

const bool TSet::have(const char _element) {
  auto it = find(this->getSet().begin(), this->getSet().end(), _element);
  return it != this->getSet().end();
}

ostream &operator<<(ostream &output, const TSet &source) {
  set<char> the_set = source.getSet();
  output << "{";
  for (auto iter = the_set.begin(); iter != the_set.end(); ++iter)
    output << *iter;
  output << "}";
  return output;
}

istream &operator>>(istream &input, TSet &destination) {
  set<char> container;
  string inString;
  getline(input, inString);
  while (inString.size()) {
    destination._set.insert(inString.back());
    inString.pop_back();
  }
  return input;
}