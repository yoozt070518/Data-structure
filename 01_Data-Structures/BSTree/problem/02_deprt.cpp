#include <iostream>
#include <stack>
#include <queue>
#include <algorithm>
using namespace std;

template<typename T>
struct TreeNode
{
    T data;
    TreeNode<T>* left;
    TreeNode<T>* right;
    
    TreeNode(const T& val): data(val), left(nullptr), right(nullptr){}
};

template<typename T>
class BSTree{
private:
    TreeNode<T>* root_;

    void clear(TreeNode<T>* node){
        if(node == nullptr) return;
        if(node->left != nullptr){
            clear(node->left);
        }
        if(node->right != nullptr){
            clear(node->right);
        }
        delete node;
    }

    TreeNode<T>* insert1(TreeNode<T>* node, const T& val){
        if(node == nullptr) return new TreeNode<T>(val);
        if(val < node->data){
            node->left = insert1(node->left, val);
        }else if(val > node->data){
            node->right = insert1(node->right, val);
        }

        return node;
    }

    void insert2(TreeNode<T>*& root, const T& val){
        if(root == nullptr){ 
            root = new TreeNode<T>(val);
            return;
        }
        TreeNode<T>* parent = nullptr;
        TreeNode<T>* curr = root;
        while(curr != nullptr){
            parent = curr;
            if(val < curr->data){
                curr = curr->left;
            }else if(val > curr->data){
                curr = curr->right;
            }else{
                return;
            }
        }

        if(val < parent->data){
            parent->left = new TreeNode<T>(val);
        }else{
            parent->right = new TreeNode<T>(val);
        }
    }
    
    bool find1(TreeNode<T>* node, const T& val){
        if(node== nullptr)return false;
        if(node->data == val) return true;
        else if(val < node->data) return find1(node->left, val);
        else return find1(node->right, val);
    }

    bool find2(TreeNode<T>* root, const T& val){
        if(root == nullptr) return false;
        TreeNode<T>* curr = root;
        while(curr != nullptr){
            if(val == curr->data) return true;
            else if(val < curr->data) curr = curr->left;
            else curr = curr->right;
        }
        return false;
    }

    TreeNode<T>* remove1(TreeNode<T>*node,const T& val){
        if(node == nullptr) return nullptr;
        if(val < node->data){
            node->left = remove1(node->left, val);
        }else if(val > node->data){
            node->right = remove1(node->right, val);
        }else{
            if(node->left != nullptr && node->right != nullptr){
                TreeNode<T>* minNode = node->right;
                while(minNode->left != nullptr){
                    minNode = minNode->left;
                }
                node->data = minNode->data;
                node->right = remove1(node->right, minNode->data);
            }else{
                TreeNode<T>* child = (node->left == nullptr) ? node->right : node->left;
                delete node;
                return child;
            }
        }
        return node;
    }

    void remove2(TreeNode<T>*& root, const T& val){
        if(root == nullptr) return;
        TreeNode<T>* curr = root;
        TreeNode<T>* parent = nullptr;

        while(curr != nullptr && val != curr->data){
            parent = curr;
            if(val < curr->data){
                curr = curr->left;
            }else{
                curr = curr->right;
            }
        }

        if(curr == nullptr) return;

        if(curr->left!= nullptr && curr->right != nullptr){
            TreeNode<T>* minNode = curr->right;
            TreeNode<T>* parent_minNode = curr;
            while(minNode->left != nullptr){
                parent_minNode = minNode;
                minNode = minNode->left;
            }
            curr->data = minNode->data;
            curr = minNode;
            parent = parent_minNode;
        }

        TreeNode<T>* child = (curr->left == nullptr) ? curr->right : curr->left;
        if(parent == nullptr){
            root = child;
        }else{
            if(curr == parent->left){
                parent->left = child;
            }else{
                parent->right = child;
            }
        }
        
       
        delete curr;
    }

    int maxDepth(TreeNode<T>* node){
        if(node == nullptr) return 0;
        return max(maxDepth(node->left), maxDepth(node->right)) + 1;
    }
    
    

public:
    BSTree(TreeNode<T>* root = nullptr): root_(root){}
    ~BSTree(){
        clear(root_);
    }

    void insert1(const T& val){
        root_ = insert1(root_, val);
    }

    void insert2(const T& val){
        insert2(root_, val);
    }

    bool find1(const T& val){
        return find1(root_, val);
    }

    bool find2(const T& val){
        return find2(root_,val);
    }

    void remove1(const T& val){
        root_ = remove1(root_, val);
    }

    void remove2(const T& val){
        remove2(root_, val);
    }

    void preOrder2(){
        if(root_ == nullptr) return;
        stack<TreeNode<T>*> myStack;
        myStack.push(root_);
        while(!myStack.empty()){
            TreeNode<T>* node = myStack.top();
            cout << node->data << " ";
            myStack.pop();
            if(node->right != nullptr){
                myStack.push(node->right);
            }
            if(node->left != nullptr){
                myStack.push(node->left);
            }
        }
    }


    void inOrder2(){
        if(root_ == nullptr) return;
        stack<TreeNode<T>*> myStack;
        TreeNode<T>* curr = root_;
        while(curr != nullptr || !myStack.empty()){
            if(curr != nullptr){
                myStack.push(curr);
                curr = curr->left;
            }else{
                TreeNode<T>* node = myStack.top();
                myStack.pop();
                cout << node->data << " ";
                curr = node->right;
            }
        }
    }

    void postOrder2(){
        if(root_ == nullptr)return;
        stack<TreeNode<T>*> myStack1;
        stack<TreeNode<T>*> myStack2;

        myStack1.push(root_);
        while(!myStack1.empty()){
            TreeNode<T>* curr = myStack1.top();
            myStack2.push(curr);
            myStack1.pop();
            
            if(curr->left != nullptr) myStack1.push(curr->left);
            if(curr->right != nullptr) myStack1.push(curr->right);
        }
        while(!myStack2.empty()){
            cout << myStack2.top()->data << " ";
            myStack2.pop();
        }
    }
    
    void levelOrder(){
        if(root_ == nullptr) return;
        queue<TreeNode<T>*> myQueue;
        myQueue.push(root_);
        while(!myQueue.empty()){
            TreeNode<T>* curr = myQueue.front();
            cout << curr->data << " ";
            myQueue.pop();
            if(curr->left != nullptr) myQueue.push(curr->left);
            if(curr->right != nullptr) myQueue.push(curr->right);
        }
    }

    int maxDepth() {
        return maxDepth(root_);
    }

    int maxDepth2(){
        if(root_ == nullptr) return 0;
        queue<TreeNode<T>*> myQueue;
        myQueue.push(root_);

        int depth = 0;

        while(!myQueue.empty()){
            int levelSize = myQueue.size();

            for(int i = 0;i < levelSize;++i){
                TreeNode<T>* curr = myQueue.front();
                myQueue.pop();

                if(curr->left != nullptr) myQueue.push(curr->left);
                if(curr->right != nullptr) myQueue.push(curr->right);
            } 
            depth++;
        }
        return depth;
    }
    
};

int main(){
   BSTree<int> tree;
    // 故意打乱顺序插入，让它长成一棵饱满的树
    tree.insert1(5);
    tree.insert1(3);
    tree.insert1(7);
    tree.insert1(2);
    tree.insert1(4);
    tree.insert1(6);
    tree.insert1(8);

    tree.levelOrder();
    cout << endl;
    cout << tree.maxDepth();
    return 0;
}