#include<iostream>
#include<thread>
#include<vector>
#include<limits.h>
#include<chrono>
using namespace std;
#define DataSize 100000000

void DataGenerate(vector<int>&arr)
{
    srand((size_t)time(NULL));
    for(int i = 0;i<DataSize;i++)
        arr.push_back(rand());
}

void Merge(vector<int>&arr,int begin,int end)
{
    int mid = (begin + end)/2,l_index = 0,r_index = 0; 
    vector<int>left(arr.begin()+begin,arr.begin()+mid+1);
    vector<int>right(arr.begin()+mid+1,arr.begin()+end+1);
    left.push_back(INT_MIN),right.push_back(INT_MIN);
    for(int i = begin;i<=end;i++) {
        arr[i] = (left[l_index]>right[r_index]?left[l_index++]:right[r_index++]);
    }
}

void MergeSort(vector<int>&arr,int begin,int end)
{
    if(begin == end)
        return;
    int mid = (begin + end)/2;
    if(end - begin < DataSize/1000) {
        MergeSort(arr,begin,mid);
        MergeSort(arr,mid+1,end);
    }
    else {
        thread line1(MergeSort,ref(arr),begin,mid);
        thread line2(MergeSort,ref(arr),mid+1,end);
        line1.join();
        line2.join();
    }
    Merge(arr,begin,end);
}

void ArrPrint(vector<int>&arr)
{
    for(auto &num : arr)
        cout<<num<<endl;
}

vector<int>arr;
int main()
{
    DataGenerate(arr);

    auto start = std::chrono::system_clock::now();
    MergeSort(arr,0,arr.size()-1);
    auto end = chrono::system_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);

    // ArrPrint(arr);
    cout <<"多"<< (double)(duration.count()) * chrono::microseconds::period::num / chrono::microseconds::period::den  << "s" << endl;

    return 0;
}