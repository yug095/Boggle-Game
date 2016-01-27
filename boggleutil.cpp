

#include"boggleutil.h"
//#include "boggleboard.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
using namespace std;

//In this file, implement all of the operations your data structures support (you have declared these operations in boggleutil.h).
bool TSTree::insert(std::string key){
	TSTNode* currnode=root;   
	int i=0;
	unsigned char d;

	int pointer;

    TSTNode* temp;
    //cout<<"test insert1 "<<key<<endl;
    if(!root){
    //cout<<"test insert2 "<<key<<endl;
     while(i<key.size()){
		TSTNode* newnode=new TSTNode(key.at(i));
		if(i==0){
			root=newnode;
			currnode=newnode;
		}
		else{
			currnode->middle=newnode;
			currnode=currnode->middle;
		}  	
     	i++;
	  }
     currnode->end=true;
     return true;
    }
    else{
    //cout<<"test insert3 "<<key<<endl;
	while(currnode){

    d=key.at(i);
    //cout<<"test insert5 "<<key<<endl;
    if((i==key.size()-1)&&(currnode->digit==d)){
    	//cout<<"1"<<endl;
        if(currnode->end==true) 
          return false;
        else{
           currnode->end=true;
           return true;
            }
    }
    if(d<currnode->digit){
      //cout<<"2"<<endl;
      pointer=0;
      temp=currnode;
      currnode=currnode->left;
    }
    else if(d>currnode->digit){
      //cout<<"3"<<endl;
      pointer=2;
      temp=currnode;
      currnode=currnode->right;
    }
    else{
      //cout<<"4"<<endl;
      i++;
      pointer=1;
      temp=currnode;
      currnode=currnode->middle;
        }
	}
    TSTNode* innode=new TSTNode(key.at(i));
    if(pointer==0){
    	temp->left=innode;
    }
    else if(pointer==1){
    	temp->middle=innode;
    }
    else {
    	temp->right=innode;
    }
    i++;
    temp=innode;
	while(i<key.size()){
		TSTNode* newnode=new TSTNode(key.at(i));
		temp->middle=newnode;
	  	temp=temp->middle;
     	i++;
	  }
    temp->end=true;
    return true;	
}
}

bool TSTree::find(std::string key){
	TSTNode* currnode=root;
	int i=0;
	while(currnode && i<key.size()){
		unsigned char d=key.at(i);
		if(currnode->end && i==key.size()-1 && currnode->digit==d){
			return true;
		}
		if(d<currnode->digit){
			currnode=currnode->left;
		}
		else if(d>currnode->digit){
			currnode=currnode->right;
		}
		else{
			i++;
			currnode=currnode->middle;
		}
	}
	return false;
}

bool TSTree::isPrefix(std::string key){
	TSTNode* currnode=root;
	int i=0;
	while(currnode && i<key.size()){
		unsigned char d=key.at(i);
		if(i==key.size()-1 && currnode->digit==d){
			return true;
		}
		if(d<currnode->digit){
			currnode=currnode->left;
		}
		else if(d>currnode->digit){
			currnode=currnode->right;
		}
		else{
			i++;
			currnode=currnode->middle;
		}
	}
	return false;
   
}

 









