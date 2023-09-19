/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:29:47 by lilizarr          #+#    #+#             */
/*   Updated: 2023/09/19 17:01:35 by lilizarr         ###   ########.fr       */
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
void	*func(t_philo *philo)
{
	t_rules	*rules;

	rules = philo->d_rules;
	usleep(10 * 1000);
	printf(" %lld \t philo [%d] %shas taken a fork%s\n", \
	current_timestamp(rules), philo->id, P_FORK, CNRM);
	philo->meal = current_timestamp(rules);
	printf(" %lld \t philo [%d] %sis    EATING    %s\n", \
	philo->meal, philo->id, P_EAT, CNRM);
	usleep(rules->t_eat * 1000);
	printf(" %lld \t philo [%d] %sis   SLEEPING   %s\n", \
	current_timestamp(rules), philo->id, P_SLEEP, CNRM);
	usleep(rules->t_sleep * 1000);
	printf(" %lld \t philo [%d] %sis   THINKING   %s\n", \
	current_timestamp(rules), philo->id, P_THINK, CNRM);
	usleep(rules->t_sleep * 1000);
	printf(" %lld \t philo [%d] %s       DIED     %s\n", \
	philo->get_time(rules), philo->id, P_DEAD, CNRM);
}

void	print_msg(t_rules *rules, t_philo *tmp)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = &*tmp;
	while (i < rules->n_philos)
	{
		printf("philo L %d | philo M %d| philo R %d\n", \
		philos[i].left->id, philos[i].id, philos[i].right->id);
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
