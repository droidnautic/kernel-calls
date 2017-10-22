//libraries
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<linux/unistd.h>
#include<time.h>
#define N 3
#define MAX_LENGTH 256

struct timeval gtodTimes[N];
char *procClockTimes[N];

//allocate mem for buffs

int main(){
   int i;
   for(i=0;i<N;i++){
      procClockTimes[i] = (char *)malloc((MAX_LENGTH+1)*sizeof(char));
   }
   int fd, ret;
   for(i=0;i<N;i++){

        fd = open("/dev/mytime", O_RDONLY);
        //check errors
        if(fd<0){
            printf("failed to open device");
            exit(1);
        }
        ret = read(fd, procClockTimes[i], MAX_LENGTH);
        if(ret<0){
            printf("failed to read device");
            exit(1);
        }
        gettimeofday(&gtodTimes[i],0);
        printf("User Report %d:\ngettimeofday: %lld %ld\n\n\nModule Report %d:\n%s\n\n", i, gtodTimes[i].tv_sec, gtodTimes[i].tv_usec, i, procClockTimes[i]);
        close(fd);
   }
   return 0;
}
