#ifndef datatype_h
#define datatype_h
#include <iostream>
#include <string>

using namespace std;

class UBikeSystem;

enum StatusType {Free, Rented};

enum ClassType { Electric, Lady, Road, Hybrid};

enum StationName
{
    Danshui, Hongshulin, Beitou,
    Shilin, Zhongshan, Xinpu,
    Ximen, Liuzhangli, Muzha,
    Guting, Gongguan, Jingmei
};


typedef char LicenseType[5];

struct BikeType
{
    LicenseType License;
    StatusType Status;
    int Mileage; /* most recently rented mileage */
    int Cursor; /* cursor to the entry in heap where there is a pointer to this node */
    StationName Station;
    ClassType Class;
};

typedef struct BikeType *BikePtr;

struct HeapType
{
    BikePtr Elem[256]; /* use array to implement heap, and each node in the heap is a pointer*/
    int Number;
};

struct StationType
{
    int Net; /* total income of station */
    int NetElectric;
    int NetLady;
    int NetRoad;
    int NetHybrid;
    int NumElectric; /* number of electric bikes */
    int NumLady; /* number of lady bikes */
    int NumRoad; /* number of road bikes */
    int NumHybrid; /* number of hybrid bikes */
    HeapType HRent;
    HeapType HElectric;
    HeapType HLady;
    HeapType HRoad;
    HeapType HHybrid;
};
struct HNodeType
{
    LicenseType License ;
    BikePtr Ptr; /* point to the node representing the bike */
    struct HNodeType *next_ptr; /*point to the next node in the chaining list*/
};
struct HTableType
{
    HNodeType table[256];
    /*since each entry in the hash table is a pointer, it will be initialized as NULL;*/
    int BikeNum; /* the number of bikes in the hash table */
};
#endif // datatype_h
