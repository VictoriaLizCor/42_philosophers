/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:23:58 by lilizarr          #+#    #+#             */
/*   Updated: 2024/03/25 16:46:03 by lilizarr         ###   ########.fr       */
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

//rules->extra = 3*rules->t_eat;
void	sleep_think_utils(t_philo *philo, t_rules *rules)
{
	t_ll	time;
	t_ll	eat_sleep;
	t_ll	time_eat;

	time = t_mu_s(rules->t_start);
	printf("\t\t\t\t%s[%d] time[%lld]%s\n", \
	warn(0), philo->id, time, font(0));
	eat_sleep = (rules->t_eat % rules->t_sleep);
	time_eat = (time + eat_sleep) / rules->t_eat;
	if (D_PHI != 0)
	{
		printf("\t\t\t\t%s[%d] wait[%lld]%s\n", \
		font(philo->id), philo->id, philo->wait, font(0));
		printf("\t\t\t\t%s[%d] time %% eat\t[%lld]%s\n", \
		font(philo->id), philo->id, time_eat, font(0));
		printf("\t\t\t\t%s[%d] time %% eat %% 3\t[%lld]%s\n", \
		font(philo->id), philo->id, time_eat % 3, font(0));
		printf("\t\t\t\t%s[%d] eat%%sleep't[%lld]%s\n", \
		font(philo->id), philo->id, eat_sleep, font(0));
	}
	if (!philo->right)
		philo->action = 2;
	else if (philo->wait != (time_eat % 3) && !check_fork(philo))
		philo->action = 2;
	else if (check_fork(philo))
		ft_usleep(rules, philo, 0, 1);
}

void	init_sync(t_rules *rules, t_philo *philo)
{
	t_philo	*next;
	int		i;

	i = 1;
	rules->last = philo->left;
	next = philo;
	if (rules->odd)
		rules->last->wait = 2;
	while (i < rules->n_philos)
	{
		if (i % 2 == 1 && D_PHI != 0)
			printf("\t%s [%d]", font(3), next->id);
		else if (i % 2 == 0 && D_PHI != 0)
			printf("\t %s [%d]", font(1), next->id);
		if (i % 2 == 1)
			next->action = 0;
		else
			next->wait = 1;
		i++;
		next = next->right;
	}
	if (D_PHI != 0)
		printf("\t %s*[%d]%s\n\n", font(1), next->id, font(0));
}

void	ft_sync(t_philo *philo, int m, void (*func)(t_rules *r, t_philo *p))
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
			func(rules, philo);
			rules->t_start = get_time();
		}
		if (rules->lock[m]->stat == 1)
			break ;
		pthread_mutex_unlock(&rules->lock[m]->lock);
	}
	philo->t_extra = t_mu_s(rules->t_start);
	philo->t_start = get_time();
	pthread_mutex_unlock(&rules->lock[m]->lock);
}

// void	init_time(t_rules *rules, t_philo *philo)
// {
// 	t_ll		extra;
// 	t_philo		*next;
// 	int			i;

// 	i = 1;
// 	extra = 0;
// 	next = philo;
// 	while (i <= rules->n_philos)
// 	{
// 		if (next->t_extra > extra)
// 			extra = next->t_extra;
// 		next = next->right;
// 		i++;
// 	}
// 	rules->extra = extra;
// }
		// if (rules->n_philos > 1)
		// 	(*philos)[i].wait = rules->t_eat;
		// if (rules->n_philos > 1 && rules->n_philos % 2 == 1)
		// 	(*philos)[i].wait = 2 * rules->t_eat;