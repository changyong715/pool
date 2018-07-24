#ifndef __CONDITION_H__
#define __CONDITION_H__

#include <pthread.h>
#include <time.h>

typedef struct condition{
	pthread_mutex_t mutex;
	pthread_cond_t cond;
}condition_t;

// 初始化
int condition_init(condition_t *pcond);

// 上锁
int condition_lock(condition_t *pcond);

// 解锁
int condition_unlock(condition_t *pcond);

// 等待
int condition_wait(condition_t *pcond);

// 超时版本等待
int condition_timedwait(condition_t *pcond,  struct timespec *abstm);

// 通知
int condition_signal(condition_t *pcond);

// 广播
int condition_boardcast(condition_t *pcond);

// 销毁
int condition_destroy(condition_t *pcond);

#endif //__CONDITION_H__

