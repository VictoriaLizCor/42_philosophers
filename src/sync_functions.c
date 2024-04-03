/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:23:58 by lilizarr          #+#    #+#             */
/*   Updated: 2024/04/03 11:35:07 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

t_ll	get_time(void)
{
	struct timeval	t;
	t_ll			time;

	if (gettimeofday(&t, NULL) == -1)
	{
		ft_error(0, NULL, "on function GETTIMEOFDAY\n", 1);
		return (0);
	}
	t.tv_sec *= 1e6;
	time = (t_ll)t.tv_usec + (t_ll)t.tv_sec;
	return ((t_ll)time);
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

void	init_sync(t_rules *rules, t_philo *philo)
{
	t_philo	*next;
	int		i;

	i = 0;
	rules->last = philo->left;
	next = philo;
	if (rules->odd)
		rules->last->t_aux = 1;
	while (++i < rules->n_philos)
	{
		if (i % 2 == 1 && D_PHI != 0)
			printf("\t %s [%d]", font(3), next->id);
		else if (i % 2 == 0 && D_PHI != 0)
			printf("\t %s [%d]", font(1), next->id);
		if (i % 2 == 1)
			next->action = 0;
		else if (rules->odd)
			next->t_aux = 2;
		if (next->t_extra > rules->extra)
			rules->extra = next->t_extra;
		next = next->right;
	}
	if (D_PHI != 0)
		printf("\t %s*[%d]%s\n\n", font(1), rules->last->id, font(0));
	rules->t_start = get_time();
}

void	harm(t_philo *p, int m, int *sum, void (*f)(t_rules *r, t_philo *p))
{
	bool		limit;
	t_rules		*rules;

	rules = p->rules;
	if (rules->n_philos == 1)
		return ;
	limit = 0;
	while (1)
	{
		pthread_mutex_lock(&rules->lock[m]->lock);
		if (rules->lock[m]->stat == 1 && *sum == 0)
			return ((void)pthread_mutex_unlock(&rules->lock[m]->lock));
		if (!limit)
		{
			(*sum)++;
			limit = 1;
		}
		if (rules->lock[m]->stat == 0 && *sum == rules->n_philos)
		{
			rules->lock[m]->stat = 1;
			f(rules, p);
			*sum = 0;
		}
		pthread_mutex_unlock(&rules->lock[m]->lock);
	}
}

// void	get_max_delay(t_rules *rules, t_philo *philo)
// {
// 	t_ll		extra;
// 	t_philo		*next;
// 	int			i;

// 	i = 1;
// 	extra = 0;
// 	rules->last = philo->left;
// 	next = philo->right;
// 	while (i < rules->n_philos)
// 	{
// 		if (next->t_extra > extra)
// 			extra = next->t_extra;
// 		next = next->right;
// 		i++;
// 	}
// 	rules->extra = extra;
// 	rules->t_start = get_time();
// }
