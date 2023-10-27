/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:29:47 by lilizarr          #+#    #+#             */
/*   Updated: 2023/10/27 12:12:07 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static bool	philo_lock_msg(t_philo *philo, t_philo *caller)
{
	bool	res;

	res = 0;
	if (died_msg(philo->d_rules, philo) != 1)
	{
		/* DELETE */
		if (philo->action >= 0 && philo->action <= 4)
		{
			pthread_mutex_lock(&philo->msg.lock);
			if (philo->to_lock)
				fprintf(stderr, " %lld \t\t\t\t\t\t[%d][%d]{%d} ==> last_meal[%lld]  last_sleep[%lld]\n", \
				current_time(philo->d_rules->t_start), philo->id, caller->id, philo->action, philo->t_meal, philo->t_sleep);
			else
				fprintf(stderr, " %lld \t\t\t\t\t\t[%d][%d]{%d} ==> last_meal[%lld]  last_sleep[%lld]\n", \
				current_time(philo->d_rules->t_start), caller->id, philo->id, philo->action, philo->t_meal, philo->t_sleep);
			pthread_mutex_unlock(&philo->msg.lock);
		}
		/*/////////*/
		if (philo->action == 1 && philo->to_lock)
			philo_msg(philo, "has taken a fork", P_FORK);
		else if (philo->action == 2 && philo->to_lock)
			philo_msg(philo, "is    EATING    ", P_EAT);
		else if (philo->action == 3)
		{
			philo_msg(philo, "is   SLEEPING   ", P_SLEEP);
			philo->t_sleep = philo->time;
		}
		else if (philo->action == 4)
			philo_msg(philo, "is   THINKING   ", P_THINK);
	}
	else
		res = 1;
	return (res);
}

static bool	philo_actions(t_philo *philo, t_rules *rules, t_philo *lock)
{
	bool	res;

	res = philo_lock_msg(philo, philo);
	if (!res)
	{
		if (lock)
		{
			pthread_mutex_lock(&lock->fork.lock);
			if (philo->action == 1 && lock->action == 0)
			{
				lock->action = 3;
				res = philo_lock_msg(lock, philo);
			}
			else if (philo->action == 2 && !res)
			{
				philo->t_meal = philo->time;
				res = ft_usleep(rules, philo, rules->t_eat);
			}
			pthread_mutex_unlock(&lock->fork.lock);
		}
		else
		{
			if (philo->action == 3)
			{
				if (philo->right)
					pthread_mutex_unlock(&philo->fork.lock);
				if (philo->time - philo->t_sleep < rules->t_sleep + 3)
					res = ft_usleep(rules, philo, rules->t_sleep);
			}
			else if (philo->action == 4)
			{
				philo->action = 0;
				if (philo->right)
					pthread_mutex_unlock(&philo->fork.lock);
			}
		}
	}
	else
		res = 0;
	return (res);
}

static bool	check_locks(t_philo *philo, t_philo *right, t_philo *left)
{
	int	res;

	if (!philo->right)
	{
		philo->action++;
		res = philo_actions(philo, philo->d_rules, NULL);
	}
	else
	{
		res = 0;
		pthread_mutex_lock(&philo->fork.lock);
		philo->action++;
		fprintf(stderr, " %lld\t\t\t\t\t\t[%d]{%d}\n", \
		current_time(philo->d_rules->t_start), philo->id, philo->action);
		if (philo->action == 1 || philo->action == 2)
		{
			philo->to_lock = right;
			res = philo_actions(philo, philo->d_rules, philo->to_lock);
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
	t_philo	*philos;
	t_rules	*rules;
	int		i;
	int		res;

	rules = philo->d_rules;
	i = 0;
	while (1)
	{
		res = check_locks(philo, philo->right, philo->left);
		if (res || died_msg(rules, philo))
		{
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
			error_thread(&philos[rand_array[i]], 0, errno);
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
