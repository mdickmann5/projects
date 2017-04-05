#ifndef PROJECT_BST_BINARYSEARCHTREE_H
#define PROJECT_BST_BINARYSEARCHTREE_H
/** DO NOT MODIFY THE LINE BELOW THIS. IT WILL BE USED FOR TESTING. */
#define UNIT_TEST

#include "Exceptions.h"
#include <vector>
#include <algorithm>
using std::vector;

template<typename T>
struct Node {
  T value;
  Node *left;
  Node *right;
  Node(T val) : value(val), left(nullptr), right(nullptr) {};
};

template<typename T>
class BinarySearchTree {

    /** any friends for testing
     */
#if defined(UNIT_TEST)
    FRIEND_TEST(BSTProjectTests, TestBSTAdd);
    FRIEND_TEST(BSTProjectTests, TestBSTSearch);
    FRIEND_TEST(BSTProjectTests, TestBSTRemove);
    FRIEND_TEST(BSTProjectTests, TestBSTInstance);
    FRIEND_TEST(BSTProjectTests, TestSetInstance);
    FRIEND_TEST(BSTProjectTests, TestSetAdd);
    FRIEND_TEST(BSTProjectTests, TestSetRemove);
    FRIEND_TEST(BSTProjectTests, TestSetContains);
    FRIEND_TEST(BSTProjectTests, TestBSTInorderTraversal);
    FRIEND_TEST(BSTProjectTests, TestSetClear);
#endif

 public:
  BinarySearchTree();
  BinarySearchTree(vector<T> values);
  ~BinarySearchTree();
  void add(T val);
  const T *search(T val) const;
  void remove(T val);
  vector<T> getValues() const;
  int size() const;

  Node<T> *root = nullptr;
  void add(Node<T> *&root_node, Node<T> *&new_node);
  Node<T> *remove(Node<T> *&root_node, T val);
  void inOrderTraversal(Node<T> *node, vector<T> &values) const;
  int size(Node<T> *node) const;
  void destroy(Node<T> *&node);
  const Node<T> *search(Node<T> *root_node, T val) const;
};

template<typename T>
BinarySearchTree<T>::BinarySearchTree() {}

template<typename T>
BinarySearchTree<T>::BinarySearchTree(vector<T> values) {
  root = new Node<T>(values[0]);
  for(int i = 1; i<values.size(); i++){
	add(values[i]);	
  }
	
}
  
template<typename T>
BinarySearchTree<T>::~BinarySearchTree() {
  
}
template<typename T>
void BinarySearchTree<T>::add(T val) {
  Node<T>* temp = new Node<T>(val);
  add(root, temp);
}

template<typename T>
void BinarySearchTree<T>::add(Node<T> *&root_node, Node<T> *&new_node) {
  if(root_node == nullptr)
        root = new_node;
  else{
  while(root_node->value != new_node->value){
	if(root_node->value > new_node->value){
		if(root_node->left!=nullptr){	
		  add(root_node->left, new_node);
          break;
            }
		else{
		  root_node->left = new_node;
		  break;
		}
        }
	else{
             if(root_node->right!=nullptr){
	       add(root_node->right, new_node);
           break;
               }
	     else{
  		root_node->right = new_node;
		break;
		}
	}
  }
   }
}

template<typename T>
const T *BinarySearchTree<T>::search(T val) const {
	const Node<T>* functionCall =  search(root, val);
        if(functionCall == nullptr){return nullptr;}
        else{
    const T* result = &functionCall->value;
    return result;
    }
}

template<typename T>
const Node<T> *BinarySearchTree<T>::search(Node<T> *root_node, T val) const {
    if(root_node == nullptr)
        return nullptr;
    else{
    while(root_node != nullptr){
	if(root_node->value>val){
		if(root_node->left!=nullptr){
                    if(root_node->left->value == val)
	           {
                        return root_node->left;
		    }
		  search(root_node->left, val);
                  break;
                }
		else 
                    return nullptr;
        }
	else if(root_node->value<val){
             if(root_node->right!=nullptr){
                 if(root_node->right->value == val){
  		    return root_node->right;
		}
	          search(root_node->right, val);
                  break;
             }
	     else
                 return nullptr;
	}
        else{

            return root_node;
        }
   }
    }
}

template<typename T>
void BinarySearchTree<T>::remove(T val) {
	remove(root, val);
}
template<typename T>
vector<T> BinarySearchTree<T>::getValues() const {
  vector<T> values; 
    inOrderTraversal(root, values);
    return values;
}

template<typename T>
void BinarySearchTree<T>::inOrderTraversal(Node<T> *node, vector<T> &values) const {
  if(node==nullptr){
        return;
    }
    inOrderTraversal(node->left, values);
    values.push_back(node->value);
    inOrderTraversal(node->right, values);
}

template<typename T>
int BinarySearchTree<T>::size() const {
	return size(root); 
}

template<typename T>
int BinarySearchTree<T>::size(Node<T> *node) const {
	return (node==nullptr) ? 0 : size(node->left)+ size(node->right) + 1;
}

template<typename T>
Node<T> *BinarySearchTree<T>::remove(Node<T> *&root_node, T val) {
    if(root_node == nullptr)
        return root_node;
    else if(val < root_node->value)
        root_node->left = remove(root_node->left, val);
    else if(val > root_node->value)
        root_node->right = remove(root_node->right, val);
    else{
        
        if(root_node->left == nullptr && root_node->right == nullptr){
            delete root_node;
            root_node = nullptr;
        }
        else if(root_node->left == nullptr){
            if(root_node->right != nullptr){
            root_node = root_node->right;
            }
        }
        else if(root_node->right == nullptr){
            if(root_node->left != nullptr){
                root_node= root_node->left;
            }
        }
        else{
            struct Node<T>* temp;
            struct Node<T>* temp2 = root_node->right;
            while(temp->left != nullptr){
                temp = temp2->left;
            }
            root_node->value = temp->value;
            root_node->right = remove(root_node->right, temp->value);
        }
    }
    return root_node;
}

template<typename T>
void BinarySearchTree<T>::destroy(Node<T> *&node) {
  delete node;
}

#endif //PROJECT_BST_BINARYSEARCHTREE_H
