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

void Merge(vector<int>&arr,int begin,int end)
{
    int mid = (begin + end)/2;
    vector<int>left(arr.begin()+begin,arr.begin()+mid+1);
    vector<int>right(arr.begin()+mid+1,arr.begin()+end+1);
    int left_index = 0,right_index = 0;

    left.push_back(INT_MIN);
    right.push_back(INT_MIN);

    for(int i = begin;i<=end;i++)
        arr[i] = (right[right_index]>left[left_index])?right[right_index++]:left[left_index++];
}
void MergeSort(vector<int>&arr,int begin,int end)
{
    int mid = (begin + end)/2;
    if(end==begin)
        return;
    MergeSort(arr,begin,mid);
    MergeSort(arr,mid+1,end);
    Merge(arr,begin,end);
}

int main()
{
    clock_t bg,ed;
    bg = clock();
    DataGenerate();
    MergeSort(arr,0,arr.size()-1);
    
    // for(int i = 0;i<arr.size();i++)
    //     cout<<arr[i]<<endl;


    ed = clock();
    cout<<endl<<"->"<<ed - bg<<"<-";
    return 0;
}