/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:29:47 by lilizarr          #+#    #+#             */
/*   Updated: 2023/11/08 16:48:29 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

bool	philo_lock_msg(t_philo *philo, t_philo *caller, bool res, bool opt)
{
	philo->action++;
	print_action(philo, caller);
	if (philo->action == 1 && philo->to_lock)
	{
		res = philo_msg(philo, "has taken a fork", P_FORK, opt);
		if (philo->to_lock->action == 0)
		{
			philo->to_lock->action = 2;
			res = philo_lock_msg(philo->to_lock, philo, 0, 1);
		}
	}
	else if (philo->action == 2 && philo->to_lock)
	{
		res = philo_msg(philo, "is    EATING    ", P_EAT, opt);
		philo->t_meal = philo->time;
	}
	else if (philo->action == 3)
	{
		res = philo_msg(philo, "is   SLEEPING   ", P_SLEEP, opt);
		philo->sleep = philo->time;
	}
	else if (philo->action == 4)
	{
		philo->action = 0;
		res = philo_msg(philo, "is   THINKING   ", P_THINK, opt);
	}
	return (res);
}

static bool	actions(t_philo *philo, t_rules *rules, t_philo *lock, bool res)
{
	debug_thread_check(philo, " actions");
	res = philo_lock_msg(philo, philo, 0, 0);
	if (lock)
	{
		if (philo->action == 2)
			res = ft_usleep(rules, philo, rules->t_eat, 2);
		pthread_mutex_unlock(&lock->fork.lock);
	}
	else
	{
		if (philo->right)
			pthread_mutex_unlock(&philo->fork.lock);
		if (philo->action == 3 && philo->time - philo->sleep < rules->t_sleep)
		{
			// if (philo->right)
			// 	pthread_mutex_unlock(&philo->fork.lock);
			res = ft_usleep(rules, philo, rules->t_sleep, 3);
		}
		// if (philo->action == 4)
		// {
		// 	if (philo->right)
		// 		pthread_mutex_unlock(&philo->fork.lock);
		// }
	}
	return (res);
}

static bool	check_locks(t_philo *philo, t_philo *right, t_philo *left)
{
	bool	res;

	res = false;
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
	int		sum_eat_sleep;
	int		res;

	rules = philo->rules;
	sum_eat_sleep = rules->t_eat + rules->t_sleep;
	while (1)
	{
		pthread_mutex_lock(&philo->fork.lock);
		if (philo->id == rules->last && rules->n_philos > 2 && \
			philo->id % 2 == 1 && \
			philo->action == 0 && philo->time % sum_eat_sleep <= 100 && \
			1)
			philo->action = 2;
		pthread_mutex_unlock(&philo->fork.lock);
		if (philo->id != 1)
			usleep(10);
		res = check_locks(philo, philo->right, philo->left);
		if (res || died_msg(rules, philo))
		{
			debug_thread_check(philo, " EXIT");
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
	if (philos[rand_array[0]].left)
		rules->last = philos[rand_array[0]].left->id;
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
