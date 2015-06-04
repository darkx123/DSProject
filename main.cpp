#include <iostream>
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

//int main(int argc, char *argv[])
//{
//    freopen("testCase03","r",stdin);
//    string a;
//    while(cin)
//    {
//        getline(cin, a);
//        cout << a <<endl;
//    }
//}

int main()
{
    UBikeSystem TaipeiUBike;
    string bc = "Electric", SN = "Zhongshan";
    string A0 = "00A00";
    string A1 = "00A01";
    string A2 = "00A02";
    string A3 = "00A03";
    string A4 = "00A04";
    string A5 = "00A05";
    string A = "Zhongshan";
    TaipeiUBike.NewBike("Electric", A0, 50, "Zhongshan");
    TaipeiUBike.NewBike("Electric", A1, 20, "Zhongshan");
    TaipeiUBike.NewBike("Electric", A2, 30, "Zhongshan");
    TaipeiUBike.NewBike("Electric", A3, 19, "Zhongshan");
    TaipeiUBike.NewBike("Electric", A4, 19, "Zhongshan");
    TaipeiUBike.NewBike("Electric", A5, 8, "Zhongshan");
    TaipeiUBike.RentBike("Zhongshan", "Electric");
    TaipeiUBike.ReturnBike("Zhongshan", A0, 70);
    TaipeiUBike.NetSearch("Zhongshan");
}
