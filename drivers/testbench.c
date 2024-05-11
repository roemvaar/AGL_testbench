/*
 * testbench.c
 */

#include <linux/module.h>
#include <linux/kernel.h>

static int __init testbench_init(void)
{
    printk(KERN_INFO "Hello World from Testbench Driver! \n");
    return 0;
}

static void __exit testbench_exit(void)
{
    printk(KERN_INFO "Goodbye world! \n");
}

module_init(testbench_init);
module_exit(testbench_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Roberto Valenzuela");
MODULE_DESCRIPTION("Testbed for quantitative evaluation of research​");
