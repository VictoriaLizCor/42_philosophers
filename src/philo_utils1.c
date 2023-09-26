/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:29:47 by lilizarr          #+#    #+#             */
/*   Updated: 2023/09/26 12:29:33 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	start_threads(t_philo *philos, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (pthread_create(&philos[i].thread, NULL, \
		(void *)rutine, &philos[i]) != 0)
			error_thread(&philos[i], 0, errno);
		i++;
	}
	i = 0;
	while (i < size)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}

static void	take_eat(t_philo *philo, t_rules *rules, int i)
{
	printf(" %lld\tphilo %s [%03d] %s %s has taken a fork %s\n", \
	current_time(rules), color(i), i, color(0), P_FORK, color(0));
	printf(" %lld\tphilo %s [%03d] %s %s is    EATING     %s\n", \
	current_time(rules), color(i), i, color(0), P_EAT, color(0));
	philo->meal = current_time(rules);
	usleep(rules->t_eat * 1000);
}

static void	sleep_think(t_philo *philo, t_rules *rules, int i)
{
	if (philo->to_lock)
	{
		fprintf(stderr, "\t\t\t\t\t\t[%d][%d] unlock\n", philo->id, philo->id);
		pthread_mutex_unlock(&philo->fork);
		fprintf(stderr, "\t\t\t\t\t\t[%d][%d] unlock\n", philo->id, philo->to_lock->id);
		pthread_mutex_unlock(&philo->to_lock->fork);
		philo->to_lock->f_status = false;
	}
	printf(" %lld\tphilo %s [%03d] %s %s is   SLEEPING    %s\n", \
	current_time(rules), color(i), i, color(0), P_SLEEP, color(0));
	usleep(rules->t_sleep * 1000);
	printf(" %lld\tphilo %s [%03d] %s %s is   THINKING    %s\n", \
	current_time(rules), color(i), i, color(0), P_THINK, color(0));
	usleep(rules->t_sleep * 1000);
}

static void	check_locks(t_philo *philo, t_philo *right, t_philo *left)
{
	int	self_lock;
	int	right_lock;
	int	left_lock;

	if (philo->f_status || !right || !left)
		return ;
	self_lock = pthread_mutex_lock(&philo->fork);
	philo->f_status = true;
	fprintf(stderr, "\t\t\t\t[%d]_status = %d | [%d]_status  = %d | [%d]_status  = %d \n", \
	philo->id, philo->f_status, right->id, right->f_status, left->id, left->f_status);
	if (!philo->to_lock && !right->f_status)
	{
		right_lock = pthread_mutex_lock(&right->fork);
		right->f_status = true;
		fprintf(stderr, "\t\t\t\t\t[%d]_status = %d | [%d]_status  = %d | [%d]_status  = %d \n", \
		philo->id, philo->f_status, right->id, right->f_status, left->id, left->f_status);
		philo->to_lock = right;
	}
	else if (!philo->to_lock && !left->f_status)
	{
		left_lock = pthread_mutex_lock(&left->fork);
		left->f_status = true;
		fprintf(stderr, "\t\t\t\t\t\t[%d]_status = %d | [%d]_status  = %d | [%d]_status  = %d \n", \
philo->id, philo->f_status, right->id, right->f_status, left->id, left->f_status);
		if (!left_lock)
			philo->to_lock = left;
	}
}

void	rutine(t_philo *philo)
{
	t_rules	*rules;
	int		i;

	i = philo->id;
	rules = philo->d_rules;
	philo->to_lock = NULL;
	fprintf(stderr, "\t\t\t\t[%d]_status = %d\n", philo->id, philo->f_status);
	check_locks(philo, philo->right, philo->left);
	fprintf(stderr, "%p \n", philo->to_lock);
	if (philo->to_lock)
		take_eat(philo, rules, i);
	sleep_think(philo, rules, i);
	if (philo->meal + current_time(rules) > rules->t_die || !philo->to_lock)
	{
		printf(" %lld\tphilo %s [%03d] %s %s        DIED      %s\n", \
		current_time(rules), color(i), i, color(0), P_DEAD, color(0));
	}
}
