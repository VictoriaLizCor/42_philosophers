/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:39:04 by lilizarr          #+#    #+#             */
/*   Updated: 2023/10/02 12:45:51 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	destroy_fork(t_philo philo)
{
	fprintf(stderr, "\t\t\t\t\t[%d]\n", philo.id);
	if (pthread_mutex_destroy(&philo.fork))
		error_thread(&philo, 1, errno);
	ft_memset(&philo, 0, sizeof(t_philo));
}

void	died_msg(t_philo *philo, int i)
{
	t_rules	*rules;

	rules = philo->d_rules;
	printf(" %lld\tphilo %s [%03d] %s %s        DIED      %s\n", \
		current_time(rules), color(i), i, color(0), P_DEAD, color(0));
}
