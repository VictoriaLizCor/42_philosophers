/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:29:47 by lilizarr          #+#    #+#             */
/*   Updated: 2023/09/25 17:45:32 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	start_threads(t_philo *philos, int size)
{
	int	i;

	i = size;
	while (i)
	{
		if (pthread_create(&philos[size - i].thread, NULL, \
		(void *)func, &philos[size - i]) != 0)
			error_thread(&philos[size - i], 0, errno);
		i--;
	}
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
	fprintf(stderr, "\t\t\t\t\t\t%d unlock = %d\n", philo->id, pthread_mutex_unlock(&philo->fork));
	fprintf(stderr, "\t\t\t\t\t\t%d unlock = %d\n", to_lock->id, pthread_mutex_unlock(&to_lock->fork));
}

static void	sleep_think(t_rules *rules, int i)
{
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

	if (!right && !left && !right->f_status && !left->f_status)
		return (NULL);
	fprintf(stderr, "%d \n", philo->f_status);
	self_lock = pthread_mutex_lock(&philo->fork);
	philo->f_status = true;
	fprintf(stderr, "\t\t\t\t\t\t[%d]_lock = %d | errno = %d\n", \
	philo->id, self_lock, errno);
	if (!self_lock && errno != EBUSY)
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
	fprintf(stderr, "%d \n", philo->f_status);
	to_lock = check_locks(philo, philo->right, philo->left);
	if (to_lock)
		take_eat(philo, rules, to_lock, i);
	sleep_think(rules, i);
	if (philo->meal + current_time(rules) > rules->t_die)
	{
		printf(" %lld\tphilo %s [%03d] %s %s        DIED      %s\n", \
		current_time(rules), color(i), i, color(0), P_DEAD, color(0));
	}
}
