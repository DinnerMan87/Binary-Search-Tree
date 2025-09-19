#pragma once

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

using namespace std;

template <typename KeyT, typename ValT>
class BSTMap {
 private:
  struct BSTNode {
    // This member should never change after initialization!
    const KeyT key;
    ValT value;
    BSTNode* parent;
    BSTNode* left;
    BSTNode* right;

    // This is fancy constructor syntax
    // Don't worry too much about it -- it's just necesssary for the const
    // member.
    BSTNode(KeyT key, ValT value, BSTNode* parent)
        : key(key),
          value(value),
          parent(parent),
          left(nullptr),
          right(nullptr) {
    }
  };

  BSTNode* root;
  size_t sz;

  // Utility pointer for begin and next.
  BSTNode* curr;

  // TODO_STUDENT: add private helper function definitions here
  void insertHelper(BSTNode*& curr, BSTNode* prev, KeyT key, ValT value){
    if(curr == nullptr){
      curr = new BSTNode(key,value,prev);
    } else if (curr->key > key){
      insertHelper(curr->left,curr,key,value);
    } else {
      insertHelper(curr->right,curr,key,value);
    }
  } 

  void insertHelperString(BSTNode*& curr, BSTNode* prev, KeyT realKey, int convKey, ValT value){
    if(curr == nullptr){
      curr = new BSTNode(realKey,value,prev);
    } else if (intify(curr->key) > convKey){
      insertHelperString(curr->left,curr,realKey,convKey,value);
    } else {
      insertHelperString(curr->right,curr,realKey,convKey,value);
    }
  }

  ValT& atHelper(BSTNode* curr,const KeyT& key) const{
    if(curr == nullptr){ 
      throw out_of_range("ts dont exist, cuh");
    }
    if (curr->key == key){
      return curr->value;
    }
    if (curr->key > key){
      return atHelper(curr->left,key);
    } else {
      return atHelper(curr->right,key);
    }
  }

  ValT& atHelperString(BSTNode* curr, KeyT realKey, int convKey) {
    if(curr == nullptr){ 
      throw out_of_range("ts dont exist, cuh");
    } else if (curr->key == realKey){
      return curr->value;
    } else if (this->intify(curr->key) > convKey) {
      return atHelperString(curr->left,realKey,convKey);
    } else {
      return atHelperString(curr->right,realKey,convKey);
    }
  }

  bool containsHelper(BSTNode* curr,const KeyT& key) const{
    if(curr == nullptr){
      return false;
    }
    if(curr->key == key){
      return true;
    }
    else if(curr->key > key){
      return containsHelper(curr->left,key);
    } else {
      return containsHelper(curr->right,key);
    }
  }

  bool containsHelperString(BSTNode*& curr, KeyT realKey, int convKey) {
    if(curr == nullptr){
      return false;
    }
    if(curr->key == realKey){
      return true;
    }
    if(this->intify(curr->key) > convKey){
      return containsHelperString(curr->left,realKey,convKey);
    } else {
      return containsHelperString(curr->right,realKey,convKey);
    }
  }

  void dHelp(BSTNode*& curr) {
    if (curr == nullptr) {
      return;
    }
    dHelp(curr->left);
    dHelp(curr->right);
    delete curr;
  }

  void toStringHelper(BSTNode* curr, stringstream& stream) const{
    if(curr != nullptr){
      toStringHelper(curr->left,stream);
      stream << curr->key << ": " << curr->value << endl;
      toStringHelper(curr->right,stream);
    }
  }

  void copyHelper(BSTNode*& thisCurr,BSTNode* prev,BSTNode* otherCurr) {
    if(otherCurr != nullptr){
      thisCurr = new BSTNode(otherCurr->key,otherCurr->value,prev);
      copyHelper(thisCurr->left, thisCurr, otherCurr->left);
      copyHelper(thisCurr->right, thisCurr, otherCurr->right);
    }
  }

  int intify(KeyT key){
    /*int conversion = 0;
    for(int i = 0; i<key.size(); i++){
      conversion+= (int) key.at(i);
    }
    return conversion;
    */
    
    return (int) key;
  }

 public:

  /**
   * Creates an empty `BSTMap`. Runs in O(1).
   */
  BSTMap() {
    // TODO_STUDENT
    this->root = nullptr;
    this->sz = 0;
    this->curr = nullptr;
  }

  /**
   * Checks if the `BSTMap` is empty. Runs in O(1).
   */
  bool empty() const {
    // TODO_STUDENT
    return (this->sz == 0);
  }

  /**
   * Returns the number of mappings in the `BSTMap`. Runs in O(1).
   */
  size_t size() const {
    // TODO_STUDENT
    return this->sz;
  }

  /**
   * Adds the mapping `{key -> value}` to the `BSTMap`. If the key already
   * exists, does not update the mapping (like the C++ STL map).
   *
   * Uses the key to determine the location in the underlying BST. Creates
   * exactly one new node.
   *
   * Runs in O(H), where H is the height of the tree.
   */
  void insert(KeyT key, ValT value) {
    // TODO_STUDENT
    if(this->sz == 0){
      this->root = new BSTNode(key, value, nullptr);
      this->sz++;
    } else {
      /*if(!isdigit(key)){
        //insertHelperString(this->root,nullptr,key,intify(key),value);
      } else { */
        this->insertHelper(this->root,nullptr,intify(key),value);
      //}
      this->sz++;
    }

  }

  /*void insertHelper(BSTNode*& curr, BSTNode*& prev, KeyT key, ValT value){
    if(curr == nullptr){
      curr = new BSTNode(key,value,prev);
    } else if (curr->key > key){
      insertHelper(curr->left,curr,key,value);
    } else {
      insertHelper(curr->right,curr,key,value);
    }
  }*/
  
  /*void insertHelperString(BSTNode*& curr, BSTNode*& prev, KeyT realKey, int convKey, ValT value){
    if(curr == nullptr){
      curr = new BSTNode(realKey,value,prev);
    } else if (intify(curr->key) > convKey){
      insertHelperString(curr->left,curr,realKey,convKey,value);
    } else {
      insertHelperString(curr->right,curr,realKey,convKey,value);
    }
  }*/

  /**
   * Return a reference to the value stored for `key` in the map.
   *
   * If key is not present in the map, throw `out_of_range` exception.
   *
   * Runs in O(H), where H is the height of the tree.
   */
  ValT& at(const KeyT& key) const {
    // TODO_STUDENT
    if(sz == 0){
      throw out_of_range("ts out a range, cuh");
    } else {
      /*if(!isdigit(key)){
        atHelperString(this->root,key,intify(key));
      } else { */
        return atHelper(this->root,key);
      //}
    }
  }

  /*ValT& atHelperString(BSTNode* curr, KeyT realKey, int convKey) const {
    if(curr == nullptr){ 
      throw out_of_range("ts dont exist, cuh");
    } else if (curr->key == realKey){
      return curr->value;
    } else if (intify(curr->key) > convKey) {
      atHelperString(curr->left,realKey,convKey);
    } else {
      atHelperString(curr->right,realKey,convKey);
    }
  }*/
  
  /*ValT& atHelper(BSTNode* curr, KeyT key) const {
    if(curr == nullptr){ 
      throw out_of_range;
    } else if (curr->key == key){
      return curr->value;
    } else if (curr->key > key){
      atHelper(curr->left,key);
    } else {
      atHelper(curr->right,key);
    }
  }*/

  /**
   * Returns `true` if the key is present in the map, and false otherwise.
   *
   * Runs in O(H), where H is the height of the tree.
   */
  bool contains(const KeyT& key) const {
    // TODO_STUDENT
    if(this->sz == 0){
      return false;
    } else {
      /*if(!isdigit(key)){
        //return containsHelperString(this->root,key,intify(key));
      } else { */
        return containsHelper(this->root,key);
      //}
    }
  }

  /*bool containsHelper(BSTNode*& curr, KeyT key) const{
    if(curr == nullptr){
      return false;
    }
    if(curr->key == key){
      return true;
    }
    if(curr->key > key){
      containsHelper(curr->left,key);
    } else {
      containsHelper(curr->right,key);
    }
  }*/

 /* bool containsHelperString(BSTNode*& curr, KeyT realKey, int convKey) const{
    if(curr == nullptr){
      return false;
    }
    if(curr->key == realKey){
      return true;
    }
    if(intify(curr->key) > convKey){
      containsHelper(curr->left,realKey,convKey);
    } else {
      containsHelper(curr->right,realKey,convKey);
    }
  } */

  /**
   * Empties the `BSTMap`, freeing all memory it controls.
   *
   * Runs in O(N), where N is the number of mappings.
   */
  void clear() {
    // TODO_STUDENT
    if(this->sz != 0){
      this->sz = 0;
      dHelp(this->root);
      this->root = nullptr;
    }
  }

  /*void dHelp(BSTnode*& curr){
    if (curr == nullptr) {
      return;
    }
    dHelp(curr->left);
    dHelp(curr->right);
    delete curr;
  }*/

  /**
   * Destructor, cleans up the `BSTMap`.
   *
   * Runs in O(N), where N is the number of mappings.
   */
  ~BSTMap() {
    // TODO_STUDENT
    clear();
  }

  /**
   * Converts the `BSTMap` to a string representation, with the values
   * in-order by key.
   *
   * Example:
   *
   * ```c++
   * BSTMap<string, int> names;
   * names.insert("Gwen", 10);
   * names.insert("Jen", 5);
   * names.insert("Ben", 10);
   * names.insert("Sven", 7);
   * ```
   *
   * Calling `names.to_string()` would return the following **multi-line**
   * string:
   *
   * ```text
   * Ben: 10
   * Gwen: 10
   * Jen: 5
   * Sven: 7
   * ```
   *
   * Runs in O(N), where N is the number of mappings.
   */
  string to_string() const {
    // TODO_STUDENT
    if(this->sz == 0){
      return "";
    }
    stringstream stream("");
    toStringHelper(this->root,stream);
    string str = stream.str();
    return str;
  }
  
  /*void toStringHelper(BSTNode*& curr, stringstream& stream) const{
    if(curr != nullptr){
      toStringHelper(curr->left,stream);
      stream << curr->key << ": " << curr->value << endl;
      toStringHelper(curr->right,stream);
    }
  }*/

  /**
   * Copy constructor.
   *
   * Copies the mappings from the provided `BSTMap`.
   * The internal tree structure must be copied exactly.
   *
   * Runs in O(N), where N is the number of mappings in `other`.
   */
  BSTMap(const BSTMap& other) {
    // TODO_STUDENT
    if(other.sz==0){
      this->root = nullptr;
      this->sz = 0;
      this->curr = nullptr;
    } else {
      //this->root = new BSTNode(other.root->key,other.root->value,nullptr);
      this->sz = other.sz;
      this->curr = nullptr;
      copyHelper(this->root,nullptr,other.root);
    }
  }

  /*void copyHelper(BSTNode*& thisCurr, BSTNode* prev, BSTNode*& otherCurr){
    if(otherCurr != nullptr){
      this->curr = new BSTNode(otherCurr->key,otherCurr->value,prev);
      copyHelper(thisCurr->left, thisCurr, otherCurr->left);
      copyHelper(thisCurr->right, thisCurr, otherCurr->right);
    }
  }*/

  /**
   * Assignment operator; `operator=`.
   *
   * Clears this tree, and copies the mappings from the provided `BSTMap`.
   * The internal tree structure must be copied exactly.
   *
   * Runs in O(N + O), where N is the number of mappings in `this`, and O is
   * the number of mappings in `other`.
   */
  BSTMap& operator=(const BSTMap& other) {
    // TODO_STUDENT
    if(this == &other){
      return *this;
    }
    this->clear();
    if(other.sz==0){
      this->root = nullptr;
      this->sz = 0;
      this->curr = nullptr;
    } else {
      //this->root = new BSTNode(other.root->key,other.root->value,nullptr);
      this->sz = other.sz;
      this->curr = nullptr;
      copyHelper(this->root,nullptr,other.root);
    }
    return *this;
  }

  // =========================================================================

  /**
   * Locates the smallest key in the BSTMap, and removes and returns its
   * mapping. If the `BSTMap` is empty, throws a `runtime_error`.
   *
   * Creates no new nodes, and does not update the key or value of any
   * existing nodes.
   *
   * Runs in O(H), where H is the height of the tree.
   */
  pair<KeyT, ValT> remove_min() {
    // TODO_STUDENT
    return {KeyT{}, ValT{}};
  }

  /**
   * Resets internal state for an iterative inorder traversal.
   *
   * See `next` for usage details. Modifies nothing except for `curr`.
   *
   * O(H), where H is the maximum height of the tree.
   */
  void begin() {
    // TODO_STUDENT
  }

  /**
   * Uses the internal state to return the next in-order key and value
   * by reference, and advances the internal state. Returns `true` if the
   * reference parameters were set, and `false` otherwise.
   *
   * Example usage:
   *
   * ```c++
   * BSTMap<string, int> bst;
   * bst.begin();
   * string key;
   * int value;
   * while (bst.next(key, val)) {
   *   cout << key << ": " << val << endl;
   * }
   * ```
   *
   * Modifies nothing except for `curr`.
   *
   * Runs in worst-case O(H) where H is the height of the tree.
   */
  bool next(KeyT& key, ValT& val) {
    // TODO_STUDENT
    return false;
  }

  // =========================================================================

  /**
   * Removes the mapping for the given key from the `BSTMap`, and returns the
   * value.
   *
   * Throws `out_of_range` if the key is not present in the map. Creates no new
   * nodes, and does not update the key or value of any existing nodes.
   *
   * Runs in worst-case O(H) where H is the height of the tree.
   */
  ValT erase(const KeyT& key) {
    // TODO_STUDENT
    return ValT{};
  }

  // =========================================================================

  /**
   * Returns a pointer to the root node of the `BSTMap`. For autograder testing
   * purposes only.
   */
  void* getRoot() const {
    return this->root;
  }
};
