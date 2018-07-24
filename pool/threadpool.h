#ifndef __POOL_H__ 
#define __POOL_H__

#include "condition.h"

// 任务节点
typedef struct task {
	void *(*callback)(void*);
	void *arg;
	struct task *next;
}task_t;

// 管理线程池的数据结构
typedef struct threadpool{
	condition_t ready; // 同步和互斥
	task_t *head;      // 任务队列的队头
	task_t *tail;      // 队尾指针
	int max_thread;    // 线程池最大个数
	int counter;       // 当前线程个数
	int idle;          // 空闲线程个数
	int quit;          // 如果为1，表示销毁
}threadpool_t;

// 初始化线程池
void threadpool_init(threadpool_t *pool, int maxtrd);

// 往线程池中添加任务
void threadpool_add(threadpool_t *pool, void *(*pf)(void*), void *arg);

// 销毁线程池
void threadpool_destroy(threadpool_t *pool);

#endif // __POOL_H__

