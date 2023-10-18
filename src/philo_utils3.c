/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:39:04 by lilizarr          #+#    #+#             */
/*   Updated: 2023/10/18 17:33:48 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	philo_actin_msg(long long time, int i, char *msg, char *msg_color)
{
	printf(" %lld\tphilo %s [%03d] %s %s %s %s\n", \
	time, color(i), i, color(0), msg_color, msg, color(0));
}

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
			// ft_memset(&philos[i], 0, sizeof(t_philo));
			i++;
		}
		// ft_memset(philos, 0, sizeof(t_philo) * size);
	}
	fprintf(stderr, "\t\t\t\t\t[ALL ERASED]\n");
	if (pthread_mutex_destroy(&rules->lock_flags.lock))
		error_thread(&philos[i], 1, errno);
}

void	wait_all_philos(t_rules *rules, t_philo *philo)
{
	static int		flag;
	struct timeval	start;

	// while (1)
	// usleep(generate_rand_num(500, 700));
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
		// philo->action++;
			// philo->to_lock->action++;
			// philo_actions(philo->to_lock, rules, philo->to_lock->id);
		//  philo_actions(philo, rules, philo->id);
		if (philo->action <= 4 && philo->action > 0)
		{
			fprintf(stderr, "\t\t\t\t\t\t\t[%d]==> last_meal[%lld] \t action = %d", \
			philo->id, philo->t_meal, philo->action);
			if (philo->to_lock)
				fprintf(stderr, "\t to_lock_id=%d\n", philo->to_lock->id);
			fprintf(stderr, "\n");
		}
		time = (current_time(rules) - philo->t_meal);
		if (time >= rules->t_die)
		{
			rules->lock_flags.stat = true;
			philo_actin_msg(current_time(rules), i, "      DIED    ", P_DEAD);
			fprintf(stderr, "\t\t\t\t\t\t\t*[%d] ==> [%lld | %lld]\n", \
			philo->id, time, rules->t_die);
			res = 1;
		}
	}
	else
		res = 1;
	pthread_mutex_unlock(&rules->lock_flags.lock);
	return (res);
}

