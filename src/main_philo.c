/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:22:17 by lilizarr          #+#    #+#             */
/*   Updated: 2023/08/29 16:55:11 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

/*
struct timeval {
time_t       tv_sec;   // seconds since Jan. 1, 1970 
suseconds_t  tv_usec;  // and microseconds 
}
*/
void	start_hunger_games(void)
{
	struct timeval	t_sys;
	time_t			tmp;

	printf("time: %d\n", gettimeofday(&t_sys, NULL));
	printf(" %ld | %d \n", t_sys.tv_sec, t_sys.tv_usec);
	printf(" ms: %f \n", t_sys.tv_sec * 1000 + t_sys.tv_usec * 0.001);
}

int	main(int argc, char *argv[], char *env[])
{
	int				error;
	char			*input;

	if (argc == 5 || argc == 6)
	{
		check_integers(argv, &error);
		if (error)
			return (printf("%d\n", error));
		start_hunger_games();
	}
	else
	{
		printf("%sError: Invalid input %s\n", CRED, CNRM);
		printf("Valid:\n" \
		"./philo number_of_philosophers t_to_die(ms) " \
		"t_to_eat(ms) t_to_sleep(ms) " \
		"[number_of_times_each_philosopher_must_eat]\n");
		printf("%si.e.: 1: ./philo 7 98 23 54%s\n", CGRN, CNRM);
		printf("%si.e.: 2: ./philo 7 98 23 54 3%s\n", CGRN, CNRM);
	}
	return (0);
}

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