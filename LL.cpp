#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "LL.h"

using namespace std;

LL::LL(){
    root = nullptr;
}

void LL::addGame(string gName, string pName){
    LLNode* foundGame = search(gName);
    if(foundGame != NULL){
        foundGame->game.amount++;
        foundGame->game.people.push_back(pName);
        return;
    }
    Game newGame;
    newGame.amount = 1;
    newGame.name = gName;
    newGame.people.push_back(pName);
    addToLL(newGame);
    return;
}

LLNode* LL::search(string name){
    LLNode* temp;
    temp = root;
    while(temp != nullptr){
        if(temp->game.name == name){
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void LL::addToLL(Game game){
    LLNode* newNode = new LLNode;
    newNode->game = game;
    if(root == NULL){ //first game to be added
        root = newNode;
        root->next = nullptr;
        root->previous = nullptr;
    } else { //add to the end of the LL
        LLNode* temp = root;
        while(temp->next != nullptr){
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->previous = temp;
        newNode->next = nullptr;
    }
}

void LL::printLL(){
    LLNode* temp = root;
    while(temp != NULL){
        printItem(temp->game.name);
        cout<<"===================="<<endl;
        temp=temp->next;
    }
}

void LL::printItem(string name){
    LLNode* thisNode = search(name);
    if(thisNode == NULL){
        cout<<"Game not found"<<endl;
        return;
    }
    cout<<"Game: "<<thisNode->game.name<<endl;
    cout<<"Amount: "<<thisNode->game.amount<<endl;
    cout<<"People: ";
    for(int i = 0; i < thisNode->game.people.size(); i++){
        cout<<thisNode->game.people[i]<<", ";
    }
    cout<<endl;
}

vector<string> LL::getPersonGames(string name){
    vector<string> personGames;
    LLNode* temp = root;
    while(temp != NULL){
        vector<string> personVector = temp->game.people;
        if(containsPerson(name, personVector)){
            personGames.push_back(temp->game.name);
        }
        temp=temp->next;
    }
    return personGames;

}

bool LL::containsPerson(string name, vector<string> personVector){
    for(int i = 0; i < personVector.size(); i++){
        if(personVector[i] == name){
            return true;
        }
    }
    return false;
}

int LL::input(){
    string menu = "==========Menu==========\n"
                  "1. Get a user's games\n"
                  "2. Add a game to a user\n"
                  "3. Remove a game from a user\n"
                  "4. Return users that play a game\n"
                  "5. Find similar games among users\n"
                  "6. Print the LL\n"
                  "7. Create priority queue\n"
                  "8. Quit\n";

    cout<<menu<<endl;
    cout<<"Select an option: ";
    int choice;
    cin>>choice;
    cin.clear();
    cin.ignore();
    return choice;
}

bool LL::removeGame(string gName, string pName){
    LLNode* foundGame = search(gName);
    if(foundGame != NULL){
        vector<string> peopleVector = foundGame->game.people;
        for(int i = 0; i < peopleVector.size(); i++){
            if(peopleVector[i] == pName){
                peopleVector.erase(peopleVector.begin()+i);
                foundGame->game.people = peopleVector;
                foundGame->game.amount--;
                if(foundGame->game.amount == 0){
                    removeFromLL(gName);
                }
                return true;
            }
        }
        return false;
    }
    return false;

}

void LL::removeFromLL(string name){
    LLNode* foundGame = search(name);
    if(foundGame->previous == nullptr){
        foundGame->next->previous = nullptr;
    } else if (foundGame->next == nullptr){
        foundGame->previous->next = nullptr;
    } else {
        foundGame->previous->next = foundGame->next;
        foundGame->next->previous = foundGame->previous;
    }
    delete foundGame;
}

void LL::organizeByAmount(){
    LLNode* temp = root;
    int changes = 0;
    while(temp->next != nullptr){
        if(temp->game.amount < temp->next->game.amount){
            swap(temp->game.name);
            changes++;

        } else {
            temp = temp->next;
        }
        if(changes > 0){
            organizeByAmount();
        }
    }

}

void LL::swap(string name){
    LLNode* foundGame = search(name);
    LLNode* temp = foundGame->next;
    if(foundGame == root){ //items being swapped are the first two
        temp->next->previous = foundGame;
        temp->previous = nullptr;
        foundGame->next = temp->next;
        temp->next = foundGame;
        foundGame->previous = temp;
    } else if(temp->next == nullptr){
        foundGame->previous->next = temp;
        temp->previous = foundGame->previous;
        foundGame->next = nullptr;
        temp->next = foundGame;
        foundGame->previous = temp;
    } else {
        foundGame->previous->next = temp;
        temp->next->previous = foundGame;
        temp->previous = foundGame->previous;
        foundGame->next = temp->next;
        temp->next = foundGame;
        foundGame->previous = temp; 
    }
}

vector<string> LL::findCommonGames(vector<string> names){
    string name;
    vector<string> gameVector;
    vector<string> playerVector;
    gameVector = getPersonGames(names[0]);
    for(int i = 1; i < names.size(); i++){
        playerVector = getPersonGames(names[i]);
        for(int x = 0; x < gameVector.size(); x++){
            bool found = false;
            for(int y = 0; y < playerVector.size(); y++){
                cout<<gameVector[x]<<" "<<playerVector[y]<<endl;
                if(gameVector[x] == playerVector[y]){
                    found = true;
                }
            }
            if(!found){
                gameVector.erase(gameVector.begin()+x);
                x--;
            }
        }
    }
    return gameVector;
}

void LL::writeToFile(){
    remove("people.txt");
    ofstream updatedFile("people.txt");
    vector<string> users = findAllUsers();
    for(int i = 0; i < users.size(); i++){
        updatedFile<<users[i];
        vector<string> userGames = getPersonGames(users[i]);
        for(int x = 0; x < userGames.size(); x++){
            updatedFile<<","<<userGames[x];
        }
        updatedFile<<endl;
    }
}

vector<string> LL::findAllUsers(){
    LLNode* temp = root;
    vector<string> allUsers;
    while(temp != nullptr){
        for(int i = 0; i < temp->game.people.size(); i++){
            bool found = false;
            for(int x = 0; x < allUsers.size(); x++){
                if(allUsers[x] == temp->game.people[i]){
                    found = true;
                }
            }
            if(!found){
                allUsers.push_back(temp->game.people[i]);
            }
        }
        temp = temp->next;
    }
    return allUsers;
}