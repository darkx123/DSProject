#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <sstream>
#include <iomanip>
#include "datatype.h"
#include "stringtoenum.h"
#include "heap.h"
#include "station.h"
#include "StationMap.h"
#include "LicenseTag.h"
#include "UBikeSys.h"

using namespace std;


int main(int argc, char *argv[])
{
    //read a line until EOF
    UBikeSystem TaipeiUBike;
    ifstream inFile_map;
    ifstream inFile_transaction;
    inFile_map.open(argv[2]);
    inFile_transaction.open(argv[1]);

    string lineStr;
    string name1;
    string name2;
    int distance;
    while (getline(inFile_map,lineStr))
    {
        istringstream iss(lineStr);
        iss >> name1 >> name2 >> distance;
        TaipeiUBike.inputMapData(name1, name2, distance);
    }
    inFile_map.close();

    //read a line until EOF
    while (getline(inFile_transaction,lineStr))
    {
        //make a input string stream
        istringstream iss(lineStr);
        //read from the iss until end of string
        string command;
        while( iss >> command )
        {
            cout <<command << " ";
            if (command == "NewBike")
            {
                string bike_class;
                string license;
                int mile;
                string station_Name;
                iss >> bike_class >> license >> mile >> station_Name;
                TaipeiUBike.NewBike(bike_class, license, mile, station_Name);
            }
            else if (command == "HashReport")
            {
                TaipeiUBike.HashReport();
            }
            else if (command == "JunkIt")
            {

            }
            else if (command == "Rent")
            {

            }
            else if (command == "Returns")
            {

            }
            else if (command == "Trans")
            {

            }
            else if (command == "StationReport")
            {

            }
            else if (command == "NetSearch")
            {

            }
            else if (command == "UbikeReport")
            {

            }
            else
            {

            }
        }
    }
    inFile_transaction.close();

    return 0;
}

//
//
//int main()
//{
//    UBikeSystem TaipeiUBike;
//    string A0 = "00A00";
//    string A1 = "00A01";
//    string A2 = "00A02";
//    string A3 = "00A03";
//    string A4 = "00A04";
//    string A5 = "00A05";
//    TaipeiUBike.NewBike("Electric", A0, 50, "Zhongshan");
//    TaipeiUBike.NewBike("Electric", A1, 20, "Zhongshan");
//    TaipeiUBike.NewBike("Electric", A2, 30, "Zhongshan");
//    TaipeiUBike.NewBike("Electric", A3, 19, "Zhongshan");
//    TaipeiUBike.NewBike("Electric", A4, 19, "Zhongshan");
//    TaipeiUBike.NewBike("Electric", A5, 8, "Zhongshan");
//    TaipeiUBike.RentBike("Zhongshan", "Electric");
//    TaipeiUBike.ReturnBike("Zhongshan", A0, 70);
//    TaipeiUBike.NetSearch("Zhongshan");
//}
