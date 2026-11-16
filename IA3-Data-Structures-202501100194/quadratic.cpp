// Data Structures IA-3 | Utkarsh Kapre | PRN: 202501100194
// Seed: 194 | n = 12 | m = 23 | h(k) = k % m | search key = 19
// Optional extension: quadratic probing without replacement.
#include <iostream>
#include <vector>
using namespace std;

const int S = 194, N = 12, M = 23, EMPTY = -1;

vector<int> generateData() {
    vector<int> data;
    bool used[97] = {};
    for (int i = 0; i < N; ++i) {
        int key = (S * (i + 3) + 7) % 97;
        while (used[key]) key = (key + 1) % 97;
        used[key] = true;
        data.push_back(key);
    }
    return data;
}

void display(const vector<int>& table) {
    for (int i = 0; i < M; ++i) {
        cout << i << ": ";
        if (table[i] == EMPTY) cout << "Empty";
        else cout << table[i];
        cout << "  ";
        if ((i + 1) % 6 == 0) cout << '\n';
    }
    cout << '\n';
}

int main() {
    vector<int> data = generateData();
    vector<int> table(M, EMPTY);
    int collisions = 0, checks = 0, inserted = 0;
    cout << "Utkarsh Kapre | PRN: 202501100194\n";
    cout << "Quadratic probing (optional) | m = " << M << "\nDataset: ";
    for (int key : data) cout << key << ' ';
    cout << '\n';
    for (int key : data) {
        int home = key % M;
        bool success = false;
        // For an odd prime M, these i values visit all distinct square offsets.
        cout << "\nInsert " << key << ", home index = " << home << '\n';
        for (int i = 0; i <= M / 2; ++i) {
            int index = (home + i * i) % M;
            ++checks;
            if (table[index] == EMPTY) {
                table[index] = key;
                ++inserted;
                success = true;
                cout << "Placed at index " << index << ", extra probes = " << i << '\n';
                break;
            }
            ++collisions;
            cout << "Collision at index " << index << '\n';
        }
        if (!success) cout << "No reachable empty slot for " << key << '\n';
        display(table);
    }
    cout << "\nFinal hash table:\n";
    display(table);
    cout << "Inserted: " << inserted << "\nCollisions (occupied-slot checks): "
         << collisions << "\nTotal slot checks: " << checks << '\n';
    return inserted == N ? 0 : 1;
}
