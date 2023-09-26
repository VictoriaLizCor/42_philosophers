/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:29:47 by lilizarr          #+#    #+#             */
/*   Updated: 2023/09/26 10:38:19 by lilizarr         ###   ########.fr       */
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
		(void *)func, &philos[i]) != 0)
			error_thread(&philos[i], 0, errno);
		i++;
	}
	i = 0;
	while (i < size)
	{
		pthread_join(philos[i].thread, (void **)&philos[i].status);
		i++;
	}
}

static void	take_eat(t_philo *philo, t_rules *rules, t_philo *to_lock, int i)
{
	printf(" %lld\tphilo %s [%03d] %s %s has taken a fork %s\n", \
	current_time(rules), color(i), i, color(0), P_FORK, color(0));
	printf(" %lld\tphilo %s [%03d] %s %s is    EATING     %s\n", \
	current_time(rules), color(i), i, color(0), P_EAT, color(0));
	philo->meal = current_time(rules);
	usleep(rules->t_eat * 1000);
}

static void	sleep_think(t_philo *philo, t_rules *rules, t_philo *to_lock, int i)
{
	if (to_lock)
	{
		fprintf(stderr, "\t\t\t\t\t\t%d unlock = %d\n", philo->id, pthread_mutex_unlock(&philo->fork));
		fprintf(stderr, "\t\t\t\t\t\t%d unlock = %d\n", to_lock->id, pthread_mutex_unlock(&to_lock->fork));
	}
	printf(" %lld\tphilo %s [%03d] %s %s is   SLEEPING    %s\n", \
	current_time(rules), color(i), i, color(0), P_SLEEP, color(0));
	usleep(rules->t_sleep * 1000);
	printf(" %lld\tphilo %s [%03d] %s %s is   THINKING    %s\n", \
	current_time(rules), color(i), i, color(0), P_THINK, color(0));
	usleep(rules->t_sleep * 1000);
}

static t_philo	*check_locks(t_philo *philo, t_philo *right, t_philo *left)
{
	int	self_lock;
	int	right_lock;
	int	left_lock;

	if (!right && !left)
		return (NULL);
	self_lock = pthread_mutex_lock(&philo->fork);
	philo->f_status = true;
	fprintf(stderr, "\t\t\t\t\t\t[%d]_lock = %d | errno = %d | lock=%d\n", \
	philo->id, self_lock, errno, philo->fork);
	if (!self_lock && errno != EBUSY && philo->f_status)
	{
		right_lock = pthread_mutex_lock(&right->fork);
		right->f_status = true;
		fprintf(stderr, "\t\t\t\t\t\tright_lock = %d | errno = %d\n", right_lock, errno);
		if (!right_lock && errno != EBUSY)
			return (right);
		else
		{
			left_lock = pthread_mutex_lock(&left->fork);
			left->f_status = true;
			fprintf(stderr, "\t\t\t\t\t\tleft_lock = %d | errno = %d\n", left_lock, errno);
			if (!left_lock && errno != EBUSY)
				return (left);
		}
	}
	return (NULL);
}

void	func(t_philo *philo)
{
	t_rules	*rules;
	int		i;
	t_philo	*to_lock;

	i = philo->id;
	rules = philo->d_rules;
	to_lock = check_locks(philo, philo->right, philo->left);
	fprintf(stderr, "%p \n", to_lock);
	if (to_lock)
		take_eat(philo, rules, to_lock, i);
	sleep_think(philo, rules, to_lock, i);
	if (philo->meal + current_time(rules) > rules->t_die)
	{
		printf(" %lld\tphilo %s [%03d] %s %s        DIED      %s\n", \
		current_time(rules), color(i), i, color(0), P_DEAD, color(0));
	}
}
