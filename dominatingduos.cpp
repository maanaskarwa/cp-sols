/*
 * Author: Maanas Karwa
 * It is ok to share my code anonymously for educational purposes
 * */

#include <bits/stdc++.h>

#define ll long long
using namespace std;

//stack with preallocated space for 10^6 nums. Nothing else
typedef struct customStackStruct {
  int s[1000000] = { 0 };
  int size = 0;
  int top = -1;

  void push(int number) {
    s[size++] = number;
    top = number;
  }

  void pop() {
    top = s[--size - 1];
  }

  [[nodiscard]] bool empty() const {
    return !size;
  }

  void clear() {
    size = 0;
  }
} customStack;

int n, nums[1000000], num;
ll ans = 0;
customStack s1;

/*
 * All dominating duos will be of 2 types - first person of the duo is taller / second person is taller
 * Maintain a monotonic stack and compute ans for each type.
 * Monotonically decreasing stack. If there is any number in the stack when you are inserting this num,
 * it means that a pair could have been formed.
 * Note that any 2 adjacent numbers are also duos. So even if the stack only has 1 element, it means that this element and that element form a duo
 * Hence, if our stack has elements, we increment our ans.
 * When we run into a bigger number, we pop off the stack since the numbers being popped couldn't have made a duo with any number following the bigger one anyways
 *
 * Repeat same thing in both directions to cover all duos
 */
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n;
  for (int i = 0; i < n; i++) cin >> nums[i];


#define SOLVE {                                   \
  num = nums[i];                                  \
  if (s1.empty()) { s1.push(num); }               \
  else if (s1.top > num) {                        \
    s1.push( num);                                \
    ans++;                                        \
  } else {                                        \
    s1.pop();                                     \
    while (!s1.empty() && s1.top < num) s1.pop(); \
    if (s1.empty()) { s1.push(num); }             \
    else {                                        \
      s1.push(num);                               \
      ans++;                                      \
    }                                             \
  }                                               \
}
  for (int i = 0; i < n; i++) SOLVE
  s1.clear();
  for (int i = n - 1; i >= 0; i--) SOLVE

  cout << ans;
  return 0;
}