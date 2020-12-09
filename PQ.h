#include <string>
#include "LL.h"

using namespace std;

class PQ{
    public:
        PQ();
        void queue(Game game);
        void dequeue(Game game);
    private:
        void heapify();
        Game gameQueue[8];
        int tSize; //totalSize
        int cSize; //currentSize
};