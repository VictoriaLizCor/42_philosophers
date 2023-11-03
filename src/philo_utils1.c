/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:29:47 by lilizarr          #+#    #+#             */
/*   Updated: 2023/11/03 17:02:38 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

bool	philo_lock_msg(t_philo *philo, t_philo *caller, bool res)
{
	res = died_msg(philo->rules, philo);
	if (philo->action == 1 && philo->to_lock)
	{
		res = philo_msg(philo, "has taken a fork", P_FORK);
		if (philo->to_lock->action == 0)
		{
			philo->to_lock->action = 2;
			res = philo_msg(philo->to_lock, "is   SLEEPING   ", P_SLEEP);
		}
		// else
		// {
		// 	philo->to_lock->action = 0;
		// 	// res = philo_lock_msg(philo->to_lock, philo, 0);
		// 	// res = philo_msg(philo->to_lock, "is   THINKING   ", P_THINK);
		// }
	}
	else if (philo->action == 2 && philo->to_lock)
	{
		res = philo_msg(philo, "is    EATING    ", P_EAT);
		philo->t_meal = philo->time;
	}
	else if (philo->action == 3 && !philo->to_lock)
	{
		// res = philo_msg(philo, "is   SLEEPING   ", P_SLEEP);
		philo->sleep = philo->time;
	}
	else if (philo->action == 4 && !philo->to_lock)
	{
		philo->action = 0;
		res = philo_msg(philo, "is   THINKING   ", P_THINK);
	}
	print_action(philo, caller);
	return (res);
}

static bool	philo_actions(t_philo *philo, t_rules *rules, t_philo *lock, bool res)
{
	philo->action++;
	res = philo_lock_msg(philo, philo, 0);
	if (lock)
	{
		debug_thread_check(philo, " 1 | 2");
		if (philo->action == 2)
			res = ft_usleep(rules, philo, rules->t_eat, 2);
		pthread_mutex_unlock(&lock->fork.lock);
	}
	else
	{
		if (philo->right)
			pthread_mutex_unlock(&philo->fork.lock);
		// pthread_mutex_unlock(&philo->fork.lock);
		debug_thread_check(philo, " 3 | 4");
		if (philo->time - philo->sleep < rules->t_sleep)
		{
			res = philo_msg(philo, "is   SLEEPING   ", P_SLEEP);
			res = ft_usleep(rules, philo, rules->t_sleep, 3);
		}
		// else
		// 	res = philo_msg(philo, "is   THINKING   ", P_THINK);
		// else if (philo->action == 4)
		// {
		// 	philo->action = 0;
		// 	if (philo->right)
		// 		pthread_mutex_unlock(&philo->fork.lock);
		// }
	}
	return (res);
}

static bool	check_locks(t_philo *philo, t_philo *right, t_philo *left)
{
	bool	res;

	if (!philo->right)
		res = philo_actions(philo, philo->rules, NULL, 0);
	else
	{
		pthread_mutex_lock(&philo->fork.lock);
		if (philo->action == 0 || philo->action == 1)
		{
			pthread_mutex_lock(&right->fork.lock);
			philo->to_lock = right;
			res = philo_actions(philo, philo->rules, right, 0);
			philo->to_lock = NULL;
			pthread_mutex_unlock(&philo->fork.lock);
		}
		else
			res = philo_actions(philo, philo->rules, NULL, 0);
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
	while (!died_msg(rules, philo))
	{
		pthread_mutex_lock(&philo->fork.lock);
		if (philo->id == rules->last && rules->n_philos > 2 && \
			philo->id % 2 == 1 && \
			philo->action == 0 && philo->time % sum_eat_sleep <= 100 && \
			1)
		{
			philo->action = 2;
			// res = philo_msg(philo, "is   SLEEPING   ", P_SLEEP);
		}
		pthread_mutex_unlock(&philo->fork.lock);
		res = check_locks(philo, philo->right, philo->left);
		if (res)
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
