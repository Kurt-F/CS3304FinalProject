#include <iostream>
#include <stdlib.h>

using namespace std;
template<class T>
class Node{
    public: 
        Node(T v){next = NULL; value = v;}
        T value;
        Node* next;
    };

template<class T>
class LinkedList{
    public:
        LinkedList(){
            head = NULL;
            length = 0;
        }


        void add(T elem){
            length += 1;
            if(head == NULL){
                head = new Node<T>(elem);
                                    cout << "test" << endl;
            }
            else{
                Node<T>* n = new Node<T>(elem);
                //Iteratively descend the list until elem < next elem
                Node<T>* index = head;
                //Use short-circuiting to make sure sorting works
                //  (comparison comes before null check)
                while(index->elem > n->elem && index->next != NULL){
                    index = index->next;
                }
                Node* temp = index->next;
                index->next = n;
                n->next = temp;
                   
            }
        }
        //Return a link to the 
        void get(T elem){

        int getLength(){
            return length;
        }
    private:
        Node<T>* head;
        Node<T>* tail;
        int length;
};

int main(){
    LinkedList<int>* test = new LinkedList<int>();
    test->add(3);
    test->add(4);
    test->add(45);
    int l = test->getLength();
    cout << l << endl;
    return 0;
    }

