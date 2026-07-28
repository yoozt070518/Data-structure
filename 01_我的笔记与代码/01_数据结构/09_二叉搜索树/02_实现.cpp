#include <iostream>
#include <stack>
using namespace std;

template <typename T>
struct TreeNode{
    T data;
    TreeNode<T>* left;
    TreeNode<T>* right;

    TreeNode(T val): data(val), left(nullptr), right(nullptr){}
};

template<typename T>
class BSTree{
private:
    TreeNode<T>* root_;
    void clear(TreeNode<T>* node){
        if(node == nullptr) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

    TreeNode<T>* insert1(TreeNode<T>* node,const T& val){
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
        TreeNode<T>* curr = root;
        TreeNode<T>* parent = nullptr;
        while(curr != nullptr){
            parent = curr;
            if(val == curr->data){
                return;
            }else if(val < curr->data){
                curr = curr->left;
            }else{
                curr =  curr->right;
            }
        }
        if(val < parent->data) parent->left = new TreeNode<T>(val);
        else parent->right = new TreeNode<T>(val);
    }

    bool find1(TreeNode<T>* node, const T& val){
        if(node == nullptr) return false;
        if(val == node->data) return true;
        else if(val < node->data) return find1(node->left, val);
        else return find1(node->right, val);
    }

    TreeNode<T>* remove1(TreeNode<T>* node, const T& val){
        if(node == nullptr) return nullptr;
        if(val == node->data){
            if(node->left == nullptr){
                TreeNode<T>* temp = node->right;
                delete node;
                return temp;
            }else if(node->right == nullptr){
                TreeNode<T>* temp = node->left;
                delete node;
                return temp;
            }else{
                TreeNode<T>* minNode = node->right;
                while(minNode->left != nullptr){
                    minNode = minNode->left;
                }
                node->data = minNode->data;
                node->right = remove1(node->right, minNode->data);
            }
        }else if(val > node->data){
            node->right = remove1(node->right, val);
        }else{
            node->left = remove1(node->left, val);
        }
        return node;
    }

    void remove2(TreeNode<T>*& root, const T& val){
        if(root == nullptr) return;
        TreeNode<T>* curr = root;
        TreeNode<T>* parent = nullptr;

        while(curr != nullptr && curr->data != val){
            parent = curr;
            if(val < curr->data) curr = curr->left;
            else curr = curr->right;
        }

        if(curr == nullptr) return;
        
        if(curr->left != nullptr && curr->right != nullptr){
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
            if(parent->left == curr) parent->left = child;
            else parent->right = child;
        }
        delete curr;
    }

public:
    BSTree(TreeNode<T>* root = nullptr): root_(root){}
    ~BSTree(){
        clear(root_);
        root_ = nullptr;
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
        TreeNode<T>* curr = root_;
        while(curr != nullptr && curr->data != val){
            if(val < curr->data){
                curr = curr->left;
            }else{
                curr = curr->right;
            }
        }
        return curr != nullptr;
    }

    void remove1(const T& val){
        root_ = remove1(root_, val);
    }

    void remove2(const T& val){
        remove2(root_, val);
    }
};