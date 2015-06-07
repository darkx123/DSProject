#ifndef stringtoenum_cpp
#define stringtoenum_cpp
#include <string>
#include <map>
#include "datatype.h"
using namespace std;
//
//enum StatusType {Free, Rented};
//
//enum ClassType { Electric, Lady, Road, Hybrid};


StatusType StatusStringToEnum(string name)
{
    map <string, StatusType> StringToEnum;
    StringToEnum["Free"] = StatusType(0);
    StringToEnum["Rented"] = StatusType(1);

    return (StringToEnum[name]);
}

ClassType ClassStringToEnum(string name)
{
    map <string, ClassType> StringToEnum;
    StringToEnum["Electric"] = ClassType(0);
    StringToEnum["Lady"] = ClassType(1);
    StringToEnum["Road"] = ClassType(2);
    StringToEnum["Hybrid"] = ClassType(3);

    return (StringToEnum[name]);
}

string ClassEumToString(ClassType Class)
{
    map <ClassType, string> EumToString;
    EumToString[ClassType(0)] = "Electric";
    EumToString[ClassType(1)] = "Lady";
    EumToString[ClassType(2)] = "Road";
    EumToString[ClassType(3)] = "Hybrid";

    return (EumToString[Class]);
}

StationName Station_NameToEnum(string name)
{
    map <string, StationName> NameToEnum;
    NameToEnum["Danshui"] = StationName(0);
    NameToEnum["Hongshulin"] = StationName(1);
    NameToEnum["Beitou"] = StationName(2);
    NameToEnum["Shilin"] = StationName(3);
    NameToEnum["Zhongshan"] = StationName(4);
    NameToEnum["Xinpu"] = StationName(5);
    NameToEnum["Ximen"] = StationName(6);
    NameToEnum["Liuzhangli"] = StationName(7);
    NameToEnum["Muzha"] = StationName(8);
    NameToEnum["Guting"] = StationName(9);
    NameToEnum["Gongguan"] = StationName(10);
    NameToEnum["Jingmei"] = StationName(11);

    return (NameToEnum[name]);
}

string Station_EnumToName(StationName name)
{
    map <StationName, string> EnumToString;
    EnumToString[StationName(0)] = "Danshui";
    EnumToString[StationName(1)] = "Hongshulin";
    EnumToString[StationName(2)] = "Beitou";
    EnumToString[StationName(3)] = "Shilin";
    EnumToString[StationName(4)] = "Zhongshan";
    EnumToString[StationName(5)] = "Xinpu";
    EnumToString[StationName(6)] = "Ximen";
    EnumToString[StationName(7)] = "Liuzhangli";
    EnumToString[StationName(8)] = "Muzha";
    EnumToString[StationName(9)] = "Guting";
    EnumToString[StationName(10)] = "Gongguan";
    EnumToString[StationName(11)] = "Jingmei";

    return (EnumToString[name]);
}
#endif
