/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:29:47 by lilizarr          #+#    #+#             */
/*   Updated: 2023/10/09 17:34:04 by lilizarr         ###   ########.fr       */
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
	if (rules->death_flag.stat)
		return ;
	printf(" %lld\tphilo %s [%03d] %s %s has taken a fork %s\n", \
	current_time(rules), color(i), i, color(0), P_FORK, color(0));
	printf(" %lld\tphilo %s [%03d] %s %s is    EATING     %s\n", \
	current_time(rules), color(i), i, color(0), P_EAT, color(0));
	philo->t_meal = current_time(rules) + (rules->t_eat / 2);
	usleep(rules->t_eat * 1000);
}

static void	sleep_think(t_philo *philo, t_rules *rules, int i)
{
	if (philo->to_lock)
	{
		philo->fork.stat = false;
		pthread_mutex_unlock(&philo->fork.lock);
		fprintf(stderr, "\t\t\t\t\t[%d][%d] unlock\n", philo->id, philo->id);
		philo->to_lock->fork.stat = false;
		pthread_mutex_unlock(&philo->to_lock->fork.lock);
		fprintf(stderr, "\t\t\t\t\t[%d][%d] unlock\n", philo->id, philo->to_lock->id);
		philo->to_lock = NULL;
	}
	if (!rules->death_flag.stat)
	{
		printf(" %lld\tphilo %s [%03d] %s %s is   SLEEPING    %s\n", \
		current_time(rules), color(i), i, color(0), P_SLEEP, color(0));
		usleep(rules->t_sleep * 1000);
		printf(" %lld\tphilo %s [%03d] %s %s is   THINKING    %s\n", \
		current_time(rules), color(i), i, color(0), P_THINK, color(0));
		usleep(rules->t_sleep * 1000);
	}
}

static void	check_locks(t_philo *philo, t_philo *right, t_philo *left)
{
	if (!philo->fork.stat && !philo->d_rules->death_flag.stat)
	{
		pthread_mutex_lock(&philo->fork.lock);
		philo->fork.stat = true;
		if (philo->fork.stat && !philo->to_lock && !right->fork.stat)
		{
			pthread_mutex_lock(&right->fork.lock);
			right->fork.stat = true;
			fprintf(stderr, "\t\tright\t\t\t[%d]_status = %d | [%d]_status  = %d | [%d]_status  = %d \n", \
			philo->id, philo->fork.stat, right->id, right->fork.stat, left->id, left->fork.stat);
			philo->to_lock = right;
		}
		else if (philo->fork.stat && !philo->to_lock && !left->fork.stat)
		{
			pthread_mutex_lock(&left->fork.lock);
			left->fork.stat = true;
			fprintf(stderr, "\t\tleft\t\t[%d]_status = %d | [%d]_status  = %d | [%d]_status  = %d \n", \
			philo->id, philo->fork.stat, right->id, right->fork.stat, left->id, left->fork.stat);
			philo->to_lock = left;
		}
	}
}

void	rutine(t_philo *philo)
{
	t_rules	*rules;

	rules = philo->d_rules;
	while (1)
	{
		if ((current_time(rules) - philo->t_meal) >= rules->t_die)
		{
			died_msg(philo, philo->id);
			return ;
		}
		else
		{
			philo->to_lock = NULL;
			if (philo->right && philo->left)
				check_locks(philo, philo->right, philo->left);
			if (philo->to_lock)
				take_eat(philo, rules, philo->id);
			sleep_think(philo, rules, philo->id);
		}
	}
}
