#include<iostream>
#include<vector>

using namespace std;
vector<int>arr;

void DataGenerate()
{
    srand((size_t)time(NULL));
    for(int i = 0;i<10;i++)
        arr.push_back(rand());
}

int main()
{
    DataGenerate();
    return 0;
}