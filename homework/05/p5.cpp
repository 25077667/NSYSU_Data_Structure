#include <iostream>
#include <utility>
using namespace std;

struct Term {
  int coef, exp;
  Term *next;
  Term(const int _coef, const int _exp, Term *_next = nullptr)
      : coef(_coef), exp(_exp), next(_next) {}
};

class Chain {
public:
  Chain() { this->head = nullptr; }
  pair<Term *, bool> findExp(int _exp);
  void addNode(int _coef, int _exp);
  void cleanNode();
  void freeChain();

protected:
  Term *head = nullptr;
};

class Poly : public Chain {
public:
  Poly() { Chain(); }
  Poly operator+(const Poly);
  Poly operator*(const Poly);
  friend ostream &operator<<(ostream &, const Poly &);
};

int main() {
  int p, q, cases = 1, coef, exp;
  Poly A, B, C, D;
  while (1) {
    A.freeChain();
    B.freeChain();
    C.freeChain();
    D.freeChain();

    cin >> p;
    for (int i = 0; i < p; i++) {
      cin >> coef >> exp;
      A.addNode(coef, exp);
    }
    cin >> q;
    for (int i = 0; i < q; i++) {
      cin >> coef >> exp;
      B.addNode(coef, exp);
    }
    if (p == 0 && q == 0)
      break;

    C = A + B;
    D = A * B;

    printf("Case%d:\n", cases++);
    cout << "ADD\n" << C << "MULTIPLY\n" << D;
  }
  return 0;
}

pair<Term *, bool> Chain::findExp(int _exp) {
  Term *current = this->head, *preverious = nullptr;
  for (; current && current->exp >= _exp; current = current->next)
    preverious = current;
  return make_pair(preverious, preverious && preverious->exp == _exp);
}

void Chain::addNode(int _coef, int _exp) { // need sort first
  auto newTerm = new Term(_coef, _exp);
  if (this->head) { // if chain is not empty
    auto [insertPlace, isExist] =
        findExp(_exp); // find where can I insert new Term in

    if (isExist) {
      insertPlace->coef += _coef; // has the same exp just add the coef
      delete newTerm;
    } else if (insertPlace == nullptr) {
      newTerm->next = this->head;
      this->head = newTerm; // _exp greater than head
    } else if (insertPlace == this->head) {
      newTerm->next = this->head->next;
      this->head->next = newTerm;
    } else if (insertPlace->next) {
      newTerm->next = insertPlace->next;
      insertPlace->next = newTerm; // the middle of the Chain
    } else
      insertPlace->next = newTerm; // the tail
  } else
    this->head = newTerm;
}

void Chain::cleanNode() {
  auto current = this->head, preverious = this->head;
  while (current) {
    auto theNext = current->next;
    preverious = ((current->coef) ? current : preverious);
    if (!current->coef) {
      ((current == this->head) ? this->head : preverious->next) = current->next;
      delete current;
    }
    current = theNext;
  }
}

void Chain::freeChain() {
  auto temp = this->head;
  for (auto i = this->head; i != nullptr; i = temp) {
    temp = i->next;
    delete (i);
  }
  this->head = nullptr; // after delete need to reset the head, or it will be
                        // dangling pointer
}

Poly Poly::operator+(const Poly source) {
  Poly *result = new Poly();
  for (auto i = this->head; i != nullptr; i = i->next)
    result->addNode(i->coef, i->exp);
  for (auto i = source.head; i != nullptr; i = i->next)
    result->addNode(i->coef, i->exp);
  result->cleanNode();
  return *result;
}

Poly Poly::operator*(const Poly source) {
  Poly *result = new Poly();
  for (auto i = source.head; i != nullptr; i = i->next)
    for (auto j = this->head; j != nullptr; j = j->next)
      result->addNode(i->coef * j->coef, i->exp + j->exp);
  result->cleanNode();
  return *result;
}

ostream &operator<<(ostream &output, const Poly &source) {
  for (auto i = source.head; i != nullptr; i = i->next)
    output << i->coef << " " << i->exp << endl;
  if (source.head == nullptr)
    output << "0 0" << endl;
  return output;
}