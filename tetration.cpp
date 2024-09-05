/*
 * Author: Maanas Karwa
 * It is ok to share my code anonymously for educational purposes
 * */

#include <bits/stdc++.h>
int main() {
  double ans;
  scanf("%lf",&ans);
  printf("%.8f",(ans == 1 ? ans : pow(ans, 1/ans)));
}

/*
 * a^(a^(a...) = N
 * a^N = N
 * a = N^(1/N)
 */