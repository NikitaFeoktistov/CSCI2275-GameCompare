#include <string>
#include <vector>

using namespace std;

struct Game{
    string name;
    int amount;
    vector<string> people;
};


struct LLNode{
    LLNode* next;
    LLNode* previous;
    Game game;
};


class LL{
    public:
        LL();
        void printLL(); //prints out the LL (completed)
        void addGame(string gName, string pName); //adds a person's name to a game, or creates a node for the game (completed)
        bool removeGame(string gName, string pName); //removes a person's name from a game (completed)
        void writeToFile(); //update the file with any added games
        void organizeByAmount(); //organizes the list by amount (completed)
        vector<string> getPersonGames(string name); //returns the games a person has (completed)
        int input(); //prints input options and allows the user to make a choice (completed)
        LLNode* search(string name); //finds the node of the game (completed)
        void printItem(string name); //prints out the people that play that game (completed)
        vector<string> findCommonGames(vector<string> names); //find the games these users have in common (users entered together, seperated by spaces) (completed)
        LLNode* root;
    private:
        void removeFromLL(string name); //deletes a game with no people
        void addToLL(Game g); //adds a game to the LL
        void swap(string name); //swaps a game with its neighbor in the LL
        bool containsPerson(string name, vector<string> personVector); //checks if a vector contains a name (could use this for findCommonGames)
        vector<string> findAllUsers();

};