/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 12:46:39 by lilizarr          #+#    #+#             */
/*   Updated: 2023/12/07 11:50:58 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdint.h>
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

# ifndef D_PHI
#  define D_PHI 0
# endif

# define EXTRA_TIME 0
# define T_DIED_EXTRA 0

typedef long long		t_ll;
typedef struct s_rules	t_rules;
typedef struct s_philo	t_philo;
// typedef t_ll			(*t_get_time)(t_rules *);

typedef enum e_mutexes
{
	DEAD,
	TIME,
	MSG,
	START,
	MEAL,
	N_MUTEX
}	t_mutexes;

typedef struct s_mutex
{
	bool			stat;
	pthread_mutex_t	lock;
}	t_mutex;

struct s_rules
{
	t_ll			t_start;
	t_ll			t_die;
	t_ll			t_eat;
	t_ll			t_sleep;
	int				n_philos;
	int				n_meals;
	t_mutex			**lock;
	t_mutex			dead;
	int				*error;
	struct s_philo	*last;
};

struct	s_philo
{
	int				id;
	int				action;
	int				n_meals;
	t_ll			t_meal;
	t_ll			sleep;
	t_ll			wait;
	t_ll			time;
	t_ll			t_aux;
	t_ll			t_extra;
	pthread_t		thread;
	time_t			t_start;
	t_mutex			fork;
	struct s_philo	*lock_by;
	struct s_philo	*right;
	struct s_philo	*left;
	t_rules			*rules;
};
// t_ll			(*g_time)(t_philo *);
// t_get_time		t;

/* function_pointer.c */
t_ll		time_ms(t_philo *philo);
t_ll		t_mu_s(t_ll start);
t_ll		get_time(void);
void		init_sync(t_rules *rules, t_philo *philo, int i);
void		wait_all(t_rules *rules, t_philo *philo, bool tmp, int size);
/* libft1.c */
size_t		ft_strlen(const char *str);
int			ft_isdigit(int ch);
long int	ft_atol(const char *s);
char		*ft_strchr(const char *s, int c);
/* libft2.c */
int			*random_values(int min, int max, int size);
/* philo_utils1.c */
void		lock_msg(t_philo *philo);
void		start_threads(t_philo *philos, t_rules *rules, int *array);
/* philo_utils2.c */
char		*color(int idx);
char		*warn(int idx);
void		print_msg(t_philo *philo, char *msg, t_ll time);
void		philo_neightbor(t_philo *philos, int i, int left, int right);
void		init_neightbor(t_philo *philos, int size);
/* philo_utils3.c */
void		ft_usleep(t_rules *rules, t_philo *philo, t_ll time, t_ll tmp);
void		philo_msg(t_philo *philo, char *msg);
bool		died_msg(t_rules *rules, t_philo *philo);
bool		meal_done(t_rules *rules, t_philo *philo, bool check);
void		destroy_mutex(t_philo *philo, t_rules *rules);
/* philo_utils4.c */
void		lock_mutex(t_mutex *mutex);
void		unlock_mutex(t_mutex *mutex);
bool		check_mutex(t_mutex *mutex);
bool		check_fork(t_philo *philo);
bool		check_action(t_philo *philo, char op, int val);
/* check_error.c*/
void		ft_error(int id, char *str1, char *str2, int exit_error);
void		error_thread(void *data, int type);
void		check_arguments(char **argv, int *error);
/* debug.c*/
void		print_action(t_philo *philo);
void		debug_death(t_philo *p, t_rules *rules, t_ll time);
void		debug_thread_check(t_philo *philo, char *msg);
void		print_ft_usleep(t_rules *rules, t_philo *philo, t_ll time, t_ll tmp);
void		print_neightbor(t_rules *rules, t_philo *philos);

# define P_EAT "\x1B[1;41;33m is    EATING     \x1B[0m"
# define P_SLEEP "\x1B[48;5;97m\x1B[38;5;81m is   SLEEPING    \x1B[0m"
# define P_THINK "\x1B[48;5;31m\x1B[38;5;118m is   THINKING    \x1B[0m"
# define P_DEAD "\x1B[48;5;237m\x1B[38;5;172m       DIED       \x1B[0m"
# define P_FORK "\x1B[48;5;255m\x1B[38;5;0m has taken a fork \x1B[0m"

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
