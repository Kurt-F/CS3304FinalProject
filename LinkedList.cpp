#include <stdlib.h>

using namespace std;
template<class T>
class LNode{
    public: 
        LNode<T>* next;
        LNode(int k, T v){next = NULL; value = v; key = k;}
        T getValue(){
            return value;
        }

        void setValue(T v){
            value = v;
        }

        int getKey(){
            return key;
        }
    private:
        T value;
        int key;
    };

template<class T>
class LinkedList{
    public:
        LinkedList(){
            head = NULL;
            length = 0;
        }

        //Define a destructor
        ~LinkedList(){
            LNode<T>* next = head;
            while(next){
                LNode<T>* temp = next->next;
                delete next;
                next = temp;
            }
        }

        //Add a key to the list
        void add(int key, T elem){
            //If the list is empty then make the head
            if(head == NULL){
                head = new LNode<T>(key, elem);
                length += 1;
            }
            else{

                //Iteratively descend the list until elem < next elem
                LNode<T>* cursor = head;
                //Use short-circuiting to make sure sorting works
                while(cursor->next != NULL && cursor->next->getKey() < key){
                    cursor = cursor->next;
                }
                //If there already exists a node with the same key then override the value
                if(cursor->getKey() == key)
                    cursor->setValue(elem);
                else{
                length += 1;
                //Create the new node
                LNode<T>* n = new LNode<T>(key, elem);
                //Keep the next node in a temporary variable
                LNode<T>* temp = cursor->next;
                //Set the next node to our new node
                cursor->next = n;
                //Set the next node of our new node to the old next node.
                n->next = temp;
                }
            }
        }
        //return true if the list contains a node with the given key, false otherwise
        bool contains(int key){
            LNode<T>* cursor = head;
            //Iterate through the list until we find the desired key
			while(cursor->next != NULL){
                    if(cursor->getKey == key)
                        return true;
                    else
                        cursor = cursor->next;
                }
            //If we iterate through the entire list and can't find it, return false
            return false;
		}

        //Remove the node with the given key
        void remove(int key){
            LNode<T>* cursor = head;
            while(cursor->next != NULL){
                    //If we find the node, then remove it
                    if(cursor->next->getKey() == key){
                        LNode<T>* temp = cursor->next->next;
                        //Delete the node we want to delete
                        delete cursor->next;
                        //Relink the chain
                        cursor->next = temp;
                    }
                    else
                        cursor = cursor->next;
                }
            //If we iterate through the entire list and can't find it, do nothing
        }
        int getLength(){
            return length;
        }

    private:
        LNode<T>* head;
        int length;
};
