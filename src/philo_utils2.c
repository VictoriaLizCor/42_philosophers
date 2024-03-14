/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 16:43:25 by lilizarr          #+#    #+#             */
/*   Updated: 2023/12/04 15:10:46 by lilizarr         ###   ########.fr       */
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
		"\x1B[48;5;255m\x1B[38;5;8m", \
		"\x1B[48;5;8m\x1B[38;5;255m", \
		"\x1B[48;5;255m\x1B[38;5;208m", \
		"\x1B[48;5;208m\x1B[38;5;255m", \
	};
	if (idx > 16)
		idx = (idx % 16);
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

void	print_msg(t_philo *philo, char *msg, t_ll time)
{
	int		i;

	i = philo->id;
	if (!check_mutex(&philo->rules->lock[MSG]))
	{
		if (D_PHI == 1)
			printf(" %lld [%lld]\tphilo %s [%03d] %s %s\n\n", \
			time / 1000, time, color(i), i, color(0), msg);
		else
			printf(" %lld\tphilo %s [%03d] %s %s\n\n", \
			time / 1000, color(i), i, color(0), msg);
	}
}

void	philo_neightbor(t_philo *philos, int i, int left, int right)
{
	philos[i].left = &philos[left];
	philos[i].right = &philos[right];
}

void	init_neightbor(t_philo *philos, int size)
{
	int	i;

	i = 0;
	if (!size)
	{
		philos[i].left = (void *)0;
		philos[i].right = (void *)0;
		return ;
	}
	while (i <= size)
	{
		if (i == 0)
			philo_neightbor(philos, i, size, i + 1);
		else if (i != size)
			philo_neightbor(philos, i, i - 1, i + 1);
		else if (i == size)
			philo_neightbor(philos, i, i - 1, 0);
		i++;
	}
	if (D_PHI == 1)
		print_neightbor(philos->rules, philos);
}
