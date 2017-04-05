#ifndef PROJECT_BST_SET_H
#define PROJECT_BST_SET_H
#include <list>
#include "BinarySearchTree.h"
/** DO NOT MODIFY THE LINE BELOW THIS. IT WILL BE USED FOR TESTING. */
#define UNIT_TEST

#include "Exceptions.h"

template<typename T>
class Set {

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
  Set() = default;
  Set(vector<T> values);
  ~Set() = default;
  bool contains(T value) const;
  int size() const;
  void add(T value);
  void remove(T value);
  void clear();
  vector<T> getValues() const;
  bool isDisjoint(const Set<T> &other) const;
  bool isSubset(const Set<T> &other) const;
  bool isSuperset(const Set<T> &other) const;
  Set<T> unionWith(const Set<T> &other) const;
  Set<T> intersection(const Set<T> &other) const;
  Set<T> difference(const Set<T> &other) const;
  Set<T> symmetricDifference(const Set<T> &other) const;

  BinarySearchTree<T> tree;
};

template<typename T>
Set<T>::Set(vector<T> values) {
    std::list<T> skimValues(values.begin(), values.end());
    skimValues.unique();
    for(auto elem : skimValues){
        add(elem);
    }
 
}
template<typename T>
bool Set<T>::contains(T value) const {
    return (!(tree.search(value) == nullptr));
}

template<typename T>
int Set<T>::size() const {
    return tree.size();
}

template<typename T>
void Set<T>::add(T value) {
    if(tree.search(value)==nullptr){
        tree.add(value);
}
}

template<typename T>
void Set<T>::remove(T value) {
    tree.remove(value);
}

template<typename T>
void Set<T>::clear() {
    delete tree;
    tree = BinarySearchTree<T>();
}

template<typename T>
vector<T> Set<T>::getValues() const {
    return tree.getValues();
}

template<typename T>
bool Set<T>::isDisjoint(const Set<T> &other) const {
    vector<T> values = getValues();
    for(auto elem : values){
        if(other.contains(elem))
            return false;
        
    }
    return true;
}

template<typename T>
bool Set<T>::isSubset(const Set<T> &other) const {
    vector<T> values = getValues();
    for(auto elem : values){
        if(!other.contains(elem))
            return false;
    }
    return true;
}

template<typename T>
bool Set<T>::isSuperset(const Set<T> &other) const {
    return other.isSubset(this);
}

template<typename T>
Set<T> Set<T>::unionWith(const Set<T> &other) const {
    Set<T> newSet = Set(other.getValues());
    vector<T> values = this->getValues();
    for(auto elem : values){
        newSet.add(elem);
    }
    return newSet;
}

template<typename T>
Set<T> Set<T>::intersection(const Set<T> &other) const {
    Set<T> newSet = Set();
    vector<T> values = other.getValues();
    for(auto elem : values){
        if(this->contains(elem))
            newSet.add(elem);
    }
    return newSet;
}

template<typename T>
Set<T> Set<T>::difference(const Set<T> &other) const {
    Set<T> newSet = Set();
    vector<T> values = this->getValues();
    for(auto elem : values){
        if(!other->contains(elem))
            newSet.add(elem);
    }
    return newSet;
}

template<typename T>
Set<T> Set<T>::symmetricDifference(const Set<T> &other) const {
    Set<T> newSet = Set();
    vector<T> values = this->getValues();
    for(auto elem : values){
        if(!other.contains(elem))
            newSet.add(elem);
    }
    values = other.getValues();
    for(auto elem : values){
        if(!this->contains(elem))
            newSet.add(elem);
    }
}

#endif //PROJECT_BST_SET_H
