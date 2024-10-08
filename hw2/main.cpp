#include <iostream>
#include <fstream>
#include <string>
#include "ArgumentManager.h"
using namespace std;

int Split(long long int* list, int front, int back){
    int pivotInd = front + (back-front)/2;
    long long int pivot = list[pivotInd];
    //back--;
    bool done = 0;
    while(!done){
        while(list[front] < pivot){
            front++;
        }
        while(pivot < list[back]){
            back--;
        }
        if(front >= back){
            done = 1;
        }
        else{
            swap(list[front], list[back]);
            front++;
            back--;
        }
        //cout << "front: " << front << " back: " << back << endl;
    }
return back;
}

long long int QuickSelect(long long int* arr, int front, int back, int ind){
    if(front >= back){
        return arr[front];
    }
    int newBack = Split(arr, front, back);
    if(ind > newBack){
        return QuickSelect(arr, newBack + 1, back, ind);
    }
    return QuickSelect(arr, front, newBack, ind);
}

int main(int argc, char *argv[]) {
    ArgumentManager am(argc, argv);//begin debug
    string input = am.get("input");
    string output = am.get("output");
    ifstream fin(input);
    ofstream fout(output);//end debug
    /*string fileNum = "3";//begin debug
    ifstream fin("input" + fileNum + ".txt");*///end debug
    int amount;
    /*if (!fin) {
        cerr << "Error opening file" << endl;
        return 1;
    }*/
    fin >> amount;
    //cout << amount << endl;
    long long int *arr = new long long int[amount];
    for(int i = 0; i < amount; i++){
        fin >> arr[i];
        //cout << "num: " << arr[i] << endl;
    }

    int q1Ind = (amount-1)/4;
    int q2Ind = (amount-1)/2;
    int q3Ind = (3*amount)/4;
    ostream *out = &fout;
    //cout << "start" << endl;
    //*out << QuickSelect(arr, 0, amount-1, q1Ind-1) << endl;
    *out << QuickSelect(arr, 0, amount-1, q1Ind) << endl;
    //*out << QuickSelect(arr, 0, amount-1, q1Ind+1) << endl;
    //*out << QuickSelect(arr, 0, amount-1, q2Ind-1) << endl;
    *out << QuickSelect(arr, 0, amount-1, q2Ind) << endl;
    //*out << QuickSelect(arr, 0, amount-1, q2Ind+1) << endl;
    //*out << QuickSelect(arr, 0, amount-1, q3Ind-1) << endl;
    *out << QuickSelect(arr, 0, amount-1, q3Ind) << endl;
    //*out << QuickSelect(arr, 0, amount-1, q3Ind+1) << endl;
    /*for(int i = 0; i < amount; i++){
        cout << QuickSelect(arr, 0, amount-1, i) << endl;
    }*/
   delete [] arr;
}