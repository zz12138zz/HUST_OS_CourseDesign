#include <linux/kernel.h>
#include  <linux/module.h>   
#include  <linux/version.h>
#include <linux/types.h>   
#include <linux/fs.h>   
#include <linux/mm.h>
#include <linux/init.h>
#include <linux/uaccess.h>   
#include <linux/errno.h>   
#include <asm/segment.h>
long int dev_no = 0;
int mutex=0;
char dev_info[1024]="you can rewrite this sentence.";

ssize_t myread(struct file *flip,char *buf,size_t count, loff_t*f_pos)
{ 
    int res = copy_to_user(buf, dev_info, sizeof(dev_info));
    if(res == 0)
    {
        printk("read success!\n");
        return count;
    }
    else
    {
        printk("can't read!\n");
        return -1;
    }

}

ssize_t mywrite(struct file *flip,const char *buf,size_t count, loff_t*f_pos) 
{ 
    int res = copy_from_user(dev_info, buf, sizeof(dev_info));
    if(res == 0)
    {
        printk("write success!\n");
        return 0;
    }
    else
    {
        printk("can't write!\n");
        return -1;
    }
}
 
int myopen(struct inode *inode,struct file *file ) 
{
    if (mutex == 0)
    { 
        mutex++; 
        try_module_get(THIS_MODULE);
        printk("the device is opened!\n");
        return 0; 
    }  
    else 
    { 
        printk("another process open the device!\n");
        return -1; 
    }  

}
 
int myrelease (struct inode *inode,struct file *file )
{
    mutex--;
    module_put(THIS_MODULE);
    printk("the device is released!\n");
    return 0;

}

struct file_operations fops={
	.read = myread,
	.write=mywrite,
	.open=myopen,
	.release=myrelease
};

static int init_mymodule(void) 
{ 
	int result;
	result = register_chrdev(0, "yizumi", &fops); 
	if (result < 0) { 
		printk("register failed!\n"); 
		return result;
	} 
	if (dev_no == 0) dev_no = result;
   	printk("register succeed!\n"); 
	return 0; 
}

static void cleanup_mymodule(void) 
{ 
	unregister_chrdev(dev_no,"yizumi"); 
    	printk("the driver has been cleaned!\n");
} 

module_init(init_mymodule);
module_exit(cleanup_mymodule);
MODULE_LICENSE("GPL");














