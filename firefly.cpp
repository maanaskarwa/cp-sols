/*
 * Author: Maanas Karwa
 * It is ok to share my code anonymously for educational purposes
 * */

#include <iostream>
#include <algorithm>
#include <map>

#define ll long long
#define u unsigned

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, h;
    cin >> n >> h;
    int stalagmite_heights[n / 2];
    int stalactite_heights[n / 2];
    for (int i = 0; i < n / 2; ++i) {
        cin >> stalagmite_heights[i];
        cin >> stalactite_heights[i];
    }

    sort(stalagmite_heights, stalagmite_heights + n / 2);
    sort(stalactite_heights, stalactite_heights + n / 2);

    int min = INT_MAX;

    map<int, int> level_frequency; //histogram

    for (int i = 1; i <= h; ++i) {
        int stalagmite_target = i;

        // flip the picture vertically, visualise the stalactites as stalagmites.
        int stalactite_target = h - i + 1;

        int lower;
        int higher;
        int collided_stalagmites;
        int collided_stalactites;

        // Find index of target height in stalagmite lists. If index is p, it means you didn't collide with those p (too short) i.e. you collided with the remaining n/2 - p
        // Same logic for stalactites

        if (stalagmite_target > stalagmite_heights[n/2 - 1]) {
            //edge case. Binary search will return highest element's index (n/2 - 1), we need n/2.
            collided_stalagmites = 0;
        } else {
            lower = 0;
            higher = n / 2 - 1;
            while (lower < higher) {
                int mid = lower + (higher - lower) / 2;
                if (stalagmite_heights[mid] < stalagmite_target) lower = mid + 1;
                else higher = mid;
            }
            collided_stalagmites = n / 2 - lower;
        }

        if (stalactite_target > stalactite_heights[n/2 - 1]) {
            collided_stalactites = 0;
        } else {
            lower = 0;
            higher = n / 2 - 1;
            while (lower < higher) {
                int mid = lower + (higher - lower) / 2;
                if (stalactite_heights[mid] < stalactite_target) lower = mid + 1;
                else higher = mid;
            }
            collided_stalactites = n / 2 - lower;
        }

        ++level_frequency[collided_stalagmites + collided_stalactites];
        if (collided_stalagmites + collided_stalactites < min) min = collided_stalagmites + collided_stalactites;
    }
    cout << min << " " << level_frequency[min] << "\n";
    return 0;
}

/* Problem Statement: https://open.kattis.com/problems/firefly
 *
 * A Japanese firefly has flown into a cave full of obstacles: stalagmites (rising from the floor) and stalactites (hanging from the ceiling).
 * The cave is N units long (where N is even) and H units high. The first obstacle is a stalagmite after which stalactites and stalagmites alternate.
 * The Japanese firefly is not the type that would fly around the obstacle, instead it will choose a single height and ram from one end of the cave to the other, destroying all obstacles in its path with its mighty kung-fu moves.
 *
 * You are given the width and length of the cave and the sizes of all obstacles.
 *
 * Write a program that determines the minimum number of obstacles the firefly needs to destroy to reach the end of the cave, and on how many distinct levels it can achieve that number.
 *
 * Input:
 * The first line contains two integers N and H, 2 <= N <= 200000, 2 <= H <= 500000, the length and height of the cave. N will always be even.
 * The next N lines contain the sizes of the obstacles, one per line. All sizes are positive integers less than H.
 *
 * Output:
 * Output two integers separated by a single space on a single line. The first number is the minimum number of obstacles the firefly has to destroy and the second is the number of levels on which that can be achieved.

Sample Input 1
6 7
1
5
3
3
5
1

Sample Output 1
2 3

Sample Input 2
14 5
1
3
4
2
2
4
3
4
3
3
3
2
3
3

Sample Output 2
7 2
 */