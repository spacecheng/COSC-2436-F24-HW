#include "ArgumentManager.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
int main(int argc, char *argv[]) {
    ArgumentManager am(argc, argv);
    string input = am.get("input");
    string output = am.get("output");
    ifstream fin(input);
    ofstream fout(output);
    /*string fileNum = "1";
    ifstream fin("input" + fileNum + ".txt");*/
    string card;
    int suit, denom;
    int cardArr[15][5];
    for(int i = 0; i < 15; i++){
        for(int j = 0; j < 5; j++){
            cardArr[i][j] = 0;
        }
    }
    while(fin >> card){
        if(card.back() == ','){
            card.pop_back();
        }
        switch(card.back()){
            case 'A':
                suit = 1;
                break;
            case 'E':
                suit = 2;
                break;
            case 'F':
                suit = 3;
                break;
            case 'W':
                suit = 4;
                break;
            case 'H':
                suit = 5;
                break;
        }
        card.pop_back();
        if(isdigit(card[0])){
            denom = stoi(card);
        }
        else{
            switch(card[0]){
                case 'P':
                    denom = 1;
                    break;
                case 'R':
                    denom = 11;
                    break;
                case 'N':
                    denom = 12;
                    break;
                case 'B':
                    denom = 13;
                    break;
                case 'Q':
                    denom = 14;
                    break;
                case 'K':
                    denom = 15;
                    break;
            }
        }
    cardArr[denom-1][suit-1]++;//-1 to make it fit in the array
    }
    for(int i = 0; i < 15; i++){
        for(int j = 0; j < 4; j++){
            fout << cardArr[i][j] << " ";//for spacing
        }
        fout << cardArr[i][4] << endl;
    }
}