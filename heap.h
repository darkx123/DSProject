#ifndef heap_h
#define heap_h
#include <iostream>
#include <string>
#include <sstream>
#include "datatype.h"

using namespace std;

class heap
{
friend class Station;
//friend class BikeType;
public:
    heap();
   ~heap();
    void InsertHeap(BikePtr aBike);
    void DeleteHeap(BikePtr aBike);

private:
    HeapType Bikes;
};

heap::heap()
{
    Bikes.Number = 0;
}

void heap::InsertHeap(BikePtr aBike)
{
    int currentNode = ++Bikes.Number;
    while(currentNode != 1 && Bikes.Elem[currentNode/2]->Mileage < aBike->Mileage)
    {
        Bikes.Elem[currentNode] = Bikes.Elem[currentNode/2];
        currentNode = currentNode / 2;
    }
    Bikes.Elem[currentNode] = aBike;
    aBike->Cursor = currentNode;
}

void heap::DeleteHeap(BikePtr aBike)
{
    int currentNode = aBike->Cursor;
    int child = 2*currentNode;
    while(child <= Bikes.Number)
    {
        if(child < Bikes.Number && Bikes.Elem[child]->Mileage < Bikes.Elem[child + 1]->Mileage)
        {
            child++;
        }
        if(Bikes.Elem[Bikes.Number -1 ]->Mileage > Bikes.Elem[child]->Mileage)
        {
            break;
        }
        Bikes.Elem[currentNode] = Bikes.Elem[child];
        currentNode = child;
        child = child / 2;
    }
    Bikes.Elem[currentNode] = Bikes.Elem[Bikes.Number -1 ];
    Bikes.Number  = Bikes.Number - 1;
}
#endif // heap_h
