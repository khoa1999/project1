#include <stdio.h>
#include <signal.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#define DEFAULT_NUM_THREAD 40
#define BUFFER_SIZE 200
const int KEY = -50;
int max;
struct Queue{
	int circular_buffer[BUFFER_SIZE];
	int head;
	int tail;
}queue;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock3 = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t not_empty = PTHREAD_COND_INITIALIZER;
static pthread_t* pool;
static int size;
static int employed = 1;
static int counter = 0;
void enqueue(int);
int dequeue();
void* execute(void*);
void thread_pool_create(void* execute(void *),void *);
void thread_pool_destroy();
void find_max(int);
int isempty();
int main(int args, char **argv){
	FILE *p;
	queue.tail = 0;
	queue.head = 0;//Intitialize the queue
	pthread_cond_init(&not_empty,NULL);
	int i = 0,num = 0;
	if(args >= 3)
		num = atoi(argv[2]);
	else if(args == 2)
		num = DEFAULT_NUM_THREAD;
	else{
		perror("Not specified argument");
		return 0;
	}
	pthread_t array[num];
	pool = array;//create the thread pool
	size = num;
	thread_pool_create(execute,NULL);
	/*Open the file and push each line into stack*/
	p = fopen(argv[args - 1],"r");
	int flag = 1;
	if(p == NULL){
		perror("Cannot open file");
		return 0;
	}
	while(!feof(p)){
		char s[60];
		fgets(s,60,p);
		int e = atoi(s);
		if(flag){
			max = e;
			flag = 0;
		}
		printf("%d",e);
		enqueue(e);
	}
	while(counter != 3);
	thread_pool_destroy();
	printf("the largest number is %d",max);
	return 1;
}
/*Intitialize the thread pool*/
void thread_pool_create(void *execute(void *),void *args){
	int i;
	for(i = 0;i < size;i++){
		int error = pthread_create(&pool[i],NULL,execute,args);
		if(error != 0)
			perror(strerror(error));
	}
}
void thread_pool_destroy(){
	int i;
	employed = 0;
	for(i = 0;i < size;i++){
		pthread_join(pool[i],NULL);
	}
}
void *execute(void *args){
	int num;
	while(employed){
		pthread_mutex_lock(&lock);
		num = dequeue();//find work to do
		pthread_mutex_lock(&lock3);
		if(num == KEY){
			printf("thread %u find key\n",(unsigned int) pthread_self());
			counter += 1;
		}
		pthread_mutex_unlock(&lock3);
		find_max(num);
	}
	return NULL;
}
void find_max(int num){
	pthread_mutex_lock(&lock2);
	if(num >= max){
		max = num;
	}
	pthread_mutex_unlock(&lock2);
}
/*Queue with circular buffer design*/
void enqueue(int item){
	int temp = queue.tail;
	if(queue.tail == (BUFFER_SIZE - 1))
		temp = 0;
	else
		temp -= 1;
	queue.circular_buffer[temp] = item;
	queue.tail = temp;//avoiding race condition
	pthread_cond_broadcast(&not_empty);
}
int dequeue(){
	pthread_mutex_lock(&lock);
	while(queue.head == queue.tail)
		pthread_cond_wait(&not_empty,&lock);
	int b;
	if(queue.head == (BUFFER_SIZE - 1)){
		queue.head = 0;
		b = queue.circular_buffer[BUFFER_SIZE - 1];
	}
	else{
		queue.head -= 1;
		b = queue.circular_buffer[queue.head - 1];
	}
	pthread_mutex_unlock(&lock);
	return b;
}
int isempty(){
	pthread_mutex_lock(&lock);
	int flag = 0;
	if(queue.tail == queue.head){
		flag = 1;
	}
	pthread_mutex_unlock(&lock);
	return flag;
}
