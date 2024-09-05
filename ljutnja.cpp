/*
 * Author: Maanas Karwa
 * It is ok to share my code anonymously for educational purposes
 * */

#include <iostream>
#include <algorithm>
#include <cmath>

#define ll long long
#define u unsigned

using namespace std;

int wishes[100000];

/*
 * Logic:
 * Can I get everybody below a certain candy threshold?
 * If so, then I can use greedy to minimize sum at that point.
 *
 * Eg. Sample input 2: I can get everybody to 1.
 * I might need to optimize further beyond this. eg 15 4, 5 5 5 5.
 * Threshold is 2, but I will have candies left over at the end and can distribute those too.
 * 5 - 3 - 1 = 1 (not 2)
 * 5 - 3 - 1 = 1
 * 5 - 3 - 1 = 1
 * 5 - 3 = 2
 * Ans = 7
 *
 * This function only calculates threshold, candy distribution handled after threshold reached.
 * */
bool answer_in_threshold(ll person_candy_threshold, int remaining_candy_count,
                         int number_of_children) {
    for (int i = 0; i < number_of_children; ++i) {
        int wish = (wishes)[i];
        if (remaining_candy_count < wish - person_candy_threshold) {
            // don't have enough candy to get kid to threshold
            return false;
        }
        // if kid wishes for more than the threshold, give candy such that he gets to the threshold
        if (wish > person_candy_threshold) remaining_candy_count -= wish - person_candy_threshold;
    }
    // if u reached this far with remaining candy, job done
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> m >> n;
    ll low = 1;
    ll high = 0;
    for (int i = 0; i < n; ++i) {
        cin >> wishes[i];
        if (high < wishes[i]) high = wishes[i];
    }
    if (low != high) {
        // if low = high, we don't need to BSTA.
        // Case in point: 1 2, 1 1. Low = high = 1 here.
        while (low < high) {
            ll mid = low + (high - low) / 2;
            bool possible_ans = answer_in_threshold(mid, m, n);
            if (!possible_ans) low = mid + 1;
            else {
                high = mid;
            }
        }
    }

    // found threshold. Now assign candies
    sort(wishes, wishes + n, greater());
    // renaming for readability
    ll ans = 0;
    ll per_person_candy_threshold = high;
    int remaining_candies = m;
    for (int i = 0; i < n; ++i) { // get everybody to threshold
        int wish = wishes[i];
        if (wish > per_person_candy_threshold) {
            wishes[i] = per_person_candy_threshold;
            remaining_candies -= wish - per_person_candy_threshold;
        }
    }
    for (int i = 0; i < n; ++i) {
        // reduce further with residual candies
        // since we are guaranteed that candies < wishes, at min threshold we will have enough candy left for giving a child one more candy at best
        if (remaining_candies > 0 && wishes[i] > 0) {
            --wishes[i];
            --remaining_candies;
        }
    }

    //calculate sum. powl to avoid overflow (pow was causing overflow)
    for (int i = 0; i < n; ++i) ans += powl(wishes[i], 2);
    cout << ans << "\n";
    return 0;
}

/* Problem Statement: (https://open.kattis.com/problems/ljutnja)
 *
 * Children in a kindergarten have received a large sack containing M candies.
 * It has been decided that the candies are to be distributed among N children.
 *
 * Each child has stated the number of candies that it wants. If a child isn’t given the amount of candy it wants, it will get angry. In fact it’ll get angrier for each candy it is deprived of. Some speculate that it’s anger will be equal to the square of the number of candy it is deprived of.
 * For instance, if Mirko states that he wants 32 candies but receives only 29, he would be missing 3 candies, so his anger would be equal to 9.
 *
 * Unfortunately, there is an insufficient amount of candy to satisfy all children. Therefore, the candies should be distributed in such a way that the sum of the children’s anger is minimal.
 *
 * Input:
 * The first line contains two integers, M (1 <= M <= 2 * 10^9) and N (1 <= N <= 100000).
 * The following N lines contain integers (one per line) which represent the wishes of the children.
 * Those numbers are all strictly less than 2 * 10^9, and their sum always exceeds M.
 *
 * Output:
 * The first and only line of output must contain the minimum sum of the children’s anger.
 * Note: The test cases will ensure that the result fits in a 64-bit unsigned integer.

Sample Input 1
5 3
1
3
2

Sample Output 1
1

Sample Input 2
10 4
4
5
2
3

Sample Output 2
4
*/