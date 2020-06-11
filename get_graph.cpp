#include <iostream>

using namespace std;

int main() {
    int n;
    long long int num;
    cout << "Please give the dimension\n";
    cin >> n;
    cout << "Please give the proper integer representation\n";
    cin >> num;
    int pivot = 0;

    // pivot point to current index in long number
    cout << num << endl;
    for (int i = 0; i < n; i++) {
        cout << "[ ";
        for (int j = 0; j < n; j++) {
            cout << ((num & (1 << pivot)) >> pivot) << " ";
            pivot++;
        }
        cout << "]" << endl;
    }
    
    pivot = 0;
    for (int i = 0; i < n; i++) {
        cout << "[ ";
        for (int j = 0; j < n; j++) {
            cout << (num & 1) << " ";
            num = num >> 1;
            pivot++;
        }
        cout << "]" << endl;
    }

    
}
