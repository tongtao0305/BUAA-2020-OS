#include <env.h>
#include <pmap.h>
#include <printf.h>

/* Overview:
 *  Implement simple round-robin scheduling.
 *
 *
 * Hints:
 *  1. The variable which is for counting should be defined as 'static'.
 *  2. Use variable 'env_sched_list', which is a pointer array.
 *  3. CANNOT use `return` statement!
 */
/*** exercise 3.14 ***/
/*
void sched_yield(void)
{
    static int count = 0; // remaining time slices of current env
    static int point = 0; // current env_sched_list index
    static struct Env *e = NULL;
  */  
    /*  hint:
     *  1. if (count==0), insert `e` into `env_sched_list[1-point]`
     *     using LIST_REMOVE and LIST_INSERT_TAIL.
     *  2. if (env_sched_list[point] is empty), point = 1 - point;
     *     then search through `env_sched_list[point]` for a runnable env `e`, 
     *     and set count = e->env_pri
     *  3. count--
     *  4. env_run()
     *
     *  functions or macros below may be used (not all):
     *  LIST_INSERT_TAIL, LIST_REMOVE, LIST_FIRST, LIST_EMPTY
     */
    /*
    if(--count <= 0 || curenv == NULL || curenv->env_status != ENV_RUNNABLE){
        do { 
        	if(LIST_EMPTY(&env_sched_list[point])){
            	point = 1 - point;
       		}
        	e = LIST_FIRST(&env_sched_list[point]);
			if (e != NULL) {
        		LIST_REMOVE(e, env_sched_link);
        		LIST_INSERT_HEAD(&env_sched_list[1-point], e, env_sched_link);
        		count = e->env_pri;
			}
    	} while (e == NULL || e->env_status != ENV_RUNNABLE);
	}
    env_run(e);
}
*/
void sched_yield(void)
{
    //记录当前进程已经使用的时间片数目
    static int counter = 0;
    //t = 0/1表示从哪个待调度队列中取进程
    static int t = 0;
    counter++;
    int flag = 0;
    /*
     * 切换进程的条件
     * 1. 当前进程时NULL，这种情况只发生在运行第一个进程的时候
     * 2. 当前进程的时间片已经用完了
    */
    if (curenv == NULL|| curenv->env_status != ENV_RUNNABLE || counter >= curenv->env_pri)
    {
        // 如果不是第一次运行进程，则要将当前进程添加到另一个待调度队列中以便下一次调度
        if (curenv != NULL)
        {
            LIST_INSERT_HEAD(&env_sched_list[t^1], curenv, env_sched_link);
        }
        //在当前调度队列中寻找下一个可调度来运行的进程
        flag = 0;
        while(1) {
            struct  Env *e = LIST_FIRST(&env_sched_list[t]);
            //如果没找到，则换一个调度队列继续找
            if (e == NULL)
            {
            	if (flag == 0) {
            		flag = 1;
            	} else if (flag == 1) {
            		// 两个链表都没找到
            		return;
            	}
                t = t ^ 1;
                continue;
            }
            //找到一个可执行的
            if (e->env_status == ENV_RUNNABLE)
            {
                //从待调度队列中移除
                LIST_REMOVE(e, env_sched_link);
                //初始化已使用时间片个数
                counter = 0;
                env_run(e);//在env_run()方法中会将curenv设置为e
                return;
            }
        }
    } 
    //如果不需要调度则当前进程继续执行
    env_run(curenv);

    
}
