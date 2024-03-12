/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 10:48:37 by lilizarr          #+#    #+#             */
/*   Updated: 2024/03/12 15:50:43 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	lock_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork.lock); 
	philo->fork.stat = true;
	pthread_mutex_unlock(&philo->fork.lock);
}

void	unlock_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork.lock); 
	philo->fork.stat = false;
	pthread_mutex_unlock(&philo->fork.lock);
}

bool	check_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork.lock); 
	if (philo->fork.stat == 1 || t_mu_s(philo->rules) < 10)
		return ((void)pthread_mutex_unlock(&philo->fork.lock), true);
	return ((void) pthread_mutex_unlock(&philo->fork.lock), false);
}

bool	check_action(t_philo *philo, char op, int val)
{
	bool		result;

	result = false;
	pthread_mutex_lock(&philo->fork.lock);
	if (op == '<')
		result = philo->action < val;
	else if (op == '>')
		result = philo->action > val;
	else if (op == '=')
		result = philo->action == val;
	return ((void)pthread_mutex_unlock(&philo->fork.lock), result);
}
