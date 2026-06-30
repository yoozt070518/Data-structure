#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

void StringSort(string* s,int size){
    for(int i = 0;i < size-1;++i){
        bool flag = false;
        for(int j = 0;j < size-1-i;++j){
            if(s[j].length() > s[j+1].length()){
                swap(s[j], s[j+1]);
                flag = true;
            }
        }
        if(!flag){
            return;
        }
    }
}


int main(){
    string words[] = {"apple", "cat", "banana", "dog", "elephant"};
    for(string v: words){
        cout << v << " ";
    }
    cout << endl;
    StringSort(words, 5);
    for(string v: words){
        cout << v << " ";
    }

    return 0;
}