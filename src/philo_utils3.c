/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:39:04 by lilizarr          #+#    #+#             */
/*   Updated: 2023/11/09 15:45:52 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

bool	ft_usleep(t_rules *rules, t_philo *philo, long long time, int opt)
{
	t_philo	*lock;
	bool	tmp;

	tmp = 0;
	while (1)
	{
		if (died_msg(rules, philo))
			return (1);
		print_ft_usleep(philo, time, opt);
		if (opt == 2 && philo->to_lock)
		{
			lock = philo->to_lock;
			if (died_msg(rules, lock))
				return (1);
			else if (odd_philo(philo) && !tmp && \
			current_time(rules) == lock->sleep + rules->t_sleep)
			{
				tmp = 1;
				philo_lock_msg(philo->to_lock, philo, 0, 1);
				philo->to_lock->action = 2;
				philo_lock_msg(philo->to_lock, philo, 0, 1);
			}
			else if (current_time(rules) >= philo->t_meal + time)
				return (0);
		}
		else if (current_time(rules) > philo->sleep + time)
			return (0);
		usleep(100);
	}
}

bool	philo_msg(t_philo *philo, char *msg, char *msg_color, bool opt)
{
	int			i;
	bool		res;

	pthread_mutex_lock(&philo->msg.lock);
	res = 0; 
	i = philo->id;
	philo->time = current_time(philo->rules);
	if (!died_msg(philo->rules, philo))
		printf(" %lld\tphilo %s [%03d] %s %s %s %s\n", \
		philo->time, color(i), i, color(0), msg_color, msg, color(0));
	else
		res = 1;
	pthread_mutex_unlock(&philo->msg.lock);
	return (res);
}

bool	died_msg(t_rules *rules, t_philo *philo)
{
	bool		res;
	long long	death_time;
	long long	time;

	res = 0;
	pthread_mutex_lock(&rules->lock_flags.lock);
	if (!rules->lock_flags.stat)
	{
		time = current_time(philo->rules);
		death_time = (time - philo->t_meal);
		if (death_time > rules->t_die)
		{
			rules->lock_flags.stat = 1;
			printf(" %lld\tphilo %s [%03d] %s %s %s %s\n", \
			time, color(philo->id), philo->id, color(0), \
			P_DEAD, "      DIED      ", color(0));
			print_death_action(philo, rules, death_time);
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
			if (pthread_mutex_destroy(&philos[i].msg.lock))
				error_thread(&philos[i], 1);
			ft_memset(&philos[i], 0, sizeof(t_philo));
			i++;
		}
	}
	if (pthread_mutex_destroy(&rules->lock_flags.lock))
		error_thread(&rules->lock_flags.stat, 2);
	if (pthread_mutex_destroy(&rules->lock_time.lock))
		error_thread(&rules->lock_time.stat, 2);
}

// void	wait_all_philos(t_rules *rules, t_philo *philo)
// {
// 	static int		flag;
// 	struct timeval	start;

// 	{
// 		pthread_mutex_lock(&rules->lock_flags.lock);
// 		if (!rules->lock_flags.philo_group)
// 		{
// 			gettimeofday(&start, NULL);
// 			rules->t_start = (start.tv_sec * 1000) + (start.tv_usec / 1000);
// 		}
// 		rules->lock_flags.philo_group++;
// 		fprintf(stderr, "\t\t\t\t\t\t\t check[%d]{%d}\n", 
// 		philo->id, rules->lock_flags.philo_group);
// 		if (rules->lock_flags.philo_group < rules->n_philos)
// 			flag ++;
// 		pthread_mutex_unlock(&rules->lock_flags.lock);
// 	}
// }