#include<iostream>
#include<vector>
#include<limits.h>
using namespace std;

vector<int>arr;

void DataGenerate()
{
    srand((size_t)time(NULL));
    for(int i = 0;i<10000000;i++)
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

void MergeSort(vector<int>&arr,int begin,int end) {
    if(begin==end)
        return;
    int mid = (begin + end)/2;
    MergeSort(arr,begin,mid);
    MergeSort(arr,mid+1,end);
    Merge(arr,begin,mid,end);
}

void ArrPrint(vector<int>&arr)
{
    int count = 0;
    for(int i = 0;i<arr.size();i++)
        cout<<arr[i]<<endl,count++;
    cout<<count;
}

int main()
{
    clock_t c1,c2;
    DataGenerate();
    time_t t1,t2;
    // c1 = clock();
    t1 = time(NULL);
    MergeSort(arr,0,arr.size()-1);
    t2 = time(NULL);
    // c2 = clock();
    
    // cout<<endl<<"单线程->"<<(c2 - c1)<<"<-";
    cout<<"单线程 done! 共用"<<t2-t1<<"秒"<<endl;
    return 0;
}