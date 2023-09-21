/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:29:47 by lilizarr          #+#    #+#             */
/*   Updated: 2023/09/21 11:35:11 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

long long	current_time(t_rules *rules)
{
	long long	miliseconds;

	gettimeofday(&rules->t_end, NULL);
	miliseconds = ((rules->t_end.tv_sec - rules->t_start.tv_sec) * 1000LL + \
	(rules->t_end.tv_usec - rules->t_start.tv_usec) * 0.001);
	return (miliseconds);
}

void	func(t_philo *philo)
{
	t_rules	*rules;
	int		i;

	i = philo->id;
	rules = philo->d_rules;
	printf(" %lld\tphilo %s [%02d] %s %s has taken a fork %s\n", \
	current_time(rules), color(i), i, color(0), P_FORK, color(0));
	philo->meal = current_time(rules);
	printf(" %lld\tphilo %s [%02d] %s %s is    EATING     %s\n", \
	philo->meal, color(i), i, color(0), P_EAT, color(0));
	usleep(rules->t_eat * 1000);
	printf(" %lld\tphilo %s [%02d] %s %s is   SLEEPING    %s\n", \
	current_time(rules), color(i), i, color(0), P_SLEEP, color(0));
	usleep(rules->t_sleep * 1000);
	printf(" %lld\tphilo %s [%02d] %s %s is   THINKING    %s\n", \
	current_time(rules), color(i), i, color(0), P_THINK, color(0));
	usleep(rules->t_sleep * 1000);
	printf(" %lld\tphilo %s [%02d] %s %s        DIED      %s\n", \
	philo->get_time(rules), color(i), i, color(0), P_DEAD, color(0));
}
