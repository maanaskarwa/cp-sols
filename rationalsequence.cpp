/*
 * Author: Maanas Karwa
 * It is ok to share my code anonymously for educational purposes
 * */

#include <iostream>
#define ll long long

/*
 * Logic: If you are a left child, the next node in the bfs order will be your parent's right child.
 * If you are a right child, it will be the next left child in that bfs level. Unless you are the last right child,
 * in which case we move to the next bfs layer
 */

int main() {
  int numCases;
  ll n1, n2;
  scanf("%d\n", &numCases);
  for (int i = 1; i <= numCases; i++) {
    if (i == numCases) scanf("%lld %lld/%lld", &n1, &n1, &n2);
    else scanf("%lld %lld/%lld\n", &n1, &n1, &n2);
    if (n2 == 1) {
      // either right child or root. either way, we need to output the first element in the next bfs layer
      printf("%d 1/%lld\n", i, n1 + 1);
    } else if (n1 < n2) { //left child, all we need to do is traverse up to its parent and then go right
      printf("%d %lld/%lld\n", i, n2, n2 - n1);
    } else {
      // right child. you need to go up till you find a left child, then do what you did for a left child,
      // then come back down to the same bfs level while going only left

      ll num_layers = n1 / n2;
      n1 -= n2 * num_layers;
      n2 -= n1;
      n1 += n2;
      n2 += num_layers * n1;
      printf("%d %lld/%lld\n", i, n1, n2);
    }
  }
}