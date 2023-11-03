/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:39:04 by lilizarr          #+#    #+#             */
/*   Updated: 2023/11/03 16:53:01 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

bool	ft_usleep(t_rules *rules, t_philo *philo, long long time, int opt)
{
	t_philo	philo_tmp;

	// if (philo->right && opt == 3)
	// 	pthread_mutex_unlock(&philo->fork.lock);
	while (1)
	{
		if (died_msg(rules, philo))
			return (1);
		print_ft_usleep(philo, time, opt);
		if (opt == 2 && philo->to_lock)
		{
			philo_tmp = *philo->to_lock;
			if (died_msg(rules, &philo_tmp))
				return (1);
			else if (philo->time >= philo->t_meal + time)
			{
				// return (philo_lock_msg(philo, philo, 0));
				break ;
			}
		}
		else if (philo->time >= philo->sleep + time)
		{
			// return (philo_msg(philo, "is   THINKING   ", P_THINK));
			break ;
		}
		usleep(100);
	}
	return (0);
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
	fprintf(stderr, "\t\t\t\t\t[ALL ERASED]\n");
	if (pthread_mutex_destroy(&rules->lock_flags.lock))
		error_thread(&rules->lock_flags.stat, 2);
}

bool	philo_msg(t_philo *philo, char *msg, char *msg_color)
{
	int		i;
	bool	res;

	pthread_mutex_lock(&philo->msg.lock);
	res = 0;
	i = philo->id;
	if (!died_msg(philo->rules, philo))
		printf(" %lld\tphilo %s [%03d] %s %s %s %s\n", \
		philo->time, color(i), i, color(0), msg_color, msg, color(0));
	else
		res = 1;
	pthread_mutex_unlock(&philo->msg.lock);
	res = died_msg(philo->rules, philo);
	return (res);
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
// 		fprintf(stderr, "\t\t\t\t\t\t\t check[%d]{%d}\n", \
// 		philo->id, rules->lock_flags.philo_group);
// 		if (rules->lock_flags.philo_group < rules->n_philos)
// 			flag ++;
// 		pthread_mutex_unlock(&rules->lock_flags.lock);
// 	}
// }

bool	died_msg(t_rules *rules, t_philo *philo)
{
	bool		res;
	int			id;
	long long	death_time;

	res = 0;
	pthread_mutex_lock(&rules->lock_flags.lock);
	if (!rules->lock_flags.stat)
	{
		philo->time = current_time(rules->t_start);
		death_time = (philo->time - philo->t_meal);
		if (death_time > rules->t_die)
		{
			rules->lock_flags.stat = true;
			id = philo->id;
			printf(" %lld\tphilo %s [%03d] %s %s %s %s\n", \
			philo->time, color(id), id, color(0), \
			P_DEAD, "      DIED      ", color(0));
			philo->msg.stat = true;
			print_death_action(philo, rules, death_time);
			res = 1;
		}
	}
	else
		res = 1;
	pthread_mutex_unlock(&rules->lock_flags.lock);
	return (res);
}
