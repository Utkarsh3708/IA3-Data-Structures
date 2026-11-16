/*
 * Data Structures IA-3 - Trace Portfolio (Question 1)
 * Name: Utkarsh Kapre
 * PRN: 202501100194
 * Seed: 194 | Dataset size: 12 | Search key: 19 | Hash size: 23
 * Sorting order: Ascending
 * Duplicate rule: increment repeated values until unique.
 * This program reproduces the uploaded seven-page PDF.
 */
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <iomanip>
using namespace std;

const long long PRN = 202501100194LL;
const int S = PRN % 10000;
const int N = 12;
const int K = S % 89 + 3;
const int EMPTY = -1; // Generated keys are nonnegative.

bool isPrime(int x) {
    if (x < 2) return false;
    for (int d = 2; d <= x / d; ++d)
        if (x % d == 0) return false;
    return true;
}
int hashSize() {
    int m = S % 23 + 11;
    while (!isPrime(m)) ++m;
    return m;
}
void printArray(const vector<int>& a) {
    for (int x : a) cout << x << ' ';
    cout << '\n';
}
vector<int> generateDataset() {
    vector<int> a;
    cout << "Index | Raw | Corrected\n";
    for (int i = 0; i < N; ++i) {
        int raw = (S * (i + 3) + 7) % 97;
        int x = raw;
        while (find(a.begin(), a.end(), x) != a.end()) ++x;
        a.push_back(x);
        cout << i << " | " << raw << " | " << x << '\n';
    }
    return a;
}

// 1. Bubble Sort: fixed n-1 passes, as in the PDF.
void bubbleSort(vector<int> a) {
    cout << "\nBUBBLE SORT\n";
    int n = static_cast<int>(a.size()), comparisons = 0, swaps = 0;
    for (int i = 0; i < n - 1; ++i) {
        int passSwaps = 0;
        for (int j = 0; j < n - i - 1; ++j) {
            ++comparisons;
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
                ++swaps; ++passSwaps;
                cout << "  Swap indices " << j << ", " << j + 1 << ": ";
                printArray(a);
            }
        }
        cout << "Pass " << i + 1 << " | comparisons=" << n-i-1
             << " | swaps=" << passSwaps << " | ";
        printArray(a);
    }
    cout << "Total comparisons: " << comparisons << "; swaps: " << swaps << '\n';
}

// 2. Insertion Sort: count actual key-to-key comparisons.
void insertionSort(vector<int> a) {
    cout << "\nINSERTION SORT\n";
    int n = static_cast<int>(a.size()), comparisons = 0, shifts = 0;
    for (int i = 1; i < n; ++i) {
        int key = a[i], j = i - 1, pc = 0, ps = 0;
        while (j >= 0) {
            ++comparisons; ++pc;
            if (a[j] <= key) break;
            a[j + 1] = a[j];
            ++shifts; ++ps;
            cout << "  Shift index " << j << " to " << j+1 << ": ";
            printArray(a);
            --j;
        }
        a[j + 1] = key;
        cout << "Pass " << i << " | key=" << key << " | comparisons=" << pc
             << " | shifts=" << ps << " | ";
        printArray(a);
    }
    cout << "Total comparisons: " << comparisons << "; shifts: " << shifts << '\n';
}

// 3. Quick Sort: Lomuto partition, last element as pivot.
// Self-swaps are excluded from the swap count.
int partitionArray(vector<int>& a, int low, int high, int& comparisons, int& swaps) {
    int pivot = a[high], i = low - 1;
    for (int j = low; j < high; ++j) {
        ++comparisons;
        if (a[j] < pivot) {
            ++i;
            if (i != j) {
                swap(a[i], a[j]); ++swaps;
                cout << "  Swap indices " << i << ", " << j << ": "; printArray(a);
            }
        }
    }
    if (i + 1 != high) {
        swap(a[i + 1], a[high]); ++swaps;
        cout << "  Pivot swap: "; printArray(a);
    }
    cout << "Range " << low << '-' << high << " | pivot=" << pivot
         << " | final index=" << i+1 << " | comparisons=" << high-low << " | ";
    printArray(a);
    return i + 1;
}
void quickSort(vector<int>& a, int low, int high, int& comparisons, int& swaps, int& partitions) {
    if (low >= high) return;
    ++partitions;
    int p = partitionArray(a, low, high, comparisons, swaps);
    quickSort(a, low, p - 1, comparisons, swaps, partitions);
    quickSort(a, p + 1, high, comparisons, swaps, partitions);
}

// 4. Stable LSD Radix Sort. Generated values are in the two-digit range.
// Two passes suffice for this personalized dataset; no max-key scan needed.
vector<int> radixSort(vector<int> a) {
    cout << "\nRADIX SORT\n";
    int placements = 0, passes = 0;
    for (int exp = 1; exp <= 10; exp *= 10) {
        ++passes;
        vector<int> buckets[10];
        for (int x : a) {
            buckets[(x / exp) % 10].push_back(x);
            ++placements;
        }
        cout << "Pass " << passes << (exp == 1 ? " (units)\n" : " (tens)\n");
        a.clear();
        for (int digit = 0; digit < 10; ++digit) {
            cout << "Bucket " << digit << ": ";
            if (buckets[digit].empty()) cout << "Empty\n";
            else printArray(buckets[digit]);
            for (int x : buckets[digit]) a.push_back(x);
        }
        cout << "After pass: "; printArray(a);
    }
    cout << "Total comparisons: 0; bucket placements: " << placements
         << "; digit passes: " << passes << '\n';
    return a;
}

void searchResult(int index, int probes) {
    if (index == -1) cout << "Key not found";
    else cout << "Key found at index " << index;
    cout << "; comparisons/probes: " << probes << '\n';
}
// Count one inspected array element as one comparison/probe in searches.
void linearSearch(const vector<int>& a, int key) {
    cout << "\nLINEAR SEARCH\n";
    int probes = 0;
    for (int i = 0; i < static_cast<int>(a.size()); ++i) {
        ++probes;
        cout << "Step " << probes << " | index=" << i << " | value=" << a[i] << '\n';
        if (a[i] == key) { searchResult(i, probes); return; }
    }
    searchResult(-1, probes);
}
void binarySearch(const vector<int>& a, int key) {
    cout << "\nBINARY SEARCH\n";
    int low = 0, high = static_cast<int>(a.size()) - 1, probes = 0;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        ++probes;
        cout << "Step " << probes << " | low=" << low << " | high=" << high
             << " | mid=" << mid << " | value=" << a[mid];
        if (a[mid] == key) { cout << " | found\n"; searchResult(mid, probes); return; }
        if (a[mid] < key) {
            low = mid + 1; cout << " | new low=" << low << '\n';
        } else {
            high = mid - 1; cout << " | new high=" << high << '\n';
        }
    }
    searchResult(-1, probes);
}
void fibonacciSearch(const vector<int>& a, int key) {
    cout << "\nFIBONACCI SEARCH\n";
    int n = static_cast<int>(a.size()), f2 = 0, f1 = 1, f = 1;
    while (f < n) { f2 = f1; f1 = f; f = f1 + f2; }
    int offset = -1, probes = 0;
    cout << "Initial (fibM, fib1, fib2) = (" << f << ',' << f1 << ',' << f2 << ")\n";
    while (f > 1) {
        int i = min(offset + f2, n - 1);
        ++probes;
        cout << "Step " << probes << " | index=" << i << " | value=" << a[i];
        if (a[i] == key) { cout << " | found\n"; searchResult(i, probes); return; }
        if (a[i] < key) {
            f = f1; f1 = f2; f2 = f - f1; offset = i;
            cout << " | right";
        } else {
            f = f2; f1 = f1 - f2; f2 = f - f1;
            cout << " | left";
        }
        cout << " | offset=" << offset << " | fib=(" << f << ',' << f1 << ',' << f2 << ")\n";
    }
    if (f1 && offset + 1 < n) {
        ++probes;
        cout << "Final candidate index=" << offset + 1 << " | value=" << a[offset + 1] << '\n';
        if (a[offset + 1] == key) { searchResult(offset + 1, probes); return; }
    }
    searchResult(-1, probes);
}

// 5. Hashing: division method, then linear probing.
void printLinear(const vector<int>& table) {
    cout << "Table: ";
    for (int i = 0; i < static_cast<int>(table.size()); ++i) {
        cout << i << ':';
        if (table[i] == EMPTY) cout << '-'; else cout << table[i];
        cout << ' ';
    }
    cout << '\n';
}
void linearProbing(const vector<int>& a, int m) {
    cout << "\nLINEAR PROBING\n";
    vector<int> table(m, EMPTY);
    int collisions = 0, extra = 0, checks = 0, inserted = 0;
    for (int key : a) {
        int home = key % m, i = 0;
        cout << "Insert " << key << " | home=" << home << '\n';
        while (i < m) {
            int pos = (home + i) % m;
            ++checks;
            if (table[pos] == EMPTY) {
                table[pos] = key; ++inserted;
                cout << "  Placed at " << pos << " | extra probes=" << i << '\n';
                break;
            }
            cout << "  Collision at " << pos << " (holds " << table[pos] << ")\n";
            if (i == 0) ++collisions;
            ++extra; ++i;
        }
        if (i == m) cout << "  Table full; insertion failed\n";
        printLinear(table);
    }
    cout << "Inserted: " << inserted << "; collisions: " << collisions
         << "; extra probes: " << extra << "; slot checks: " << checks << '\n';
    cout << "Load factor: " << fixed << setprecision(3) << double(inserted)/m << '\n';
}

// 6. Separate chaining: one linked list per hash index.
void printChains(const vector<list<int>>& table) {
    cout << "Table: ";
    for (int i = 0; i < static_cast<int>(table.size()); ++i) {
        cout << i << ':';
        for (int x : table[i]) cout << x << "->";
        cout << "NULL ";
    }
    cout << '\n';
}
void separateChaining(const vector<int>& a, int m) {
    cout << "\nSEPARATE CHAINING\n";
    vector<list<int>> table(m);
    int collisions = 0, occupied = 0, maxLength = 0;
    for (int key : a) {
        int pos = key % m;
        if (!table[pos].empty()) ++collisions;
        else ++occupied;
        table[pos].push_back(key);
        maxLength = max(maxLength, static_cast<int>(table[pos].size()));
        cout << "Insert " << key << " | index=" << pos << " | chain: ";
        for (int x : table[pos]) cout << x << " -> ";
        cout << "NULL\n";
        printChains(table);
    }
    cout << "Collisions: " << collisions << "; occupied chains: " << occupied
         << "; empty chains: " << m-occupied << "; maximum chain length: " << maxLength << '\n';
}

int main() {
    int m = hashSize();
    cout << "DATA STRUCTURES IA-3\nName: Utkarsh Kapre\nPRN: " << PRN
         << "\nSeed: " << S << "\nSearch key: " << K
         << "\nHash table size: " << m << "\nSorting order: Ascending\n\n";
    vector<int> a = generateDataset();
    cout << "Corrected dataset: "; printArray(a);
    bubbleSort(a);
    insertionSort(a);
    cout << "\nQUICK SORT\n";
    vector<int> q = a;
    int comparisons = 0, swaps = 0, partitions = 0;
    quickSort(q, 0, static_cast<int>(q.size()) - 1, comparisons, swaps, partitions);
    cout << "Total comparisons: " << comparisons << "; distinct-position swaps: " << swaps
         << "; partitions: " << partitions << '\n';
    vector<int> sorted = radixSort(a);
    cout << "\nSorted array: "; printArray(sorted);
    linearSearch(sorted, K);
    binarySearch(sorted, K);
    fibonacciSearch(sorted, K);
    linearProbing(a, m);
    separateChaining(a, m);
    return 0;
}
