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


using namespace std;


int main() {
    //  1 2 3
    //1 1 1 0
    //2 0 1 1
    //3 1 0 1

    const clock_t begin_time = clock();
    int matrix[10];
    vector<long long int> vec;
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
            tot_num_of_matchings[i][j] = 0;
        }
    }

    // Loop through different sizes of the graph from 2 x 3 to 2 x 6 nodes
    // Let every graph be represented by an integer and let upper be the upper limit
    // for the values of these integer representations
    for (int z = 3; z <= 6; z++) {
        int lowest = 1000;
        int evaluated_graphs = 0;
        long long int tot_eval = 0;
        long long int upper = (int)pow(2.0, z*(z-1));
        long long int curr_val;
        unordered_map<long long int, bool> checked_graph;
        // The and_num is a series of ones used for a "logical and" operation when 
        // turning the integer representation of a graph into a matrix representation
        int and_num = 0;
        for (int i = 0; i < z; i++) {
            and_num += (1 << i);
        }

        long long int one = 1;

        int percentage = 0;
        cout << "Starting evaluating for " << z << "x" << z << endl;
        for (long long int x = 0; x < upper; x++) {
            // For keeping track of collision matchings
            if ((z == 6) && ((x % 10737418) == 0)) {
                cout << "Percentage: " << percentage << "%" << endl;
                 percentage++;
            }
            int pivot = 0;
            // pivot point to current index in long number
            curr_val = 0;
            // Calculate better integer representation
            for (int i = 0; i < z; i++) {
                for (int j = 0; j < z; j++) {
                    if (j == i) {
                        curr_val += (one << ((z * i) + j));
                    } else {
                        curr_val += (((long long int)x & (one << pivot)) >> pivot) << ((z * i) + j);
                        pivot++;
                    }
                }
            }


            // Turn integer representation into matrix representation
            for (int i = 0; i < z; i++) {
                matrix[i] = ((curr_val & (and_num << z*i)) >> z*i);
            }
            vector<tuple<int, int>> index_tuple;
            int tmp = 0;
            // Create tuple that holds the column index as well as its number if ones
            for (int i = 0; i < z; i++) {
                for (int j = 0; j < z; j++) {
                    tmp += ((matrix[j] & (1 << i)) >> i);
                }
                index_tuple.push_back({tmp, i});
                tmp = 0;
            }
            // Sort the tuple after number of ones in their respective columns
            sort(index_tuple.begin(), index_tuple.end());

            int matrix2[10];
            bool first_check = true;
            bool first_hit = false;
            // Loop through different representations of the graphs by changing order of colummns
            // and then sorting the rows. If the first checked representation is in the dictionary
            // of previously checked graphs, then skip this current graph and continue to next graph.
            // Otherwise keep looping and mark all different representations of the current graph and continue.
            do {
                for (int i = 0; i < z; i++) {
                    matrix2[i] = 0;
                }
                for (int i = 0; i < z; i++) {
                    int curr_idx = get<1>(index_tuple.at(i));
                    for (int j = 0; j < z; j++) {
                        matrix2[j] += (((matrix[j] & (1 << curr_idx)) >> curr_idx) << i);
                    }
                }
                sort(matrix2, matrix2 + z);
                reverse(matrix2, matrix2 + z);
                curr_val = 0;
                for (int i = 0; i < z; i++) {
                    curr_val += ((long long int)matrix2[i]) << z*i;
                }
                if (first_check) {
                    first_check = false;
                    if (checked_graph.count(curr_val) > 0) {
                        first_hit = true;
                        break;
                    }
                }
                if (checked_graph.count(curr_val) > 0) {
                    continue;
                } else {
                    checked_graph[curr_val] = true;
                }
            } while (next_permutation(index_tuple.begin(), index_tuple.end()));

            if (first_hit) {
                continue;
            }

            // Sort and recalculate curr_val
            sort(matrix, matrix + z);
            reverse(matrix, matrix + z);
            curr_val = 0;
            for (int i = 0; i < z; i++) {
                curr_val += ((long long int)matrix[i]) << z*i;
            }

            // Evaluate the highest guaranteed matching of the graph
            evaluated_graphs++;
            int t = find_upper_limit(matrix, z);
            if (t < lowest) {
                lowest = t;
                vec.clear();
                vec.push_back(curr_val);
            } else if (t == lowest) {
                vec.push_back(curr_val);
            }
            num_of_matchings[z][t] += 1;
        }
        // Write the results to a file
        if (z == 3) {
            file.open("output_3x3");
        } else if (z == 4) {
            file.open("output_4x4");
        } else if (z == 5) {
            file.open("output_5x5");
        } else {
            file.open("output_6x6");
        }
        file << "The lowest number of matchings: " << lowest << "/" << z << '\n';
        file << "Number of unique graphs evaluated: " << evaluated_graphs << '\n';
        for (int l = 0; l <= z; l++) {
            file << "Number of matchings of size " << l << ": " << num_of_matchings[z][l] << '\n';
        }
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
