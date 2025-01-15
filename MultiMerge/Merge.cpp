#include<iostream>
#include<vector>
#include<limits.h>
#include<chrono>
using namespace std;

#define DataSize 10000000

vector<int>arr;

void DataGenerate()
{
    srand((size_t)time(NULL));
    for(int i = 0;i<DataSize;i++)
        arr.push_back(rand());
}

void Merge(vector<int>&arr,int begin,int mid,int end) {
    vector<int>left(arr.begin()+begin,arr.begin()+mid+1);
    vector<int>right(arr.begin()+mid+1,arr.begin()+end+1);
    left.push_back(INT_MIN),right.push_back(INT_MIN);
    int Lindex = 0,Rindex = 0;
    for(int i = begin;i<=end;i++)    
        arr[i] = (left[Lindex]>right[Rindex]?left[Lindex++]:right[Rindex++]);
}

void MergeSort(int begin,int end) {
    if(begin==end)
        return;
    int mid = (begin + end)/2;
    MergeSort(begin,mid);
    MergeSort(mid+1,end);
    Merge(arr,begin,mid,end);
}

void ArrPrint(vector<int>&arr)
{
    int count = 0;
    for(int i = 0;i<arr.size();i++)
        cout<<arr[i]<<endl,count++;
    cout<<count<<endl;
}

int main()
{
    DataGenerate();
    auto start = std::chrono::system_clock::now();

    MergeSort(0,arr.size());

    auto end = chrono::system_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);

    // ArrPrint(arr);
    cout <<"单"<< (double)(duration.count()) * chrono::microseconds::period::num / chrono::microseconds::period::den  << "s" << endl;

    return 0;
}