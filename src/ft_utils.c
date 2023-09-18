/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:29:47 by lilizarr          #+#    #+#             */
/*   Updated: 2023/09/18 17:50:40 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

long long	current_timestamp(t_rules *rules)
{
	long long	miliseconds;

	gettimeofday(&rules->t_end, NULL);
	miliseconds = ((rules->t_end.tv_sec - rules->t_start.tv_sec) * 1000LL + \
	(rules->t_end.tv_usec - rules->t_start.tv_usec) * 0.001);
	return (miliseconds);
}

// printf("philo L %d | philo M %d| philo R %d\n", philo->left->id,
// philo->id, philo->right->id);
void	*func(void *tmp)
{
	t_rules	*rules;
	t_philo	*philo;

	philo = (t_philo *)tmp;
	rules = &*philo->d_rules;
	printf("\t\t\t\t\t\teat: %d | sleep: %d | die %d \n", rules->t_eat, rules->t_sleep, rules->t_die);
	printf(" %lld \t philo [%d] is %s EATING %s\n", \
	current_timestamp(&*rules), philo->id, P_EAT, CNRM);
	usleep(rules->t_eat * 1000);
	printf(" %lld \t philo [%d] is %s SLEEPING %s\n", \
	current_timestamp(&*rules), philo->id, P_SLEEP, CNRM);
	usleep(rules->t_sleep * 1000);
	// printf(" %lld \t philo [%d] %s     DIED    %s\n", \
	// (*philo).get_time(rules), philo->id, P_DEAD, CNRM);
}
	// pthread_mutex_lock(&phil[n]);
	// pthread_mutex_lock(&chopstick[(n + 1) % 5]);
	// printf("\nPhilosopher %d is eating ", n);
	// sleep(3);
	// pthread_mutex_unlock(&chopstick[n]);
	// pthread_mutex_unlock(&chopstick[(n + 1) % 5]);
	// printf("\nPhilosopher %d Finished eating ", phil->id);
	// rules = philo->d_rules;
	// printf("eat: %d | sleep: %d | die %d \n", rules->t_eat, rules->t_sleep, rules->t_die);
	// printf(" %lld \t philo [%d] is %s EATING %s\n", \
	// (*philo).get_time(rules), philo->id, P_EAT, CNRM);
	// usleep(philo->d_rules->t_eat * 1000);
	// printf(" %lld \t philo [%d] is %s SLEEPING %s\n", \
	// philo->get_time(rules), philo->id, P_SLEEP, CNRM);
	// usleep(rules->t_sleep * 1000);

// void	print_msg(t_rules *rules, t_philo **philos)
// {
// 	int				i;

// 	i = 0;
// 	while (i < rules->n_philos)
// 	{
// 		usleep(rules->t_die * 1000);
// 		printf(" %lld\t ", (*philos)[i].get_time(rules));
// 		printf("philo [%d] is %s THINKING %s\n", \
// 		(*philos)[i].id, P_THINK, CNRM);
// 		usleep(rules->t_die * 1000);
// 		printf(" %lld \t philo [%d] %s     DIED    %s\n", \
// 		(*philos)[i].get_time(rules), (*philos)[i].id, P_DEAD, CNRM);
// 		i++;
// 	}
// }

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
