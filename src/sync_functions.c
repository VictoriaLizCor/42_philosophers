/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:23:58 by lilizarr          #+#    #+#             */
/*   Updated: 2024/03/16 15:50:20 by lilizarr         ###   ########.fr       */
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

t_ll	t_mu_s(t_ll start)
{
	t_ll	ms;
	t_ll	current;

	current = get_time();
	if (current == 0)
		return (-1);
	ms = current - start;
	return (ms);
}

void	init_time(t_rules *rules, t_philo *philo)
{
	t_ll		extra;
	t_philo		*next;
	int			i;

	i = 1;
	extra = 0;
	next = philo;
	while (i <= rules->n_philos)
	{
		if (next->t_extra > extra)
			extra = next->t_extra;
		next = next->right;
		i++;
	}
	printf("\t\t%sMAX_EXTRA [%lld]%s\n", color(15), extra, color(0));
}

void	init_sync(t_rules *rules, t_philo *philo)
{
	t_philo	*next;
	int		i;

	i = 1;
	rules->last = philo->left;
	rules->last->wait = philo->t_aux;
	next = philo;
	while (i < rules->n_philos)
	{
		if (i % 2 == 1 && D_PHI != 0)
			printf("\t%s [%d]", color(3), next->id);
		else if (i % 2 == 0 && D_PHI != 0)
			printf("\t %s [%d]", color(1), next->id);
		if (i % 2 == 1)
			next->action = 0;
		else
			next->wait = philo->t_aux;
		i++;
		next = next->right;
	}
	rules->t_start = get_time();
	printf("\t %s*[%d]%s\n\n", color(1), rules->last->id, color(0));
}

void	ft_sync(t_philo *philo, int m, void (*f)(t_rules *r, t_philo *p))
{
	static int	sum;
	bool		limit;
	t_rules		*rules;

	rules = philo->rules;
	limit = 0;
	while (1)
	{
		pthread_mutex_lock(&rules->lock[m]->lock);
		if (!limit++)
			sum++;
		if (rules->lock[m]->stat == 0 && sum == rules->n_philos)
		{
			rules->lock[m]->stat = 1;
			f(rules, philo);
		}
		if (rules->lock[m]->stat == 1)
			break ;
		pthread_mutex_unlock(&rules->lock[m]->lock);
	}
	philo->t_extra = t_mu_s(rules->t_start);
	if (rules->t_sleep > rules->t_eat)
		philo->t_aux = rules->t_sleep;
	pthread_mutex_unlock(&rules->lock[m]->lock);
}
			// if (philo->id == rules->last->id)
			// {
			// 	sum = 0;
			// 	printf("\t\t%s SUM[%d]\n", warn(0),philo->id);
			// }