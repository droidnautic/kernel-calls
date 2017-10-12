#include<stdio.h>
#include<unistd.h>
#include<linux/unistd.h>
#include<linux/time.h>
int main(){
    int y = 0;
    struct timespec ts;
    y = syscall(326, &ts);
    if(y==0) printf("my_xtime is %lld seconds and %ld nanoseconds.\n", (long long)ts.tv_sec, ts.tv_nsec);
    printf(" totaltime in nano sec: %lld%.9ld\n",(long long)ts.tv_sec,ts.tv_nsec);
    return y;
}
