#ifndef map_h
#define map_h
#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>
#include "datatype.h"

using namespace std;



class StationMap
{
public:
    StationMap();
    void inputMapData(string name1, string name2, int distance);
    void MinDis();
    int GetDistance(StationName name1, StationName name2);
private:
    int a[12][12];
};

StationMap::StationMap()
{
    for(int i = 0; i < 12; i++)
    {
        for(int j = 0; j < 12; j++)
        {
            if(i == j)
            {
                a[i][j] = 0;
            }
            else a[i][j] = 1000000;
        }
    }
}

void StationMap::inputMapData(string name1, string name2, int distance)
{
    int i = Station_NameToEnum(name1);
    int j = Station_NameToEnum(name2);
    a[i][j] = distance;
    a[j][i] = distance;
}

void StationMap::MinDis()
{
    for(int k = 0; k < 12; k++)
    {
        for(int i = 0; i < 12; i++)
        {
            for(int j = 0; j < 12; j++)
            {
                if((a[i][k]+a[k][j]) < a[i][j])
                    a[i][j] = a[i][k]+a[k][j];
            }
        }
    }
}

int StationMap::GetDistance(StationName name1, StationName name2)
{
    return a[name1][name2];
}

#endif // map_h
