#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool check(const vector<int>& position, int m, int k){
    int placed = 1;
    int lastPosition = position.front();

    for (int i = 1; i < static_cast<int>(position.size()); ++i) {
        if (position[i] - lastPosition >= k) {
            ++placed;
            lastPosition = position[i];
        }
    }

    return placed >= m;
}

int getmaxMin(const vector<int>& position, int m){
    if (position.empty() || m <= 1) {
        return 0;
    }
    if (m > static_cast<int>(position.size())) {
        return -1;
    }

    vector<int> sortedPosition = position;
    sort(sortedPosition.begin(), sortedPosition.end());

    int left = 1;
    int right = sortedPosition.back() - sortedPosition.front();
    int answer = 0;

    while(left <= right){
        int mid = left + (right - left) / 2;
        if(check(sortedPosition, m, mid)) {
            answer = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return answer;
}





int main(){
    vector<int> position = {1, 2, 8, 4, 9};
    cout << getmaxMin(position, 3) << "\n";

    return 0;
}
