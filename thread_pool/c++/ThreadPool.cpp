/*************************************************************************
	> File Name: ThreadPool.cpp
	> Author: Soul
	> Mail:souldong1591@gmail.com 
	> Created Time: 2014年08月03日 星期日 22时47分13秒
 ************************************************************************/

#include "ThreadPool.h"
#include "Thread.h"
using namespace std;

ThreadPool::ThreadPool(size_t queueSize, size_t poolSize)
	:empty_(mutex_),
	 full_(mutex_),
	 queueSize_(queueSize),
	 poolSize_(poolSize),
	 isStarted_(false)
{}

ThreadPool::~ThreadPool()
{
	if(isStarted_)
		stop();
}

void ThreadPool::addTask(const Task &task)
{
	MutexLockGuard lock(mutex_);
	while(queue_.size() >= queueSize_)
		empty_.wait();
	queue_.push(task);
	full_.notify();

}

ThreadPool::Task ThreadPool::getTask()
{
	MutexLockGuard lock(mutex_);
	while(queue_.empty() && isStarted_)
		full_.wait();

	Task task;
	if(!queue_.empty())
	{
		task = queue_.front();
		queue_.pop();
		empty_.notify();
	}

	return task;
}

void ThreadPool::runInThread()
{
	while(isStarted_)
	{
		Task task(getTask());
		if(task)
			task();
	}
}

void ThreadPool::start()
{
	if(isStarted_)
		return;
	isStarted_ = true;
	for (size_t i = 0; i != poolSize_; i++) 
		threads_.push_back(new Thread(bind(&ThreadPool::runInThread, this)));
	
	for (size_t i = 0; i != poolSize_; i++)
		threads_[i]->start();
}

void ThreadPool::stop()
{
	if(isStarted_ == false)
		return;
	{
		MutexLockGuard lock(mutex_);
		isStarted_ = false;
		full_.notifyAll();
	}
	for (size_t i = 0; i != poolSize_; i++)
		threads_[i]->join();

	while(!queue_.empty())
		queue_.pop();
}
