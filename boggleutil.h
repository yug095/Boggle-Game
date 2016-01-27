

#ifndef BOGGLEUTIL_H
#define BOGGLEUTIL_H
#include <string>
#include <iostream>
//Data structures for lexicon and board should reside in this file.
using namespace std;
class TSTNode {
public:
    unsigned char digit;
    TSTNode* left;
    TSTNode* middle;
    TSTNode* right;
    bool end;
    TSTNode(unsigned char d) : left(0), middle(0),right(0),digit(d) { end=false;}
};

class TSTree{
public:
	TSTree() : root(0) {  }
	TSTNode* root;
	bool insert(std::string key);
	bool find(std::string key);
	bool isPrefix(std::string key);
	virtual ~TSTree(){
		//cout<<"call ~TSTree"<<endl;
		deleteAll(root);
	}
	static void deleteAll(TSTNode* n){
	if(!n) return ;
	deleteAll(n->left);
	deleteAll(n->middle);
	deleteAll(n->right);
	delete n;
	}

};

//All of the operations your data structures support should be declared within your data structures.
#endif
