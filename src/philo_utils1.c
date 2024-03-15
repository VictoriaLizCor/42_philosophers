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

static void	action_ext(t_philo *philo, t_rules *rules, t_philo *last)
{
	if (check_action(philo, '=', 3))
	{
		philo->sleep = t_mu_s(rules->t_start);
		philo_msg(philo, P_SLEEP);
		if (t_mu_s(rules->t_start) < rules->t_sleep + philo->sleep)
			ft_usleep(rules, philo, philo->sleep, rules->t_sleep);
	}
	else if (check_action(philo, '=', 4))
	{
		philo_msg(philo, P_THINK);
		philo->action = 0;
		if ((philo->right || check_fork(philo)) && \
		t_mu_s(rules->t_start) < philo->t_meal + rules->t_eat)
			philo->action = 2;
		else if (check_fork(philo))
		{
			ft_usleep(rules, philo, 0, 1);
		}
	}
}
// ft_usleep(rules, philo, 0, 1);
// philo->sleep + rules->t_eat
// while (check_fork(philo) || !dead(rules, philo))
// 	usleep(10);
// printf("STATUS [%d] -> time [%d] \n", check_fork(philo),
		//time_ms(philo) < philo->t_meal + rules->t_eat);

static void	action(t_philo *philo, t_rules *rules, bool stat, t_philo *last)
{
	philo->action++;
	if (check_action(philo, '=', 1) && stat)
	{
		lock_mutex(&philo->fork);
		debug_thread_check(philo, "LOCKING", color(14));
		lock_mutex(&philo->right->fork);
		philo_msg(philo, P_FORK);
		if (rules->n_philos > 1 && rules->n_philos % 2 == 1)
		{
			if (philo->id == last->right->id || \
				philo->id == last->left->id)
				lock_mutex(&philo->left->fork);
		}
	}
	else if (check_action(philo, '=', 2) && stat)
	{
		usleep(10);
		philo_msg(philo, P_EAT);
		philo->t_meal = t_mu_s(rules->t_start);
		if (philo->n_meals > 0)
			philo->n_meals--;
		if (!meal_done(rules, philo, true))
			ft_usleep(rules, philo, -1, 1);
		if (philo->right)
		{
			debug_thread_check(philo, "UNLOCKING", color(13));
			unlock_mutex(&philo->right->fork);
			if (rules->n_philos > 1 && rules->n_philos % 2 == 1)
			{
				debug_thread_check(philo, "UNLOCKING LEFT", color(15));
				if (philo->id == last->right->id || \
					philo->id == last->left->id)
					unlock_mutex(&philo->left->fork);
			}
			unlock_mutex(&philo->fork);
		}
	}
	else
		action_ext(philo, rules, last);
}

/*
	if(fork-lock)
		sleep and wake
*/
/*
  ** @brief
*/
static void	exe(t_philo *philo)
{
	t_rules	*rules;
	bool	stat;

	rules = philo->rules;
	if (rules->n_philos > 1)
		wait_all(philo, START, init_sync);
	else
		rules->t_start = get_time();
	philo_msg(philo, P_THINK);
	while (1)
	{
		stat = (philo->right != NULL || check_fork(philo)) && \
		check_action(philo, '<', 3);
		action(philo, rules, stat, rules->last);
		if (check_mutex(rules->lock[DEAD]) || check_mutex(rules->lock[MEAL]))
			return ;
	}
}

void	start_threads(t_philo *philos, t_rules *rules, int *rand_array)
{
	int			i;

	i = 0;
	while (i < rules->n_philos)
	{
		if (pthread_create(&philos[rand_array[i]].thread, NULL, \
		(void *)exe, &philos[rand_array[i]]))
		{
			rules->error++;
			error_thread(&philos[rand_array[i]], 0);
			return ;
		}
		i++;
	}
	i = 0;
	while (i < rules->n_philos)
	{
		if (pthread_join(philos[rand_array[i]].thread, NULL))
		{
			rules->error++;
			return ;
		}
		i++;
	}
}
