/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:39:04 by lilizarr          #+#    #+#             */
/*   Updated: 2023/10/20 11:00:29 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	destroy_mutex(t_philo *philos, t_rules *rules)
{
	int	i;

	i = 0;
	if (philos)
	{
		while (i < rules->n_philos)
		{
			philos[i].t_meal = rules->t_die;
			if (pthread_mutex_destroy(&philos[i].fork.lock))
				error_thread(&philos[i], 1, errno);
			ft_memset(&philos[i], 0, sizeof(t_philo));
			i++;
		}
	}
	fprintf(stderr, "\t\t\t\t\t[ALL ERASED]\n");
	if (pthread_mutex_destroy(&rules->lock_flags.lock))
		error_thread(&philos[i], 1, errno);
}

void	wait_all_philos(t_rules *rules, t_philo *philo)
{
	static int		flag;
	struct timeval	start;

	{
		pthread_mutex_lock(&rules->lock_flags.lock);
		if (!rules->lock_flags.philo_group)
		{
			gettimeofday(&start, NULL);
			rules->t_start = (start.tv_sec * 1000) + (start.tv_usec / 1000);
		}
		rules->lock_flags.philo_group++;
		fprintf(stderr, "\t\t\t\t\t\t\t check[%d]{%d}\n", \
		philo->id, rules->lock_flags.philo_group);
		if (rules->lock_flags.philo_group < rules->n_philos)
			flag ++;
		pthread_mutex_unlock(&rules->lock_flags.lock);
	}
}

int	died_msg(t_rules *rules, t_philo *philo, int i)
{
	int			res;
	long long	time;

	res = 0;
	pthread_mutex_lock(&rules->lock_flags.lock);
	if (!rules->lock_flags.stat)
	{
		philo->t_current = rules->lock_flags.get_time(rules->t_start);
		time = (philo->t_current - philo->t_meal);
		if (time >= rules->t_die)
		{
			rules->lock_flags.stat = true;
			philo_msg(philo->t_current, i, "      DIED      ", P_DEAD);
			fprintf(stderr, "\t\t\t\t\t\t\t*[%d] ==> [%lld/%lld | %lld]\n", \
			philo->id, philo->t_meal, time, rules->t_die);
			res = 1;
		}
	}
	else
		res = 1;
	pthread_mutex_unlock(&rules->lock_flags.lock);
	return (res);
}

