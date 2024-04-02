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

void	sleep_think_utils(t_philo *philo, t_rules *rules)
{
	t_ll	time;
	t_ll	last_meal;

	time = (t_mu_s(rules->t_start) / 1000) * 1000;
	last_meal = philo->t_meal;
	if (last_meal == 0 && philo->right)
		last_meal = -1 * (philo->t_aux * rules->t_eat);
	philo->n_meal = ((last_meal / 1000) * 1000) + (2 * rules->t_eat);
	if (rules->odd)
		philo->n_meal = last_meal + (3 * rules->t_eat);
	philo->n_meal = (philo->n_meal / 1000) * 1000;
	if (D_PHI == 2 && !check_mutex(rules->lock[DEAD]))
	{
		printf("\t\t\t\t%s[%d]>n_meal - time => [%lld]-[%lld]=[%lld]%s\n", \
		font(philo->id), philo->id, philo->n_meal, time, \
		philo->n_meal - time, font(0));
	}
	if (!philo->right || philo->n_meal - time >= rules->t_sleep)
		philo->action = 2;
	else
		ft_usleep(rules, philo, 0, philo->n_meal);
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

void	destroy_mutex(t_philo *philos, t_rules *rules)
{
	int	i;

	i = 0;
	if (philos)
	{
		while (i < rules->n_philos)
		{
			if (pthread_mutex_destroy(&philos[i].fork.lock))
				error_thread(&philos[i], 1);
			memset(&philos[i], 0, sizeof(t_philo));
			i++;
		}
	}
	i = 0;
	while (i < N_MUTEX)
	{
		if (rules->lock[i])
		{
			if (pthread_mutex_destroy(&rules->lock[i]->lock))
				error_thread(NULL, 2);
			free(rules->lock[i]);
		}
		i++;
	}
	free(rules->lock);
}
