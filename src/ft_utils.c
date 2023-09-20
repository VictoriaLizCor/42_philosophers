/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:29:47 by lilizarr          #+#    #+#             */
/*   Updated: 2023/09/20 17:26:16 by lilizarr         ###   ########.fr       */
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

// printf("philo L %d | philo M %d| philo R %d\n", philo->left->id,
// philo->id, philo->right->id);
void	func(t_philo *philo)
{
	t_rules	*rules;
	int		i;

	i = philo->id;
	rules = philo->d_rules;
	usleep(10 * 1000);
	printf(" %lld\tphilo %s[%d]%s\t%shas taken a fork%s\n", \
	current_time(rules), color(i), philo->id, color(0), P_FORK, color(0));
	philo->meal = current_time(rules);
	printf(" %lld\tphilo %s[%d]%s\t%sis    EATING    %s\n", \
	philo->meal, color(i), philo->id, color(0), P_EAT, color(0));
	usleep(rules->t_eat * 1000);
	printf(" %lld\tphilo %s[%d]%s\t%sis   SLEEPING   %s\n", \
	current_time(rules), color(i), philo->id, color(0), P_SLEEP, color(0));
	usleep(rules->t_sleep * 1000);
	printf(" %lld\tphilo %s[%d]%s\t%sis   THINKING   %s\n", \
	current_time(rules), color(i), philo->id, color(0), P_THINK, color(0));
	usleep(rules->t_sleep * 1000);
	printf(" %lld\tphilo %s[%d]%s\t%s       DIED     %s\n", \
	philo->get_time(rules), color(i), philo->id, color(0), P_DEAD, color(0));
}

void	philo_neightbor(t_philo *philos, int i, int left, int right)
{
	philos[i].left = &philos[left];
	philos[i].right = &philos[right];
}

void	print_msg(t_rules *rules, t_philo *tmp)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = &*tmp;
	while (i < rules->n_philos)
	{
		if (philos[i].left && philos[i].right)
		{
			printf("philo L %d | philo M %d| philo R %d\n", \
			philos[i].left->id, philos[i].id, philos[i].right->id);
		}
		else
			printf("philo L %p | philo M %d| philo R %p\n", \
			philos[i].left, philos[i].id, philos[i].right);
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
