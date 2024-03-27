/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:39:04 by lilizarr          #+#    #+#             */
/*   Updated: 2023/12/07 10:13:41 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	ft_usleep(t_rules *rules, t_philo *philo, t_ll time, t_ll limit)
{
	while (1)
	{
		print_usleep(rules, philo, time, limit);
		if (dead(rules, philo) || meal_done(rules, philo, false))
			return ;
		if (time == -1 && (t_mu_s(philo->t_start) > rules->t_eat + limit))
			return ;
		else if (time == 0)
		{
			if (!check_fork(philo->right) && !check_fork(philo->left))
				return ((void)debug_thread_check(philo, "BACK", font(12)));
		}
		else if (time > 0 && (limit < t_mu_s(philo->t_start) - time))
			return ;
		usleep(10);
	}
}

void	print_msg(t_philo *philo, char *msg, t_ll time)
{
	int		i;
	t_ll	ms;
	t_rules	*rules;

	rules = philo->rules;
	i = philo->id;
	pthread_mutex_lock(&rules->lock[PRINT]->lock);
	if (time == 0)
		time = t_mu_s(rules->t_start);
	ms = time / 1000;
	if (!rules->lock[PRINT]->stat)
	{
		if (D_PHI == 1)
			print_action(philo, time);
		if (D_PHI == 0)
			printf(" %03lld\tphilo %s [%03d] %s %s\n\n", \
			ms, font(i), i, font(0), msg);
		else
			printf(" %03lld [%lld]\tphilo %s [%03d] %s %s\n\n", \
			ms, time, font(i), i, font(0), msg);
	}
	pthread_mutex_unlock(&rules->lock[PRINT]->lock);
}


bool	dead(t_rules *rules, t_philo *philo)
{
	t_ll	time;
	t_ll	last_meal;
	t_ll	t_aux;

	t_aux = 0;
	if (!check_mutex(rules->lock[DEAD]))
	{
		time = (t_mu_s(philo->t_start) / 1000) * 1000;
		last_meal = time - philo->t_meal;
		if (rules->t_die < last_meal)
		{
			printf("time {%lld} last_meal [%lld]\n", time, last_meal);
			lock_mutex(rules->lock[DEAD]);
			t_aux = t_mu_s(rules->t_start);
			if (!check_mutex(rules->lock[PRINT]))
			{
				print_msg(philo, P_DEAD, time);
				lock_mutex(rules->lock[PRINT]);
				debug_death(philo, rules, time, t_aux);
			}
		}
	}
	return (check_mutex(rules->lock[DEAD]));
}

bool	meal_done(t_rules *rules, t_philo *philo, bool check)
{
	bool		status;
	static int	done;

	pthread_mutex_lock(&rules->lock[MEAL]->lock);
	if (check && (philo->n_meals == rules->n_meals))
	{
		done++;
		if (D_PHI == 1)
			printf("%s\t RULES[%d] PhILO_MEALS[%d] [%d]%s\n", \
			warn(0), rules->n_meals, philo->n_meals, philo->id, font(0));
	}
	if (!check && !rules->lock[MEAL]->stat && done == rules->n_philos)
	{
		rules->lock[MEAL]->stat = 1;
		if (D_PHI == 1)
			printf("%s [%d]PhILO_MEALS[%d]%s\n", \
			warn(1), philo->id, philo->n_meals, font(0));
	}
	status = rules->lock[MEAL]->stat;
	return ((void)pthread_mutex_unlock(&rules->lock[MEAL]->lock), status);
}
