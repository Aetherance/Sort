#include<iostream>
#include<vector>
#include<limits.h>
#include<time.h>
using namespace std;
vector<int>arr;

void * presort(vector<int>&subarr);
void Merge(vector<int>&arr,int begin,int end);

void DataGenerate()
{
    srand((size_t)time(NULL));
    for(int i = 0;i<10;i++)
        arr.push_back(rand());
}

vector<int> SortWithThread()
{   
    pthread_t ptd1,ptd2,ptd3,ptd4;
    int mid = (0+arr.size())/2;
    int mid2 = (0+mid)/2;
    vector<int>line1(arr.begin(),arr.begin()+mid2+1);
    vector<int>line2(arr.begin()+mid2+1,arr.begin()+mid+1);
    vector<int>line3(arr.begin()+mid+1,arr.begin()+mid+mid2+1);
    vector<int>line4(arr.begin()+mid+mid2+1,arr.end());
    pthread_create(&ptd1,NULL,(void*(*)(void*))presort,&line1);
    pthread_create(&ptd2,NULL,(void*(*)(void*))presort,&line2);
    pthread_create(&ptd3,NULL,(void*(*)(void*))presort,&line3);
    pthread_create(&ptd4,NULL,(void*(*)(void*))presort,&line4);

    pthread_join(ptd1,NULL);
    pthread_join(ptd2,NULL);
    pthread_join(ptd3,NULL);
    pthread_join(ptd4,NULL);

    line1.insert(line1.end(),line2.begin(),line2.end());
    line3.insert(line3.end(),line4.begin(),line4.end());

    Merge(line1,0,line1.size()-1);
    Merge(line3,0,line3.size()-1);

    line1.insert(line1.end(),line3.begin(),line3.end());

    Merge(line1,0,line1.size());

    return line1;
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
    vector<int>subarr(arr.begin()+begin,arr.begin()+end+1);
    pthread_t ptd;
    Merge(arr,begin,end);
}

void* presort(vector<int>&subarr)
{
    MergeSort(subarr,0,subarr.size()-1);
    return NULL;
}

int main()
{
    clock_t c1,c2;
    DataGenerate(); 

    // c1 = clock();
    time_t t1,t2;
    t1 = time(NULL);
    arr = SortWithThread();
    t2 = time(NULL);
    // c2 = clock();

    // cout<<endl<<"多线程->"<<(c2 - c1)<<"<-";

    cout<<"多线程 done! 共用"<<t2-t1<<"秒"<<endl;
    return 0;
}