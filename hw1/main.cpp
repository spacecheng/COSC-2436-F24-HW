#include <string>
#include <iostream>
#include <fstream>
#include "ArgumentManager.h"
using namespace std;
struct person{
    string name = "";
    int id = 0;
    bool head;
    person* next = nullptr;
    person(string n, bool h = 0){name = n; head = h;}
};
class meetList{
    public:
        void meet(string value);
        bool checkMeet(string value);
        meetList(string name){self = new person(name, 1); lastMet = self; size = 1;}
        person* getSelf(){return self;}
        person *lastMet = nullptr;
        int size = 0;
    private:
        person *self = nullptr;
};
void meetList::meet(string value){
    person* temp = new person(value);
    size++;
    if(lastMet == nullptr){//whole thing is empty
        self = temp;
        lastMet = temp;
        return;
    }
    lastMet->next = temp;
    lastMet = temp;
}
bool meetList::checkMeet(string value){
    for(person* curr = self; curr != nullptr; curr = curr->next){
        if(curr->name == value){
            return 1;
        }
    }
    return 0;
}
int main(int argc, char *argv[]) {
    ArgumentManager am(argc, argv);
    string input = am.get("input");
    string output = am.get("output");
    ifstream fin(input);
    ofstream fout(output);
    /*string fileNum = "3";
    ifstream fin("input" + fileNum + ".txt");*/
    string personInput[2];
    int peopleNum;
    meetList* first = nullptr;
    fin >> peopleNum;
    meetList* meetMatrix[peopleNum];
    int inPeopleNum = 0;
    bool foundValue[2] = {0, 0};
    meetList* selected[2];
    while(first == nullptr && fin >> personInput[0] >> personInput[1]){
        if(inPeopleNum == 0){
            meetMatrix[inPeopleNum] = new meetList(personInput[0]);
            selected[0] = meetMatrix[inPeopleNum];
            inPeopleNum++;
            meetMatrix[inPeopleNum] = new meetList(personInput[1]);
            selected[1] = meetMatrix[inPeopleNum];
            inPeopleNum++;
        }
        else{
            foundValue[0] = 0;
            foundValue[1] = 0;
            for(int i = 0; i < inPeopleNum; i++){
                if(meetMatrix[i]->getSelf()->name == personInput[0]){
                    selected[0] = meetMatrix[i];
                    foundValue[0] = 1;
                }
                if(meetMatrix[i]->getSelf()->name == personInput[1]){
                    selected[1] = meetMatrix[i];
                    foundValue[1] = 1;
                }
            }
            if(!foundValue[0]){
                meetMatrix[inPeopleNum] = new meetList(personInput[0]);
                selected[0] = meetMatrix[inPeopleNum];
                inPeopleNum++;
            }
            if(!foundValue[1]){
                meetMatrix[inPeopleNum] = new meetList(personInput[1]);
                selected[1] = meetMatrix[inPeopleNum];
                inPeopleNum++;
            }
        }
        if(!(selected[0]->checkMeet(personInput[1]))){
            selected[0]->meet(personInput[1]);
            if(selected[0]->size == peopleNum){
                first = selected[0];
            }

        }
        if(!(selected[1]->checkMeet(personInput[0]))){
            selected[1]->meet(personInput[0]);
            if(selected[1]->size == peopleNum){
                first = selected[1];
            }
        }
    }
    if(first != nullptr){
        fout << "First: " << first->getSelf()->name << endl;;
        for(person* curr = first->getSelf()->next; curr != nullptr; curr = curr->next){
            if(curr != first->getSelf()->next){
                fout << ", ";
            }
            fout << curr->name;
        }
        fout << endl;
    }
    /*for(int i = 0; i < peopleNum; i++){
        for(person* curr = meetMatrix[i]->getSelf(); curr != nullptr; curr = curr->next){
            cout << curr->name << " ";
        }
        cout << endl;
    }*/
    return 0;
}