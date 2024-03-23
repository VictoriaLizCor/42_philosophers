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
		philo->sleep = t_mu_s(philo->t_start);
		philo_msg(philo, P_SLEEP);
		ft_usleep(rules, philo, philo->sleep, rules->t_sleep);
	}
	else if (check_value(philo, &philo->action, '=', 4))
	{
		philo_msg(philo, P_THINK);
		philo->action = 0;
		if (philo->id == rules->last->id && rules->odd)
			usleep(50);
		if (!rules->odd)
		{
			if (!philo->right)
				philo->action = 2;
			else if (rules->t_eat % rules->t_sleep == 0 && \
			t_mu_s(philo->t_start) < philo->t_meal + rules->t_eat)
				philo->action = 2;
			else if (check_fork(philo))
				ft_usleep(rules, philo, 0, 1);
		}
		else
			sleep_think_utils(philo, rules);
	}
}

static void	lock_eat(t_philo *philo, t_rules *rules, t_philo *last)
{
	if (!check_fork(philo))
	{
		lock_mutex(&philo->fork);
		lock_mutex(&philo->right->fork);
		lock_mutex(&philo->left->fork);
		philo_msg(philo, P_FORK);
		debug_thread_check(philo, "LOCKING", font(14));
		philo->t_meal = t_mu_s(philo->t_start);
		philo->n_meals++;
		usleep(10);
		philo_msg(philo, P_EAT);
		if (!meal_done(rules, philo, true))
			ft_usleep(rules, philo, -1, philo->t_meal);
		unlock_mutex(&philo->right->fork);
		unlock_mutex(&philo->left->fork);
		debug_thread_check(philo, "UNLOCKING", font(13));
		unlock_mutex(&philo->fork);
	}
	philo->action += 1;
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
	t_rules		*rules;

	rules = philo->rules;
	if (rules->n_philos == 1)
		rules->t_start = get_time();
	else
		ft_sync(philo, START, init_sync);
	philo_msg(philo, P_THINK);
	while (1)
	{
		philo->action++;
		if (philo->right && check_value(philo, &philo->action, '=', 1))
			lock_eat(philo, rules, rules->last);
		else
			sleep_think(philo, rules);
		if (check_mutex(rules->lock[DEAD]) || check_mutex(rules->lock[MEAL]))
			return ;
	}
}

	// i = 0;
	// while (i < rules->n_philos)
	// {
		// if (pthread_create(&philos[rand_array[i]].thread, NULL, \
		// (void *)exe, &philos[rand_array[i]]))
	// 	{
	// 		rules->error++;
	// 		error_thread(&philos[rand_array[i]], 0);
	// 		return ;
	// 	}
	// 	i++;
	// }
void	start_threads(t_philo *philos, t_rules *rules, int *rand_array)
{
	int			i;

	i = rules->n_philos - 1;
	while (i >= 0)
	{
		if (pthread_create(&philos[i].thread, NULL, \
		(void *)exe, &philos[i]))
		{
			rules->error++;
			error_thread(&philos[rand_array[i]], 0);
			return ;
		}
		i--;
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
// 	printf("\t\t\t%sMAX_EXTRA [%lld]%s\n", font(15), extra, font(0));

		// printf("\t\t\t\t\t%s [%d] last meal [%lld]%s\n", warn(0), philo->id, \
		// 	t_mu_s(rules->t_start) - philo->t_meal, font(0));
		// if (rules->n_philos % 2 == 1)
		// {
		// 	printf("\t\t\t\t\t%s [%d] last meal > 3 * last_meal[%d]%s\n", warn(0), philo->id, \
		// 	t_mu_s(rules->t_start) > (philo->t_meal + rules->t_eat * 3), font(0));
		// }
		// printf("\t\t\t\t\t %s*[%lld]%s\n\n", font(1), philo->wait, font(0));
		// printf("\t\t\t\t\t%s [%d] DIE [%lld]%s\n", warn(0), philo->id, \
		// t_mu_s(rules->t_start) % rules->t_die , font(0));
		// printf("\t\t\t\t\t%s [%d] DIE %% AUX[%lld]%s\n", warn(0), philo->id, \
		// rules->t_die % philo->wait, font(0));
// if ((!philo->right || check_fork(philo)) && \
// 		(rules->t_eat / rules->t_sleep) > 1 && \
// 		((t_mu_s(rules->t_start)) % rules->t_eat) / 1000)
// printf("\t\t\t\t\t%s [%d]time %% eat %lld%s\n", warn(0), philo->id, \
// ((t_mu_s(rules->t_start)) % rules->t_eat) / 1000, font(0));
// printf("\t\t\t\t\t%s [%d] eat %% sleep [%lld]%s\n", warn(0), philo->id, \
// rules->t_eat % rules->t_sleep, font(0));
// printf("\t\t\t\t\t%s [%d] eat / sleep [%lld]%s\n", warn(0), philo->id, \
// rules->t_eat / rules->t_sleep, font(0));