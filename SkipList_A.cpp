#include <stdlib.h>


using namespace std;


template<class T>
class Node{
    public:
        Node* next;
        T *array;
        Node(T v, Node* n){next = n; value = v;}
};

template<class T>
class SkipList_AL{
    public:
        SkipList_AL(T elem){
            if(elem != NULL){
                Node<T> *n = new Node<T>(elem, NULL);
                head = n;    
            }
            else{
                head = NULL;   
            }
        }
        //Delete the head node, and move the head pointer back
        
        //Add a node after tail, and move tail forward 
        void add_node(T elem){
            Node<T> *temp = head;
            head = new Node(elem, temp);
            
        } 
        void get_value(){
            
        }
    private:
        Node<T> *head; 

};

class SkipList_A{

};

class SkipList_L{


};


int main(){
    SkipList<int> *test = new SkipList<int>();    
    return 0;
}
