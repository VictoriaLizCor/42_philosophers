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

	i = philo->id;
	pthread_mutex_lock(&philo->rules->lock[PRINT]->lock);
	if (time == 0)
		time = t_mu_s(philo->rules->t_start);
	ms = time / 1000;
	if (D_PHI == 0)
		printf(" %03lld\tphilo %s [%03d] %s %s\n\n", \
		ms, font(i), i, font(0), msg);
	else
		printf(" %03lld [%lld]\tphilo %s [%03d] %s %s\n\n", \
		ms, time, font(i), i, font(0), msg);
	pthread_mutex_unlock(&philo->rules->lock[PRINT]->lock);
}

void	philo_msg(t_philo *philo, char *msg)
{
	int		i;
	t_rules	*rules;
	t_ll	time;

	rules = philo->rules;
	i = philo->id;
	time = 0;
	if (!check_mutex(rules->lock[MSG]))
	{
		print_action(philo, 0);
		print_msg(philo, msg, time);
	}
	else if (!check_mutex(rules->lock[DEAD]))
	{
		lock_mutex(rules->lock[DEAD]);
		print_msg(philo, P_DEAD, t_mu_s(rules->t_start));
		debug_death(philo, rules, t_mu_s(philo->t_start));
	}
}

bool	dead(t_rules *rules, t_philo *philo)
{
	t_ll	time;
	int		i;

	i = philo->id;
	if (!check_mutex(rules->lock[MSG]))
	{
		time = t_mu_s(philo->t_start) - philo->t_meal;
		if (rules->t_die < time)
			return ((void)lock_mutex(rules->lock[MSG]), 1);
	}
	return (check_mutex(rules->lock[MSG]));
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
