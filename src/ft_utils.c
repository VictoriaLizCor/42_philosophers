/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:29:47 by lilizarr          #+#    #+#             */
/*   Updated: 2023/09/15 16:55:19 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

// printf("philo L %d | philo M %d| philo R %d\n", philo->left->id,
// philo->id, philo->right->id);
void	func(t_philo *philo)
{
	// printf(" %lld\t ", philo->get_time(philo->d_rules));
	// printf("philo [%d] is %s THINKING %s\n", philo->id, P_THINK, CNRM);
	// usleep(philo->d_rules->t_think * 1000);
	printf(" %lld\t ", philo->get_time(philo->d_rules));
	printf("philo [%d] is %s  EATING  %s\n", philo->id, P_EAT, CNRM);
	printf(" %lld \t philo [%d] is %s SLEEPING %s\n", \
	current_timestamp(philo->d_rules), philo->id, P_SLEEP, CNRM);
	usleep(philo->d_rules->t_sleep * 1000);
	printf(" %lld \t philo [%d] %s     DIED    %s\n", \
	philo->get_time(philo->d_rules), philo->id, P_DEAD, CNRM);
}
	// pthread_mutex_lock(&phil[n]);
	// pthread_mutex_lock(&chopstick[(n + 1) % 5]);
	// printf("\nPhilosopher %d is eating ", n);
	// sleep(3);
	// pthread_mutex_unlock(&chopstick[n]);
	// pthread_mutex_unlock(&chopstick[(n + 1) % 5]);
	// printf("\nPhilosopher %d Finished eating ", phil->id);

long long	current_timestamp(t_rules *rules)
{
	long long	miliseconds;

	gettimeofday(&rules->t_end, NULL);
	miliseconds = ((rules->t_end.tv_sec - rules->t_start.tv_sec) * 1000LL + \
	(rules->t_end.tv_usec - rules->t_start.tv_usec) * 0.001);
	return (miliseconds);
}

void	print_msg(t_rules *rules, t_philo **philos)
{
	int				i;

	i = 0;
	while (philos[i])
	{
		printf(" %lld\t ", philos[i]->get_time(&*rules));
		printf("philo [%d] is %s THINKING %s\n", philos[i]->id, P_THINK, CNRM);
		usleep(rules->t_think * 1000);
		printf(" %lld\t ", philos[i]->get_time(&*rules));
		printf("philo [%d] is %s  EATING  %s\n", philos[i]->id, P_EAT, CNRM);
		printf(" %lld \t philo [%d] is %s SLEEPING %s\n", \
		current_timestamp(&*rules), philos[i]->id, P_SLEEP, CNRM);
		usleep(rules->t_sleep * 1000);
		printf(" %lld \t philo [%d] %s     DIED    %s\n", \
		philos[i]->get_time(&*rules), philos[i]->id, P_DEAD, CNRM);
		i++;
	}
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
