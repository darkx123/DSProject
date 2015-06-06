#ifndef ubikesys_h
#define ubikesys_h
#include "datatype.h"
#include "station.h"
#include "StationMap.h"
#include "stringtoenum.h"
#include "LicenseTag.h"
#include <iostream>
#include <string>

using namespace std;

class UBikeSystem
{
public:
    UBikeSystem();
    void NewBike(string bikeclass, string license, int Mile, string S_Name);
    int JunkIt(string license);
    void RentBike(string s_name, string Class);
    void ReturnBike(string s_name, string license, int Mile);
    void TransBike(string s_name, string license);
    void Inquire(string license);
    void StationReport(string s_name);
    void UbikeReport();
    void NetSearch(string s_name);
    void inputMapData(string name1, string name2, int distance);
    void MinDis();
    void HashReport();
    int Charge(StationName returnStation, int Mile, BikePtr aBike);
private:
    HashingTable HT;
    Station Stations[12];
    StationMap S_Map;
    BikePtr bike;
};

UBikeSystem::UBikeSystem()
{

}

void UBikeSystem::NewBike(string bikeclass, string license, int Mile, string S_Name)
{
    bike = new BikeType;
    for(int i = 0; i < 5; i++)
    {
        bike->License[i] = license[i];
    }
    bike->Class = ClassStringToEnum(bikeclass);
    bike->Cursor = 0;
    bike->Mileage = Mile;
    bike->Station = Station_NameToEnum(S_Name);
    bike->Status = Free;

    HT.InsertNewBike(bike); // insert newbike into hashing table.
    Stations[bike->Station].InsertHeap(bike); // insert newbike into correspondeding type heap
    switch(bike->Class)
    {
        case 0 : Stations[bike->Station].m_Station.NumElectric++; break;
        case 1 : Stations[bike->Station].m_Station.NumLady++; break;
        case 2 : Stations[bike->Station].m_Station.NumRoad++; break;
        case 3 : Stations[bike->Station].m_Station.NumHybrid++; break;
    }
    cout << "New bike is received by Station " << S_Name << "." << endl;
}

int UBikeSystem::JunkIt(string license)
{
    LicenseType L;
    for(int i = 0; i < 5; i++)
    {
        L[i] = license[i];
    }
    bike = HT.SearhBike(L);
    cout << "Bike ";
    for(int i = 0; i < 5; i++)
    {
        cout << license[i];
    }
    if(!bike) //check existence of bike
    {
        cout <<" does not belong to our company." << endl;
        return 1;
    }

    if(bike->Status == 1)
    {
        cout <<" is now being rented." << endl;
        return 1;
    }

    Stations[bike->Station].DeleteHeap(bike);
    switch(bike->Class)
    {
        case 0 : Stations[bike->Station].m_Station.NumElectric--; break;
        case 1 : Stations[bike->Station].m_Station.NumLady--; break;
        case 2 : Stations[bike->Station].m_Station.NumRoad--; break;
        case 3 : Stations[bike->Station].m_Station.NumHybrid--; break;
    }
    HT.DeleteBikeFromHTable(bike);
    cout <<" is deleted from " << Station_EnumToName(bike->Station) << "." <<endl;
    delete bike;
    return 0;
}

void UBikeSystem::RentBike(string s_name, string Class)
{
    if(Stations[Station_NameToEnum(s_name)].RentBike(ClassStringToEnum(Class)) == 0)
        cout << "A bike is rented from " << s_name << "." <<endl;
    else
        cout << "No free bike is available." <<endl;
}

void UBikeSystem::ReturnBike(string s_name, string license, int Mile)
{
    LicenseType l;
    for(int i = 0; i < 5; i++)
    {
        l[i] = license[i];
    }
    bike = HT.SearhBike(l);
    int chargevalue = Charge(Station_NameToEnum(s_name), Mile - bike->Mileage, bike);
    bike->Mileage = Mile;
    Stations[bike->Station].DeleteHeap(bike);
    bike->Status = Free;
    Stations[bike->Station].InsertHeap(bike);
    Stations[bike->Station].m_Station.Net = Stations[bike->Station].m_Station.Net + chargevalue;
    switch(bike->Class)
    {
        case 0 : Stations[bike->Station].m_Station.NetElectric = Stations[bike->Station].m_Station.NetElectric + chargevalue; break;
        case 1 : Stations[bike->Station].m_Station.NetLady = Stations[bike->Station].m_Station.NetLady + chargevalue; break;
        case 2 : Stations[bike->Station].m_Station.NetRoad = Stations[bike->Station].m_Station.NetRoad + chargevalue; break;
        case 3 : Stations[bike->Station].m_Station.NetHybrid = Stations[bike->Station].m_Station.NetHybrid + chargevalue; break;
    }
    cout << "Rental charge for this bike is " << chargevalue << "." <<endl;
}

void UBikeSystem::TransBike(string s_name, string license)
{
    LicenseType l;
    cout << "Bike ";
    for(int i = 0; i < 5; i++)
    {
        l[i] = license[i];
        cout << l[i];
    }
    BikePtr aBike = HT.SearhBike(l);
    if(!aBike)
    {
        cout << " does not belong to our company." <<endl;
        return;
    }
    if(aBike->Status == Rented)
    {
        cout << " is now being rented." <<endl;
        return;
    }
    //Stations[aBike->Station].RemoveBike(aBike);
    Stations[aBike->Station].DeleteHeap(aBike);
    switch(aBike->Class)
    {
        case 0 : Stations[aBike->Station].m_Station.NumElectric--; break;
        case 1 : Stations[aBike->Station].m_Station.NumLady--; break;
        case 2 : Stations[aBike->Station].m_Station.NumRoad--; break;
        case 3 : Stations[aBike->Station].m_Station.NumHybrid--; break;
    }
    aBike->Station = Station_NameToEnum(s_name);
    Stations[aBike->Station].InsertHeap(aBike);
    switch(aBike->Class)
    {
        case 0 : Stations[aBike->Station].m_Station.NumElectric++; break;
        case 1 : Stations[aBike->Station].m_Station.NumLady++; break;
        case 2 : Stations[aBike->Station].m_Station.NumRoad++; break;
        case 3 : Stations[aBike->Station].m_Station.NumHybrid++; break;
    }
    cout << " is transferred to " << s_name << "." <<endl;
}

void UBikeSystem::Inquire(string license)
{
    LicenseType l;
    for(int i = 0; i < 5; i++)
    {
        l[i] = license[i];
    }
    BikePtr aBike = HT.SearhBike(l);
    if(!aBike)
    {
        cout << "Bike ";
        for(int i = 0; i < 5; i++)
        {
            cout << l[i];
        }
        cout << " does not belong to our company." <<endl;
        return;
    }
    cout << setw(15) << "License" << setw(15) << "Mileage" << setw(15) << "Class" << setw(15) << "Station" << endl;
    for(int i = 0; i < 4; i ++)
        cout << "=====" << "=====" << "=====";
    cout <<endl;
    cout << setw(15) << license;
    cout << setw(15) << aBike->Mileage;
    cout << setw(15) << ClassEumToString(aBike->Class);
    cout << setw(15) << Station_EnumToName(aBike->Station);
    cout << endl;

}

void UBikeSystem::StationReport(string s_name)
{
    cout <<setw(30) << s_name <<endl;
    /*================Free Bike Part==================================================================================*/
    cout <<setw(30) << "Free Bikes" <<endl;
    cout << setw(15) << "License" << setw(15) << "Mileage" << setw(15) << "Class" << setw(15) << "SubTotal" << endl;
    for(int i = 0; i < 4; i ++)
        cout << "=====" << "=====" << "=====";
    cout << endl;
    int subtotal = 0;
    for(int i = 0; i < 4; i++)
    {
        HeapType *aHeap = Stations[Station_NameToEnum(s_name)].GetHeapType(ClassType(i));
        subtotal = subtotal + aHeap->Number;
        for(int j = 1; j <= aHeap->Number; j++)
        {
             cout << setw(15) << LicenseToString(aHeap->Elem[j]->License);
             cout << setw(15) << aHeap->Elem[j]->Mileage;
             cout << setw(15) << ClassEumToString(aHeap->Elem[j]->Class);
             cout << endl;
        }
    }

    for(int i = 0; i < 4; i ++)
        cout << "=====" << "=====" << "=====";
    cout << endl;
    cout << setw(60) << subtotal;
    cout << endl <<endl;

/*================Rented Bike Part==================================================================================*/
    cout <<setw(30) << "Rented Bikes" <<endl;
    cout << setw(15) << "License" << setw(15) << "Mileage" << setw(15) << "Class" << setw(15) << "SubTotal" << endl;
    for(int i = 0; i < 4; i ++)
        cout << "=====" << "=====" << "=====";
    cout << endl;

    for(int j = 1; j <= Stations[Station_NameToEnum(s_name)].m_Station.HRent.Number; j++)
    {
         cout << setw(15) << LicenseToString(Stations[Station_NameToEnum(s_name)].m_Station.HRent.Elem[j]->License);
         cout << setw(15) << Stations[Station_NameToEnum(s_name)].m_Station.HRent.Elem[j]->Mileage;
         cout << setw(15) << ClassEumToString(Stations[Station_NameToEnum(s_name)].m_Station.HRent.Elem[j]->Class);
         cout << endl;
    }

    for(int i = 0; i < 4; i ++)
        cout << "=====" << "=====" << "=====";
    cout << endl;
    cout << setw(60) << Stations[Station_NameToEnum(s_name)].m_Station.HRent.Number;
    cout << endl <<endl;

/*================ Net Part ==================================================================================*/
    cout << setw(12) << "Net" << setw(12) << "Electric" << setw(12) << "Lady";
    cout << setw(12) << "Road" << setw(12) << "Hybrid" <<endl;
    for(int i = 0; i < 5; i ++)
        cout << "====" << "====" << "====";
    cout << endl;
    cout << setw(12) << Stations[Station_NameToEnum(s_name)].m_Station.Net;
    cout << setw(12) << Stations[Station_NameToEnum(s_name)].m_Station.NumElectric;
    cout << setw(12) << Stations[Station_NameToEnum(s_name)].m_Station.NumLady;
    cout << setw(12) << Stations[Station_NameToEnum(s_name)].m_Station.NumRoad;
    cout << setw(12) << Stations[Station_NameToEnum(s_name)].m_Station.NumHybrid;
    cout << endl;
    for(int i = 0; i < 5; i ++)
        cout << "====" << "====" << "====";
    cout << endl << endl;
}

void UBikeSystem::UbikeReport()
{
    cout << setw(30) << "Taipei U-bike" <<endl;
    cout << setw(30) << "Free Bikes" <<endl;
    cout << setw(12) << "License" << setw(12) << "Mileage";
    cout << setw(12) << "Class" << setw(12) << "Station" << setw(12) << "Total" <<endl;
    int FreeTotal = 0, RentedTotal = 0, Net = 0;
    int ElectricNumber = 0, LadyNumber = 0, RoadNumber = 0, HybridNumber = 0;
    for(int i = 0; i < 5; i++)
        cout << "====" << "====" << "====";
    cout << endl;
    for(int i = 0; i < 12; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            HeapType *aHeap = Stations[i].GetHeapType(ClassType(j));
            FreeTotal = FreeTotal + aHeap->Number;
            for(int k = 1; k <= aHeap->Number; k++)
                {
                     cout << setw(12) << LicenseToString(aHeap->Elem[k]->License);
                     cout << setw(12) << aHeap->Elem[k]->Mileage;
                     cout << setw(12) << ClassEumToString(aHeap->Elem[k]->Class);
                     cout << setw(12) << Station_EnumToName(StationName(i));
                     cout << endl;
                }
        }
        ElectricNumber = ElectricNumber + Stations[i].m_Station.NumElectric;
        LadyNumber = LadyNumber + Stations[i].m_Station.NumLady;
        RoadNumber = RoadNumber + Stations[i].m_Station.NumRoad;
        HybridNumber = HybridNumber + Stations[i].m_Station.NumHybrid;
        Net = Net + Stations[i].m_Station.Net;
    }
    for(int i = 0; i < 5; i ++)
        cout << "====" << "====" << "====";
    cout << endl;
    cout << setw(60) << FreeTotal << endl  << endl;

    cout << setw(30) << "Rented Bikes" <<endl;
    cout << setw(12) << "License" << setw(12) << "Mileage";
    cout << setw(12) << "Class" << setw(12) << "Station" << setw(12) << "Total" <<endl;
    for(int i = 0; i < 5; i ++)
        cout << "====" << "====" << "====";
    cout << endl;
    for(int i = 0; i < 12; i++)
    {
        for(int j = 1; j <= Stations[i].m_Station.HRent.Number; j++)
        {
             cout << setw(12) << LicenseToString(Stations[i].m_Station.HRent.Elem[j]->License);
             cout << setw(12) << Stations[i].m_Station.HRent.Elem[j]->Mileage;
             cout << setw(12) << ClassEumToString(Stations[i].m_Station.HRent.Elem[j]->Class);
             cout << setw(12) << Station_EnumToName(StationName(i));
             cout << endl;
        }
        RentedTotal = RentedTotal + Stations[i].m_Station.HRent.Number;
    }
    for(int i = 0; i < 5; i ++)
        cout << "====" << "====" << "====";
    cout << endl;
    cout << setw(60) << RentedTotal << endl  << endl;

    cout << setw(12) << "Net" << setw(12) << "Electric" << setw(12) << "Lady";
    cout << setw(12) << "Road" << setw(12) << "Hybrid" <<endl;
    for(int i = 0; i < 5; i ++)
        cout << "====" << "====" << "====";
    cout << endl;
    cout << setw(12) << Net;
    cout << setw(12) << ElectricNumber;
    cout << setw(12) << LadyNumber;
    cout << setw(12) << RoadNumber;
    cout << setw(12) << HybridNumber;
    cout << endl;
    for(int i = 0; i < 5; i ++)
        cout << "====" << "====" << "====";
    cout << endl << endl;
}

void UBikeSystem::NetSearch(string s_name)
{
    cout << s_name << endl;
    cout << "=====" << "=====" << "=====" << endl;
    cout << "Electric " << Stations[Station_NameToEnum(s_name)].m_Station.NetElectric << endl;
    cout << "Lady " << Stations[Station_NameToEnum(s_name)].m_Station.NetLady << endl;
    cout << "Road " << Stations[Station_NameToEnum(s_name)].m_Station.NetRoad << endl;
    cout << "Hybrid " << Stations[Station_NameToEnum(s_name)].m_Station.NetHybrid << endl;
    cout << "=====" << "=====" << "=====" << endl;
    cout << "Total "<< Stations[Station_NameToEnum(s_name)].m_Station.Net << endl <<endl;
}

int UBikeSystem::Charge(StationName returnStation, int Mile, BikePtr aBike)
{
    if(Mile <= S_Map.GetDistance(aBike->Station, returnStation))
    {
        int chargevalue[4] = {30, 25, 15, 20};

        return (chargevalue[aBike->Class] * Mile);
    }
    else
    {
        int chargevalue[4] = {40, 30, 20, 25};
        return (chargevalue[aBike->Class] * Mile);
    }
}

void UBikeSystem::inputMapData(string name1, string name2, int distance)
{
    S_Map.inputMapData(name1, name2, distance);
}

void UBikeSystem::MinDis()
{
    S_Map.MinDis();
}

void UBikeSystem::HashReport()
{
    HT.HashReport();
}

#endif // ubikesys_h
