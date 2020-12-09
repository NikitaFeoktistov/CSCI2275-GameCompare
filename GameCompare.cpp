#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "LL.h"
#include "utilities.h"
#include "PQ.h"

using namespace std;

int main(int argc, char* argv[]){
    LL gameList;
    string filename = argv[1];
    
    ifstream peopleFile(filename);
    string line;
    string name;
    string game;
    while(getline(peopleFile,line)){
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

    // string menu = "==========Menu==========\n"
    //               "1. Get a user's games\n"
    //               "2. Add a game to a user\n"
    //               "3. Remove a game from a user\n"
    //               "4. Return users that play a game\n"
    //               "5. Find similar games among users\n"
    //               "6. Create priority queue\n"
    //               "7. Quit\n";

    // cout<<menu<<endl;
    // cout<<"Select an option: ";
    int choice;

    while(true){
        choice = gameList.input();

        switch(choice){
            case 1:{
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
            case 2:{
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
            case 3:{
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
            case 4:{
                string getGame;
                cout<<"Enter game: ";
                cin>>getGame;
                cin.clear();
                cin.ignore();
                getGame = toUpperCase(getGame);
                gameList.printItem(getGame);
                break;
            }
            case 5:{
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
            case 6:{
                gameList.printLL();
                break;
            }
            case 7:{
                gameList.organizeByAmount();
                PQ gamePQ;
                break;
            }
            case 8:{
                gameList.writeToFile();
                return 1;
            }
        }
        cout<<endl;
    }
    




}
