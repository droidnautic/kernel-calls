#include<stdio.h>
#include<unistd.h>
#include<linux/unistd.h>
#include<linux/time.h>
int main(){
    int y = 0;
    struct timespec ts;
    y = syscall(326, &ts);
    printf("my_xtime is %ld seconds and %ld nanoseconds.\n", ts.tv_sec, ts.tv_nsec);
    return y;
}
