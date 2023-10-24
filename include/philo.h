/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 12:46:39 by lilizarr          #+#    #+#             */
/*   Updated: 2023/10/24 11:18:28 by lilizarr         ###   ########.fr       */
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
# include <sys/types.h>
# include <stdbool.h>
# include <errno.h>

# ifndef DEBUG_PHI
#  define DEBUG_PHI 0
# endif

typedef struct s_mutex
{
	bool			stat;
	pthread_mutex_t	lock;
}	t_mutex;

typedef struct s_rules
{
	long long		t_start;
	int				n_philos;
	long long		t_die;
	long long		t_eat;
	long long		t_sleep;
	int				n_to_eat;
	t_mutex			lock_flags;
}	t_rules;

typedef struct s_philo
{
	int				id;
	int				action;
	int				n_to_eat;
	long long		t_meal;
	long long		t_sleep;
	long long		time;
	pthread_t		thread;
	t_mutex			fork;
	t_mutex			msg;
	t_rules			*d_rules;
	struct s_philo	*to_lock;
	struct s_philo	*right;
	struct s_philo	*left;
}	t_philo;

/* main_philo.c */
/* libft.c */
long long	current_time(time_t t_start);
size_t		ft_strlen(const char *str);
int			ft_isdigit(int ch);
long int	ft_atol(const char *s);
void		*ft_memset(void *s, int c, size_t n);
char		*ft_strchr(const char *s, int c);
int			*random_non_repetive_values(int min, int size);
/* philo_utils1.c */
void		start_threads(t_philo *philos, t_rules *rules, int *array);
/* philo_utils2.c */
char		*color(int idx);
char		*warn(int idx);
void		philo_msg(t_philo *philo, char *msg, char *msg_color);
void		print_msg(t_rules *rules, t_philo *philos);
void		philo_neightbor(t_philo *philos, int i, int left, int right);
/* philo_utils3.c */
bool		ft_usleep(t_rules *rules, t_philo *philo, long long time);
void		wait_all_philos(t_rules *rules, t_philo *philo);
void		destroy_mutex(t_philo *philo, t_rules *rules);
int			died_msg(t_rules *rules, t_philo *philo);
/* check_error.c*/
void		ft_error(t_philo *philo, char *str1, char *str2, int exit_error);
void		error_thread(t_philo *philo, int type, int errnum);
void		check_arguments(char **argv, int *error);

# define P_EAT "\x1B[1;41;33m"
# define P_SLEEP "\x1B[48;5;97m\x1B[38;5;81m"
# define P_THINK "\x1B[48;5;31m\x1B[38;5;118m"
# define P_DEAD "\x1B[48;5;237m\x1B[38;5;172m"
# define P_FORK "\x1B[48;5;255m\x1B[38;5;0m"

// # define CNRM "\x1B[0m"
// # define CRED "\x1B[31m"
// # define CGRN "\x1B[32m"
// # define CYEL "\x1B[33m"
// # define CBLU "\x1B[34m"
// # define CMAG "\x1B[35m"
// # define CCYN "\x1B[36m"
// # define CWHT "\x1B[37m"
// # define BBLK "\x1B[40m"
// # define BRED "\x1B[41m"
// # define BGRN "\x1B[42m"
// # define BYEL "\x1B[43m"
// # define BBLU "\x1B[44m"
// # define BMAG "\x1B[45m"
// # define BCYN "\x1B[46m"
// # define BWHT "\x1B[47m"
// 	P_EAT "\x1B[1;41;33m"
// 	P_SLEEP "\x1B[48;5;97m\x1B[38;5;81m"
// 	P_THINK "\x1B[48;5;31m\x1B[38;5;118m"
// 	P_DEAD "\x1B[48;5;237m\x1B[38;5;172m"
// 	P_FORK "\x1B[48;5;255m\x1B[38;5;0m"
// 	CTEST1 "\033[38;1;42m"
// 	CTEST2 "\x1B[48;5;97m\x1B[38;5;0m"
// // 	CTEST1 "\x1B[41m"
// 	CTESTN "\033[0m"
// // 	CTEST2 "\x1B[0m"
// 	CNRM2 "\033[0m"
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