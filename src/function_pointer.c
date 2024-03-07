/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:23:58 by lilizarr          #+#    #+#             */
/*   Updated: 2024/03/07 16:24:34 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

t_ll	get_time(void)
{
	struct timeval	t;

	if (gettimeofday(&t, NULL) == -1)
	{
		ft_error(0, NULL, " GETTIMEOFDAY(2)\n", 1);
		return (0);
	}
	t.tv_sec *= 1e6;
	t.tv_usec += t.tv_sec;
	return ((t_ll)t.tv_usec);
}

// rules->t_start = ((start.tv_sec * 1000) + ((long)start.tv_usec / 1000));
t_ll	time_ms(t_philo *philo)
{
	t_ll	ms;
	t_ll	t;
	t_rules	*rules;

	rules = philo->rules;
	pthread_mutex_lock(&rules->lock[TIME]->lock);
	t = get_time();
	ms = (t) - philo->t_start;
	pthread_mutex_unlock(&rules->lock[TIME]->lock);
	return (ms);
}

t_ll	t_mu_s(t_rules *rules)
{
	t_ll	ms;
	t_ll	t;

	pthread_mutex_lock(&rules->lock[TIME]->lock);
	t = get_time();
	ms = (t) - rules->t_start;
	pthread_mutex_unlock(&rules->lock[TIME]->lock);
	return (ms);
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
}

void	wait_all(t_rules *rules, t_philo *philo, bool limit, int size)
{
	static int	sum;

	while (1)
	{
		pthread_mutex_lock(&rules->lock[COUNT]->lock);
		if (!limit++)
			sum += philo->id;
		if (!rules->lock[COUNT]->stat && sum == size)
		{
			rules->lock[COUNT]->stat = true;
			init_sync(rules, philo, 1);
		}
		if (rules->lock[COUNT]->stat)
			break ;
		pthread_mutex_unlock(&rules->lock[COUNT]->lock);
	}
	if (rules->t_sleep > rules->t_eat)
		philo->t_aux = rules->t_sleep;
	philo->t_start = rules->t_start;
	pthread_mutex_unlock(&rules->lock[COUNT]->lock);
}
