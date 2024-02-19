# 42_philosophers
Summary: In this project, you will learn the basics of threading a process. You will see how to create threads and you will discover mutexes
Philosophers with threads and mutexes

/*
The functions used:

	pthread_mutex_init (&mutex, NULL) – initialization of mutex variable
	pthread_mutex_lock (&mutex) – attempt to lock a mutex
	pthread_mutex_unlock (&mutex) – unlock a mutex
	pthread_create (ptr to thread, NULL, (void*) func, (void*) )
	pthread_join (ptr to thread, &msg)-This function will make the main 
	program wait until the called thread is finished executing it’s task.
	pthread_mutex_destroy (ptr to thread)-
	pthread_exit(NULL)


create a function that waits for all threads to be created with simple C and using following functios: pthread_mutex_init, pthread_mutex_lock, pthread_mutex_unlock, pthread_create, pthread_join, pthread_mutex_destroy, pthread_exit without semaphores or pthread_cond_t

Note: while compiling this program use the following:
[root@Linux philo]# gcc –o dining dining.c -lpthread

Algorithm for process:
1. Start.
2. Declare and initialize the thread variables (philosophers) as required.
3. Declare and initialize the mutex variables (chopsticks) as required.
4. Create the threads representing philosophers.
5. Wait until the threads finish execution.
6. Stop.

Algorithm for thread (philosopher i) function:

	Start.
	Philosopher i is thinking.
	Lock the left fork spoon.
	Lock the right fork spoon.
	Philosopher i is eating.
	sleep
	Release the left fork spoon.
	Release the right fork spoon.
	Philosopher i Finished eating.
	Stop.

should be <= 10000 and >= 60 ms.

[1] number_of_philosophers = forks
[2] time_to_die (in milliseconds)>  time_to_eat + time_to_sleep.
[3] time_to_eat (in milliseconds):
[4] time_to_sleep (in milliseconds):
[5] number_of_times_each_philosopher_must_eat
** the simulation stops when a philosopher dies.

◦ timestamp_in_ms X has taken a fork 
◦ timestamp_in_ms X is eating
◦ timestamp_in_ms X is sleeping
◦ timestamp_in_ms X is thinking
◦ timestamp_in_ms X died

** Each philosopher has a number ranging from 1 to number_of_philosophers.
** To prevent philosophers from duplicating forks, \
	you should protect the forks state with a mutex for each of them.

--- MANDATORY:
memset
printf
malloc
free
write,
usleep(useconds_t microseconds) = usleep(25 ms * 1000) = usleep(25000)
	-- suspend thread execution for an interval measured in microseconds
gettimeofday
pthread_create
pthread_detach
pthread_join
pthread_mutex_init
pthread_mutex_destroy
pthread_mutex_lock
pthread_mutex_unlock


--- BONUS:
fork
kill
exitma
waitpid
sem_open
sem_close
sem_post
sem_wait
sem_unlink

*/

<!-- <ul>
<li>Do not test with more than 200 philosophers.</li>
<li>Do not test with time_to_die or time_to_eat or time_to_sleep set
	to values lower than 60 ms.</li>
<li>Test 1 800 200 200. The philosopher should not eat and should die.</li>
<li>Test 5 800 200 200. No philosopher should die.</li>
<li>Test 5 800 200 200 7. No philosopher should die and the simulation
	should stop when every philosopher has eaten at least 7 times.</li>
<li>Test 4 410 200 200. No philosopher should die.</li>
<li>Test 4 310 200 100. One philosopher should die.</li>
<li>Test with 2 philosophers and check the different times: a death
	delayed by more than 10 ms is unacceptable.</li>
<li>Test with any values of your choice to verify all the requirements.
	Ensure philosophers die at the right time, that they don't steal
	forks, and so forth.</li>
</ul> -->