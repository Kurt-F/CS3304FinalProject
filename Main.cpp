#include <iostream>
#include "TestCases.cpp"

using namespace std;


//Makes booleans print nicer
string pBool(bool b){
	//If the parameter is true, return the string "true"
	if(b)
		return "true";
	//else return the string "false"
	return "false";
}

int main(){
	/*
	 * Perform border testing, ensure all basic functions work
	 *
	*/
	//test BSTs
	BinaryTree<string>* tree = new BinaryTree<string>();
	tree->add(1, "Utah");
	tree->add(3, "Europe");
	tree->add(2, "Yugoslavia");
	tree->add(5, "");
	tree->add(1231231, "bigkey");
	cout << "(1 is yes, 0 is no)" << endl;
	cout << "Does the tree contain a node with key five? \n" << tree->contains(5) << endl <<endl;
	cout << "What is the value of the node with key 3(Europe)? \n" << tree->get(3) << endl << endl;
	cout << "What is the value of the node with key 1(Utah)? \n" << tree->get(1) << endl << endl;
	cout << "What is the value of the node with key 2(Yugoslavia)? \n" << tree->get(3) << endl << endl;
	cout << "What is the value of the node with key 1231231? \n" << tree->get(1231231) << endl;
	cout << "What happens when you use an invalid key? \n";
	//Use a try-catch block to handle the error thrown by using an invalid key
	try{
	cout << "Pointer to the value of the node with index -1 is: " << tree->get(-1) << endl;
	}
	catch(logic_error& e){
		cout << "The answer is it returns null, or throws an error if null is not defined for T" << endl << endl;
	}
	cout << "Inserting a random number < 10 of integer pointers into a skiplist" << endl;
	SkipList<int*>* plist = new SkipList<int*>(log2(101), NULL);
	int end = rand()%10;
	for(int i = 0; i < end; i++){
		plist->add(i, &i);
	}
	cout << "Printing all addresses in the pointer list:" << endl;
	int i = 0;
	while(plist->getLength()){
		cout << plist->search(i)->getValue() << endl;
		plist->remove(i);
		i++;
	}
	cout << "Inserting a random number < 100 of nodes into a skiplist" << endl;
	SkipList<Node<int>*>* nlist = new SkipList<Node<int>*>(log2(101), NULL);
	end = rand()%100;
	for(int i = 0; i < end; i++){
		Node<int>* node = new Node<int>(i,i,i);
		nlist->add(i, node);
	}
	cout << "Printing all adresses in the node list:" << endl;
	i = 0;
	while(nlist->getLength()){
		cout << nlist->search(i)->getValue() << endl;
		nlist->remove(i);
		i++;
	}

	

	//test skiplists
	SkipList<int>* list = new SkipList<int>(100, 0);
    //Fill the list with random numbers
	cout << "Populating a skiplist with 50 integers with random key" << endl;
    for(int i = 0; i < 50; i++)
    	list->add(rand()%100,i);
   	//Remove all occurences of 13
   	cout << "Removing all occurences of 13 from the skiplist" << endl;
   	while(!list->remove(13));
    cout << "Skip list populated with random values, enter an integer to search keys. Enter -1 to quit." << endl;
    int key = 0;
 	while(key >-1){
 		cin >> key;
 		Node<int>* result = list->search(key);
 		if(result)
 			cout << "Key found! Value = "<< result->getValue() << endl;
 		else if(key > -1)
 			cout << "Key not found." << endl;
 	}




	//Run insertion/search tests
	insertTest();
	//objectTest();
	deleteTest();
	return 0;
}
