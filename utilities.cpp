#include "utilities.h"
#include <iostream>

using namespace std;

string toUpperCase(string toBeChanged){
    string uppercaseName;
    for(int i = 0; i < toBeChanged.length(); i++){
        uppercaseName += toupper(toBeChanged[i]);
    }
    return uppercaseName;
}
