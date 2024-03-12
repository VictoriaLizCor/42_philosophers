/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:23:58 by lilizarr          #+#    #+#             */
/*   Updated: 2024/03/12 14:22:42 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

t_ll	get_time(void)
{
	struct timeval	t;

	if (gettimeofday(&t, NULL) == -1)
	{
		ft_error(0, NULL, "on function GETTIMEOFDAY\n", 1);
		return (0);
	}
	t.tv_sec *= 1e6;
	t.tv_usec += t.tv_sec;
	return ((t_ll)t.tv_usec);
}

t_ll	time_ms(t_philo *philo)
{
	t_ll	ms;
	t_ll	current;

	current = get_time();
	ms = current - philo->t_start;
	return (ms);
}

t_ll	t_mu_s(t_rules *rules)
{
	t_ll	ms;
	t_ll	current;

	pthread_mutex_lock(&rules->lock[TIME]->lock);
	current = get_time();
	ms = current - rules->t_start;
	pthread_mutex_unlock(&rules->lock[TIME]->lock);
	return (ms);
}

void	init_sync(t_rules *rules, t_philo *philo, int i)
{
	t_philo		*next;

	if (rules->n_philos > 1)
	{
		rules->last = philo->left;
		rules->last->wait = philo->t_aux;
		next = philo;
		printf("\t\t\tStart with[%d] \n\t\t\tLast [%d]\n", \
		philo->id, rules->last->id);
		while (i < rules->n_philos)
		{
			if (i % 2 == 1)
				next->action = 0;
			else
				next->wait = philo->t_aux;
			i++;
			next = next->right;
		}
	}
	rules->t_start = get_time();
}

void	wait_all(t_rules *rules, t_philo *philo, bool limit, int size)
{
	static int	sum;

	while (1)
	{
		pthread_mutex_lock(&rules->lock[START]->lock);
		if (!limit++)
			sum += philo->id;
		if (!rules->lock[START]->stat && sum == size)
		{
			rules->lock[START]->stat = true;
			init_sync(rules, philo, 1);
		}
		if (rules->lock[START]->stat)
			break ;
		pthread_mutex_unlock(&rules->lock[START]->lock);
	}
	if (rules->t_sleep > rules->t_eat)
		philo->t_aux = rules->t_sleep;
	philo->t_start = rules->t_start;
	printf("[%d]->ACTION = %d\n", philo->id, philo->action);
	pthread_mutex_unlock(&rules->lock[START]->lock);
}
