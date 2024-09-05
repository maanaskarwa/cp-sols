/*
 * Author: Maanas Karwa
 * It is ok to share my code anonymously for educational purposes
 * */

#include <iostream>

using namespace std;

int main() {
    short count;
    cin >> count;
    while (count) {
        unsigned long long p; // can reach 10^9 * 10^9 in limiting upper case
        unsigned int r, f;
        cin >> p >> r >> f;
        int years = 0;
        while (p <= f) {
            ++years;
            p *= r;
        }
        cout << years << "\n";
        --count;
    }
    return 0;
}

/*Problem statement: https://open.kattis.com/problems/thanos
 *
 * Dr. Thanos, data scientist and self-described nihilist, recently published a paper titled The snapping point of the universe: why rates of population growth point towards imminent destruction.
 * In his paper, Thanos explains that in many planets, the increasing population count is leading to a diminished quality of life. He is convinced that his findings will drive sweeping reforms in intergalactic law, leading to a better life for all organisms.
 * Thanos turns to you, his confidant, to do some investigation. He would like some concrete evidence for his findings to present to the Association of VENGE’s Research Society.
 * The society, one of the galatic leaders in egalitarianism and social justice, is holding a special panel to discuss Thano’s findings. As this involves the chance of actual legislation being passed, Thanos is convinced that the panelists are going to be a tough sell.
 * He asks you to investigate several datasets and see if they could be potentially helpful in supporting his argument.
 *
 * Thanos hands you the data for several planets.
 * On each planet’s file, you read that: the planet currently has a population of P,
 * its population grows by a factor of R times per year,
 * and its annual food production F in tons.
 * All food produced in a year must be consumed that year; it cannot be saved.
 * Assume that each individual consumes 1 ton of food per year, and that the population for each planet each year is always counted as a whole number, rounded down.
 * Given this information, your task is to find out the number of years a planet has remaining before its population is no longer sustainable by its food production.
 *
 * Input:
 * The first line of input consists of a single integer T (1 <= T <= 2000), the number of planets that need to be analyzed.
 * T lines follow, the rth of which consists of three space-separated integers:
 * P (1 <= P <= 10^9),
 * R (1 <= P <= 10^9), and
 * F (1 <= P <= 10^9),
 * the metrics of planet i as described above.
 *
 * Output:
 * Print T lines, the ith of which should consist of a single integer denoting the number of years the ith planet has before it is no longer sustainable.

Sample Input 1
3
1 3 9
2 2 16
5 2 11

Sample Output 1
3
4
2
*/