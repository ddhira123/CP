#include <bits/stdc++.h>
using namespace std;

struct Journal {
  string title;
  string subtitle;
  string name;
  int volume;
  int issue;
  int year;

  void read() {
    getline(cin, title);
    getline(cin, subtitle);
    getline(cin, name);
    cin >> volume;
    cin >> issue;
    cin >> year;
  }

  bool operator <(Journal other) const {
    if(name == other.name) {
      if(year == other.year) {
        if(volume == other.volume) {
          if(issue == other.issue) {
            if(title == other.title)
              return subtitle < other.subtitle;
            return title < other.title;
          }
          return issue < other.issue;
        }
        return volume < other.volume;
      }
      return year < other.year;
    }
    return name < other.name;
  }

  void print() {
    cout << "title: " << title << "\n";
    cout << "subtitle: " << subtitle << "\n";
    cout << "journal info\n";
    cout << "_name: " << name << "\n";
    cout << "_volume: " << volume << "\n";
    cout << "_issue: " << issue << "\n";
    cout << "_publication year: " << year << "\n";
  }
};

const int N = 100005;
Journal arr[N];
int n;

int main() {
  cin >> n;
  for(int i = 0 ; i < n ; i++) {
    string dummy; getline(cin, dummy);
    arr[i].read();
  }
  sort(arr, arr + n);

  for(int i = 0 ; i < n ; i++) {
    if(i) puts("");
    arr[i].print();
  }
  return 0;
}