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
		if (time == -1)
		{
			if (t_mu_s(rules->t_start) > rules->t_eat + limit)
				return ;
		}
		else
		{
			if (time == 0 && !check_fork(philo))
			{
				debug_thread_check(philo, "RETURN", color(12));
				return ;
			}
			else if(time == 0 && !check_fork(philo))
				debug_thread_check(philo, "WAITING LOCK", color(12));
			else if (time > 0 && (limit < t_mu_s(rules->t_start) - time))
				return ;
		}
		usleep(10);
	}
}
// else if (t_mu_s(rules) > philo->t_meal + limit * rules->t_sleep)
// limit++;
//rules->t_eat < t_mu_s(rules) - philo->t_meal

void	print_msg(t_philo *philo, char *msg, t_ll time)
{
	int		i;
	t_ll	ms;

	i = philo->id;
	ms = time / 1000;
	if (D_PHI == 0)
		printf(" %03lld\tphilo %s [%03d] %s %s\n\n", \
		ms, color(i), i, color(0), msg);
	else
		printf(" %03lld [%lld]\tphilo %s [%03d] %s %s\n\n", \
		ms, time, color(i), i, color(0), msg);
}

void	philo_msg(t_philo *philo, char *msg)
{
	int		i;
	t_rules	*rules;
	t_ll	time;

	rules = philo->rules;
	i = philo->id;
	time = t_mu_s(rules->t_start);
	if (!check_mutex(rules->lock[MSG]))
	{
		print_action(philo, time);
		print_msg(philo, msg, time);
	}
	else if (!check_mutex(rules->lock[DEAD]))
	{
		lock_mutex(rules->lock[DEAD]);
		lock_mutex(rules->lock[TIME]);
		print_msg(philo, P_DEAD, time);
		debug_death(philo, rules, time, time - philo->t_meal);
		if (philo->right)
			init_time(rules, philo);
	}
}

bool	dead(t_rules *rules, t_philo *philo)
{
	t_ll	starve;
	t_ll	time;
	int		i;

	i = philo->id;
	if (!check_mutex(rules->lock[MSG]))
	{
		time = t_mu_s(rules->t_start);
		starve = time - (philo->t_meal);
		if (starve > (rules->t_die + philo->t_extra))
			lock_mutex(rules->lock[MSG]);
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
		if (D_PHI != 0)
			printf("%s\t RULES[%d] PhILO_MEALS[%d] [%d]%s\n", \
			warn(0), rules->n_meals, philo->n_meals, philo->id, color(0));
	}
	if (!check && !rules->lock[MEAL]->stat && done == rules->n_philos)
	{
		rules->lock[MEAL]->stat = 1;
		if (D_PHI != 0)
			printf("%s [%d]PhILO_MEALS[%d]%s\n", \
			warn(1), philo->id, philo->n_meals, color(0));
	}
	status = rules->lock[MEAL]->stat;
	return ((void)pthread_mutex_unlock(&rules->lock[MEAL]->lock), status);
}
