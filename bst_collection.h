# ifndef BST_COLLECTION_H
# define BST_COLLECTION_H

# include <iostream>
# include < vector >
# include " collection .h"


template < typename K , typename V >
class BSTCollection : public Collection <K ,V >
{
 public :

 // create an empty linked list
 BSTCollection ();

 // copy a linked list
 BSTCollection ( const BSTCollection <K ,V >& rhs );

 // assign a linked list
 BSTCollection <K ,V >& operator=(const BSTCollection <K ,V >& rhs);

 // delete a linked list
 ~ BSTCollection ();

 // insert a key - value pair into the collection
 void insert(const K& key , const V& val);

 // remove a key - value pair from the collection
 void remove( const K& key );

 // find the value associated with the key
 bool find(const K& key , V& val) const ;

 // find the keys associated with the range
 void find(const K& k1 , const K& k2 , std :: vector <K >& keys) const ;

 // return all keys in the collection
 void keys(std :: vector <K >& keys) const ;

 // return collection keys in sorted order
 void sort(std :: vector <K >& keys) const ;

 // return the number of keys in collection
 int size() const ;

 // return the height of the tree
 int height() const ;

private :

 // binary search tree node structure
 struct Node {
  K key ;
  V value ;
  Node* left ;
  Node* right ;
 };

 // root node of the search tree
 Node* root ;

 // number of k-v pairs in the collection
 int collection_size ;

 // helper to recursively empty search tree
 void make_empty(Node* subtree_root);

 // helper to recursively build sorted list of keys
 void inorder(const Node* subtree, std :: vector <K >& keys  const ;

 // helper to recursively build sorted list of keys
 void preorder(const Node* subtree, std :: vector <K >& keys) const ;

 // helper to recursively find range of keys
 void range_search(const Node* subtree, const K& k1, const K& k2,
 std :: vector <K >& keys) const ;

 // return the height of the tree rooted at subtree_root
 int height(const Node* subtree_root) const ;

};


template < typename K , typename V >
BSTCollection <K ,V >:: BSTCollection () :
collection_size (0) , root ( nullptr )
{
}


template < typename K , typename V >
void BSTCollection <K ,V >:: make_empty(Node* subtree_root)
{
 if(subtree_root != nullptr)
 {
  make_empty(subtree_root->left);
  make_empty(subtree_root->right);
  delete subtree_root;
 }
}


template < typename K , typename V >
BSTCollection <K ,V >::~ BSTCollection ()
{
 make_empty(root);
}


template < typename K , typename V >
BSTCollection <K ,V >:: BSTCollection ( const BSTCollection <K ,V >& rhs )
: collection_size (0) , root ( nullptr )
{
 *this = rhs ;
}


template < typename K , typename V >
BSTCollection <K ,V >& BSTCollection <K ,V >:: operator=(const BSTCollection <K ,V >& rhs)
{
 if (this == &rhs)
  return *this ;
 // delete current
 make_empty(root);
 // build tree
 std :: vector <K > ks ;
 preorder(rhs.root, ks);
 
 for (K key : ks)
 {
  V val;
  rhs.find(key, val);
  insert(key, val);
 }
 return *this ;
}


template < typename K , typename V >
void BSTCollection <K ,V >:: insert(const K& key , const V& val)
{
 Node* ins=new Node;
 ins->key=key;
 ins->value=val;
 ins->left=nullptr;
 ins->right=nullptr;
 if(root == nullptr)
 {
  root=ins;
  collection_size++;
  return;
 }

 if(root->left == nullptr && root->right == nullptr)
 {
  if(key<root->key){
    root->left=ins;
  }
  else{
   root->right = ins;
  }
  collection_size++;
  return;
 }

 Node* cur=root;
 Node* parent=nullptr;
 while(cur != nullptr)
 {
  parent=cur;
  if(key <= cur->key) {
   cur=cur->left;
  }
  else {
   cur=cur->right;
  }
 }

 if(key <= parent->key) {
  parent->left = ins;
 }
 else {
  parent->right = ins;
 }
 collection_size++;
}



template < typename K , typename V >
void BSTCollection <K ,V >:: remove(const K& key)
{
 if(subtree_root && key < subtree_root->key) {
   subtree_root->left=remove(key, subtree_root->left);
 }
 else if(subtree_root && key > subtree_root->key) {
    subtree_root->right=remove(key, subtree_root->right);
 }
 else if(subtree_root && key == subtree_root->key)
 {
  if(subtree_root->left == nullptr && subtree_root->right == nullptr)
  {
   subtree_root=nullptr;
   collection_size--;
  }
  else if(subtree_root->left != nullptr && subtree_root->right == nullptr)
  {
   V v=subtree_root->left->value;
   K k=subtree_root->left->key;
   Node* nlef=subtree_root->left->left;
   remove(key, subtree_root->left);
   subtree_root->key=k;
   subtree_root->value=v;
   subtree_root->left=nlef;
   collection_size--;
   return subtree_root;
  }
  else if(subtree_root->left == nullptr && subtree_root->right != nullptr)
  {
   V v=subtree_root->right->value;
   K k=subtree_root->right->key;
   Node* nri=subtree_root->right->right;
   remove(key, subtree_root->right);
   subtree_root->key=k;
   subtree_root->value=v;
   subtree_root->right=nri;
   collection_size--;
   return subtree_root;
  }
  else if(subtree_root->left != nullptr && subtree_root->right != nullptr)
  {
   Node* cur;
   cur=subtree_root;
   while(cur->left != nullptr) {
    cur=cur->left;
   }
   V v=cur->value;
   K k=cur->key;
   remove(key, cur);
   cur=nullptr;
   subtree_root->key=k;
   subtree_root->value=v;
   collection_size--;
   return subtree_root;
   }
 }

 return subtree_root;
}


template < typename K , typename V >
bool BSTCollection <K ,V >:: find(const K& key , V& val) const
{
 Node* cur=root;
 while(cur != nullptr)
 {
  if(cur->key == key)
  {
   val=cur->value;
   return true;
  }
  else if(key <= cur->key) {
   cur=cur->left;
  }
  else if(key > cur->key) {
   cur=cur->right;
  }
  return false;
}


template < typename K , typename V > void
BSTCollection <K ,V >::
range_search(const Node* subtree, const K& k1, const K& k2, std :: vector <K >& ks ) const
{
 if(subtree == nullptr) {
  return;
 }

 if(k1 < subtree->key){
  range_search(subtree->left, k1, k2, keys);
 }
 if(subtree->key > k1 && subtree->key < k2){
  keys.push_back(subtree->key);
 }
 if(k2 > subtree->key){
  range_search(subtree->right, k1, k2, keys);
 }
}


template < typename K , typename V > void
BSTCollection <K ,V >:: find(const K& k1, const K& k2, std :: vector <K >& ks) const
{
 // defer to the range search ( recursive ) helper function
 range_search(root, k1, k2, ks);
}


template < typename K , typename V >
void BSTCollection <K ,V >:: inorder(const Node* subtree, std :: vector <K >& ks) const
{
 if(subtree == nullptr){
    return;
 }
 inorder(subtree->left, ks);
 ks.push_back(subtree->key);
 inorder(subtree->right, ks);
}


template < typename K , typename V >
void BSTCollection <K ,V >:: preorder(const Node* subtree , std :: vector <K >& ks) const
{
 if(subtree == nullptr) {
    return;
 }
 ks.push_back(subtree->key);
 inorder(subtree->left, ks);
 inorder(subtree->right, ks);
}


template < typename K , typename V >
void BSTCollection <K ,V >:: keys(std :: vector <K >& ks) const
{
 // defer to the inorder ( recursive ) helper function
 inorder(root, ks);
}


template < typename K , typename V >
 void BSTCollection <K ,V >:: sort(std :: vector <K >& ks) const
{
 // defer to the inorder ( recursive ) helper function
 inorder(root, ks);
}


template < typename K , typename V >
int BSTCollection <K ,V >:: size() const
{
 return collection_size ;
}


template < typename K , typename V >
int BSTCollection <K ,V >:: height(const Node* subtree_root) const
{
 if(subtree_root == nullptr) {
    return 0;
 }
 int lhs=1 + height(subtree_root->left);
 int rhs=1 + height(subtree_root->right);
 if(lhs > rhs) {
  return lhs;
 }
 else {
  return rhs; 
 }
}


template < typename K , typename V >
int BSTCollection <K ,V >:: height() const
{
 // defer to the height ( recursive ) helper function
 return height(root);
}

# endif
