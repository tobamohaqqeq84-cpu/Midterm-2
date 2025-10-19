// Toba Mohaqqeq
// COMSC-210
// Midterms 2

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList {
private:
  struct Node {
    string data;
    Node *prev;
    Node *next;
    Node(string val, Node *p = nullptr, Node *n = nullptr) {
      data = val;
      prev = p;
      next = n;
    }
  };

  Node *head;
  Node *tail;

public:
  DoublyLinkedList() {
    head = nullptr;
    tail = nullptr;
  }

  void push_back(string v) {
    Node *newNode = new Node(v);
    if (!tail)
      head = tail = newNode;
    else {
      tail->next = newNode;
      newNode->prev = tail;
      tail = newNode;
    }
  }

  void push_front(string v) {
    Node *newNode = new Node(v);
    if (!head)
      head = tail = newNode;
    else {
      newNode->next = head;
      head->prev = newNode;
      head = newNode;
    }
  }

  void pop_front() {
    if (!head)
      return;
    Node *temp = head;
    if (head->next) {
      head = head->next;
      head->prev = nullptr;
    } else
      head = tail = nullptr;
    delete temp;
  }

  void pop_back() {
    if (!tail)
      return;
    Node *temp = tail;
    if (tail->prev) {
      tail = tail->prev;
      tail->next = nullptr;
    } else
      head = tail = nullptr;
    delete temp;
  }

  int size() {
    int count = 0;
    Node *temp = head;
    while (temp) {
      count++;
      temp = temp->next;
    }
    return count;
  }
  string get_at_pos(int pos) {
    Node *temp = head;
    for (int i = 0; i < pos && temp; ++i)
      temp = temp->next;
    return temp ? temp->data : "";
  }
  void delete_pos(int pos) {
    if (!head)
      return;
    if (pos == 0) {
      pop_front();
      return;
    }
    Node *temp = head;
    for (int i = 0; i < pos && temp; ++i)
      temp = temp->next;
    if (!temp)
      return;

    if (temp->prev)
      temp->prev->next = temp->next;
    if (temp->next)
      temp->next->prev = temp->prev;
    if (temp == tail)
      tail = temp->prev;
    delete temp;
  }
  bool empty() { return head == nullptr; }

  void print() {
    Node *current = head;
    if (!current) {
      cout << "    List is empty." << endl;
      return;
    }
    while (current) {
      cout << current->data << "     ";
      current = current->next;
    }
    cout << endl;
  }
  string front() {
    if (head != nullptr)
      return head->data;
    else
      return "";
  }
  string back() {
    if (tail != nullptr)
      return tail->data;
    else
      return "";
  }
};

int main() {
  srand(time(0));

  ifstream file("names.txt");
  vector<string> names;
  string name;
  while (getline(file, name)) {
    if (!name.empty())
      names.push_back(name);
  }
  DoublyLinkedList line;

  cout << "Store opens:" << endl;

  for (int i = 0; i < 5; ++i) {
    int randomIndex = rand() % names.size();
    string n = names[randomIndex];
    cout << "    " << n << " joins the line." << endl;
    line.push_back(n);
  }
  cout << "Resulting line: " << endl;
  line.print();

  for (int minute = 2; minute <= 20; ++minute) {
    cout << "Time Step #" << minute << ":" << endl;

    if (rand() % 100 < 40 && !line.empty()) {
      cout << "    " << line.front() << " is served." << endl;
      line.pop_front();
    }

    if (rand() % 100 < 60) {
      int randomIndex = rand() % names.size();
      string n = names[randomIndex];
      cout << "    " << n << " joins the line." << endl;
      line.push_back(n);
    }
    if (rand() % 100 < 20 && !line.empty()) {
      cout << "    " << line.back() << " leaves the line." << endl;
      line.pop_back();
    }
    if (rand() % 100 < 10 && !line.empty()) {
      int randomIndex = rand() % line.size();
      string leaving = line.get_at_pos(randomIndex);
      cout << "    " << leaving << " left the line." << endl;
      line.delete_pos(randomIndex);
    }
    if (rand() % 100 < 10) {
      int randomIndex = rand() % names.size();
      string n = names[randomIndex];
      cout << "   " << n << "(VIP) joins the front line." << endl;
      line.push_front(n);
    }
    cout << "Resulting line: " << endl;
    line.print();
  }

  cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS; // dummy statement to avoid
  // compiler warning
  return 0;
}
