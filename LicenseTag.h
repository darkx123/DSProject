#ifndef LicenseTag_h
#define LicenseTag_h
#include <string>
#include <fstream>
#include "datatype.h"

class HashingTable
{
public:
    HashingTable();
    void InsertNewBike(BikePtr aBike);
    int LicenseTag(LicenseType license);
    int DeleteBikeFromHTable(BikePtr aBike); //only delete HNodeType from Hashing Table, BikePtr still exists.
    void HashReport(ofstream &outFile);
    BikePtr SearhBike(LicenseType license);
private:
    HTableType LicenseTable;
};

HashingTable::HashingTable()
{
    LicenseTable.BikeNum = 0;
    for(int i = 0; i < 256; i ++)
    {
        LicenseTable.table[i].next_ptr = NULL;
        LicenseTable.table[i].Ptr = NULL;
        for(int j = 0; j < 5; j++)
            LicenseTable.table[i].License[j] = ' ';
    }
}

void HashingTable::InsertNewBike(BikePtr aBike)
{
    LicenseTable.BikeNum++;
    HNodeType *currentNode = NULL;
    int HTableIndex = LicenseTag(aBike->License);
    if( LicenseTable.table[HTableIndex].Ptr == NULL )
    {
        LicenseTable.table[HTableIndex].Ptr = aBike;
        for(int i = 0; i < 5; i++)
            LicenseTable.table[HTableIndex].License[i] = aBike->License[i];
    }
    else
    {
        currentNode = &(LicenseTable.table[HTableIndex]);
        while(currentNode->next_ptr)
        {
            currentNode = currentNode->next_ptr;
        }
        HNodeType *newNode;
        newNode = new HNodeType;
        for(int i = 0; i < 5; i++)
            newNode->License[i] = aBike->License[i];
        newNode->Ptr = aBike;
        newNode->next_ptr = NULL;
        currentNode->next_ptr = newNode;
    }
}

void HashingTable::HashReport(ofstream &outFile)
{
    cout << "Hash Table";
    outFile << "Hash Table";
    for(int i = 0; i < 256; i++)
    {
        HNodeType *currentNode = &(LicenseTable.table[i]);
        if(currentNode->Ptr)
        {
            cout << endl;
            outFile << endl;
            cout << i << " ";
            outFile << i << " ";
            for(int j = 0; j < 5; j++)
            {
                cout << currentNode->License[j];
                outFile << currentNode->License[j];
            }
        }
        currentNode = currentNode->next_ptr;
        while(currentNode)
        {
            cout << "->";
            outFile << "->";
            for(int j = 0; j < 5; j++)
            {
                cout << currentNode->License[j];
                outFile << currentNode->License[j];
            }
            currentNode = currentNode->next_ptr;
        }
    }
    cout << endl;
    outFile << endl;
}

BikePtr HashingTable::SearhBike(LicenseType license)
{
    int HTableIndex = LicenseTag(license);
    HNodeType *currentNode = &(LicenseTable.table[HTableIndex]);
    while(currentNode)
    {
        bool compare = true;
        for(int i = 0; i < 5; i++)
        {
            if(currentNode->License[i] != license[i])
            {
                compare = false;
                break;
            }
        }
        if(compare)
        {
            return currentNode->Ptr;
        }
        currentNode = currentNode->next_ptr;
    }
    return NULL;
}

int HashingTable::DeleteBikeFromHTable(BikePtr aBike)
{
    int HTableIndex = LicenseTag(aBike->License);
    HNodeType *currentNode = &(LicenseTable.table[HTableIndex]);
    HNodeType *previousNode = NULL;
    while(currentNode)
    {
        bool compare = true;
        for(int i = 0; i < 5; i++)
        {
            if(currentNode->License[i] != aBike->License[i])
            {
                compare = false;
                break;
            }
        }
        if(compare)
        {
            if(previousNode == NULL) // currentNode = LicenseTable.table[HTableIndex]
            {
                if(currentNode->next_ptr) // LicenseTable.table[HTableIndex]->HNodeType1 ->...===>LicenseTable.table[HTableIndex] = HNodeType1 ->....
                {
                    currentNode = currentNode->next_ptr;
                    LicenseTable.table[HTableIndex].next_ptr = currentNode->next_ptr;
                    LicenseTable.table[HTableIndex].Ptr = currentNode->Ptr;
                    for(int i = 0; i < 5; i++)
                    {
                        LicenseTable.table[HTableIndex].License[i] = currentNode->License[i];
                    }
                    delete currentNode;
                }
                else  // LicenseTable.table[HTableIndex] -> NULL
                {
                    currentNode->Ptr = NULL;
                    currentNode->next_ptr = NULL;
                    for(int i = 0; i < 5; i++)
                    {
                        currentNode->License[i] = ' ';
                    }
                }
            }
            else
            {
                previousNode->next_ptr = currentNode->next_ptr;
                delete currentNode;
            }
            return 0;
        }
        previousNode = currentNode;
        currentNode = currentNode->next_ptr;
    }
    return 1;
}


int HashingTable::LicenseTag(LicenseType license)
{
    int licenseValue = 0;
    int charValue = 0;
    for(int i = 0; i < 5; i++)
    {
        switch(license[i])
        {
            case 'A' : charValue = 10; break;
            case 'B' : charValue = 11; break;
            case 'C' : charValue = 12; break;
            case 'D' : charValue = 13; break;
            case 'E' : charValue = 14; break;
            case 'F' : charValue = 15; break;
            case 'G' : charValue = 16; break;
            case 'H' : charValue = 17; break;
            case 'I' : charValue = 18; break;
            case 'J' : charValue = 19; break;
            case 'K' : charValue = 20; break;
            case 'L' : charValue = 21; break;
            case 'M' : charValue = 22; break;
            case 'N' : charValue = 23; break;
            case 'O' : charValue = 24; break;
            case 'P' : charValue = 25; break;
            case 'Q' : charValue = 26; break;
            case 'R' : charValue = 27; break;
            case 'S' : charValue = 28; break;
            case 'T' : charValue = 29; break;
            case 'U' : charValue = 30; break;
            case 'V' : charValue = 31; break;
            case 'W' : charValue = 32; break;
            case 'X' : charValue = 33; break;
            case 'Y' : charValue = 34; break;
            case 'Z' : charValue = 35; break;
            case '0' : charValue = 0; break;
            case '1' : charValue = 1; break;
            case '2' : charValue = 2; break;
            case '3' : charValue = 3; break;
            case '4' : charValue = 4; break;
            case '5' : charValue = 5; break;
            case '6' : charValue = 6; break;
            case '7' : charValue = 7; break;
            case '8' : charValue = 8; break;
            case '9' : charValue = 9; break;
        }
        licenseValue = charValue + licenseValue * 31;
    }

    return ((licenseValue >> 10) & 0xFF);

}



#endif // LicenseTag_h
