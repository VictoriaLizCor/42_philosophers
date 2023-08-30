/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:22:17 by lilizarr          #+#    #+#             */
/*   Updated: 2023/08/30 16:46:56 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	init_data(t_rules *rules, t_philo **philos, char **argv)
{
	int	i;

	i = 0;
	gettimeofday(&rules->t_start, NULL);
	rules->n_philos = ft_atol(argv[1]);
	rules->t_die = ft_atol(argv[2]);
	rules->t_eat = ft_atol(argv[3]);
	rules->t_sleep = ft_atol(argv[4]);
	rules->n_to_eat = 0;
	if (argv[5])
		rules->n_to_eat = ft_atol(argv[5]);
	*philos = (t_philo *)malloc(sizeof(t_philo) * (rules->n_philos + 1));
	if (!philos)
		philos = NULL;
	while (i < rules->n_philos)
	{
		(*philos + i)->d_rules = rules;
		(*philos + i)->n_to_eat = rules->n_to_eat;
		(*philos + i)->get_time = &current_timestamp;
		i++;
	}
}

void	start_hunger_games(t_rules *rules, char **argv)
{
	t_philo			*philos;
	int				i;

	init_data(&*rules, &philos, argv);
	printf("philosophers: %d\n", philos[0].d_rules->n_philos);
	printf("philo chances to eat: %d\n", philos[0].n_to_eat);
	i = 1;
	sleep(i);
	printf("%lld miliseconds\n", philos[0].get_time(&*rules));
	sleep(i);
	printf("%lld miliseconds\n", philos[1].get_time(&*rules));
}

int	main(int argc, char **argv, char **env)
{
	t_rules		rules;
	int			error;
	char		*input;

	if (argc == 5 || argc == 6)
	{
		check_arguments(argv, &error);
		if (error)
			return (printf("%d\n", error));
		start_hunger_games(&rules, argv);
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
usleep(useconds_t microseconds)
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
exit
waitpid
sem_open
sem_close
sem_post
sem_wait
sem_unlink

*/