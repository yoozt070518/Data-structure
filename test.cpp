#include <iostream>
#include <string>
#include <cstring>
using namespace std;

const int SIZE = 20;

void set(int* bitmap, int n) {
    int idx = n / 32;
    int bit = n % 32;
    bitmap[idx] |= (1 << bit);
}

bool get(int* bitmap, int n) {
    int idx = n / 32;
    int bit = n % 32;
    return bitmap[idx] & (1 << bit);
}

int hash1(const string& s) {
    int h = 0;
    for (const auto& c : s)
        h = h * 31 + c;
    return abs(h) % SIZE;
}

int hash2(const string& s) {
    int h = 0;
    for (const auto& c : s)
        h = h * 37 + c;
    return abs(h) % SIZE;
}

int hash3(const string& s) {
    int h = 0;
    for (const auto& c : s)
        h = h * 41 + c;
    return abs(h) % SIZE;
}

void insert(int* bitmap, const string& s) {
    set(bitmap, hash1(s));
    set(bitmap, hash2(s));
    set(bitmap, hash3(s));
}

bool contains(int* bitmap, const string& s) {
    return get(bitmap, hash1(s)) &&
           get(bitmap, hash2(s)) &&
           get(bitmap, hash3(s));
}

int main() {
    int bitmap[SIZE / 32 + 1];
    memset(bitmap, 0, sizeof(bitmap));
    insert(bitmap, "a");
    insert(bitmap, "b");
    insert(bitmap, "c");
    insert(bitmap, "d");
    insert(bitmap, "e");
    insert(bitmap, "f");
    insert(bitmap, "g");
    insert(bitmap, "h");
    insert(bitmap, "i");
    insert(bitmap, "j");
    insert(bitmap, "apple");
    insert(bitmap, "banana");
    insert(bitmap, "cherry");

    cout << contains(bitmap, "apple")  << "\n";  // 1
    cout << contains(bitmap, "banana") << "\n";  // 1
    cout << contains(bitmap, "grape")  << "\n";  // 0（大概率）
    cout << contains(bitmap, "xyz") << "\n";
cout << contains(bitmap, "hello") << "\n";
cout << contains(bitmap, "world") << "\n";
    cout << contains(bitmap, "acb") << "\n";
cout << contains(bitmap, "kdkdj") << "\n";
cout << contains(bitmap, "adad") << "\n";
    cout << contains(bitmap, "hole") << "\n";
cout << contains(bitmap, "mylist") << "\n";
cout << contains(bitmap, "mysql") << "\n";
cout << contains(bitmap, "fahhf") << "\n";
cout << contains(bitmap, "fafa") << "\n";
cout << contains(bitmap, "fafnds") << "\n";


}