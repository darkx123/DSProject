#ifndef station_h
#define station_h
#include <iostream>
#include <string>
#include <iomanip>
#include "datatype.h"

class Station
{
friend class UBikeSystem;
public:
    Station();
   //~Station();
    void InsertHeap(BikePtr aBike);
    void DeleteHeap(BikePtr aBike);
    HeapType *GetHeapType(ClassType Class);
    int RentBike(ClassType Class);
private:
    StationType m_Station;
//    int Net; /* total income of station */
//    int NetElectric;
//    int NetLady;
//    int NetRoad;
//    int NetHybrid;
//    int NumElectric; /* number of electric bikes */
//    int NumLady; /* number of lady bikes */
//    int NumRoad; /* number of road bikes */
//    int NumHybrid; /* number of hybrid bikes */
//    HeapType HRent;
//    HeapType HElectric;
//    HeapType HLady;
//    HeapType HRoad;
//    HeapType HHybrid;
};

Station::Station()
{
    m_Station.Net = 0;
    m_Station.NetElectric = 0;
    m_Station.NetHybrid = 0;
    m_Station.NetLady = 0;
    m_Station.NetRoad = 0;
    m_Station.NumElectric = 0;
    m_Station.NumHybrid = 0;
    m_Station.NumLady = 0;
    m_Station.NumRoad = 0;
    m_Station.HElectric.Number = 0;
    m_Station.HHybrid.Number = 0;
    m_Station.HLady.Number = 0;
    m_Station.HRent.Number = 0;
    m_Station.HRoad.Number = 0;
}

void Station::InsertHeap(BikePtr aBike)  //If a bike is rented, insert it into HRent.
{                                        //Otherwise, insert it into corresponding Heap(elec, lady, road or hybrid).
    HeapType *aHeap;
    if(aBike->Status == 0)
    {
        aHeap = GetHeapType(aBike->Class);
    }
    else
    {
        aHeap = &m_Station.HRent;
    }
    int currentNode = ++aHeap->Number;
    while(currentNode != 1 && aHeap->Elem[currentNode/2]->Mileage < aBike->Mileage)
    {
        aHeap->Elem[currentNode/2]->Cursor = currentNode;
        aHeap->Elem[currentNode] = aHeap->Elem[currentNode/2];
        currentNode = currentNode / 2;
    }
    aHeap->Elem[currentNode] = aBike;
    aBike->Cursor = currentNode;
}

void Station::DeleteHeap(BikePtr aBike) //If a bike is rented, delete it from HRent.
{                                       //Otherwise, delete it from corresponding Heap(elec, lady, road or hybrid).
    HeapType *aHeap;
    if(aBike->Status == 0)
    {
        aHeap = GetHeapType(aBike->Class);
    }
    else
    {
        aHeap = &m_Station.HRent;
    }
    BikePtr lastNode = aHeap->Elem[aHeap->Number];
    int currentNode = aBike->Cursor;
    if (currentNode == 0) return;
    aBike->Cursor = 0;
    aHeap->Number  = aHeap->Number - 1;
    int child = 2*currentNode;

    if(currentNode != 1 && aHeap->Elem[currentNode/2]->Mileage == lastNode->Mileage)
    {
        aHeap->Elem[currentNode] = lastNode;
        lastNode->Cursor = currentNode;
        return;
    }
    else if (currentNode != 1 && aHeap->Elem[currentNode/2]->Mileage < lastNode->Mileage)
    {
        while(currentNode != 1 && aHeap->Elem[currentNode/2]->Mileage < lastNode->Mileage)
        {
            aHeap->Elem[currentNode/2]->Cursor = currentNode;
            aHeap->Elem[currentNode] = aHeap->Elem[currentNode/2];
            currentNode = currentNode / 2;
        }
        lastNode->Cursor = currentNode;
        aHeap->Elem[currentNode] = lastNode;
        return;
    }
    else
    {
        while(child <= aHeap->Number)
        {
            if(child < aHeap->Number && aHeap->Elem[child]->Mileage < aHeap->Elem[child + 1]->Mileage)
            {
                child++;
            }
            if(lastNode->Mileage >= aHeap->Elem[child]->Mileage)
            {
                break;
            }
            aHeap->Elem[child]->Cursor = currentNode;
            aHeap->Elem[currentNode] = aHeap->Elem[child];
            currentNode = child;
            child = child * 2;
        }
        aHeap->Elem[currentNode] = lastNode;
        lastNode->Cursor = currentNode;
    }
}

HeapType *Station::GetHeapType(ClassType Class)
{
    HeapType *temp;
    switch(Class)
    {
        case 0 : temp = &m_Station.HElectric; break;
        case 1 : temp = &m_Station.HLady; break;
        case 2 : temp = &m_Station.HRoad; break;
        case 3 : temp = &m_Station.HHybrid; break;
    }
    return temp;
}

int Station::RentBike(ClassType Class)
{
    HeapType *aHeap = GetHeapType(Class);
    if(aHeap->Number == 0)
    {
        return 1;
    }
    BikePtr tempBikePtr = aHeap->Elem[1];
    DeleteHeap(tempBikePtr);
    tempBikePtr->Status = Rented;
    InsertHeap(tempBikePtr);
    return 0;
}



#endif // station_h
