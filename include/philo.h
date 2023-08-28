/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 12:46:39 by lilizarr          #+#    #+#             */
/*   Updated: 2023/08/28 16:54:51 by lilizarr         ###   ########.fr       */
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

typedef struct s_philo
{
	pthread_t	id;
	int			t_die;
	int			t_eat;
	int			t_sleep;
	int			n_to_eat;
}	t_philo;

/* philo.c */
void	print_intro(void);
void	check_integers(char **argv);
void	ft_error(void);
/* libft.c */
int		ft_isdigit(int ch);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *str);
long int	ft_atoi(const char *s);
// // /* testing utils pipe_list.c */
// void	check_fd(int num, t_pipex *node);
// void	printf_stderr(char *str1, char *str2, int exit_error);
// void	print_variable(char **variable, char *msg);
// void	print_list(t_pipex *print, int opt);
// void	print_node_info(t_pipex *node, int opt);

# define CNRM  "\x1B[0m"
# define CRED  "\x1B[31m"
# define CGRN  "\x1B[32m"
# define CYEL  "\x1B[33m"
# define CBLU  "\x1B[34m"
# define CMAG  "\x1B[35m"
# define CCYN  "\x1B[36m"
# define CWHT  "\x1B[37m"

#endif