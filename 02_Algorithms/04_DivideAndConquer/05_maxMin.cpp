#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool check(const vector<int>& position, int m, int k){
    
}

int getmaxMin(const vector<int>& position, int m){
    sort(position.begin(),position.end());
    int left = 1;
    int right = position.back() - position.front();
    while(left <= right){
        int mid = left + (right - left) / 2;
        if(check(position,m,mid))
    }



}





int main(){
    

    return 0;
}