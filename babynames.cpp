/*
 * Author: Maanas Karwa
 * It is ok to share my code anonymously for educational purposes
 * */

#include <bits/stdc++.h>

#define ll long long

using namespace std;

struct vertex {
    vertex *child[26] = {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                         nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                         nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
    vertex *parent;
    int numberOfWordsEndingInSubtree;
    char alphabet;
    bool exist;

    explicit vertex(char a, vertex *p = nullptr) : alphabet(a), exist(false) {
      parent = p;
      numberOfWordsEndingInSubtree = 0;
    }
};

class Trie {
public:
    Trie() { root = new vertex('!'); }

    vertex *root;

    void insert(const string &word) { // insert a word into trie
      vertex *cur = root;
      for (char i: word) { // O(n)
        int alphaNum = i - 'A';
        if (cur->child[alphaNum] == nullptr) // add new branch if NULL
        {
          cur->child[alphaNum] = new vertex(i, cur);
        }
        cur->numberOfWordsEndingInSubtree++;
        cur = cur->child[alphaNum];
      }
      cur->exist = true;
      cur->numberOfWordsEndingInSubtree++;
    }

    bool deleteWord(const string &word) {
      vertex *cur = root;
      int alphaNum;
      for (const char &i: word) { // O(n)
        alphaNum = i - 'A';
        if (cur->child[alphaNum] == nullptr)
          return false;
        cur = cur->child[alphaNum];
      }
      vertex *parent = cur->parent;
      if (cur->numberOfWordsEndingInSubtree > 1) {
        if (!cur->exist) {
          return false;
        }
        cur->exist = false;
        cur->numberOfWordsEndingInSubtree--;
      } else {
        parent->child[alphaNum] = nullptr;
        delete cur;
      }
      while (parent) {
        parent->numberOfWordsEndingInSubtree--;
        if (parent->numberOfWordsEndingInSubtree < 0)
          parent->numberOfWordsEndingInSubtree = 0;
        parent = parent->parent;
      }
      return true;
    }
};

/*
 * Logic: for intervals, the left bound will have to be either a substring of right bound (eg ABC, ABCDE),
 * or they will differ at a character within the min length of the two strings (eg ABD, AC)
 */
int findWordsInInterval(vertex *v, const string &l, const string &r) {
  auto minLen = min(l.length(), r.length());
  int ans = 0;
  vertex *curL = v, *curR = v; //two pointer approach
  int i = 0;
  for (; i < minLen; ++i) {
    int alphaL = l[i] - 'A', alphaR = r[i] - 'A';
    if (alphaL == alphaR) {
      curL = curL->child[alphaL];
      curR = curR->child[alphaR];
      if (curL == nullptr) { //no words in this interval since trie does not have element
        return 0;
      }
    } else {
      // at the first point of diff, both l and r will be the same.
      // we want to include all the strings between l and r, r exclusive
      // first count everything from l+1 to r-1 inclusive
      for (int j = alphaL + 1; j < alphaR; j++) {
        auto child = curL->child[j];
        if (child)
          ans += child->numberOfWordsEndingInSubtree;
      }

      // more chars left in left string
      if (curL && curL->child[alphaL]) {
        curL = curL->child[alphaL];
        int iNew = i + 1;
        if (iNew < l.length() - 1) {
          // count stuff after the chars start being diff but to the right.
          // eg for bound ABCD to AF, i want to count all strings of form ABCE..., ABCF... etc
          for (; iNew < l.length() - 1 && curL; iNew++) {
            alphaL = l[iNew] - 'A';
            for (int j = alphaL + 1; j < 26; j++)
              if (curL->child[j])
                ans += curL->child[j]->numberOfWordsEndingInSubtree;
            curL = curL->child[alphaL];
          }

          // also want to count ABCD... all
          alphaL = l[l.length() - 1] - 'A';
          if (curL && curL->child[alphaL]) {
            ans += curL->child[alphaL]->numberOfWordsEndingInSubtree;
          }
        } else { //string is over, eg AC, ADP
          //we want to count all of C's children
          ans += curL->numberOfWordsEndingInSubtree;
        }
      }

      // eg AB to AFBP
      // want to count AFA..., AFBA... to AFBO...
      // things that share some substring with right bound but not the whole thing
      if (curR && curR->child[alphaR]) {
        curR = curR->child[alphaR];
        for (int iNew = i + 1; iNew < r.length() - 1 && curR; iNew++) {
          alphaR = r[iNew] - 'A';
          for (int j = alphaR - 1; j >= 0; j--)
            if (curR->child[j])
              ans += curR->child[j]->numberOfWordsEndingInSubtree;
          curR = curR->child[alphaR];
        }
      }

      return ans;
    }
  }
  // if we reached this point, l is a substring of r. otherwise, we would have returned ans already
  assert(curL == curR);
  // eg AB, ABDF

  if (r.length() > minLen && curR) {
    ans += curR->exist; // want to include AB if it exists

    // also want to include ABA... to ABC..., ABDA... to ABDE..., etc
    int alphaR = r[minLen] - 'A';
    for (int j = 0; j < alphaR; j++) {
      if (curR->child[j])
        ans += curR->child[j]->numberOfWordsEndingInSubtree;
    }
    if (curR->child[alphaR]) {
      curR = curR->child[alphaR];
      for (; i < r.length() - 1 && curR; i++) {
        alphaR = r[i] - 'A';
        for (int j = alphaR - 1; j >= 0; j--)
          if (curR->child[j])
            ans += curR->child[j]->numberOfWordsEndingInSubtree;
        curR = curR->child[alphaR];
      }
    }
  }
  return ans;
}

Trie male, female;
int commandNumber, gender;
string name, l, r;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin.exceptions(std::istream::failbit);
  while (true) {
    cin >> commandNumber;
    if (!commandNumber)
      break;
    switch (commandNumber) {
      case 1:
        cin >> name >> gender;
        if (gender == 1) {
          male.insert(name);
        } else {
          female.insert(name);
        }
        break;
      case 2:
        cin >> name;
        if (!male.deleteWord(name))
          female.deleteWord(name);
        break;
      case 3: {
        cin >> l >> r >> gender;
        int ans;
        if (gender == 0) {
          ans = findWordsInInterval(male.root, l, r) + findWordsInInterval(female.root, l, r);
        } else if (gender == 1) {
          ans = findWordsInInterval(male.root, l, r);
        } else {
          ans = findWordsInInterval(female.root, l, r);
        }
        cout << ans << "\n";
        break;
      }
      default:
        return 2;
    }
  }
}

#undef ll
#undef u