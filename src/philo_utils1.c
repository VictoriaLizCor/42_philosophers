/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:29:47 by lilizarr          #+#    #+#             */
/*   Updated: 2023/12/07 10:10:47 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	sleep_think(t_philo *philo, t_rules *rules)
{
	if (check_value(philo, &philo->action, '=', 3))
	{
		philo->sleep = t_mu_s(rules->t_start);
		print_msg(philo, P_SLEEP, 0);
		ft_usleep(rules, philo, philo->sleep, rules->t_sleep);
	}
	else if (check_value(philo, &philo->action, '=', 4))
	{
		print_msg(philo, P_THINK, 0);
		philo->action = 0;
		sleep_think_utils(philo, rules);
	}
}

static void	lock_eat(t_philo *philo, t_rules *rules, t_philo *last)
{
	(void)last;
	if (!check_fork(philo))
	{
		lock_mutex(&philo->fork, 1);
		lock_mutex(&philo->right->fork, 1);
		print_msg(philo, P_FORK, 0);
		debug_thread_check(philo, "LOCKING", font(14));
		philo->n_meals++;
		philo->t_meal = t_mu_s(rules->t_start);
		philo->n_meal = ((philo->t_meal / 1000) * 1000) + (2 * rules->t_eat);
		if (rules->odd)
			philo->n_meal = (philo->t_meal / 1000) * 1000 + (3 * rules->t_eat);
		usleep(10);
		print_msg(philo, P_EAT, 0);
		if (!meal_done(rules, philo, true))
			ft_usleep(rules, philo, -1, rules->t_eat - 10);
		debug_thread_check(philo->right, "UNLOCKING", font(13));
		lock_mutex(&philo->right->fork, 0);
		lock_mutex(&philo->fork, 0);
		philo->action += 1;
	}
}

/*
  ** @brief
*/
static void	exe(t_philo *philo)
{
	t_rules		*rules;

	rules = philo->rules;
	philo->t_extra = t_mu_s(rules->t_start);
	if (rules->n_philos == 1)
		rules->t_start = get_time();
	harm(philo, START, &rules->sum1, init_sync);
	philo->t_start = get_time();
	if (check_value(philo, &philo->action, '=', 0))
		print_msg(philo, P_THINK, 0);
	while (1)
	{
		philo->action++;
		debug_thread_check(philo, "EXE", font(philo->id));
		if (check_value(philo, &philo->action, '=', 1))
			lock_eat(philo, rules, rules->last);
		else
			sleep_think(philo, rules);
		if (check_mutex(rules->lock[DEAD]) || check_mutex(rules->lock[MEAL]))
			return ;
	}
	pthread_exit(NULL);
}

void	start_threads(t_philo *philos, t_rules *rules, int *rand_array)
{
	int	i;

	i = -1;
	rules->t_start = get_time();
	while (++i < rules->n_philos)
	{
		if (pthread_create(&philos[rand_array[i]].thread, NULL, \
		(void *)exe, &philos[rand_array[i]]))
		{
			(*rules->error)++;
			error_thread(&philos[rand_array[i]], 0);
			while (i--)
				pthread_join(philos[rand_array[i]].thread, NULL);
			return ;
		}
	}
	i = -1;
	while (++i < rules->n_philos && !(*rules->error))
	{
		if (pthread_join(philos[rand_array[i]].thread, NULL))
		{
			(*rules->error)++;
			return ;
		}
	}
}

// // TEST VERSION
// void	start_threads(t_philo *philos, t_rules *rules, int *rand_array)
// {
// 	int			i;

// 	i = rules->n_philos - 1;
// 	while (i >= 0)
// 	{
// 		if (pthread_create(&philos[rules->n_philos - 1 - i].thread, NULL,
// 		(void *)exe, &philos[i]))
// 		{
// 			(*rules->error)++;
// 			error_thread(&philos[i], 0);
// 			return ;
// 		}
// 		i--;
// 	}
// 	i = 0;
// 	while (i < rules->n_philos)
// 	{
// 		if (pthread_join(philos[i].thread, NULL))
// 		{
// 			(*rules->error)++;
// 			return ;
// 		}
// 		i++;
// 	}
// }
