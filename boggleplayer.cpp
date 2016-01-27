

#include "boggleplayer.h"
#include "boggleutil.h"
#include <unordered_map>
#include <string>
#include <map>
#include <set>
#include <iostream>
using namespace std;

void BogglePlayer::buildLexicon(const set<string>& word_list){
   for (set<string>::iterator it=word_list.begin(); it!=word_list.end(); ++it){
    if((*it).size()>0)
    //cout<<"dictionary insert "<< *it <<endl;
    this->dictionary.insert(*it);
  
}
}

//using  two hash board to sore the dictionary
void BogglePlayer::setBoard(unsigned int rows, unsigned int cols, string** diceArray) {

  this->ROWS=rows;
  this->COLS=cols;
  for(unsigned int r=0;r<rows;r++)    {
    for(unsigned int c=0;c<cols;c++)        {
       transform(diceArray[r][c].begin(), diceArray[r][c].end(), diceArray[r][c].begin(), ::tolower); 
       this->board2[r*cols+c]=diceArray[r][c];                
      if(this->board1.count(diceArray[r][c])){

      	std::unordered_map<std::string,std::vector<int> >::const_iterator got = board1.find (diceArray[r][c]);

      	std::vector<int> v=got->second;
      	this->board1.erase(diceArray[r][c]);
      	v.push_back(r*cols+c);
      	this->board1[diceArray[r][c]]=v;
      }
      else{
      	std::vector<int> v;
      	v.push_back(r*cols+c);
      	this->board1[diceArray[r][c]]=v;
      }
    }
  }

}

//this function assumes that there are at least 2*2 large board; This may be wrong. 
vector<int> BogglePlayer::FindNeighbous(int index){              
   vector<int> result;  
   if(((ROWS==1)&&(COLS>1))||((ROWS>1)&&(COLS==1))){
    if(index==0){result.push_back(index+1);}
    else if(index==COLS*ROWS-1){result.push_back(index-1);}
    else {result.push_back(index-1);result.push_back(index+1);}
   }
   else if((ROWS>1)&&(COLS>1)){

   if(index==0){
     result.push_back(index+1);result.push_back(index+this->COLS);result.push_back(index+this->COLS+1);
   }
   else if(index==this->COLS-1){
   	result.push_back(index-1);result.push_back(index+this->COLS);result.push_back(index+this->COLS-1);
   }
   else if(index==(this->ROWS-1)*this->COLS){
   	result.push_back(index+1);result.push_back(index-this->COLS);result.push_back(index-this->COLS+1);
   }
   else if(index==(this->COLS)*(this->ROWS)-1){
   	result.push_back(index-1);result.push_back(index-this->COLS);result.push_back(index-this->COLS-1);
   }
   else if(index<this->COLS){
   	result.push_back(index-1);result.push_back(index+1);result.push_back(index+this->COLS);result.push_back(index+this->COLS+1);result.push_back(index+this->COLS-1);  
   	 }
   else if(index>(this->ROWS-1)*COLS){
   	   	result.push_back(index-1);result.push_back(index+1);result.push_back(index-this->COLS);result.push_back(index-this->COLS+1);result.push_back(index-this->COLS-1);   
   }
   else if(index%COLS==0){
      result.push_back(index+1);result.push_back(index+1-this->COLS);result.push_back(index+1+this->COLS);result.push_back(index-this->COLS);result.push_back(index+this->COLS); 
   }
   else if((index+1)%COLS==0){
      result.push_back(index-1);result.push_back(index-1-this->COLS);result.push_back(index-1+this->COLS);result.push_back(index-this->COLS);result.push_back(index+this->COLS); 
   }
   else{
      result.push_back(index-1);result.push_back(index+1);result.push_back(index-1-this->COLS);result.push_back(index-1+this->COLS);
      result.push_back(index-this->COLS);result.push_back(index+this->COLS);result.push_back(index+1-this->COLS);result.push_back(index+1+this->COLS);
   }
 }

   return result;
}

//This is a bad function which find prefix very slowly
// std::map<std::vector<int>,std::string> BogglePlayer::Delete_Prefix(string& word, std::vector<int> v){
//      std::map<vector<int>,string > tmap;
  
//        for(int i=0;i<word.size();i++){
       	   
//        	  if(board1.count(word.substr(0,i+1))){
//   	      std::unordered_map<std::string,std::vector<int> >::const_iterator got = board1.find (word.substr(0,i+1));
//   	      std::vector<int> v1;
//   	      v1=got->second;
  	      
//           for(int j=0;j<v1.size();j++){
//     	    std::vector<int> vtemp;
//     	    vtemp=v;
//     	if(v.size()==0){
//     		vtemp.push_back(v1.at(j));
//     		tmap[vtemp]=word.substr(i+1,word.size()-i-1);
//     	}
//     	else{
//     		std::vector<int> nbor=FindNeighbous(v.back());
//     		if((std::find(nbor.begin(), nbor.end(), v1.at(j)) != nbor.end())&&(std::find(v.begin(),v.end(),v1.at(j))==v.end())){ 
//                vtemp.push_back(v1.at(j));
//     		   tmap[vtemp]=word.substr(i+1,word.size()-i-1);
//     		}
//     	}
//      }
//     }
//   }
//       return tmap;
//  }

//It did not verify whether a board or a lexcon has been constructed. But it is fast
bool BogglePlayer::getAllValidWords(unsigned int minimum_word_length, set<string>* words) {
    
  if(((!ROWS)&&(!COLS))||(!dictionary.root)){
    cout<<"either board or lexicon has not been constructed yet!!!"<<endl;
    return false;
  }
  int num=this->COLS*this->ROWS;
	for(int i=0;i<num; i++){
		int visited[num];
		int revisit[num];
		for(int j=0;j<num;j++){
			visited[j]=0;
			revisit[j]=0;
		}

		std::vector<int> S;
		int u;
		std::vector<string> word;
		S.push_back(i);

		while(S.size()){
           u=S.back();
           S.pop_back();
           if(revisit[u]){

           	revisit[u]=0;
           	visited[u]=0;

            word.pop_back();
              
           }

           else if((!visited[u])&& this->dictionary.isPrefix(combine(word)+this->board2[u])){  //combine 
           	revisit[u]=1;
            word.push_back(this->board2[u]);
            if(this->dictionary.find(combine(word))&&(combine(word).size()>=minimum_word_length)){
            	words->insert(combine(word));
            }
            visited[u]=1;
            S.push_back(u);
            vector<int> temp=FindNeighbous(u);
             for (std::vector<int>::iterator it = temp.begin() ; it != temp.end(); ++it){
                      if(!visited[*it])
                      	S.push_back(*it);
              }
           }
		}
	}
        return true;
}

//A helper function to combine all the string in a vector to be a string
 string BogglePlayer::combine(std::vector<string> word){
 	string res;
 	for (std::vector<string>::iterator it = word.begin() ; it != word.end(); ++it){
 		res=res+ *it;
 	}
 	return res;
 }

//does not verify whether a lexicon has been constructed    DONE!!!
bool BogglePlayer::isInLexicon(const string& word_to_check) {  
	    if(!this->dictionary.root){
        cout<<"have not build lexicon yet!!!"<<endl;
        return false;
      }
      if(this->dictionary.find(word_to_check))
           return true;
        else 
           return false;
}

//does not verify whether a board has been constructed   DONE!!!
// vector<int> BogglePlayer::isOnBoard(const string& word) {
// 	     std::map<std::vector<int>,string> cmap;
// 	     std::vector<int> evector;
// 	     cmap[evector]=word;
//        if((!COLS)&&(!ROWS)) {cout<<"have not set board yet!!!"<<endl; return evector; }
// 	     while(1){
// 	     	 for (std::map<vector<int>,string>::iterator it=cmap.begin(); it!=cmap.end(); ++it){
//                   if(it->second.size()==0) return it->first;
// 	     	 }
// 	     	 if(cmap.size()==0){
// 	     	 	return evector;
// 	     	 }
// 	     	 std::map<std::vector<int>,string> tempmap;
// 	     	 for (std::map<vector<int>,string>::iterator it=cmap.begin(); it!=cmap.end(); ++it){
// 	     	 	std::map<std::vector<int>,string> temp;
// 	     	 	temp=Delete_Prefix(it->second,it->first);
// 	     	 	tempmap.insert(temp.begin(),temp.end());
// 	     	 }
// 	     	 cmap=tempmap;
// 	     }
//          vector<int> result;
//          return result;
// }


vector<int> BogglePlayer::isOnBoard(const string& word) {
  vector<int> v;  
  if(((!ROWS)&&(!COLS))){
    
    cout<<" board  has not been constructed yet!!!"<<endl;
    return v;
  }
 if(!word.size()) return v;
 TSTree tree;
 tree.insert(word);
int num=this->COLS*this->ROWS;
  for(int i=0;i<num; i++){
    int visited[num];
    int revisit[num];
    for(int j=0;j<num;j++){
      visited[j]=0;
      revisit[j]=0;
    }

    std::vector<int> S;
    int u;
    vector<string> word_onboard;
    vector<int> res;
    S.push_back(i);

    while(S.size()){
           u=S.back();
           S.pop_back();
           if(revisit[u]){

            revisit[u]=0;
            visited[u]=0;
            res.pop_back();
            word_onboard.pop_back();
              
           }

           else if((!visited[u])&& tree.isPrefix(combine(word_onboard)+this->board2[u])){  //combine 
            revisit[u]=1;
            word_onboard.push_back(this->board2[u]);
            res.push_back(u);
            if(tree.find(combine(word_onboard))){
              return res;
            }
            visited[u]=1;
            S.push_back(u);
            vector<int> temp=FindNeighbous(u);
             for (std::vector<int>::iterator it = temp.begin() ; it != temp.end(); ++it){
                      if(!visited[*it])
                        S.push_back(*it);
              }
           }
    }
  }
        return v;
}






//test??
void BogglePlayer::getCustomBoard(string** &new_board, unsigned int *rows, unsigned int *cols) {
}

