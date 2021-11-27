/*
	animal.cpp

	author: Massimo Giusti
	date: 26 November 2021

	Animal/20 questions program for CSCI 262, starter code.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <queue>
#include <sstream>
#include <queue>

using namespace std;

class node {
public:
    string data;
    node* left;
    node* right;
	node(string nodeData);
	bool isLeaf();
};

/**
 * @brief Construct a new node::node object
 * 
 * @param nodeData the question stored in each node
 */
node::node(string nodeData){
	data = nodeData;
	left = nullptr;
	right = nullptr;
}

/**
 * @brief checks if node is leaf
 * 
 * @return true if both left and right pointer are null
 * @return false otherwise
 */
bool node::isLeaf(){
	return(left == nullptr && right == nullptr);
}

void play_game(node*, queue<string>&);
node* read_game_tree();
void write_game_tree(node*);
void delete_game_tree(node*);
void printTree(node*, string&);

/**
 * Handles showing the main menu/basic UI
 */
int main() {
	node* root = read_game_tree();
	if (root == NULL) return -1;

	while (true) {
		string tmp;
		int choice;

		cout << "Welcome to 20 questions!" << endl;
		cout << "  1) Play the game" << endl;
		cout << "  2) Save the game file" << endl;
		cout << "  3) Quit" << endl;
		cout << "Please make your selection: ";
		getline(cin, tmp);
		choice = atoi(tmp.c_str());
		queue<string> q;

		switch (choice) {
    		case 1:
    			play_game(root, q);
    			break;
    		case 2:
    			write_game_tree(root);
    			break;
    		case 3:
    			break;
    		default:
    			cout << "Sorry, I don't understand." << endl << endl;
		}
		if (choice == 3) break;
	}

	delete_game_tree(root);
	return 0;
}

/**
 * @brief recursive constructor function for binary tree to represent game, constructs tree in preorder
 * 
 * @param fin ifstream file containing questions
 * @return node* head node
 */
node* constructNode(ifstream& fin){
	if(!fin.eof()){
		string data = "";
		string nodeType = "";
		string question = "";
		getline(fin, data);
		//parse line into nodetype and data
		istringstream stream(data);
		stream >> nodeType;
		getline(stream, question);
		//first char in question is a space char when parsed
		question.erase(question.begin());
		node* nd = new node(question);
		//if nodetype is a question, construct and recurse on children. 
		//if nodetype is leaf, return node
		if(nodeType == "#Q"){
			nd->left = constructNode(fin);
			nd->right = constructNode(fin);
		}
		return nd;
	}
	return nullptr;
}

/**
 * @brief prints tree data recursively by preorder traversal
 * 
 * @param head pointer to head node
 * @param result string representation of new file format
 */
void printTree(node* head, string& result){
	if(!head->isLeaf()){
		result.append("#Q " + head->data + "\n");
		printTree(head->left, result);
		printTree(head->right, result);
	}else{
		result.append("#A " + head->data + "\n");
	}
}


/**
 * Sets up the recursive call to the read_preorder
 * @return root of the binary tree
 */
node* read_game_tree() {
	ifstream fin("animal_game_tree.txt");
	node* head = constructNode(fin);
	return head;
}

/**
 * @brief expands tree when guessing algorithm fails to guess correctly, expands based on user input
 * 
 * @param nd pointer to node that will be expanded
 * @param q queue of all questions asked in current game
 */
void expandTree(node* nd, queue<string> q){
	string animal = "";
	string newQuestion = "";
	string str = "";
	cout << "I asked the following:" << endl;
	//print out questions asked
	while(!q.empty()){
		cout << q.front() << endl;
		q.pop();
	}
	//get input for new animal
	cin.clear();
	cout << "Enter a new animal in the form of a question, e.g., 'Is it a whale?': ";
	//clear cin for next input: beginning of cin is \n, getline clears it
	getline(cin, str);
	//get animal
	getline(cin, animal);
	//get new question
	cout << "Now enter a question for which the answer is 'yes' for your new animal, and which does not contradict your previous answers: ";
	getline(cin, newQuestion);
	//expand graph: newQuestion overwrites nd->data, and temp becomes its right child and newNode becomes left child
	node* temp = new node(nd->data);
	node* newNode = new node(animal);
	nd->data = newQuestion;
	nd->left = newNode;
	nd->right = temp;
}

/**
 * Plays the game by traversing through graph recursively
 * @param root Root of the game tree
 * @param q queue holding all the questions asked in current game
 */
void play_game(node* root, queue<string>& q) {
	string answer = "";
	cout << root->data << " (y/n): ";
	getline(cin, answer);
	q.push(root->data + " " + answer);
	if(root->isLeaf()){
		if(answer == "Y" || answer == "y"){
			cout << "YAY! I guessed your animal!" << endl;
		}else if(answer == "N" || answer == "n"){
			cout << "BOO! I don't know!" << endl << endl;
			//if guess incorrect, ask to expand game
			cout << "Would you like to expand the game tree?" << " (y/n)" << endl;
			cin >> answer;
			if(answer == "Y" || answer == "y"){
				expandTree(root, q);
			}
		}else{
			//handle invalid inputs
			cout << "Invalid input: try again" << endl;
			play_game(root, q);
		}
	}else{
		//if current node is not a leaf, recurse on corresponding child node
		if(answer == "Y" || answer == "y"){
			play_game(root->left, q);
		}else if(answer == "N" || answer == "n"){
			play_game(root->right, q);
		}else{
			//handle invalid inputs
			cout << "Invalid input: try again" << endl;
			play_game(root, q);
		}
	}
}

/**
 * Writes the game tree, sets up a recursive call to write_preorder();
 * @param root The root of the tree
 */
void write_game_tree(node* root) {
	string newTree = "";
	printTree(root, newTree);
	//create ostream and delete contents of ostream file
	ofstream ofs;
	ofs.open("animal_game_tree.txt");
	//write tree to file
	ofs << newTree;
	ofs.close();
	cout << "Game file saved in 'animal_game_tree.txt'" << endl;
}

/**
 * Deletes the game tree
 * @param root Root of the game tree
 */
void delete_game_tree(node* root) {
    // Optional. Do a post-order deletion of the game tree.
    // This isn't strictly needed as the program exits after this is called,
    // which frees up all the memory anyway.
}
