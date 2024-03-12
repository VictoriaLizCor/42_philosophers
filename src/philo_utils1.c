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

// void	lock_msg(t_philo *philo, t_philo *cal)
// {
// 	philo->action++;
// 	if (philo->action == 1 && philo->to_lock)
// 	{
// 		philo_msg(philo, P_FORK, cal);
// 		philo->right->action = 2;
// 		lock_msg(philo->right, philo);
// 	}
// 	else if (philo->action == 2 && philo->to_lock)
// 	{
// 		philo_msg(philo, P_EAT, cal);
// 		philo->t_meal = t_mu_s(philo->rules);
// 		if (philo->n_meals > 0)
// 			philo->n_meals--;
// 	}
// 	else if (philo->action == 3)
// 	{
// 		philo_msg(philo, P_SLEEP, cal);
// 		philo->sleep = t_mu_s(philo->rules);
// 	}
// 	else if (philo->action == 4)
// 		philo_msg(philo, P_THINK, cal);
// }

// static void	action(t_philo *philo, t_rules *rules, t_philo *lock)
// {
// 	lock_msg(philo, philo);
// 	if (lock && philo->action < 3)
// 	{
// 		if (!meal_done(rules, philo, true) && philo->action == 2)
// 			ft_usleep(rules, philo, -1, 1);
// 		pthread_mutex_unlock(&lock->fork.lock); 
// 	}
// 	if ((!lock || meal_done(rules, philo, 0)) && philo->action == 3)
// 	{
// 		if (philo->right)
// 			pthread_mutex_unlock(&philo->fork.lock);
// 		if (rules->t_sleep > t_mu_s(rules) - philo->sleep)
// 			ft_usleep(rules, philo, philo->sleep, rules->t_sleep);
// 	}
// 	else if ((!lock || meal_done(rules, philo, 0)) && philo->action >= 4)
// 	{
// 		philo->action = 0;
// 		if (philo->right)
// 			pthread_mutex_unlock(&philo->fork.lock);
// 		else
// 			philo->action = 2;
// 		usleep(100);
// 	}
// }
// (!lock || meal_done(rules, philo, 0))

// static bool	check_locks(t_philo *philo, t_philo *right, t_philo *left)
// {
// 	if (right)
// 	{
// 		pthread_mutex_lock(&philo->fork.lock);
// 		debug_thread_check(philo, "ACTION", 0);
// 		if (philo->action < 2)
// 		{
// 			pthread_mutex_lock(&right->fork.lock);
// 			right->lock_by = philo;
// 			philo->to_lock = right;
// 			action(philo, philo->rules, right);
// 			philo->to_lock = NULL;
// 			pthread_mutex_unlock(&philo->fork.lock);
// 			right->lock_by = NULL;
// 		}
// 		else
// 			action(philo, philo->rules, NULL);
// 	}
// 	else
// 	{
// 		debug_thread_check(philo, "CHECK", 0);
// 		action(philo, philo->rules, NULL);
// 	}
// 	return (died_msg(philo->rules, philo) || \
// 	meal_done(philo->rules, philo, false));
// }

static void	action_ext(t_philo *philo, t_rules *rules, t_philo *lock)
{
	if (check_action(philo, '=', 3))
	{
		philo_msg(philo, P_SLEEP, lock);
		philo->sleep = time_ms(philo);
		if (rules->t_sleep > t_mu_s(rules) - philo->sleep)
			ft_usleep(rules, philo, philo->sleep, rules->t_sleep);
	}
	else if (check_action(philo, '=', 4))
	{
		philo_msg(philo, P_THINK, lock);
		philo->action = 0;
		if (!philo->right)
			philo->action = 2;
	}
}/*!!! ADD MEAL CHECK!!!*/
static void	action(t_philo *philo, t_rules *rules, t_philo *lock)
{
	philo->action++;
	debug_thread_check(philo, "ACTION", 0);
	if (check_action(philo, '=', 1))
	{
		philo->to_lock = philo->right;
		philo_msg(philo, P_FORK, lock);
		lock_fork(philo);
		lock_fork(philo->right);
	}
	else if (check_action(philo, '=', 2))
	{
		philo_msg(philo, P_EAT, lock);
		philo->t_meal = time_ms(philo);
		if (philo->n_meals > 0)
			philo->n_meals--;
		ft_usleep(rules, philo, -1, 1);
		unlock_fork(philo->right);
		unlock_fork(philo);
		philo->to_lock = NULL;
	}
	else
		action_ext(philo, rules, lock);
}

/*
  ** @brief
*/
static void	exe(t_philo *philo)
{
	t_rules	*rules;

	rules = philo->rules;
	wait_all(rules, philo, 0, (rules->n_philos * (rules->n_philos + 1) / 2));
	if (philo->wait)
		ft_usleep(rules, philo, 0, 10);
	while (1)
	{
		if (philo->right && check_fork(philo))
		{
			if (check_action(philo, '<', 3))
				action(philo, rules, philo->right);
		}
		else if (check_fork(philo) == false)
		{
			action(philo, philo->rules, NULL);
		}
		if (died_msg(philo->rules, philo) || meal_done(rules, philo, false))
			return ;
	}
}
// static bool	check_locks(t_philo *philo, t_philo *right, t_philo *left)
// {
// 	if (right)
// 	{
// 		lock_fork(philo);
// 		if (check_action(philo, '<', 2))
// 		{
// 			lock_fork(philo->right);
// 			right->lock_by = philo;
// 			philo->to_lock = right;
// 			action(philo, philo->rules, right);
// 			philo->to_lock = NULL;
// 			unlock_fork(philo);
// 			right->lock_by = NULL;
// 		}
// 		else
// 			action(philo, philo->rules, NULL);
// 	}
// 	else
// 	{
// 		debug_thread_check(philo, "CHECK", 0);
// 		action(philo, philo->rules, NULL);
//}
// 	return (died_msg(philo->rules, philo) || \
// 	meal_done(philo->rules, philo, false));
// }

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
