/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:39:04 by lilizarr          #+#    #+#             */
/*   Updated: 2023/12/07 10:13:41 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

bool	ft_usleep(t_rules *rules, t_philo *philo, bool	tmp, int opt)
{
	while (1)
	{
		if (died_msg(rules, philo))
			return (1);
		print_ft_usleep(philo, opt);
		if (opt == 2 && philo->to_lock)
		{
			if (died_msg(rules, philo->to_lock))
				return (1);
			else if (current_time(rules) > \
			philo->to_lock->sleep + rules->t_sleep)
			{
				tmp = 1;
				philo_lock_msg(philo->to_lock, philo, 0);
				philo->to_lock->action = 2;
				philo_lock_msg(philo->to_lock, philo, 0);
			}
			else if (current_time(rules) >= philo->t_meal + rules->t_eat)
				return (died_msg(rules, philo));
		}
		else if (philo->g_time(rules) > (philo->sleep + rules->t_sleep))
			return (died_msg(rules, philo));
		usleep(50);
	}
}

bool	philo_msg(t_philo *philo, char *msg, char *msg_color, t_philo *cal)
{
	int			i;

	pthread_mutex_lock(&philo->rules->lock_msg.lock);
	print_action(philo, cal);
	i = philo->id;
	if (!died_msg(philo->rules, philo))
	{
		philo->time = current_time(philo->rules);
		printf(" %ld\tphilo %s [%03d] %s %s %s %s\n", \
		philo->time, color(i), i, color(0), msg_color, msg, color(0));
	}
	pthread_mutex_unlock(&philo->rules->lock_msg.lock);
	return (died_msg(philo->rules, philo));
}

bool	died_msg(t_rules *rules, t_philo *philo)
{
	bool	res;
	long	death;
	long	time;

	res = 0;
	pthread_mutex_lock(&rules->lock_flags.lock);
	if (!rules->lock_flags.stat)
	{
		time = current_time(philo->rules);
		death = (time - philo->t_meal);
		if (death >= rules->t_die)
		{
			printf(" %ld\tphilo %s [%03d] %s %s %s %s\n", \
			time, color(philo->id), philo->id, color(0), \
			P_DEAD, "      DIED      ", color(0));
			debug_death(philo, rules, time, death);
			rules->lock_flags.stat = 1;
			res = 1;
		}
	}
	else
		res = 1;
	pthread_mutex_unlock(&rules->lock_flags.lock);
	return (res);
}

void	destroy_mutex(t_philo *philos, t_rules *rules)
{
	int	i;

	i = 0;
	if (philos)
	{
		while (i < rules->n_philos)
		{
			if (pthread_mutex_destroy(&philos[i].fork.lock))
				error_thread(&philos[i], 1);
			ft_memset(&philos[i], 0, sizeof(t_philo));
			i++;
		}
	}
	if (pthread_mutex_destroy(&rules->lock_flags.lock))
		error_thread(&rules->lock_flags.stat, 2);
	if (pthread_mutex_destroy(&rules->lock_time.lock))
		error_thread(&rules->lock_time.stat, 2);
	if (pthread_mutex_destroy(&rules->lock_msg.lock))
		error_thread(&rules->lock_msg.stat, 2);
	if (pthread_mutex_destroy(&rules->lock_count.lock))
		error_thread(&rules->lock_msg.stat, 2);
}

void	wait_all(t_rules *rules, t_philo *philo, bool tmp, long size)
{
	static long		sum;
	struct timeval	t;

	while (1)
	{
		pthread_mutex_lock(&rules->lock_count.lock);
		if (!tmp)
		{
			tmp = 1;
			sum += philo->id;
		}
		if (sum == size)
		{
			if (!rules->lock_count.stat)
			{
				rules->t_start = (get_time().tv_usec) / 1000;
				rules->lock_count.stat = 1;
			}
			else
				break ;
		}
		pthread_mutex_unlock(&rules->lock_count.lock);
	}
	pthread_mutex_unlock(&rules->lock_count.lock);
}
