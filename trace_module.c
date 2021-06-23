#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/kthread.h>

#define CREATE_TRACE_POINTS
#include "trace_module.h"

static struct task_struct *simple_tsk;

static const char *random_string[] = {
	"james",
	"sameer",
	"shaik",
	"ambala",
	"dambala"
};

static void thread_func(int cnt)
{
	int array[6];
	int len = cnt % 5;
	int i;

	set_current_state(TASK_INTERRUPTIBLE);
	schedule_timeout(HZ);
	printk(KERN_INFO "I am inside the thread\n");

	for (i = 0; i < len; i++)
		array[i] = i + 1;
	array[i] = 0;

	/* tracepoint */
	trace_sameer_shaik("sameer", cnt, array, random_string[len]);
}
	
static int simple_thread(void *arg)
{
	int cnt = 0;
	
	while (!kthread_should_stop()) {
		thread_func(cnt++);		
	}
	return 0;
}
static int __init sample_init(void)
{
	simple_tsk = kthread_run(simple_thread, NULL, "event-sample");
	if (IS_ERR(simple_tsk))
		return -1;
	return 0;
}

static void __exit sample_exit(void)
{
	kthread_stop(simple_tsk);
	printk(KERN_ERR "Getting removed by module\n");
}

module_init(sample_init);
module_exit(sample_exit);

MODULE_AUTHOR("sameer");
MODULE_LICENSE("GPL");
