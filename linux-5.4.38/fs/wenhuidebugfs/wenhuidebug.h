#ifndef _WENHUI_H 
#define _WENHUI_H

#include <linux/module.h>
#include <linux/debugfs.h>
#include <linux/kernel.h>
#include <linux/fs.h>


// extern int wenhui_debug = 0; // 0 is off, 1 is on

static ssize_t wenhui_debugfile_read(struct file *filp, char __user *buffer,
                                size_t count, loff_t *ppos);

static ssize_t wenhui_debugfile_write(struct file *filp, const char __user *buffer,
                size_t count, loff_t *ppos);


#endif /* _WENHUI_H */
