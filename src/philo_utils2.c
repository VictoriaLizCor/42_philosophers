/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 16:43:25 by lilizarr          #+#    #+#             */
/*   Updated: 2023/09/26 12:34:36 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

char	*color(int idx)
{
	char	**s_color;

	s_color = (char *[]){
		"\x1B[0m", \
		"\x1B[48;5;255m\x1B[38;5;1m", \
		"\x1B[41m", \
		"\x1B[48;5;255m\x1B[38;5;2m", \
		"\x1B[42m", \
		"\x1B[48;5;255m\x1B[38;5;3m", \
		"\x1B[43m", \
		"\x1B[48;5;255m\x1B[38;5;4m", \
		"\x1B[44m", \
		"\x1B[48;5;255m\x1B[38;5;5m", \
		"\x1B[45m", \
		"\x1B[48;5;255m\x1B[38;5;6m", \
		"\x1B[46m", \
		"\x1B[48;5;255m\x1B[38;5;9m", \
		"\x1B[48;5;255m\x1B[38;5;8m", \
		"\x1B[48;5;255m\x1B[38;5;10m", \
	};
	if (idx > 15)
		idx = (idx % 15);
	return (s_color[idx]);
}

char	*warn(int idx)
{
	char	**s_color;

	s_color = (char *[]){
		"\x1B[31m", \
		"\x1B[32m", \
	};
	return (s_color[idx]);
}

long long	current_time(t_rules *rules)
{
	long long	miliseconds;

	gettimeofday(&rules->t_end, NULL);
	miliseconds = ((rules->t_end.tv_sec - rules->t_start.tv_sec) * 1000LL + \
	(rules->t_end.tv_usec - rules->t_start.tv_usec) * 0.001);
	return (miliseconds);
}

void	philo_neightbor(t_philo *philos, int i, int left, int right)
{
	philos[i].left = &philos[left];
	philos[i].right = &philos[right];
}

void	print_msg(t_rules *rules, t_philo *tmp)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = tmp;
	while (i < rules->n_philos)
	{
		if (philos[i].left && philos[i].right)
		{
			printf("philo L %d [%p]| philo M %d| philo R %d [%p]\n", \
			philos[i].left->id, philos[i].left ,philos[i].id, \
			philos[i].right->id, philos[i].right);
		}
		else
			printf("philo L %p | philo M %d| philo R %p\n", \
			philos[i].left, philos[i].id, philos[i].right);
		i++;
	}
	printf("\n");
}

// void	*ft_free(char **str)
// {
// 	int		i;

// 	i = 0;
// 	while (str[i] != 0)
// 	{
// 		free(str[i]);
// 		i++;
// 	}
// 	free(str);
// 	return (NULL);
// }