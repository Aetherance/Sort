#include<iostream>
#include<vector>
#include<limits.h>
#include<chrono>
using namespace std;

#define DataSize 100000000

vector<int>arr;

struct Args
{
    int begin;
    int end;
};

pthread_mutex_t mtx1 = PTHREAD_MUTEX_INITIALIZER;

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

void MergeSort(Args* args) {
    int begin = args->begin,end = args->end;
    if(begin==end)
        return;
    int mid = (begin + end)/2;
    
    if (end - begin <= DataSize/1000) {
        Args Larg = Args{begin, mid};
        Args Rarg = Args{mid + 1, end};

        MergeSort(&Larg);
        MergeSort(&Rarg);
        Merge(arr, begin, mid, end);

        return;
    }

    pthread_t ptd1,ptd2;

    Args Largs = {begin,mid},Rargs = {mid+1,end};
    pthread_create(&ptd1,NULL,(void*(*)(void*))MergeSort,&Largs);
    pthread_create(&ptd2,NULL,(void*(*)(void*))MergeSort,&Rargs);

    pthread_join(ptd1,NULL);
    pthread_join(ptd2,NULL);
    Merge(arr,begin,mid,end);
}

void ArrPrint(vector<int>&arr)
{
    int count = 0;
    for(int i = 0;i<arr.size();i++)
        cout<<arr[i]<<endl,count++;
    cout<<endl<<"Count::"<<count<<endl;
}

int main()
{
    DataGenerate();
    auto start = std::chrono::system_clock::now();

    Args args = {0,(int)arr.size()-1};
    MergeSort(&args);

    auto end = chrono::system_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);

    // ArrPrint(arr);
    cout <<"多"<< (double)(duration.count()) * chrono::microseconds::period::num / chrono::microseconds::period::den  << "s" << endl;

    return 0;
}