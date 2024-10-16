#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "ArgumentManager.h"

using namespace std;

struct space{
    int value;
    bool isValid(){
        return (value == 0);
    }
    space(int val){value = val;}
    void mark(int val){value = val;}
};
class Board{
    private:
      int rowNum, colNum, holeNum, openSpace;
      space** holes;
      space*** board;
    public:
      Board(int, int);
      void draw(ostream*);
      space* markSpace(int, int, int);
      void makeHoles(int, ifstream*);
      bool validMove(int, int);
      bool knightTour(int, int, int, int);
};

Board::Board(int rNum, int cNum){
  rowNum = rNum;
  colNum = cNum;
  openSpace = rNum * colNum;
  board = new space**[rowNum];
  for(int row = 0; row < rowNum; row++){
    board[row] = new space*[colNum];
    for(int col = 0; col < colNum; col++){
      board[row][col] = new space(0);
    }
  }
}
space* Board::markSpace(int row, int col, int val){
  board[row][col]->mark(val);
  if(val == 1){
    return board[row][col];//leave return node open
  }
  if(val == 0){//backtrack
    openSpace++;
  }
  else{
    openSpace--;
  }
  return board[row][col];
}
void Board::makeHoles(int holN, ifstream* inCoord){
  holeNum = holN;
  holes = new space*[holeNum];
  int holRow, holCol;
  for(int hol = 0; hol < holeNum; hol++){
    *inCoord >> holRow >> holCol;
    holes[hol] = markSpace(holRow, holCol, -1);
  }
}
bool Board::validMove(int row, int col){
  return (row >= 0 && col >= 0 && row < rowNum && col < colNum && (board[row][col]->isValid() || (openSpace == 1 && board[row][col]->value == 1)));
}
struct coord{
  int col;
  int row;
  coord(int x, int y){col = x; row = y;}
};
coord knightAction[8] = {coord(2, -1), coord(1, -2), coord(-1, -2), coord(-2, -1), coord(-2, 1), coord(-1, 2), coord(1, 2), coord(2,1)};
bool Board::knightTour(int row, int col, int moveNum, int prevMove = -1){
  if(!validMove(row, col)){
    return 0;
  }
  //string debug; cout << "Current move:" << moveNum << endl;//debugO
  markSpace(row, col, moveNum);
  //draw(&cout);//debugO
  //cout << endl; cin >>debug;//debugO
  int redundMove = (4+prevMove)%8;
  for(int i = 0; i < 8; i++){
    if(prevMove != -1 && i == redundMove){//skip redundant moves
      continue;
    }
    knightTour(row + knightAction[i].row, col + knightAction[i].col, moveNum+1, i);
  }//if for loop ends, either it is done or it failed
  if(openSpace > 0){
    //cout << "backtrack" << endl;//debugO
    markSpace(row, col, 0);//backtrack
    return false;
  }
  return true;
}
void Board::draw(ostream* out){
  for(int row = 0; row < rowNum; row++){
    for(int col = 0; col < colNum; col++){
      *out << "+--";
    }
    *out << "+" << endl;
    for(int col = 0; col < colNum; col++){
      *out << "|";
      if(board[row][col]->value > 0){
        *out << setw(2) << board[row][col]->value;
      }
      else if(board[row][col]->value == -1){              
        *out << "XX";
      }
      else {
        *out << " ";
      }
    }
    *out << "|" << endl;
  }
  for(int col = 0; col < colNum; col++){
      *out << "+--";
    }
    *out << "+" << endl;
}

int main(int argc, char *argv[]) {
    ArgumentManager am(argc, argv);//begin debug
    string input = am.get("input");
    string output = am.get("output");
    ifstream fin(input);
    ofstream fout(output);//end debug
    /*string fileNum = "2";//begin debug
    ifstream fin("input" + fileNum + ".txt");
    int amount;
    if (!fin) {
        cerr << "Error opening file" << endl;
        return 1;
    }*///end debug
    ostream *out = &fout;
    int rowNum, colNum, startRow, startCol, holeNum, moveNum = 1;
    int* holes;
    bool validTour = 0;
    fin >> rowNum >> colNum >> startRow >> startCol >> holeNum;
    Board kBoard = Board(rowNum, colNum);
    kBoard.makeHoles(holeNum, &fin);
    validTour = kBoard.knightTour(startRow, startCol, moveNum);
    if(validTour){
      *out << "A closed tour exists!" << endl;
      kBoard.markSpace(startRow, startCol, 1);//set last node back to first value to complete cycle
      kBoard.draw(out);
    }else{
      *out << "A closed tour does not exist!" << endl;
    }
    return 0;
}
