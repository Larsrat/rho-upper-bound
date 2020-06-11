#include <algorithm>
#include <iostream>
#include <cmath>
#include <sstream>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <ctime>
#include <tuple>
#include "match_funcs.hpp"
#include <boost/multiprecision/cpp_int.hpp>

#include <cstdlib>

using namespace std;


int main() {
    //  1 2 3
    //1 1 1 0
    //2 0 1 1
    //3 1 0 1

    const clock_t begin_time = clock();
    int matrix[10];
    vector<boost::multiprecision::int128_t> vec;
    ofstream file;
    string str;
    int n;
    int m;


    // Initialize matrix for keeping track of occurrences of numbers of matchings for different
    // sizes of the graph. 
    // for keeping track of unique matchings
    int num_of_matchings[10][10];
    // for keeping track of matchings with collisions
    int tot_num_of_matchings[10][10];
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            num_of_matchings[i][j] = 0;
        }
    }

    // Loop through different sizes of the graph from 2 x 3 to 2 x 6 nodes
    // Let every graph be represented by an integer and let upper be the upper limit
    // for the values of these integer representations
    for (int z = 7; z <= 9; z++) {
        int lowest = 1000;
        long long int tot_eval = 0;
        boost::multiprecision::int128_t upper = (int)pow(2.0, z*(z-1));
        boost::multiprecision::int128_t curr_val;
        boost::multiprecision::int128_t and_num = 0;
        for (int i = 0; i < z; i++) {
            and_num += (1 << i);
        }

        boost::multiprecision::int128_t one = 1;

        int percentage = 0;
        cout << "Starting evaluating for " << z << "x" << z << endl;
        int array_map[200000];
        int added_num = 1;
        
        const clock_t loop_time = clock();
        srand(time(NULL));
        while (((clock() - loop_time)/CLOCKS_PER_SEC) < 60*60*24) {
            if (z == 9) {
                cout << ((clock() - loop_time)/CLOCKS_PER_SEC) << endl;
            }
            boost::multiprecision::int128_t random_num = ((boost::multiprecision::int128_t)rand() << 32) | (boost::multiprecision::int128_t)rand();
            if (z == 7) {
                random_num = (random_num & ((boost::multiprecision::int128_t)4398046511103));
            } else if (z == 8) {
                random_num = (random_num & ((boost::multiprecision::int128_t)72057594037927935));
            } else {
                random_num = random_num | ((((boost::multiprecision::int128_t)rand() << 32) | (boost::multiprecision::int128_t)rand()) << 64);
            }

            // For keeping track of collision matchings
            int pivot = 0;
            // pivot point to current index in long number
            curr_val = 0;
            // Calculate better integer representation, which is used to take into account the edges from the fact of it being a perfect matching
            for (int i = 0; i < z; i++) {
                for (int j = 0; j < z; j++) {
                    if (j == i) {
                        curr_val += (one << ((z * i) + j));
                    } else {
                        curr_val += (((boost::multiprecision::int128_t)random_num & (one << pivot)) >> pivot) << ((z * i) + j);
                        pivot++;
                    }
                }
            }

            for (int i = 0; i < z; i++) {
                matrix[i] = (int)((curr_val & (and_num << z*i)) >> z*i);
            }
            sort(matrix, matrix + z);
            reverse(matrix, matrix + z);

            // Evaluate the highest guaranteed matching of the graph
            tot_eval++;
            int t = find_upper_limit(matrix, z);
            array_map[added_num] = t;
            added_num++;
            if (t < lowest) {
                lowest = t;
                vec.clear();
                vec.push_back(curr_val);
            } else if (t == lowest) {
                vec.push_back(curr_val);
            }
            num_of_matchings[z][t] += 1;
            tot_num_of_matchings[z][t] += 1;
        }
        // Write the results to a file
        if (z == 7) {
            file.open("output_7x7");
        } else if (z == 8) {
            file.open("output_8x8");
        } else {
            file.open("output_9x9");
        }
        file << "The lowest number of matchings: " << lowest << "/" << z << '\n';
        file << "Total number of graphs evaluated " << tot_eval << '\n';
        for (int l = 0; l <= z; l++) {
            file << "Tot number of matchings of size " << l << ": " << tot_num_of_matchings[z][l] << '\n';
        }
        for (int l = 0; l < vec.size(); l++) {
            file << vec.at(l) << '\n';
        }
        file.close();
        vec.clear();
        cout << float( clock () - begin_time ) /  CLOCKS_PER_SEC << endl;
    }
    
    return 0;
}
