/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:23:58 by lilizarr          #+#    #+#             */
/*   Updated: 2024/03/15 18:03:57 by lilizarr         ###   ########.fr       */
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

void	init_time(t_rules *rules, t_philo *philo, int i)
{
	t_philo		*next;
	static t_ll	extra;

	i = 0;
	next = philo;
	while (i++ <= rules->n_philos)
	{
		if (next->t_extra > extra)
			extra = next->t_extra;
		next = next->right;
	}
	if (check_mutex(rules->lock[TIME]))
		printf("\t\t\t%sMAX_EXTRA [%lld]%s\n", color(15), extra, color(0));
}

void	init_sync(t_philo *philo)
{
	t_philo	*next;
	int		i;
	t_rules	*rules;

	rules = philo->rules;
	i = 0;
	rules->last = philo->left;
	rules->last->wait = philo->t_aux;
	next = philo;
	while (i < rules->n_philos)
	{
		if (i % 2 == 1)
		{
			printf("%s\t [%d]", color(3), next->id);
			next->action = 0;
		}
		else
		{
			next->wait = philo->t_aux;
			printf("%s\t [%d]", color(1), next->id);
		}
		i++;
		next = next->right;
	}
	rules->t_start = get_time();
	printf("\t %s*[%d]%s\n\n", color(1), rules->last->id, color(0));
}
// void	handling_files(void (*fun)(t_pipex *), t_pipex *ptr)
// handling_files(openfile, node->next);

void	wait_all(t_philo *philo, int mutex, void (*fun)(t_philo *philo))
{
	static int	sum;
	static bool	limit;
	t_rules		*rules;

	rules = philo->rules;
	while (1)
	{
		pthread_mutex_lock(&rules->lock[mutex]->lock);
		if (!limit++)
			sum++;
		if (rules->lock[mutex]->stat == 0 && sum == rules->n_philos)
		{
			rules->lock[mutex]->stat = 1;
			fun(philo);
		}
		if (rules->lock[mutex]->stat)
			break ;
		pthread_mutex_unlock(&rules->lock[mutex]->lock);
	}
	pthread_mutex_unlock(&rules->lock[mutex]->lock);
	if (rules->t_sleep > rules->t_eat)
		philo->t_aux = rules->t_sleep;
}
	// sum = 0;
	// size = 0;
	// next = philo;
	// philo->t_extra = t_mu_s(rules->t_start);
	// while (size++ <= rules->n_philos)
	// {
	// 	if (next->t_extra > sum)
	// 		sum = next->t_extra;
	// 	next = next->right;
	// }
	// printf("\t\t\t%sMAX_EXTRA [%lld]%s\n", color(15), sum, color(0));
