
#include <linux/linkage.h>
#include <linux/export.h>
#include <linux/time.h>
#include <asm/uaccess.h>
#include <linux/printk.h>
#include <linux/slab.h>

asmlinkage int sys_my_xtime(struct timespec *current_time){
    if( (!current_time) || (current_time->tv_sec < 0) || (current_time->tv_nsec < 0) ){
        return -EFAULT;
    }else{
        getnstimeofday(current_time);
        printk(KERN_INFO "Current Time since epoch (total nanoseconds): %lld%.9ld", (long long)current_time->tv_sec, current_time->tv_nsec);
        return 0;
    }
}

EXPORT_SYMBOL(sys_my_xtime);

