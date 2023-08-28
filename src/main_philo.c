/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:22:17 by lilizarr          #+#    #+#             */
/*   Updated: 2023/08/28 16:53:59 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	main(int argc, char *argv[], char *env[])
{
	if (argc == 5 || argc == 6)
	{
		print_intro();
		check_integers(++argv);
		printf("(%d + 1) %% %d = %d\n", argc, argc, (argc + 1) % argc);
	}
	return (0);
}
/*
The functions used:

	pthread_mutex_init (&mutex, NULL) – initialization of mutex variable
	pthread_mutex_lock (&mutex) – attempt to lock a mutex
	pthread_mutex_unlock (&mutex) – unlock a mutex
	pthread_create (ptr to thread, NULL, (void*) func, (void*) )
	pthread_join (ptr to thread, &msg)-This function will make the main program wait until the called thread is finished executing it’s task.
	pthread_mutex_destroy (ptr to thread)-
	pthread_exit(NULL)

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

number_of_philosophers = forks
time_to_die (in milliseconds):
time_to_eat (in milliseconds):
time_to_sleep (in milliseconds):
number_of_times_each_philosopher_must_eat
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
usleep
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
exit
waitpid
sem_open
sem_close
sem_post
sem_wait
sem_unlink

*/
