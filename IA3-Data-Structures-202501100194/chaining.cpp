// Data Structures IA-3 | Utkarsh Kapre | PRN: 202501100194
// Seed: 194 | n = 12 | m = 23 | h(k) = k % m | search key = 19
// Separate chaining using linked lists; append keys in insertion order.
#include <iostream>
#include <vector>
#include <list>
using namespace std;

const int S = 194, N = 12, M = 23;

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

void display(const vector<list<int>>& table) {
    for (int i = 0; i < M; ++i) {
        cout << i << ": ";
        for (int key : table[i]) cout << key << " -> ";
        cout << "NULL\n";
    }
}

int main() {
    vector<int> data = generateData();
    vector<list<int>> table(M);
    int collisions = 0, maxChain = 0, occupied = 0;
    cout << "Utkarsh Kapre | PRN: 202501100194\n";
    cout << "Separate chaining | m = " << M << "\nDataset: ";
    for (int key : data) cout << key << ' ';
    cout << '\n';
    for (int key : data) {
        int index = key % M;
        if (!table[index].empty()) ++collisions;
        else ++occupied;
        table[index].push_back(key);
        int length = static_cast<int>(table[index].size());
        if (length > maxChain) maxChain = length;
        cout << "\nInsert " << key << " at index " << index << '\n';
        display(table);
    }
    cout << "\nFinal hash table:\n";
    display(table);
    cout << "Inserted: " << data.size() << "\nCollisions: " << collisions
         << "\nOccupied chains: " << occupied << "\nEmpty chains: " << M - occupied
         << "\nMaximum chain length: " << maxChain << '\n';
    return 0;
}
