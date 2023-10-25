/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:39:04 by lilizarr          #+#    #+#             */
/*   Updated: 2023/10/25 11:59:12 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

bool	ft_usleep(t_rules *rules, t_philo *philo, long long time)
{
	int			i;

	i = 0;
	while (i <= time)
	{
		if (died_msg(rules, philo))
			return (1);
		usleep(840);
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
			philos[i].t_meal = rules->t_die;
			if (pthread_mutex_destroy(&philos[i].fork.lock))
				error_thread(&philos[i], 1, errno);
			if (pthread_mutex_destroy(&philos[i].msg.lock))
				error_thread(&philos[i], 1, errno);
			ft_memset(&philos[i], 0, sizeof(t_philo));
			i++;
		}
	}
	fprintf(stderr, "\t\t\t\t\t[ALL ERASED]\n");
	if (pthread_mutex_destroy(&rules->lock_flags.lock))
		error_thread(&philos[i], 1, errno);
}

void	philo_msg(t_philo *philo, char *msg, char *msg_color)
{
	int	i;

	pthread_mutex_lock(&philo->msg.lock);
	i = philo->id;
	printf(" %lld\tphilo %s [%03d] %s %s %s %s\n", \
	philo->time, color(i), i, color(0), msg_color, msg, color(0));
	pthread_mutex_unlock(&philo->msg.lock);
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

int	died_msg(t_rules *rules, t_philo *philo)
{
	int			res;
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
			philo_msg(philo, "      DIED      ", P_DEAD);
			fprintf(stderr, "\t\t\t\t\t\t\t*[%d] ==> [%lld/%lld | %lld]\n", \
			philo->id, philo->t_meal, death_time, rules->t_die);
			/* DELETE */
			if (philo->action <= 4 && philo->action >= 0)
			{
				pthread_mutex_lock(&philo->msg.lock);
				if (philo->to_lock)
					fprintf(stderr, " %lld \t\t\t\t\t\t[%d]{%d} ==> last_meal[%lld] \t last_sleep[%lld]\n", \
					current_time(rules->t_start), philo->id, philo->action, philo->t_meal, philo->t_sleep);
				else
					fprintf(stderr, " %lld \t\t\t\t\t\t[%d]{%d} ==> last_meal[%lld] \t last_sleep[%lld]\n", \
					current_time(rules->t_start), philo->id, philo->action, philo->t_meal, philo->t_sleep);
				fprintf(stderr, "\n");
				pthread_mutex_unlock(&philo->msg.lock);
			}
			/*/////////*/
			res = 1;
		}
	}
	else
		res = 1;
	pthread_mutex_unlock(&rules->lock_flags.lock);
	return (res);
}
