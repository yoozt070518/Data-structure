#include <iostream>
#include <stdexcept>
using namespace std;

int fib(int n){
    if(n <= 0){
        throw std:: invalid_argument("Index is invalid!");
    }
    if(n == 1 || n == 2){
        return 1;
    }
    return fib(n-1) + fib(n-2);
}




int main(){
    cout << fib(5);
    return 0;
}