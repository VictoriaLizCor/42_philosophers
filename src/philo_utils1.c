/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:29:47 by lilizarr          #+#    #+#             */
/*   Updated: 2023/10/16 16:56:50 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	take_eat(t_philo *philo, t_rules *rules, int i)
{
	if (died_msg(rules, philo, philo->id) == 1)
		return ;
	printf(" %lld\tphilo %s [%03d] %s %s has taken a fork %s\n", \
	current_time(rules), color(i), i, color(0), P_FORK, color(0));
	if (died_msg(rules, philo, philo->id) == 1)
		return ;
	printf(" %lld\tphilo %s [%03d] %s %s is    EATING     %s\n", \
	current_time(rules), color(i), i, color(0), P_EAT, color(0));
	philo->t_meal = current_time(rules);
	fprintf(stderr, "\t\t\t\t\t\t\t\t\t[%d] ==> %lld| %lld \t\n", \
	philo->id, philo->t_meal, rules->t_die);
	usleep(rules->t_eat * 1000);
}

static void	sleep_think(t_philo *philo, t_rules *rules, int i)
{
	if (died_msg(rules, philo, philo->id) == 1)
		return ;
	printf(" %lld\tphilo %s [%03d] %s %s is   SLEEPING    %s\n", \
	current_time(rules), color(i), i, color(0), P_SLEEP, color(0));
	usleep(rules->t_sleep * 1000);
	if (died_msg(rules, philo, philo->id) == 1)
		return ;
	printf(" %lld\tphilo %s [%03d] %s %s is   THINKING    %s\n", \
	current_time(rules), color(i), i, color(0), P_THINK, color(0));
	usleep(rules->t_sleep * 1000);
}

static void	check_locks(t_philo *philo, t_philo *right, t_philo *left)
{
	pthread_mutex_lock(&philo->fork.lock);
	if (!philo->fork.stat)
	{
		philo->fork.stat = true;
		if (!philo->to_lock && right && left)
		{
			pthread_mutex_lock(&right->fork.lock);
			if (!right->fork.stat)
			{
				right->fork.stat = true;
				philo->to_lock = right;
			}
			else
			{
				pthread_mutex_lock(&left->fork.lock);
				if (!left->fork.stat)
				{
					left->fork.stat = true;
					philo->to_lock = left;
				}
			}
		}
	}
}

static void	exe(t_philo *philo)
{
	t_rules	*rules;

	rules = philo->d_rules;
	while (1)
	{
		if (died_msg(rules, philo, philo->id))
			return ;
		philo->to_lock = NULL;
		check_locks(philo, philo->right, philo->left);
		if (philo->to_lock)
		{
			take_eat(philo, rules, philo->id);
			philo->to_lock->fork.stat = false;
			pthread_mutex_unlock(&philo->to_lock->fork.lock);
			fprintf(stderr, "\t\t\t\t\t %s[%d][%d] unlock%s\n", color(philo->id), philo->id, philo->id, color(0));
			fprintf(stderr, "\t\t\t\t\t %s[%d][%d] unlock%s\n", color(philo->id), philo->id, philo->to_lock->id, color(0));
		}
		philo->fork.stat = false;
		pthread_mutex_unlock(&philo->fork.lock);
		sleep_think(philo, rules, philo->id);
	}
}

void	start_threads(t_philo *philos, int size)
{
	int	i;
	int	res;

	i = 0;
	while (i < size)
	{
		res = pthread_create(&philos[i].thread, NULL, \
		(void *)exe, &philos[i]);
		if (res)
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
