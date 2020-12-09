#include <string>
#include "PQ.h"
#include <iostream>

using namespace std;

PQ::PQ(){
    cSize = 1;
    tSize = 8;
}

void PQ::queue(Game game){
    if(cSize = tSize){
        cout<<"PQ is full"<<endl;
    } else {
        gameQueue[cSize] = game;
        cSize++;
    }
    heapify();
}

void PQ::heapify(){


}