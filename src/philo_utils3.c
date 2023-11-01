/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:39:04 by lilizarr          #+#    #+#             */
/*   Updated: 2023/11/01 16:50:46 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

bool	ft_usleep(t_rules *rules, t_philo *philo, long long time, int opt)
{
	int	i;

	i = 0;
	time *= 10;
	if (philo->right && opt == 3)
		pthread_mutex_unlock(&philo->fork.lock);
	if (philo->time - philo->t_sleep > rules->t_sleep && opt == 3)
		return (0);
	while (i <= (time))
	{
		if (died_msg(rules, philo))
		{
			fprintf(stderr, " %lld\t\t\t\t[%d]FT_USLEEP{%d}\n", \
	current_time(philo->d_rules->t_start), philo->id, opt);
			return (1);
		}
		if (i == time - 1 && opt == 2)
			fprintf(stderr, " %lld\t\t\t\t[%d]DONE eating\n", \
			current_time(philo->d_rules->t_start), philo->id);
		if (philo->to_lock && died_msg(rules, philo->to_lock))
			return (1);
		usleep(76);
		i++;
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
	if (!philo->msg.stat && !died_msg(philo->d_rules, philo))
		printf(" %lld\tphilo %s [%03d] %s %s %s %s\n", \
		philo->time, color(i), i, color(0), msg_color, msg, color(0));
	else
		res = 1;
	pthread_mutex_unlock(&philo->msg.lock);
	res = died_msg(philo->d_rules, philo);
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
