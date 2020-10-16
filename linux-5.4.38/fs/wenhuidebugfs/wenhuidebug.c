#include <linux/module.h>
#include <linux/debugfs.h>
#include <linux/kernel.h>

#include <linux/list.h>
#include <linux/sched.h>
#include <linux/fs.h>
#include <linux/binfmts.h>
#include <linux/in.h>
#include <linux/spinlock.h>
#include <linux/msg.h>


#include "wenhuidebug.h"


#define BUF_SIZE 16
int wenhui_debug = 0; // 0 is off, 1 is on



static ssize_t wenhui_debugfile_read(struct file *filp, char __user *buffer,
				size_t count, loff_t *ppos)
{
	/*reading mode, (e.g. CW-Lite value) value from the kernel*/
	char tmpbuf[BUF_SIZE];
	memset(&tmpbuf, 0, BUF_SIZE);

	//u32 ssid = get_current_sid();
	//int wenhui_mode = ( 0xf0000000 & ssid ) > 28;

	sprintf(tmpbuf, "%d", wenhui_debug);
	goto to_user;

to_user:
	if( *ppos >  0)
		return 0;
	if (count > BUF_SIZE)
		count = BUF_SIZE;
		
	if(copy_to_user(buffer, tmpbuf + *ppos, count))
		return -EFAULT;

	*ppos += count;

	return count;
}


static ssize_t wenhui_debugfile_write(struct file *filp, const char __user *buffer,
		size_t count, loff_t *ppos)
{

	/* collect value to write from user space*/
	char page[BUF_SIZE];

	memset(&page, 0, BUF_SIZE);

	if( *ppos > 0)
		return 0;
	if(copy_from_user(page + *ppos, buffer, count))
		return -EFAULT;

	*ppos += count;

	printk(KERN_INFO "WENHUI previous DEBUG: wenhui_debug mode %d\n", wenhui_debug);
	
	sscanf(page, "%d", &wenhui_debug);
	printk(KERN_INFO "WENHUI now DEBUG: wenhui_debug mode %d\n", wenhui_debug);

	return count;

}



static const struct file_operations wenhui_debugfile_fops = {
	.read = wenhui_debugfile_read,
	.write = wenhui_debugfile_write,
};


static int __init wenhui_debugfs(void)
{
	int ret;
	struct dentry *debug_dir;
	struct dentry *debug_file;
	wenhui_debug = 0;

	debug_dir = debugfs_create_dir("wenhui", NULL);
	if(IS_ERR(debug_dir)){
		ret = PTR_ERR(debug_dir);
		goto Fail;
	}


	debug_file = debugfs_create_file("wenhui_debug", 0644, debug_dir, NULL, &wenhui_debugfile_fops);
	if(IS_ERR(debug_file)){
		printk(KERN_INFO "WENHUI DEBUG: create debugfs 'wenhui_debug' file failed\n");
		ret = PTR_ERR(debug_file);
		goto Fail;
	}

	printk(KERN_INFO "WENHUI DEBUG: debugfs created :\n \t debug dir: 0x%pd, \n\t debug file: 0x%pd.\n", debug_dir, debug_file);
	return 0;
Fail:
	debugfs_remove(debug_dir);
	debug_dir = NULL;
	return ret;


}


fs_initcall(wenhui_debugfs);
