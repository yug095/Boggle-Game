

#ifndef BOGGLEPLAYER_H
#define BOGGLEPLAYER_H
#include "baseboggleplayer.h"
#include "boggleutil.h"
#include "boggleutil.cpp"
#include <unordered_map>
#include <set>
#include <map>
using namespace std;

class BogglePlayer : public BaseBogglePlayer {
  public:
  
  std::unordered_map<std::string,std::vector<int> > board1; //use hashtable
  std::unordered_map<int,std::string> board2; //use hashtable
  

  
  TSTree dictionary;          //不确定要写指针还是直接这样

  int COLS;
  int ROWS;

  vector<int> FindNeighbous(int index);  //假设至少是2*2的，以后出问题了再改

  string combine(std::vector<string> word);


  std::map<std::vector<int>,std::string> Delete_Prefix(string& word, std::vector<int> v); 
  void buildLexicon(const set<string>& word_list);
  
  void setBoard(unsigned int rows, unsigned int cols, string** diceArray); 

  bool getAllValidWords(unsigned int minimum_word_length, set<string>* words);
  
  bool isInLexicon(const string& word_to_check); 

  vector<int> isOnBoard(const string& word);

  void getCustomBoard(string** &new_board, unsigned int *rows, unsigned int *cols);

  BogglePlayer() {
  }
  
  ~BogglePlayer() {
  }

  private:
};

#endif
