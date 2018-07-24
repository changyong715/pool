#include "condition.h"

// 初始化
int condition_init(condition_t *pcond)
{
	pthread_mutex_init(&pcond->mutex, NULL);
	pthread_cond_init(&pcond->cond, NULL);
}

// 上锁
int condition_lock(condition_t *pcond)
{
	return pthread_mutex_lock(&pcond->mutex);
}

// 解锁
int condition_unlock(condition_t *pcond)
{
	return pthread_mutex_unlock(&pcond->mutex);
}

// 等待
int condition_wait(condition_t *pcond)
{
	return pthread_cond_wait(&pcond->cond, &pcond->mutex);
}

// 超时版本等待
int condition_timedwait(condition_t *pcond,  struct timespec *abstm)
{
	return pthread_cond_timedwait(&pcond->cond, &pcond->mutex, abstm);
}

// 通知
int condition_signal(condition_t *pcond)
{
	pthread_cond_signal(&pcond->cond);
}

// 广播
int condition_boardcast(condition_t *pcond)
{
	pthread_cond_broadcast(&pcond->cond);
}

// 销毁
int condition_destroy(condition_t *pcond)
{
	pthread_cond_destroy(&pcond->cond);
	pthread_mutex_destroy(&pcond->mutex);
}

