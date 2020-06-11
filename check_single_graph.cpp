#include <algorithm>
#include <iostream>
#include <cmath>
#include <sstream>
#include <vector>
#include <fstream>
#include <map>
#include <ctime>
#include <tuple>
#include "match_funcs.hpp"


using namespace std;


int main() {
    int n;
    long long int num;
    cout << "Please give the dimension\n";
    cin >> n;
    cout << "Please give the proper integer representation\n";
    cin >> num;
    long long int num2;
    num2 = num;
    int matrix[n];
    int pivot = 0;
    // pivot point to current index in long number
    for (int i = 0; i < n; i++) {
        matrix[i] = 0;
        for (int j = 0; j < n; j++) {
            matrix[i] += (num2 & 1) << n-j-1;
            pivot++;
            num2 = num2 >> 1;
        }
    }
    cout << calc_variations(matrix, n) << endl;
    cout << find_upper_limit(matrix, n) << "/" << n << endl;

}
