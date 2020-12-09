#include <string>
#include "Q.h"
#include <iostream>

using namespace std;

Q::Q(){
    tSize = 6;
    cSize = 0;
}

void Q::queue(string game){
    if(tSize == cSize){
        cout<<"Queue is full"<<endl;
    } else {
        gameQueue[cSize] = game;
        cSize++;
    }
}

string Q::dequeue(){
    string game = gameQueue[0];
    if(cSize == 0){
        cout<<"Queue Empty"<<endl;
        return "";
    }
    for(int i = 1; i < cSize; i++){
        gameQueue[i-1] = gameQueue[i];
    }
    cSize--;
    return game;

}