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

bool	odd_philo(t_philo *p)
{
	bool	died;
	int		n_philos;

	n_philos = p->rules->n_philos;
	died = (p->id == n_philos && p->id % 2 && n_philos > 2);
	return (died);
}

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

void	init_sync(t_rules *rules, t_philo *philo, int i)
{
	t_philo		*next;

	if (rules->t_sleep > rules->t_eat)
		rules->t_aux = rules->t_sleep;
	rules->last = philo->left;
	next = philo;
	fprintf(stderr, "\t\t\tLAST[%d]{%d}\n", philo->id, rules->last->id);
	while (i < rules->n_philos)
	{
		if (i % 2 == 1)
			next->action = 0;
		i++;
		next = next->right;
	}
	rules->t_start = get_time();
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

void	philo_neightbor(t_philo *philos, int i, int left, int right)
{
	philos[i].left = &philos[left];
	philos[i].right = &philos[right];
}
