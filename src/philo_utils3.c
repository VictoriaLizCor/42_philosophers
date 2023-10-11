/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:39:04 by lilizarr          #+#    #+#             */
/*   Updated: 2023/10/11 15:44:52 by lilizarr         ###   ########.fr       */
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
			fprintf(stderr, "\t\t\t\t\t[%d]\n", philos[i].id);
			philos[i].t_meal = rules->t_die;
			if (pthread_mutex_destroy(&philos[i].fork.lock))
				error_thread(&philos[i], 1, errno);
			// ft_memset(&philos[i], 0, sizeof(t_philo));
			i++;
		}
		// ft_memset(philos, 0, sizeof(t_philo) * size);
	}
	if (pthread_mutex_destroy(&rules->death_flag.lock))
		error_thread(&philos[i], 1, errno);
}

void	died_msg(t_philo *philo, int i)
{
	t_rules	*rules;

	rules = philo->d_rules;
	fprintf(stderr, "\t\t\t\t\t[%d][%lld] meal\n", philo->id, philo->t_meal);
	printf(" %lld\tphilo %s [%03d] %s %s        DIED      %s\n", \
		current_time(rules), color(i), i, color(0), P_DEAD, color(0));
	rules->death_flag.stat = true;
}

