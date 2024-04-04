/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:48:37 by lilizarr          #+#    #+#             */
/*   Updated: 2024/04/04 13:09:24 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	lock_mutex(t_mutex *mutex, bool stat)
{
	pthread_mutex_lock(&mutex->lock);
	mutex->stat = stat;
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
	if (philo->fork.stat == 1)
		return ((void)pthread_mutex_unlock(&philo->fork.lock), true);
	return ((void)pthread_mutex_unlock(&philo->fork.lock), false);
}

bool	check_value(t_philo *philo, int *val1, char op, int val2)
{
	bool	result;

	result = false;
	pthread_mutex_lock(&philo->fork.lock);
	if (op == '<')
		result = *val1 < val2;
	else if (op == '>')
		result = *val1 > val2;
	else if (op == '=')
		result = *val1 == val2;
	pthread_mutex_unlock(&philo->fork.lock);
	return (result);
}
