/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 12:46:39 by lilizarr          #+#    #+#             */
/*   Updated: 2023/08/30 16:46:35 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <stdbool.h>

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
	pthread_t		id;
	const t_rules	*d_rules;
	int				n_to_eat;
	long long		(*get_time)(t_rules *rules);
}	t_philo;

/* main_philo.c */
/* philo.c */
long long	current_timestamp(t_rules *rules);
void		print_intro(void);
void		check_arguments(char **argv, int *error);
/* libft.c */
int			ft_isdigit(int ch);
char		*ft_strchr(const char *s, int c);
size_t		ft_strlen(const char *str);
long int	ft_atol(const char *s);
/*ft_utils.c*/

/* check_error.c*/
void		ft_error(char *str1, char *str2, int exit_error);
void		*ft_free(char **str);

# define CNRM  "\x1B[0m"
# define CRED  "\x1B[31m"
# define CGRN  "\x1B[32m"
# define CYEL  "\x1B[33m"
# define CBLU  "\x1B[34m"
# define CMAG  "\x1B[35m"
# define CCYN  "\x1B[36m"
# define CWHT  "\x1B[37m"

#endif