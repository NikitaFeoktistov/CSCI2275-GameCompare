#include <string>

using namespace std;

class Q{
    public:
        Q();
        void queue(string game);
        string dequeue();
    private:
        string gameQueue[6];
        int tSize; //totalSize
        int cSize; //currentSize
};