/*
 * Author: Maanas Karwa
 * It is ok to share my code anonymously for educational purposes
 * */

#include <iostream>
#include <vector>

#define ll long long
#define u unsigned

using namespace std;

//assign as many consecutive boxes as possible within weight
bool possible_in_given_weight(int weight, vector<short> *weights, int n, int k) {
    int number_of_boxes = 1;
    int box_weight = (*weights)[0];
    for (int i = 0; i < n - 1; ++i) {
        if (box_weight + (*weights)[i + 1] <= weight) {
            //add next box
            box_weight += (*weights)[i + 1];
        } else {
            //increment box count, reset box weight variable
            ++number_of_boxes;
            box_weight = (*weights)[i + 1];
        }
    }
    // greedy assumption: if I can do it in n-1 boxes, I can do it in n or more boxes (simply split a box)
    return number_of_boxes <= k;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    u int k, n;
    vector<short> weights;
    cin >> n >> k;
    weights.reserve(n);
    short max_weight = 0; //lowest possible answer
    int weight_sum = 0; //highest possible answer
    for (int i = 0; i < n; ++i) {
        short weight;
        cin >> weight;
        weights.push_back(weight);
        if (weight > max_weight) max_weight = weight;
        weight_sum += weight;
    }
    int low = max_weight;
    int high = weight_sum;
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (!possible_in_given_weight(mid, &weights, n, k)) low = mid + 1;
        else high = mid;
    }
    cout << low << "\n";
    return 0;
}

/*
 * Problem statement: https://open.kattis.com/problems/bigboxes

 * Brandon Greg Jr. is moving to the United States to double his salary. He has n items that he needs to pack into k big boxes.
 * The n items are currently arranged in a row, and Brandon doesn’t want to bother reordering them, so he will partition the n items into k groups of consecutive items, and put each of the k groups into their own box.
 * For convenience when moving, Brandon wants to minimize the weight of the heaviest box. The weights of the boxes themselves are negligible.
 *
 * Input:
 * The first line contains two space-separated integers n and k (1 <= k <= n <= 10^5), denoting the number of items and the number of boxes respectively.
 * The second line of input contains n space-separated integers w_i (1 <= w_i <= 10^4), representing the weight of each item in order.
 *
 * Output:
 * The only line of output should contain a single integer, denoting the minimum possible weight of the heaviest box.

Sample Input 1:
7 2
3 1 1 3 9 5 2
Sample Output 1:
16

Sample Input 2
7 4
1 2 8 3 5 2 7
Sample Output 2
9

Sample Input 3
7 5
1 2 8 3 5 2 7
Sample Output 3
8
*/