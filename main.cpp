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
    ifstream inFile_map(argv[2]);
    ifstream inFile_transaction(argv[1]);
    char *output_filename = argv[3];


    string lineStr;
    string name1;
    string name2;
    int distance;
    UBikeSystem TaipeiUBike(output_filename);
    while (getline(inFile_map,lineStr))
    {
        istringstream iss(lineStr);
        iss >> name1 >> name2 >> distance;
        TaipeiUBike.inputMapData(name1, name2, distance);
    }
    inFile_map.close();
    TaipeiUBike.MinDis();

    //read a line until EOF
    while (getline(inFile_transaction,lineStr))
    {
        //make a input string stream
        istringstream iss(lineStr);
        //read from the iss until end of string
        string command;
        while( iss >> command )
        {
//            cout << command << " ";
            if (command == "NewBike")
            {
                string bike_class;
                string license;
                int mile;
                string station_name;
                iss >> bike_class >> license >> mile >> station_name;
                TaipeiUBike.NewBike(bike_class, license, mile, station_name);
            }
            else if (command == "HashReport")
            {
                TaipeiUBike.HashReport();
            }
            else if (command == "JunkIt")
            {
                string license;
                iss >> license;
                TaipeiUBike.JunkIt(license);
            }
            else if (command == "Rent")
            {
                string s_name;
                string bike_class;
                iss >> s_name >> bike_class;
                TaipeiUBike.RentBike(s_name, bike_class);
            }
            else if (command == "Returns")
            {
                string s_name;
                string license;
                int mile;
                iss >> s_name >> license >> mile;
                TaipeiUBike.ReturnBike(s_name, license, mile);
            }
            else if (command == "Trans")
            {
                string s_name;
                string license;
                iss >> s_name >> license;
                TaipeiUBike.TransBike(s_name, license);
            }
            else if (command == "StationReport")
            {
                string s_name;
                iss >> s_name;
                TaipeiUBike.StationReport(s_name);
            }
            else if (command == "NetSearch")
            {
                string s_name;
                iss >> s_name;
                TaipeiUBike.NetSearch(s_name);;
            }
            else if (command == "UbikeReport")
            {
                TaipeiUBike.UbikeReport();
            }
            else if (command == "Inquire")
            {
                string license;
                iss >> license;
                TaipeiUBike.Inquire(license);
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
