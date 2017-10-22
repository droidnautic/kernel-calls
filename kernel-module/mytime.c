/*
Raymond Rolston
October 18 2017
mytime charachter device
prints kernel time and time of day
*/

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/device.h>
#include <linux/module.h>
#include <linux/string.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

static int dev_open(struct inode *, struct file *);
static int dev_release(struct inode *, struct file *);
static ssize_t dev_read(struct file *, char *, size_t, loff_t *);
static ssize_t dev_write(struct file *, const char *, size_t, loff_t *);

#define MAX_LENGTH 256
#define DEV_NAME "mytime"
#define CLASS_NAME "classtime"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Raymond Rolston");
MODULE_DESCRIPTION("Charachter Device that can be used to obtain time information");
MODULE_VERSION("0.3");

static int dev_number;
static int device_open = 0;
static char tstr[MAX_LENGTH] = {0};
//static char* tstr_ptr;
static int string_size;
static struct timespec ker_time;
static struct timespec get_time;
static struct class* mytimeClass = NULL;
static struct device* mytimeDevice = NULL;

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .read = dev_read,
    .write = dev_write,
    .open = dev_open,
    .release = dev_release
};

static int __init mytime_init(void){
    dev_number = register_chrdev(0, DEV_NAME, &fops);
    if(dev_number<0){
        printk(KERN_ALERT "Registering charachter device failed with %d\n", dev_number);
        return dev_number;
    }
    printk(KERN_INFO "Charachter device %s with number %d registered.\n", DEV_NAME, dev_number);

    mytimeClass = class_create(THIS_MODULE, CLASS_NAME);
    if(IS_ERR(mytimeClass)){
        unregister_chrdev(dev_number, DEV_NAME);
        printk(KERN_ALERT "Registering charachter device CLASS failed with %d\n", dev_number);
        return PTR_ERR(mytimeClass);
    }
    printk(KERN_INFO "Charachter device %s CLASS  with number %d registered.\n", DEV_NAME, dev_number);

    mytimeDevice = device_create(mytimeClass, NULL, MKDEV(dev_number, 0), NULL, DEV_NAME);
    if(IS_ERR(mytimeDevice)){
        class_destroy(mytimeClass);
        unregister_chrdev(dev_number, DEV_NAME);
        printk(KERN_ALERT "Registering charachter device DRIVER failed with %d\n", dev_number);
        return PTR_ERR(mytimeDevice);
    }
    printk(KERN_INFO "Charachter device %s DRIVER with number %d registered.\n", DEV_NAME, dev_number);

    return 0;
}

static void __exit mytime_exit(void){
    device_destroy(mytimeClass, MKDEV(dev_number,0));
    class_unregister(mytimeClass);
    class_destroy(mytimeClass);
    unregister_chrdev(dev_number, DEV_NAME);
    printk(KERN_INFO "%s Exit: module unloaded", DEV_NAME);
}

static int dev_open(struct inode *inodep, struct file *filep){
    if(device_open){
        return -EBUSY;
    }else{
        device_open++;
    }
    printk(KERN_INFO "process opening device%d: securing module %s\n", dev_number, DEV_NAME);
    try_module_get(THIS_MODULE);
    return 0;
}

static ssize_t dev_read(struct file *filep, char *buffer, size_t len, loff_t *offset){
    printk(KERN_INFO "process reading device%d: %s", dev_number, DEV_NAME);
    getnstimeofday(&get_time);
    ker_time = current_kernel_time();
    sprintf(tstr, "current_kernel_time: %lld %ld\ngetnstimeofday: %lld %ld\n", ker_time.tv_sec, ker_time.tv_nsec, get_time.tv_sec, get_time.tv_nsec);
    //tstr_ptr = tstr;
    string_size = strlen(tstr);
    if((copy_to_user(buffer, tstr, string_size))==0){
        printk(KERN_INFO "mytime device sent the time string:\n %s \n", buffer);
        return 0;
    }else{
        printk(KERN_INFO "failed to read mytime device message");
        return -EFAULT;
    }
    /*
    while(len && *tstr_ptr){
        put_user(*(tstr_ptr++), buffer++);
        len--;
    }
    return 0;
    */
}

static ssize_t dev_write( struct file *filep, const char *buffer, size_t len, loff_t *offset){
    printk(KERN_ALERT "this operation is not supported\n");
    return -EINVAL;
}

static int dev_release(struct inode *inodep, struct file *filep){
    device_open--;
    printk(KERN_INFO "process closing device%d: releasing module %s", dev_number, DEV_NAME);
    module_put(THIS_MODULE);
    return 0;
}

module_init(mytime_init);
module_exit(mytime_exit);
