/*
 * Author: Maanas Karwa
 * It is ok to share my code anonymously for educational purposes
 * */

#include <iostream>
#include <map>
#include <vector>
#include <cstring>

using namespace std;

int t, f, person_count = 0;
map<string, int> name_to_number;

int network_size[100001];
int parent[100001];

/*
 * Code modified from CP slides
 */

int find(int p) {
  if (p == parent[p]) return p;
  parent[p] = find(parent[p]); // path compression
  return parent[p];
}

void union_sets(int p, int q) {
  int a = find(p), b = find(q);
  if (a == b) {
    return;
  }
  if (network_size[a] <= network_size[b]) {
    network_size[b] += network_size[a];
    parent[a] = b;
  } else {
    network_size[a] += network_size[b];
    parent[b] = a;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    memset(parent, -1, sizeof(parent));
    memset(network_size, 0, sizeof(network_size));
    name_to_number.clear();
    person_count = 0;
    cin >> f;
    while (f--) {
      string a, b;
      cin >> a >> b;
      if (name_to_number.find(a) == name_to_number.end()) {
        name_to_number[a] = person_count;
        parent[person_count] = person_count;
        network_size[person_count] = 1;
        ++person_count;
      }
      if (name_to_number.find(b) == name_to_number.end()) {
        name_to_number[b] = person_count;
        parent[person_count] = person_count;
        network_size[person_count] = 1;
        ++person_count;
      }
      int a_num = name_to_number[a], b_num = name_to_number[b];
      int a_find = find(a_num), b_find = find(b_num);
      // if already in same set, output network size. else, union and then output
      // note: always use find since only the root's value is guaranteed to update
      if (a_find != b_find) union_sets(a_num, b_num);
      cout << network_size[find(a_num)] << "\n";
    }
  }
  return 0;
}