/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:29:47 by lilizarr          #+#    #+#             */
/*   Updated: 2023/12/07 10:10:47 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

bool	lock_msg( t_rules *rules, t_philo *philo, t_philo *cal, bool res)
{
	philo->action++;
	res = died_msg(philo->rules, philo);
	if (philo->action == 1 && philo->to_lock && !res)
	{
		res = philo_msg(philo, "has taken a fork", P_FORK, cal);
		if (philo->to_lock->action == 0)
		{
			philo->to_lock->action = 2;
			res = lock_msg(rules, philo->to_lock, philo, 0);
		}
	}
	else if (philo->action == 2 && philo->to_lock && !res)
	{
		res = philo_msg(philo, "is    EATING    ", P_EAT, cal);
		philo->t_meal = philo->time;
	}
	else if (philo->action == 3 && !philo->to_lock && !res)
	{
		res = philo_msg(philo, "is   SLEEPING   ", P_SLEEP, cal);
		philo->sleep = r_ms(rules);
	}
	else if (philo->action == 4 && !philo->to_lock && !res)
		res = philo_msg(philo, "is   THINKING   ", P_THINK, cal);
	return (died_msg(philo->rules, philo));
}
// else if (philo->action == 4 && !philo->to_lock && !res) \
&& time_ms(philo) > philo->sleep + philo->rules->t_sleep

static bool	actions(t_philo *philo, t_rules *rules, t_philo *lock, bool res)
{
	res = lock_msg(rules, philo, philo, 0);
	if (lock)
	{
		if (philo->action == 2)
			res = ft_usleep(rules, philo, 0, 2);
		pthread_mutex_unlock(&lock->fork.lock);
	}
	else
	{
		if (philo->action == 3)
		{
			if (philo->right)
				pthread_mutex_unlock(&philo->fork.lock);
			if (rules->t_sleep > philo->time - philo->sleep)
				res = ft_usleep(rules, philo, 0, 3);
			else
				lock_msg(rules, philo, philo, 0);
		}
		else if (philo->action >= 4)
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
	bool	res;

	res = 0;
	debug_thread_check(philo, "CHECK");
	if (!philo->right)
		res = actions(philo, philo->rules, NULL, 0);
	else
	{
		pthread_mutex_lock(&philo->fork.lock);
		if (philo->action < 2)
		{
			pthread_mutex_lock(&right->fork.lock);
			philo->to_lock = right;
			res = actions(philo, philo->rules, right, 0);
			philo->to_lock = NULL;
			pthread_mutex_unlock(&philo->fork.lock);
		}
		else
			res = actions(philo, philo->rules, NULL, 0);
	}
	return (res);
}

static void	exe(t_philo *philo)
{
	t_rules	*rules;
	int		sum;
	bool	res;

	rules = philo->rules;
	wait_all(rules, philo, 0, (rules->n_philos * (rules->n_philos + 1) / 2));
	philo->t_start = rules->t_start;
	if (!philo->right)
		philo->action = 2;
	sum = rules->t_eat + rules->t_sleep;
	if (philo->id % 2 == 0 && (rules->t_sleep / 2) < 100)
		usleep((rules->t_sleep / 2));
	if (philo->id % 2 == 0 && (rules->t_sleep / 2) > 100)
		usleep(100);
	while (1)
	{
		pthread_mutex_lock(&philo->fork.lock);
		if (odd_philo(philo) && !philo->action && philo->time % sum <= 100)
			philo->action = 2;
		pthread_mutex_unlock(&philo->fork.lock);
		if (!died_msg(rules, philo))
			res = check_locks(philo, philo->right, philo->left);
		if (res || died_msg(rules, philo))
			return ;
	}
}

void	start_threads(t_philo *philos, t_rules *rules, int *rand_array)
{
	int			i;
	int			res;

	i = 0;
	if (philos[rand_array[0]].left)
		rules->last = philos[rand_array[0]].left->id;
	else
		rules->last = 1;
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
