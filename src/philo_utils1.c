/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:29:47 by lilizarr          #+#    #+#             */
/*   Updated: 2023/11/01 16:50:42 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static bool	philo_lock_msg(t_philo *philo, t_philo *caller)
{
	bool	res;

	res = died_msg(philo->d_rules, philo);
	if (philo->action == 1 && philo->to_lock)
	{
		res = philo_msg(philo, "has taken a fork", P_FORK);
		if (philo->to_lock->action == 0)
		{
			philo->to_lock->action = 3;
			res = philo_lock_msg(philo->to_lock, philo);
		}
	}
	else if (philo->action == 2 && philo->to_lock)
		res = philo_msg(philo, "is    EATING    ", P_EAT);
	else if (philo->action == 3 && !philo->to_lock)
	{
		res = philo_msg(philo, "is   SLEEPING   ", P_SLEEP);
		philo->t_sleep = philo->time ;
	}
	else if (philo->action == 4 && !philo->to_lock)
	{
		res = philo_msg(philo, "is   THINKING   ", P_THINK);
	}
	print_action(philo, caller);
	return (res);
}

static bool	philo_actions(t_philo *philo, t_rules *rules, t_philo *lock)
{
	bool	res;

	philo->action++;
	res = philo_lock_msg(philo, philo);
	if (lock)
	{
		if (philo->action == 2)
		{
			philo->t_meal = philo->time + 1;
			res = ft_usleep(rules, philo, rules->t_eat, 2);
		}
		pthread_mutex_unlock(&lock->fork.lock);
	}
	else
	{
		if (philo->action == 3)
			res = ft_usleep(rules, philo, rules->t_sleep, 3);
		else if (philo->action == 4)
		{
			philo->action = 0;
			if (philo->right)
				pthread_mutex_unlock(&philo->fork.lock);
		}
	}
	return (res);
}

static bool	check_locks(t_philo *philo, t_philo *right, t_philo *left)
{
	int	res;

	if (!philo->right)
		res = philo_actions(philo, philo->d_rules, NULL);
	else
	{
		pthread_mutex_lock(&philo->fork.lock);
		fprintf(stderr, " %lld\t\t\t\t\t\t\t\t\t\t\t\tCHECK [%d]{%d}\n", \
		current_time(philo->d_rules->t_start), philo->id, philo->action);
		if (philo->action == 0 || philo->action == 1)
		{
			pthread_mutex_lock(&right->fork.lock);
			philo->to_lock = right;
			res = philo_actions(philo, philo->d_rules, right);
			philo->to_lock = NULL;
			pthread_mutex_unlock(&philo->fork.lock);
		}
		else
			res = philo_actions(philo, philo->d_rules, NULL);
	}
	return (res);
}

static void	exe(t_philo *philo)
{
	t_rules	*rules;
	int		i;
	int		res;

	rules = philo->d_rules;
	i = 0;
	pthread_mutex_lock(&philo->fork.lock);
	if (philo->id == rules->n_philos && rules->n_philos % 2 == 1 && \
		rules->n_philos > 2)
		philo->action = 2;
	pthread_mutex_unlock(&philo->fork.lock);
	while (1)
	{
		res = check_locks(philo, philo->right, philo->left);
		if (res || died_msg(rules, philo))
		{
			fprintf(stderr, " %lld\t[%d]{%d}\tEXIT\n", \
			current_time(philo->d_rules->t_start), philo->id, philo->action);
			return ;
		}
	}
}

void	start_threads(t_philo *philos, t_rules *rules, int *rand_array)
{
	int				i;
	int				res;
	struct timeval	start;

	i = 0;
	gettimeofday(&start, NULL);
	rules->t_start = ((start.tv_sec * 1000) + (start.tv_usec / 1000));
	while (i < rules->n_philos)
	{
		res = pthread_create(&philos[rand_array[i]].thread, NULL, \
		(void *)exe, &philos[rand_array[i]]);
		if (res)
			error_thread(&philos[rand_array[i]], 0);
		i++;
	}
	i = 0;
	while (i < rules->n_philos)
	{
		if (pthread_join(philos[rand_array[i]].thread, NULL))
			return ;
		i++;
	}
}
