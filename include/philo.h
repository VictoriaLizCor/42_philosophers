/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 12:46:39 by lilizarr          #+#    #+#             */
/*   Updated: 2023/09/18 15:09:03 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <string.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <stdbool.h>
# include <errno.h>

# ifndef DEBUG_PHI
#  define DEBUG_PHI 0
# endif

typedef struct s_rules
{
	struct timeval	t_start;
	struct timeval	t_end;
	int				n_philos;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_to_eat;
}	t_rules;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	pthread_mutex_t	fork;
	t_rules			*d_rules;
	int				n_to_eat;
	long long		(*get_time)(t_rules *rules);
	struct s_philo	*right;
	struct s_philo	*left;
}	t_philo;

/* main_philo.c */
/* philo.c */
void		print_intro(void);
void		check_arguments(char **argv, int *error);
/* libft.c */
int			ft_isdigit(int ch);
char		*ft_strchr(const char *s, int c);
size_t		ft_strlen(const char *str);
long int	ft_atol(const char *s);
void		*ft_memset(void *s, int c, size_t n);
/*ft_utils.c*/
long long	current_timestamp(t_rules *rules);
void		func(t_philo *philo);
void		*ft_free(char **str);
void		print_msg(t_rules *rules, t_philo **philos);
/* check_error.c*/
void		error_thread(t_philo *philo, int type, int errnum);
void		ft_error(t_philo *philo, char *str1, char *str2, int exit_error);
void		*ft_free(char **str);

# define CNRM "\x1B[0m"
# define CRED "\x1B[31m"
# define CGRN "\x1B[32m"
# define CYEL "\x1B[33m"
# define CBLU "\x1B[34m"
# define CMAG "\x1B[35m"
# define CCYN "\x1B[36m"
# define CWHT "\x1B[37m"
# define BBLK "\x1B[40m"
# define BRED "\x1B[41m"
# define BGRN "\x1B[42m"
# define BYEL "\x1B[43m"
# define BBLU "\x1B[44m"
# define BMAG "\x1B[45m"
# define BCYN "\x1B[46m"
# define BWHT "\x1B[47m"
# define P_EAT "\x1B[1;41;33m"
# define P_SLEEP "\x1B[48;5;97m\x1B[38;5;81m"
# define P_THINK "\x1B[48;5;31m\x1B[38;5;118m"
# define P_DEAD "\x1B[48;5;237m\x1B[38;5;172m"
# define CTEST1 "\033[38;1;42m"
# define CTEST2 "\x1B[48;5;97m\x1B[38;5;0m"
// # define CTEST1 "\x1B[41m"
# define CTESTN "\033[0m"
// # define CTEST2 "\x1B[0m"
# define CNRM2 "\033[0m"
#endif

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
usleep(useconds_t microseconds) = usleep(25 ms * 1000) = usleep(250)
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