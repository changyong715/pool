#include "threadpool.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// 初始化线程池
void threadpool_init(threadpool_t *pool, int maxtrd)
{
	condition_init(&pool->ready);
	pool->head       = NULL;
	pool->tail       = NULL;
	pool->max_thread = maxtrd;
	pool->counter    = 0;
	pool->idle       = 0;
	pool->quit       = 0;
}

void *route(void *arg)
{
	threadpool_t *pool = (threadpool_t*)arg;
	while ( 1 ) {
		condition_lock(&pool->ready);
		pool->idle++;
		while ( pool->head == NULL ) {
			condition_wait(&pool->ready);
		}
		pool->idle--;

		// 有任务，执行任务
		if ( pool->head != NULL ) {
			task_t *p = pool->head;
			pool->head = p->next;
			condition_unlock(&pool->ready); // 防止任务执行时间太长
			p->callback(p->arg);
			condition_lock(&pool->ready);
			free(p);
		}
		
		condition_unlock(&pool->ready);
	}
}

// 往线程池中添加任务
void threadpool_add(threadpool_t *pool, void *(*pf)(void*), void *arg)
{
	// 创建任务节点
	task_t *pnew = malloc(sizeof(task_t));
	memset(pnew, 0x00, sizeof(task_t));
	pnew->callback = pf;
	pnew->arg      = arg;
	pnew->next     = NULL;

	condition_lock(&pool->ready);
	// 插入任务队列	
	if ( pool->head == NULL )
		pool->head = pnew;
	else
		pool->tail->next = pnew;
	pool->tail = pnew;

	if ( pool->idle > 0 ) { // 线程池有空闲线程
		condition_signal(&pool->ready); // 唤醒空闲线程
	} 
	// 没有空闲线程,线程池中线程个数没有达到阈值
	else if ( pool->counter < pool->max_thread ) {
		pthread_t tid;
		pthread_create(&tid, NULL, route, pool);
		pool->counter++;
	}
	
	condition_unlock(&pool->ready);
}

// 销毁线程池
void threadpool_destroy(threadpool_t *pool)
{
}


