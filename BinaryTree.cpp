#include <iostream>
//TODO: Finish remove function
//A node that contains a value, a key value, a left child, and a right child.
template <class T>
class BNode{
    public:
        //Constructor
        BNode(int k, T v){
            value = v;
            key = k;
            rchild = NULL;
            lchild = NULL;
        }
        //Get the value of the node
        T getValue(){
            return value;
        }
        //Get the key of the node
        int getKey(){
            return key;
        }
        //The children of the node
        BNode<T>* lchild;
        BNode<T>* rchild;
    private:
        //The value of the node
        T value;
        //The key of the node, used for searching, deleting, adding, etc
        int key;

        
};

template <class T>
class BinaryTree{
    public:
        //Create an empty binary tree
        BinaryTree(){
            root = NULL;
        }
        /* Add a value to the tree */
        void add(int key, T value){
            //If empty tree create root
            if(root == NULL){
                root = new BNode<T>(key, value);
            }
            //Else traverse the tree as usual
            else{
                BNode<T>* cursor = root;
                //Iterate until we reach a node with our value on it.
                //Implemented so that no duplicate values can exist
                while(cursor->getKey() != key){
                    //
                    if(cursor->getKey() > key){
                        if(cursor->lchild != NULL)
                            cursor = cursor->lchild;
                        else{
                            cursor->lchild = new BNode<T>(key, value);
                        }
                    }
                    else{
                        if(cursor->rchild != NULL)
                            cursor = cursor->rchild;
                        else{
                            cursor->rchild = new BNode<T>(key,value);
                        }
                    }
                }
            }
        }
        //Returns a pointer to a copy of the value of the node with the desired key
        T get(int key){
            BNode<T>* cursor;
            //An empty tree never contains anything
            if(root == NULL)
                return NULL;
            cursor = root;

            //Stop the loop if/when a key is found
            while(cursor->getKey() != key){ 
                //If there is no matching key, descend to the appropriate child node if it exists
                if(cursor-> lchild != NULL && cursor->getKey() > key)
                    cursor = cursor->lchild;
                else if (cursor -> rchild != NULL)
                    cursor = cursor->rchild; 
                //If we've reached a leaf, and no matching key has been found, then return false
                else{
                    cerr << "ERROR: INVALID KEY" << endl;
                    return NULL;
                }
            }
            //Once the key has been found, return true
            return cursor->getValue();
        }
        bool contains(int key){
            BNode<T>* cursor;
            //An empty tree never contains anything
            if(root == NULL)
                return false;
            else
                cursor = root;

            //Stop the loop if/when a key is found
            while(cursor->getKey() != key){ 
                //If there is no matching key, descend to the appropriate child node if it exists
                if(cursor-> lchild != NULL && cursor->getKey() > key)
                    cursor = cursor->lchild;
                else if (cursor -> rchild != NULL)
                    cursor = cursor->rchild; 
                //If we've reached a leaf, and no matching key has been found, then return false
                else
                    return false;
            }
            //Once the key has been found, return true
            return true;
        }

        void remove(int key){
            BNode<T>* cursor = root;
            while(cursor->getKey() != key){
                if(cursor-> lchild != NULL && cursor->getKey() > key)
                    cursor = cursor->lchild;
                else if (cursor -> rchild != NULL)
                    cursor = cursor->rchild; 
                //If we've reached a leaf, and no matching key has been found, then return.
                else
                    break;
            }

        }
    private:
        BNode<T>* root;
        
};