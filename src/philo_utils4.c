/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:48:37 by lilizarr          #+#    #+#             */
/*   Updated: 2024/03/15 13:00:06 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	lock_mutex(t_mutex *mutex)
{
	pthread_mutex_lock(&mutex->lock); 
	mutex->stat = true;
	pthread_mutex_unlock(&mutex->lock);
}

void	unlock_mutex(t_mutex *mutex)
{
	pthread_mutex_lock(&mutex->lock); 
	mutex->stat = false;
	pthread_mutex_unlock(&mutex->lock);
}

bool	check_mutex(t_mutex *mutex)
{
	pthread_mutex_lock(&mutex->lock);
	if (mutex->stat == 1)
		return ((void)pthread_mutex_unlock(&mutex->lock), true);
	return ((void) pthread_mutex_unlock(&mutex->lock), false);
}

bool	check_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork.lock); 
	if (philo->fork.stat == 1 || t_mu_s(philo->rules->t_start) < 10)
	{
		pthread_mutex_unlock(&philo->fork.lock);
		usleep(10);
		return (true);
	}
	return ((void) pthread_mutex_unlock(&philo->fork.lock), false);
}

bool	check_action(t_philo *philo, char op, int val)
{
	bool	result;

	result = false;
	pthread_mutex_lock(&philo->fork.lock);
	if (op == '<')
		result = philo->action < val;
	else if (op == '>')
		result = philo->action > val;
	else if (op == '=')
		result = philo->action == val;
	pthread_mutex_unlock(&philo->fork.lock);
	return (result);
}
