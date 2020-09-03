#include <algorithm>
#include <map>

using namespace std;


int calc_factorial(int a) {
    if (a <= 1) {
        return 1;
    }
    return (a * calc_factorial(a - 1));
}

int calc_col_num(int matrix[10], int n, int col) {
    int ret_num = 0;
    for (int i = 0; i < n; i++) {
        ret_num += (matrix[i] & col) << i;
    }
    return ret_num;
}

int calc_divisor(int matrix[10], int n) {
    int ret_num = 1;
    map<int, int>row_map;
    map<int, int>col_map;
    map<int, int>::iterator iterator;
    for (int i = 0; i < n; i++) {
        row_map[matrix[i]] += 1;
        col_map[calc_col_num(matrix, n, i)] += 1; 
    }
    for (iterator = row_map.begin(); iterator != row_map.end(); iterator++) {
        ret_num *= calc_factorial(iterator->second);
    }
    for (iterator = col_map.begin(); iterator != col_map.end(); iterator++) {
        ret_num *= calc_factorial(iterator->second);
    }
    return ret_num;
}

int calc_variations(int matrix[10], int n) {
    int ret_num = calc_factorial(n);
    ret_num = (ret_num * ret_num)/calc_divisor(matrix, n);
    return ret_num;
}


/*
    Input: orders for pi and sigma, a matrix representation of the graph, the dimensions of the matrix
    and the current upper value
    Output: The number of matched nodes
    Can also sometimes return a lesser number, as a result of pruning
*/
int perform_matching(int pi[], int sigma[], int matrix[10], int n, int temp_upper) {
    bool marked [n] = {0};
    int matched = 0;
    // Go though every node in sigma (column)
    for (int i = 0; i < n; i++) {
        // Go through every node in pi (row)
        if ((temp_upper != -1) && (temp_upper <= matched)) break;
        for (int j = 0; j < n; j++) {
            // If there is an unused edge to be used for the matching
            if (matrix[pi[j]] & (1 << sigma[i]) && !marked[pi[j]]) {
                marked[pi[j]] = true;
                matched++;
                break;
            }
        }
    }
    return matched;
}

/*
    Input: graph represented as a matrix, int giving the dimensions of the matrix
    Output: the highgest number of matches we can guarantee with our order of vertices
    Goes through all different orders for sigma and pi
*/
int find_upper_limit(int matrix[10], int n) {
    int upper_limit = -1;
    int sigma [n];
    int pi [n];
    for (int i = 0; i < n; i++) {
        sigma[i] = i;
        pi[i] = i;
    }
    sort(sigma, sigma + n);
    sort(pi, pi + n);
    do {
        int temp_upper = -1;
        do {
            int temp_limit = perform_matching(pi, sigma, matrix, n, temp_upper);
            if (temp_upper == -1) {
                temp_upper = temp_limit;
            } else {
                // If a previously tested pi guarantees a higher value, then break
                if (temp_upper < upper_limit) break;
            }
            if (temp_upper > temp_limit) temp_upper = temp_limit;
        } while (next_permutation(sigma, sigma + n));
        if (upper_limit == -1) upper_limit = temp_upper;
        if (upper_limit < temp_upper) upper_limit = temp_upper;
        // If some pi can guarantee complete matching, then this pi will always be chosen, thus
        // it is unnecessary to keep computing. 
        if (upper_limit == n) break;
    } while (next_permutation(pi, pi + n));
    return upper_limit;
}
