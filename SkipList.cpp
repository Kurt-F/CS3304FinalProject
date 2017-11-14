#include <stdlib.h>
#include <cstdlib>
#include <iostream>

/**********************************************************************************************************
*   SkipList.cpp
*   Kurt Floyd
*   CS 3304
*   11/12/2017
*
*
*
***********************************************************************************************************/

template<class T>
class Node{
    public:
        //An array of nodes
        Node<T> **next;
        //Constructor. Nodes require a height, a key, and a value of generic type.
        Node( int h, int k, T v){
            //Assign basic values to the node
            height = h;
            key = k; 
            value = v;
            //Create the array of pointers. 
            Node<T> **temp = new Node<T>*[height];
            next = temp;
            //Initialise all the pointers to null
            for(int i = 0; i < height; i++)
                next[i] = NULL;
        }
        
        //Get the key of the node
        int getKey(){
            return key;
        }
        //Get the value of the node
        T getValue(){
            return value;
        }
        //get the height of the node
        int getH(){
            return height;
        }
    private:
        int height;
        int key;
        T value;
};
template<class T>
class SkipList{
    public:
        //h denotes the maximum height of this skiplist
        //T is a dummy value for head
        SkipList(int h, T dummy){
            srand(time(NULL));
            length = 0;
            maxHeight = h;
            //Head is simply an array of pointers
            head = new Node<T>(maxHeight, 0, dummy);
        }
        
        //Add a new value to the skiplist
        //Height must be generated first hand in order to "remember" the proper amount of nodes
        void add(int key, T val){
            //Create a cursor pointer
            Node<T>* cursor = head;
            int h = genHeight();
            //Array for storing the nodes to be updated. Only h nodes will point to the new node.
            Node<T> *update[h];
            //Create the node we're going to insert
            Node<T>* node = new Node<T>(h, key, val);

            //Search for the node right before where we need to insert our new node
            //Use decrementing so that search starts at the top level and descends.
            for(int i = maxHeight -1 ; i >= 0; i--){
                //While we haven't reached nil and while the next value is greater than our previous one, go to the next node
                while(cursor->next[i] != NULL && cursor->next[i]->getKey() < key){
                    //Go to the next node at the ith level
                    cursor = cursor->next[i];
                }

                //Once we reach a suitable level(the top element 'reached' by the height of the new node) add the node we
                //  descend from to update
                if(i <= h - 1){
                    update[i] = cursor;
                } 
            }
            //Cursor is now at a node right before where we want to insert our new node. In order to 
            //  prevent segmentation faults, first check to see if the node we're at is the last 
            //  node. i.e. check if cursor->next[h to 0] is ever null.
            for(int i = 0; i < h; i++ ){
                //If update[i] is an ending node for its level, then just set the next node to our new node
                if(update[i]->next[i] == NULL)
                    update[i]->next[i] = node;
                //If update[i] is not an ending node, then use a temporary variable to avoid losing the next
                //  part of the list
                else{
                    //Store the node that should be after our new node in temp
                    Node<T>* temp = update[i]->next[i];
                    //Insert our new node into the list
                    update[i]->next[i] = node;
                    //Reconnect the list
                    node->next[i] = temp;
                }
            }
        }

        void remove(int key){
            //Create a cursor pointer
            Node<T>* cursor = head;
            //Array for storing the nodes to be updated.
            Node<T> *update[maxHeight];
            //Search for the node right before where the node we want to delete is.
            //Use decrementing so that search starts at the top level and descends.
            for(int i = maxHeight -1 ; i >= 0; i--){
                /*cout << cursor->next[21];
                cout << ". Next called" << endl;
                cout << cursor->next[i]->getKey();
                cout << ". getKey() called" << endl;*/
                //While we haven't reached nil and while the next value is greater than our previous one, go to the next node
                while(cursor->next[i] != NULL && cursor->next[i]->getKey() < key){
                    //Go to the next node at the ith level
                    cursor = cursor->next[i];
                }
                //Add each node we descend on to the update array
                update[i] = cursor;
            }
            //Cursor is now at a node right before where we want to insert our new node. The forward 
            //  addresses of the node to be deleted are stored in an array, then the node is deleted
            //  from memory, and then the pointers of the nodes which pointed to  the deleted node 
            //  are "repaired. "In order to prevent segmentation faults, we check to see if the 
            //  node we're at is the last node. i.e. check if cursor->next[i]->next[i] is ever null.
            for(int i = 0; i < maxHeight; i++ ){
                //If update[i]->next[i] is an ending node for its level, then just remove it
                if(update[i]->next[i]->next[i] == NULL){
                    delete update[i];
                    update[i]->next[i] = NULL;
                }
                //If update[i] is not an ending node, then use a temporary variable to avoid losing the next
                //  part of the list
                else{

                }
            }
            
            //If we iterate through to the 0th level and can't find our node, do nothing            
        }
        //Searches for and returns the node with the given key, if it exists
        Node<T>* search(int key){
            Node<T>* cursor;
            //Start searching
            for(int i = maxHeight -1 ; i >= 0; i--){
                cursor = head->next[i];
                //While we haven't reached nil and while the next value is less than
                //   or equal to key, go to the next node or return a pointer to cursor
                //   if we've found the correct node
                while(cursor != NULL && cursor->getKey() <= key){
                    //if we've found our node, return
                    if(cursor->getKey() == key)
                        return cursor;
                    //If we haven't, go to the next node
                    cursor = cursor->next[i];
                }
            }
            //If we iterate through to the 0th level and can't find our node, return false;
            return NULL;
            
        }

        //Use the search function to return a boolean indicating whether the key parameter matches with a node
        bool contains(int key){            
            if(this->search(key) == NULL){
                return false;
            }
            return true;
        }

        //Traverses the skip list and print a representation to the terminal
        void traverse(){
            //for(int i = 0; i < maxHeight; i++)
            //    cout << "head["<<i<<"] = " << head[i];
            //Iterate through each level
            Node<T>* cursor;
            for(int i = 0; i < maxHeight; i++){
                cursor = head->next[i];
                cout << "Level " << i << ": ";
                while(cursor != NULL){
                    string padding = "\t";
                    cout << "(" << cursor->getKey() << "," << cursor->getValue() << ")" << padding;
                    if(cursor->next != NULL)
                        cursor = cursor->next[i];
                    else
                        break;
                }
                cout << endl;
            }
        }

        
            
    private:
        //Generate a height for a new node
        int genHeight(){
            int level = 1;
            //Keep "flipping a coin" to determine height
            double value = (double) rand()/RAND_MAX;
            while(value > 0.5 && level < maxHeight){
                value = (double) rand()/RAND_MAX;
                level++;
            }
            return level;
        }
        int length;
        int maxHeight;
        Node<T>* head;
};

