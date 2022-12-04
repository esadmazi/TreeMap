#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <cmath>

#include "Node.h"
#include "NoSuchItemException.h"

enum TraversalMethod {preorder, inorder, postorder};

template<class T>
class ScapegoatTree {
public: // DO NOT CHANGE THIS PART.
    ScapegoatTree(); //DONE

    ScapegoatTree(const ScapegoatTree<T> &obj); //DONE

    ~ScapegoatTree(); //DONE

    bool isEmpty() const; //DONE

    int getHeight() const; //DONE

    int getSize() const; //DONE

    bool insert(const T &element); //DONE

    bool remove(const T &element); //DONE

    void removeAllNodes(); //DONE

    const T &get(const T &element) const; //DONE

    void print(TraversalMethod tp=inorder) const; //DONE

    void printPretty() const; //DONE

    ScapegoatTree<T> &operator=(const ScapegoatTree<T> &rhs); // DONE

    void balance(); //DONE

    const T &getCeiling(const T &element) const; //DONE

    const T &getFloor(const T &element) const; //DONE

    const T &getMin() const; //DONE

    const T &getMax() const; //DONE

    const T &getNext(const T &element) const; //DONE

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.
    void print(Node<T> *node, TraversalMethod tp) const;
    void printPretty(Node<T> *node, int indentLevel, bool isLeftChild) const;
    int heightHelper(Node<T> *r) const;
    int sizeHelper(Node<T> *r) const;
    Node<T>* getMinHelper(Node<T> *r) const;
    Node<T>* getMaxHelper(Node<T> *r) const;
    Node<T>* searchNode(Node<T> *r, const T &element) const;
    Node<T>* findParent(Node<T> *r,Node<T> *node) const;
    void removeAllNodesHelper(Node<T> *r) const;
    Node<T>* getFloorHelper(Node<T> *r, Node<T> *floor, const T &element) const;
    Node<T>* getCeilingHelper(Node<T> *r, Node<T> *ceiling, const T &element) const;
    Node<T>* getNextHelper(Node<T> *r, Node<T> *next, const T &element) const;
    Node<T>* balanceSubTree(Node<T> *sr) const;
    int packIntoArray(Node<T> *sr, T* arr, int i) const;
    Node<T>* sortedArrayToBST(T* arr, int start, int end) const;
    int insertNodereturnHeight(Node<T> *newNode) const;
    int BSTtoArr(Node<T> * subroot, T* arr, int i) const;
    void removeSubTree(Node<T>* subtree) const;
    Node<T>* removeHelper(Node<T>* r, const T element) const;
    Node<T>* assign(Node<T>* lr, Node<T>* rr) const;


private: // DO NOT CHANGE THIS PART.
    Node<T> *root;

    int upperBound;
};

#endif //TREE_H

template<class T>
ScapegoatTree<T>::ScapegoatTree() {
    root = NULL;
    upperBound = 0;
}

template<class T>
ScapegoatTree<T>::ScapegoatTree(const ScapegoatTree<T> &obj) {
    /* TODO */
    root = NULL;
    *this = obj;

}

template<class T>
ScapegoatTree<T>::~ScapegoatTree() {
    removeAllNodesHelper(root);
}

template<class T>
bool ScapegoatTree<T>::isEmpty() const {
    if(root)
        return 0;
    else 
        return 1;
}

template<class T>
int ScapegoatTree<T>::getHeight() const {
    
    return heightHelper(root)-1;
}

template<class T>
int ScapegoatTree<T>::getSize() const {

    return sizeHelper(root);
}

template<class T>
bool ScapegoatTree<T>::insert(const T &element) {

    
    if(root){

        if(searchNode(root, element)) return false; // check if exist, if so return false.

        Node<T> * newNode = new Node<T>(element,NULL,NULL);
        int height = insertNodereturnHeight(newNode);
        upperBound++;

        if( height > log(upperBound)/log(1.5)){ // check for condition (2)
            Node<T> * scapeGoat = newNode;
            while(3* sizeHelper(scapeGoat) <= 2* sizeHelper(findParent(root, scapeGoat))){
                scapeGoat = findParent(root, scapeGoat);
            }
            scapeGoat = findParent(root, scapeGoat);
            if(scapeGoat)
                balanceSubTree(scapeGoat);
            else
                balance();
        }
        return true;
    }
    else{
        root = new Node<T>(element,NULL,NULL);
        upperBound++;
        return true;
    }
}

template<class T>
bool ScapegoatTree<T>::remove(const T &element) {
    
    if(!searchNode(root, element)) return false;

    root = removeHelper(root, element);
    if(upperBound/2.0 > sizeHelper(root)){
        upperBound = sizeHelper(root);
        balance();
    }
    return true;
}

template<class T>
void ScapegoatTree<T>::removeAllNodes() {

    removeAllNodesHelper(root);
    root = NULL;
}

template<class T>
const T &ScapegoatTree<T>::get(const T &element) const {
    /* TODO */
    Node<T>* temp = searchNode(root, element);
    if(temp == NULL){
        throw NoSuchItemException();
    }
    return temp->element;
}

template<class T>
void ScapegoatTree<T>::print(TraversalMethod tp) const {

    if (tp == preorder) {
        // check if the tree is empty?
        if (isEmpty()) {
            // the tree is empty.
            std::cout << "BST_preorder{}" << std::endl;
            return;
        }

        // the tree is not empty.

        // recursively output the tree.
        std::cout << "BST_preorder{" << std::endl;
        print(root, tp);
        std::cout << std::endl << "}" << std::endl;

    } else if (tp == inorder) {
        // check if the tree is empty?
        if (isEmpty()) {
            // the tree is empty.
            std::cout << "BST_inorder{}" << std::endl;
            return;
        }

        // the tree is not empty.

        // recursively output the tree.
        std::cout << "BST_inorder{" << std::endl;
        print(root, tp);
        std::cout << std::endl << "}" << std::endl;
    } else if (tp == postorder) {
        // check if the tree is empty?
        if (isEmpty()) {
            std::cout << "BST_postorder{}" << std::endl;
            return;
        }

        // tree not empty.recursively output the tree.
        std::cout << "BST_postorder{" << std::endl;
        print(root, tp);
        std::cout << std::endl << "}" << std::endl;
    }
}

template<class T>
void ScapegoatTree<T>::print(Node<T> *node, TraversalMethod tp) const {

    if (tp == preorder) {
        /* TODO */
        // check if the node is NULL?
        if (node == NULL)
            return;

        // first, output the node and comma (if needed).
        std::cout << "\t" << node->element;


        //then output left subtree.
        if (node->left) {
            std::cout << "," << std::endl;
        }
        print(node->left, preorder);
        


        // finally, output comma (if needed) and the right subtree.
        if (node->right) {
            std::cout << "," << std::endl;
        }
        print(node->right, preorder);

    } 
    
    
    else if (tp == inorder) {
        // check if the node is NULL?
        if (node == NULL)
            return;

        // first, output left subtree and comma (if needed).
        print(node->left, inorder);
        if (node->left) {
            std::cout << "," << std::endl;
        }

        // then, output the node.
        std::cout << "\t" << node->element;

        // finally, output comma (if needed) and the right subtree.
        if (node->right) {
            std::cout << "," << std::endl;
        }
        print(node->right, inorder);
    } 
    
    
    else if (tp == postorder) {
        /* TODO */
        // check if the node is NULL?
        if (node == NULL)
            return;

        // first, output left subtree and comma (if needed).
        print(node->left, postorder);
        if (node->left) {
            std::cout << "," << std::endl;
        }

        // then, output the right subtree.
        print(node->right, postorder);

        // finally, output comma (if needed) and the right subtree.
        if (node->right) {
            std::cout << "," << std::endl;
        }
        std::cout << "\t" << node->element;

    }
}

template<class T>
void ScapegoatTree<T>::printPretty() const {

    // check if the tree is empty?
    if (isEmpty()) {
        // the tree is empty.
        std::cout << "BST_pretty{}" << std::endl;
        return;
    }

    // the tree is not empty.

    // recursively output the tree.
    std::cout << "BST_pretty{" << std::endl;
    printPretty(root, 0, false);
    std::cout << "}" << std::endl;

}

template<class T>
void ScapegoatTree<T>::printPretty(Node<T> *node, int indentLevel, bool isLeftChild) const {

    // check if the node is NULL?
    if (node == NULL)
        return;

    // output the indentation and the node.
    std::cout << "\t";
    for (int i = 0; i < indentLevel; ++i) {
        std::cout << "---";
    }
    std::cout << (indentLevel == 0 ? "root:" : (isLeftChild ? "l:" : "r:")) << node->element << std::endl;

    // first, output left subtree with one more indentation level.
    printPretty(node->left, indentLevel + 1, true);

    // then, output right subtree with one more indentation level.
    printPretty(node->right, indentLevel + 1, false);
}

template<class T>
ScapegoatTree<T> &ScapegoatTree<T>::operator=(const ScapegoatTree<T> &rhs) {
    /* TODO */
    removeAllNodes();
    
    root = assign(root, rhs.root);
    upperBound = rhs.upperBound;
    return *this;

}

template<class T>
void ScapegoatTree<T>::balance() {

   root = balanceSubTree(root);

}

template<class T>
const T &ScapegoatTree<T>::getCeiling(const T &element) const {
    
    Node<T>* ceiling = NULL;

    Node<T>* temp = root;
    while(temp != NULL){
        
        if(element < temp->element){
            ceiling = temp;
            temp = temp->left;
        }
        else if(element > temp->element){
            temp = temp->right;
        }
        else{
            return temp->element;
        }

    }
    if(ceiling == NULL || root == NULL){
        throw NoSuchItemException();
    }
    return ceiling->element;
}

template<class T>
const T &ScapegoatTree<T>::getFloor(const T &element) const {
    
    Node<T>* floor = NULL;

    Node<T>* temp = root;
    while(temp != NULL){
        
        if(element < temp->element){
            temp = temp->left;
        }
        else if(element > temp->element){
            floor = temp;
            temp = temp->right;
        }
        else{
            return temp->element;
        }

    }
    if(floor == NULL || root == NULL){
        throw NoSuchItemException();
    }
    return floor->element;
}

template<class T>
const T &ScapegoatTree<T>::getMin() const {

    if(isEmpty()){
        throw NoSuchItemException();
    }
    else return getMinHelper(root)->element;
}

template<class T>
const T &ScapegoatTree<T>::getMax() const {
    if(isEmpty()){
        throw NoSuchItemException();
    }
    else return getMaxHelper(root)->element;
}

template<class T>
const T &ScapegoatTree<T>::getNext(const T &element) const {
  
    Node<T>* next = NULL;

    Node<T>* temp = root;
    while(temp != NULL){
        
        if(element < temp->element){
            next = temp;
            temp = temp->left;
        }
        else if(element > temp->element){
            temp = temp->right;
        }
        else{
            temp = temp->right;
        }

    }
    if(next == NULL || root == NULL){
        throw NoSuchItemException();
    }
    return next->element;
}








/*-----------HELPER FUNCTIONS-------------*/
template<class T>
int ScapegoatTree<T>::heightHelper(Node<T> *r) const{

    if (r == NULL)
        return 0;
    else {
        int left_height = heightHelper(r->left);
        int right_height = heightHelper(r->right);
        if (left_height >= right_height)
            return left_height + 1;
        else
            return right_height + 1;
    }
}

template<class T>
int ScapegoatTree<T>::sizeHelper(Node<T> *r) const{
    if(r == NULL){
        return 0;
    }
    else{
        int leftSize = sizeHelper(r->left);
        int rightSize = sizeHelper(r->right);
        return leftSize + rightSize +1 ;
    }
}

template<class T>
Node<T>* ScapegoatTree<T>::getMinHelper(Node<T> *r) const{
    Node<T>* current = r;
  
    /* loop down to find the leftmost leaf */
    while (current && current->left){
        current = current->left;
    }
    return current;
}

template<class T>
Node<T>* ScapegoatTree<T>::getMaxHelper(Node<T> *r) const{
    Node<T>* current = r;
  
    /* loop down to find the rightmost leaf */
    while (current && current->right)
        current = current->right;
  
    return current;
}

template<class T>
Node<T>* ScapegoatTree<T>::searchNode(Node<T> *r, const T &element) const{
  
  /*FUNCTION RETURNS NULL IF NOT EXIST, IF EXISTS RETURNS THE POINTER TO THAT NODE*/
   
    if (r == NULL || r->element == element)
       return r;
    
    if (r->element < element)
       return searchNode(r->right, element);
 
    // Key is smaller than root's key
    return searchNode(r->left, element);

}
template<class T>
Node<T>* ScapegoatTree<T>::findParent(Node<T> *r, Node<T> *node) const{
  
    if(r == NULL || r == node){
        return NULL;
    }

    Node<T> *temp = r;

    while(true){
        if(temp->element > node->element){

            if(temp->left == node) return temp;

            else{
                temp = temp->left;
            }
        }
        else if(temp->element < node->element){

            if(temp->right == node) return temp;

            else{
                temp = temp->right;
            }
        }
    }
}

template<class T>
void ScapegoatTree<T>::removeAllNodesHelper(Node<T> *r) const{
    if(r == NULL){
        return;
    }
    removeAllNodesHelper(r->left);
    removeAllNodesHelper(r->right);
    delete r;
}



template<class T>
int ScapegoatTree<T>::insertNodereturnHeight(Node<T> *newNode) const{

    if(root == newNode)     return 0;
   
    Node<T> *temp = root;
    int height = 0;

    do{
        if(temp->element < newNode->element){
            if(temp->right){
                temp = temp->right;

            }
            else{
                temp->right = newNode;
                return ++height;
            }
        }
        else if(temp->element > newNode->element){
            if(temp->left){
                temp = temp->left;
            }
            else{
                temp->left = newNode;
                return ++height;
            }
        }
        ++height;
    }
    while(true);
}


template<class T>
Node<T>* ScapegoatTree<T>::balanceSubTree(Node<T> *subroot) const{

    int nsize = sizeHelper(subroot);
    Node<T> * parent = findParent(root, subroot);
    T* arr = new T [nsize];

    BSTtoArr(subroot, arr, 0);

    if(!parent){
        removeAllNodesHelper(subroot);
        delete[] arr;
        return sortedArrayToBST(arr, 0, nsize-1);
    }
    else if(parent->left == subroot){
        removeAllNodesHelper(subroot);
        parent->left = sortedArrayToBST(arr, 0, nsize-1);
    }
    else if(parent->right == subroot){
        removeAllNodesHelper(subroot);
        parent->right = sortedArrayToBST(arr, 0, nsize-1);
    }
    delete[] arr;
}

template<class T>
int ScapegoatTree<T>::BSTtoArr(Node<T> * subroot, T* arr, int i) const{
    
    if (!subroot)
        return i;
 
    else{
        i = BSTtoArr(subroot->left, arr, i);
        arr[i++] = subroot->element;
        return BSTtoArr(subroot->right, arr, i);
    }
}

template<class T>
Node<T>* ScapegoatTree<T>::sortedArrayToBST(T * arr,int start, int end) const{

     /* Base Case */
    if (start > end)
        return NULL;
 
    /* Get the middle element and make it root */
    int mid = (start + end)/2;
    Node<T> *r = new Node<T>(arr[mid], NULL, NULL);
 
    /* Recursively construct the left subtree
    and make it left child of root */
    r->left = sortedArrayToBST(arr, start, mid - 1);
 
    /* Recursively construct the right subtree
    and make it right child of root */
    r->right = sortedArrayToBST(arr, mid + 1, end);
 
    return r;
}


template<class T>
Node<T>* ScapegoatTree<T>::removeHelper( Node<T>* r, const T element) const{
    
    
    // base case
    if (!r)
        return r;
 
    if (element < r->element)
        r->left = removeHelper(r->left, element);
 
    else if (element > r->element)
        r->right = removeHelper(r->right, element);
 
    else {
        // node has no child
        if (r->left == NULL && r->right == NULL){
            delete r;
            return NULL;
        }

        // node with only one child or no child
        else if (r->left == NULL) {
            Node<T>* temp = r->right;
            delete r;
            return temp;
        }

        else if (r->right == NULL) {
            Node<T>* temp = r->left;
            delete r;
            return temp;
        }
 
        // node with two children: Get the inorder successor
        // (biggest in the left subtree)
        Node<T>* temp = getMaxHelper(r->left);
 
        r->element = temp->element;
 
        r->left = removeHelper(r->left, temp->element);
    }
    return r;

    
}


template<class T>
Node<T>* ScapegoatTree<T>::assign(Node<T>* lr, Node<T>* rr) const{

    if(rr == NULL)
        return NULL;

    lr = new Node<T>(rr->element, NULL, NULL);

    lr->left = assign(lr->left, rr->left);
    lr->right = assign(lr->left, rr->right);
    return lr;
}