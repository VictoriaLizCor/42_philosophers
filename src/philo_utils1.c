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

void	lock_msg(t_philo *philo, t_philo *cal)
{
	philo->action++;
	if (philo->action == 1 && philo->to_lock)
	{
		philo_msg(philo, "has taken a fork", P_FORK, cal);
		philo->to_lock->action = 2;
		lock_msg(philo->to_lock, philo);
	}
	else if (philo->action == 2 && philo->to_lock)
	{
		philo_msg(philo, "is    EATING    ", P_EAT, cal);
		philo->t_meal = t_mu_s(philo->rules) - philo->rules->t_eat / 2;
	}
	else if (philo->action == 3)
	{
		philo_msg(philo, "is   SLEEPING   ", P_SLEEP, cal);
		philo->sleep = t_mu_s(philo->rules);
	}
	else if (philo->action == 4)
		philo_msg(philo, "is   THINKING   ", P_THINK, cal);
}
// philo->rules->t_sleep < t_mu_s(philo->rules) - philo->sleep)
// else if (philo->action == 4 && !philo->to_lock && !died) 
// && time_ms(philo) > philo->sleep + philo->rules->t_sleep

static void	action(t_philo *philo, t_rules *rules, t_philo *lock)
{
	lock_msg(philo, philo);
	if (lock)
	{
		if (philo->action == 2)
			ft_usleep(rules, philo, -1, 1);
		pthread_mutex_unlock(&lock->fork.lock); 
	}
	else
	{
		if (philo->action == 3)
		{
			if (philo->right)
				pthread_mutex_unlock(&philo->fork.lock);
			if (rules->t_sleep > t_mu_s(rules) - philo->sleep)
				ft_usleep(rules, philo, philo->sleep, rules->t_sleep);
		}
		else if (philo->action >= 4)
		{
			philo->action = 0;
			if (philo->right)
				pthread_mutex_unlock(&philo->fork.lock);
			else
				philo->action = 2;
		}
	}
}

static bool	check_locks(t_philo *philo, t_philo *right, t_philo *left)
{
	if (right)
	{
		pthread_mutex_lock(&philo->fork.lock);
		debug_thread_check(philo, "ACTION", 0);
		if (philo->action < 2)
		{
			pthread_mutex_lock(&right->fork.lock);
			right->lock_by = philo;
			philo->to_lock = right;
			action(philo, philo->rules, right);
			philo->to_lock = NULL;
			pthread_mutex_unlock(&philo->fork.lock);
			right->lock_by = NULL;
		}
		else
			action(philo, philo->rules, NULL);
	}
	else
	{
		debug_thread_check(philo, "CHECK", 0);
		action(philo, philo->rules, NULL);
	}
	return (died_msg(philo->rules, philo));
}

/*
if time_eat >= time_sleep
	
if time_eat < time_sleep

*/
static void	exe(t_philo *philo)
{
	t_rules	*rules;

	rules = philo->rules;
	wait_all(rules, philo, 0, (rules->n_philos * (rules->n_philos + 1) / 2));
	if (philo->id % 2 != philo->rules->pair && rules->n_philos > 1)
		philo->action = 0;
	else
		ft_usleep(rules, philo, 0, rules->t_aux + 1.5e3);
	while (1)
	{
		if (check_locks(philo, philo->right, philo->left))
			return ;
	}
}
// sum = t_mu_s(rules) / rules->t_aux;
// if (philo->id % 2 == philo->rules->pair != (sum) % 2 && 
// t_mu_s(rules) > sum * rules->t_eat && philo->right)
// {
// 	debug_thread_check(philo, "SLEEP", 1);
// 	died = ft_usleep(rules, philo, sum * rules->t_aux + 100, rules->t_aux);
// }
// if (t_mu_s(rules) > sum * rules->t_eat)
// {
// 	debug_thread_check(philo, "SLEEP", 1);
// 	died = ft_usleep(rules, philo, sum * 1e5, rules->t_eat);
// }

void	start_threads(t_philo *philos, t_rules *rules, int *rand_array)
{
	int			i;
	int			died;

	i = 0;
	fprintf(stderr, "eat[%lld] | sleep[%lld]\n", rules->t_eat, rules->t_sleep);
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
