/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:39:04 by lilizarr          #+#    #+#             */
/*   Updated: 2023/10/16 16:50:59 by lilizarr         ###   ########.fr       */
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
			// ft_memset(&philos[i], 0, sizeof(t_philo));
			i++;
		}
		// ft_memset(philos, 0, sizeof(t_philo) * size);
	}
	fprintf(stderr, "\t\t\t\t\t[ALL ERASED]\n");
	if (pthread_mutex_destroy(&rules->death_flag.lock))
		error_thread(&philos[i], 1, errno);
}

int	died_msg(t_rules *rules, t_philo *philo, int i)
{
	int	res;

	res = 0;
	pthread_mutex_lock(&rules->death_flag.lock);
	if (!rules->death_flag.stat)
	{
		fprintf(stderr, "\t\t\t\t\t[%d][%lld] meal\n", philo->id, philo->t_meal);
		if ((current_time(rules) - philo->t_meal) >= rules->t_die)
		{
			rules->death_flag.stat = true;
			printf(" %lld\tphilo %s [%03d] %s %s        DIED      %s\n", \
			current_time(rules), color(i), i, color(0), P_DEAD, color(0));
			fprintf(stderr, "\t\t\t\t\t\t\t\t\t*[%d]meal[%lld] ==> [%lld | %lld]\n", \
			philo->id, philo->t_meal, current_time(rules) - philo->t_meal, rules->t_die);
			res = 1;
		}
	}
	else
		res = 1;
	pthread_mutex_unlock(&rules->death_flag.lock);
	return (res);
}

