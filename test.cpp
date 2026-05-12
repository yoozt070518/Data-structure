#include <iostream>
#include <string>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    while(N--){
        int ID;
        string Name;
        cin >> ID;
        cin.ignore();
        getline(cin,Name);
        cout << "ID: " << ID << ", Name: " << Name << '\n';
    }
    return 0;
}