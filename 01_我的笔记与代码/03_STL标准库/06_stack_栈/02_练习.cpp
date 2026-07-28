#include <iostream>
#include <deque>
#include <vector>
#include <list>
#include <stack>
using namespace std;


int main(){
    stack<int> s_default;
    stack<int,std::vector<int>> s_vec;
    stack<int, std::list<int>> s_list;
    s_default.push(999);
    s_vec.push(100);
    s_list.push(100);
    cout << s_default.top() << " ";
    cout << s_vec.top() << " ";
    cout << s_list.top() << endl;
    s_default.pop();
    s_list.pop();
    s_vec.pop();
    // 思考题：编译器不会让你这么干 因为stack的底层只允许访问栈顶 
    // 也不存在begin()这样的迭代器接口 无法得到迭代器指向stack的元素
    // 同理 for循环也做不到
    // 只有一边pop掉栈顶一遍打印栈顶元素这种方式才能做到 
    // 但是这种方式又会直接删除掉stack里的所有元素
}