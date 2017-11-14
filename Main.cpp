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
	try{
	cout << "Pointer to the value of the node with index -1 is: " << tree->get(-1) << endl;
	}
	catch(logic_error& e){
		cout << "The answer is it returns null, or throws an error if null is not defined for T" << endl << endl;
	}
	

	//test skiplists
	SkipList<int>* list = new SkipList<int>(100, 0);
	cout << "list init" << endl;
	list->add(0, 0);
	cout << "0 added" << endl;
	list->add(1, 1);
	cout << "1 added" << endl;
	list->add(3, 3);
	list->traverse();
	cout << "Does the list contain 3? ";
	cout << pBool(list->contains(3)) << endl;
	cout << "Does the list contain 5? ";
	cout << pBool(list->contains(5)) << endl;
	cout << "Removing 3" << endl;
	list->remove(3);
	cout << "Does the list contain 3? ";
	cout << pBool(list->contains(3)) << endl;



	//Run insertion/removal tests
	//intTest();
	//objectTest();
	//searchTest();
	return 0;
}