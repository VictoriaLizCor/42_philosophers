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

bool	lock_msg(t_philo *philo, t_philo *cal, bool died)
{
	philo->action++;
	died = died_msg(philo->rules, philo);
	if (philo->action == 1 && philo->to_lock && !died)
	{
		philo_msg(philo, "has taken a fork", P_FORK, cal);
		philo->to_lock->action = 2;
		lock_msg(philo->to_lock, philo, 0);
	}
	else if (philo->action == 2 && philo->to_lock && !died)
	{
		philo_msg(philo, "is    EATING    ", P_EAT, cal);
		philo->t_meal = t_mu_s(philo->rules);
	}
	else if (philo->action == 3 && !died)
	{
		philo_msg(philo, "is   SLEEPING   ", P_SLEEP, cal);
		philo->sleep = t_mu_s(philo->rules);
	}
	else if (philo->action == 4 && !died)
		philo_msg(philo, "is   THINKING   ", P_THINK, cal);
	return (died || died_msg(philo->rules, philo));
}
// philo->rules->t_sleep < t_mu_s(philo->rules) - philo->sleep)
// else if (philo->action == 4 && !philo->to_lock && !died) 
// && time_ms(philo) > philo->sleep + philo->rules->t_sleep

static bool	action(t_philo *philo, t_rules *rules, t_philo *lock, bool died)
{
	died = lock_msg(philo, philo, 0);
	if (lock)
	{
		if (philo->action == 2)
			died = ft_usleep(rules, philo, -1, 1);
		pthread_mutex_unlock(&lock->fork.lock); 
	}
	else
	{
		if (philo->action == 3)
		{
			if (philo->right)
				pthread_mutex_unlock(&philo->fork.lock);
			if (rules->t_sleep > t_mu_s(rules) - philo->sleep)
				died = ft_usleep(rules, philo, philo->sleep, rules->t_sleep);
		}
		if (philo->action >= 4)
		{
			philo->action = 0;
			if (philo->right)
				pthread_mutex_unlock(&philo->fork.lock);
		}
	}
	return (died || died_msg(philo->rules, philo));
}

static bool	check_locks(t_philo *philo, t_philo *right, t_philo *left)
{
	bool	died;

	died = died_msg(philo->rules, philo);
	if (philo->right)
	{
		pthread_mutex_lock(&philo->fork.lock);
		debug_thread_check(philo, "ACTION", 0);
		if (philo->action < 2)
		{
			pthread_mutex_lock(&right->fork.lock);
			right->lock_by = philo;
			philo->to_lock = right;
			died = action(philo, philo->rules, right, 0);
			philo->to_lock = NULL;
			pthread_mutex_unlock(&philo->fork.lock);
			right->lock_by = NULL;
		}
		else
			died = action(philo, philo->rules, NULL, 0);
	}
	else
	{
		debug_thread_check(philo, "CHECK", 0);
		died = action(philo, philo->rules, NULL, 0);
	}
	return (died);
}

static void	exe(t_philo *philo)
{
	t_rules	*rules;
	int		sum;
	bool	died;

	rules = philo->rules;
	wait_all(rules, philo, 0, (rules->n_philos * (rules->n_philos + 1) / 2));
	if (philo->id % 2 == philo->rules->pair && philo->rules->n_philos != 1)
		usleep(100);
	else
		philo->action = 0;
	while (1)
	{
		sum = t_mu_s(rules) / rules->t_eat;
		if ((philo->id % 2 == philo->rules->pair && (sum) % 2 == 0))
		{
			if (t_mu_s(rules) > sum * rules->t_eat)
			{
				debug_thread_check(philo, "SLEEP", 1);
				died = ft_usleep(rules, philo, sum * 1e5 + 100, rules->t_sleep);
			}
			died = check_locks(philo, philo->right, philo->left);
		}
		else
			died = check_locks(philo, philo->right, philo->left);
		if (died || died_msg(rules, philo))
			return ;
	}
}

void	start_threads(t_philo *philos, t_rules *rules, int *rand_array)
{
	int			i;
	int			died;

	i = 0;
	while (i < rules->n_philos)
	{
		died = pthread_create(&philos[rand_array[i]].thread, NULL, \
		(void *)exe, &philos[rand_array[i]]);
		if (died)
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

// fprintf(stderr, " t_eat[%lld] | t_sleep[%lld]\n", 
// rules->t_eat, rules->t_sleep);
