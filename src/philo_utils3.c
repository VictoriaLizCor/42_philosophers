/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:39:04 by lilizarr          #+#    #+#             */
/*   Updated: 2023/10/11 13:15:22 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	destroy_fork(t_philo *philos, t_rules *rules)
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
}

void	died_msg(t_philo *philo, int i)
{
	t_rules	*rules;

	rules = philo->d_rules;
	pthread_mutex_lock(&rules->death_flag.lock);
	fprintf(stderr, "\t\t\t\t\t[%d][%lld] meal\n", philo->id, philo->t_meal);
	rules = philo->d_rules;
	printf(" %lld\tphilo %s [%03d] %s %s        DIED      %s\n", \
		current_time(rules), color(i), i, color(0), P_DEAD, color(0));
	rules->death_flag.stat = true;
	pthread_mutex_unlock(&rules->death_flag.lock);
}

// static void	rutine(void (*arg)(t_philo *, t_rules *, int), \
// t_philo *philos, t_rules *rules, int idx)
// {
// 	fprintf(stderr, "PASS\n");
	// while (1)
	// {
	// 	if ((current_time(rules) - philo->t_meal) >= rules->t_die)
	// 	{
	// 		died_msg(philo, philo->id);
	// 		return ;
	// 	}
	// 	else
	// 	{
	// 		philo->to_lock = NULL;
	// 		if (philo->right && philo->left)
	// 			check_locks(philo, philo->right, philo->left);
	// 		if (philo->to_lock)
	// 			take_eat(philo, rules, philo->id);
	// 		sleep_think(philo, rules, philo->id);
	// 	}
	// }
// }

// void	start_threads(t_philo *philos, t_rules *rules, int size)
// {
// 	int			i;
// 	t_rutine	arg;

// 	i = 0;
// 	arg.philos = philos;
// 	arg.rules = rules;
// 	while (i < size)
// 	{
// 		arg.idx = 1;
// 		if (pthread_create(&philos[i].thread, NULL, \
// 		(void *)rutine, &arg) != 0)
// 			error_thread(&philos[i], 0, errno);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < size)
// 	{
// 		pthread_join(philos[i].thread, NULL);
// 		i++;
// 	}
// }