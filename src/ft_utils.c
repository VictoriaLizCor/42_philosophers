/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:29:47 by lilizarr          #+#    #+#             */
/*   Updated: 2023/09/15 11:39:45 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	func(t_philo *philo)
{
	printf("philo L %d | philo M %d| philo R %d\n", philo->left->id, \
	philo->id, philo->right->id);
	// pthread_mutex_lock(&phil[n]);
	// pthread_mutex_lock(&chopstick[(n + 1) % 5]);
	// printf("\nPhilosopher %d is eating ", n);
	// sleep(3);
	// pthread_mutex_unlock(&chopstick[n]);
	// pthread_mutex_unlock(&chopstick[(n + 1) % 5]);
	// printf("\nPhilosopher %d Finished eating ", phil->id);
}

long long	current_timestamp(t_rules *rules)
{
	long long	miliseconds;

	gettimeofday(&rules->t_end, NULL);
	miliseconds = ((rules->t_end.tv_sec - rules->t_start.tv_sec) * 1000LL + \
	(rules->t_end.tv_usec - rules->t_start.tv_usec) * 0.001);
	return (miliseconds);
}

void	*ft_free(char **str)
{
	int		i;

	i = 0;
	while (str[i] != 0)
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}
