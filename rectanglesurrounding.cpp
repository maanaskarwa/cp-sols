/*
 * Author: Maanas Karwa
 * It is ok to share my code anonymously for educational purposes
 * */

#include <iostream>
#include <cstring>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    short n;
    bool vals[501][501]; //bool grid of allowed coordinates
    while (true) {
        cin >> n;
        if (n == 0) break;
        int ans = 0;
        memset(vals, false, sizeof(vals));
        for (; n > 0; --n) {
            short a, b, c, d;
            cin >> a >> b >> c >> d;
            // Iterating over every point in given rectangle
            for (short i = a; i < c; ++i) {
                for (short j = b; j < d; ++j) {
                    // Ensure no point is double counted between rectangles
                    if (!vals[i][j]) {
                        vals[i][j] = true;
                        ++ans;
                    }
                }
            }
        }
        cout << ans << "\n";
    }
    return 0;
}

/* Problem Statement: https://open.kattis.com/problems/rectanglesurrounding
 *
 * You are given a list of rectangle boundaries. Each rectangle boundary is on integer coordinates.
 * The rectangles surround squares on the coordinate grid. Your job is to determine the total number of such grid squares that are surrounded by all the rectangles.
 *
 * Input:
 * Input consists of a set of 1 to 10 cases.
 * Each case starts with the number of rectangles 0 < n <= 50. Following this are n rectangles, each given as four integers, a b c d, where a < c and b < d.
 * The point (a, c) defines the bottom left corner of the rectangle and the point (b, d) defines the top right. All coordinates are between 0 and 500 (inclusive).
 * Input ends when n is 0.
 *
 * Output
 * For each set of rectangles, print the total number of grid points they surround.

Sample Input 1
1
1 1 2 2
1
10 10 19 19
2
10 10 19 19
15 15 24 24
0

Sample Output 1
1
81
146
 *
 * */