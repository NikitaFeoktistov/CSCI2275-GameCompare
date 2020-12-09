#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "LL.h"
#include "utilities.h"
#include "Q.h"

using namespace std;

int main(int argc, char* argv[]){
    LL gameList;
    string filename = argv[1];
    
    ifstream peopleFile(filename);
    string line;
    string name;
    string game;
    while(getline(peopleFile,line)){ //populating the LL
        stringstream personStream(line);
        getline(personStream,name,',');
        LLNode* newGame = new LLNode;

        while(getline(personStream,game,',')){
            stringstream formatString(game);
            string myStream;
            game = "";
            while(formatString>>myStream){
                if(myStream != ""){
                    game+=myStream + " ";
                }
            }
            game = game.substr(0,game.length()-1);
            gameList.addGame(game, name);
        }
    }
    cout<<endl;

    
    int choice;
    int times = 0; //for keeping track of the position in the queue
    Q gameQ;
    while(true){
        choice = gameList.input();

        switch(choice){
            case 0:{ //Get a user's games
                string getName;
                cout<<"Enter user's name: ";
                cin>>getName;
                cin.clear();
                cin.ignore();
                getName = toUpperCase(getName);
                vector<string> userGames = gameList.getPersonGames(getName);
                cout<<getName<<" has:"<<endl;
                for(int i = 0; i < userGames.size(); i++){
                    cout<<userGames[i]<<", ";
                }
                cout<<endl;
                break;
            }
            case 1:{ //Add a game to a user
                string getName;
                string getGame;
                cout<<"Enter user's name: ";
                cin>>getName;
                cin.clear();
                cin.ignore();
                cout<<"Enter game: ";
                cin>>getGame;
                cin.clear();
                cin.ignore();
                getName = toUpperCase(getName);
                getGame = toUpperCase(getGame);
                gameList.addGame(getGame, getName);
                break;
            }
            case 2:{ //Remove a game from a user
                string getName;
                string getGame;
                cout<<"Enter user's name: ";
                cin>>getName;
                cin.clear();
                cin.ignore();
                cout<<"Enter game: ";
                cin>>getGame;
                cin.clear();
                cin.ignore();
                getName = toUpperCase(getName);
                getGame = toUpperCase(getGame);
                gameList.removeGame(getGame, getName);
                break;
            }
            case 3:{ //Return users that play a game
                string getGame;
                cout<<"Enter game: ";
                cin>>getGame;
                cin.clear();
                cin.ignore();
                getGame = toUpperCase(getGame);
                gameList.printItem(getGame);
                break;
            }
            case 4:{ //Find common games
                string getName;
                vector<string> names;
                cout<<"Enter user name (type done to finish): ";
                cin>>getName;
                cin.clear();
                cin.ignore();
                while(getName != "done"){
                    names.push_back(getName);
                    cout<<"Enter user name (type done to finish): ";
                    cin>>getName;
                    cin.clear();
                    cin.ignore();
                }
                for(int i = 0; i < names.size(); i++){
                    names[i] = toUpperCase(names[i]);
                }
                vector<string> commonGames = gameList.findCommonGames(names);

                cout<<"The games ";
                for(int i = 0; i < names.size(); i++){
                    cout<<names[i]<<" ";
                }
                cout<<"have in common are: ";
                if(commonGames.size() == 0){
                    cout<<"NONE";
                } else {
                    for(int i = 0; i < commonGames.size(); i++){
                        cout<<commonGames[i]<<" ";
                    }
                }
                cout<<endl;
                break;
            }
            case 5:{ //Print the LL
                gameList.printLL();
                break;
            }
            case 6:{ //Create a priority queue
                gameList.organizeByAmount();
                break;
            }
            case 7:{ //Queue
                LLNode* temp = gameList.root;
                for(int i  = 0; i < times; i++){
                    temp = temp->next;
                }
                gameQ.queue(temp->game.name);
                break;
            }
            case 8:{ //Dequeue
                string returned = gameQ.dequeue();
                if(returned != ""){
                    gameList.printItem(returned);
                }
                break;
            }
            case 9:{ //Quit
                gameList.writeToFile();
                return 1;
            }
        }
        cout<<endl;
    }
    




}
