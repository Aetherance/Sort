#include<iostream>
#include<string.h>
#include<vector>
#include<fcntl.h>
#include<unistd.h>
using namespace std;
vector<string>vs;
void DataGenerate(int fd)
{
    srand((size_t)time(NULL));
    for(int i = 0;i<10000000;i++)
    {
        char buf[32];
        sprintf(buf,"%d,",rand());
        write(fd,buf,strlen(buf));
    }
}
int main()
{
    int fd = open("/home/user/CODE/Sort/Data.h",O_WRONLY);
    DataGenerate(fd);
    return 0;
}