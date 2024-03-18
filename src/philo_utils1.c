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
		printf("\t\t\t\t\t%s [%d]time %% eat %lld%s\n", warn(0), philo->id, \
		((t_mu_s(rules->t_start)) % rules->t_eat) / 1000, color(0));
		printf("\t\t\t\t\t%s [%d] eat %% sleep [%lld]%s\n", warn(0), philo->id, \
		rules->t_eat % rules->t_sleep, color(0));
		printf("\t\t\t\t\t%s [%d] eat / sleep [%lld]%s\n", warn(0), philo->id, \
		rules->t_eat / rules->t_sleep, color(0));
		if ((!philo->right || check_fork(philo)) && \
		(rules->t_eat / rules->t_sleep) > 1 && \
		((t_mu_s(rules->t_start)) % rules->t_eat) / 1000)
			philo->action = 2;
		else if (check_fork(philo))
			ft_usleep(rules, philo, 0, 1);
	}
}
// philo->t_meal + rules->t_eat + rules->t_sleep, \
// 		t_mu_s(rules->t_start) % rules->t_eat, color(0));
//  && t_mu_s(rules->t_start) < philo->t_meal + rules->t_eat
// t_mu_s(rules->t_start) % rules->t_eat > rules->t_sleep && 
// 		t_mu_s(rules->t_start) > philo->t_meal + rules->t_eat
static void	action(t_philo *philo, t_rules *rules, bool stat, t_philo *last)
{
	philo->action++;
	if (check_action(philo, '=', 1) && stat)
	{
		lock_mutex(&philo->fork);
		lock_mutex(&philo->right->fork);
		philo_msg(philo, P_FORK);
		debug_thread_check(philo, "LOCKING", color(14));
		usleep(10);
	}
	else if (check_action(philo, '=', 2) && stat)
	{
		philo->t_meal = t_mu_s(rules->t_start);
		if (philo->n_meals < rules->n_meals)
			philo->n_meals++;
		philo_msg(philo, P_EAT);
		philo->e_meal = philo->t_meal - philo->t_extra;
		if (!meal_done(rules, philo, true))
			ft_usleep(rules, philo, -1, philo->t_meal);
		if (philo->right)
		{
			unlock_mutex(&philo->right->fork);
			debug_thread_check(philo, "UNLOCKING", color(13));
			unlock_mutex(&philo->fork);
		}
	}
	else
		action_ext(philo, rules, last);
}

// if (rules->n_philos > 1 && rules->n_philos % 2 == 1)
// {
// 	if (philo->id == last->right->id || \
// 		philo->id == last->left->id)
// 		lock_mutex(&philo->left->fork);
// }
// if (rules->n_philos > 1 && rules->n_philos % 2 == 1)
// {
// 	debug_thread_check(philo, "UNLOCKING LEFT", color(15));
// 	if (philo->id == last->right->id || \
// 		philo->id == last->left->id)
// 		unlock_mutex(&philo->left->fork);
// }
/*
	if(fork-lock)
		sleep and wake
*/
/*
  ** @brief
*/
static void	exe(t_philo *philo)
{
	t_rules		*rules;
	bool		stat;

	rules = philo->rules;
	if (rules->n_philos == 1)
	{
		rules->t_start = get_time();
		philo->t_start = rules->t_start;
	}
	else
	{
		ft_sync(philo, START, init_sync);
		// ft_sync(philo, TIME, init_time);
	}
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

// extra = 0;
// 	i = 0;
// 	next = philo;
// 	while (i++ <= rules->n_philos && next->right)
// 	{
// 		if (next->t_extra > extra)
// 			extra = next->t_extra;
// 		next = next->right;
// 	}
// 	printf("\t\t\t%sMAX_EXTRA [%lld]%s\n", color(15), extra, color(0));