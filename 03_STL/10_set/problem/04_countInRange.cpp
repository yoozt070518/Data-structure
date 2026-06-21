#include <set>
#include <iostream>
#include <vector>
#include <iterator>
using namespace std;

int countInRange(const set<int>& s, int a, int b){
    if(a > b) return 0;
    auto lit = s.lower_bound(a);
    auto rit = s.upper_bound(b);
    return distance(lit, rit);
}

int main(){
    



    return 0;
}