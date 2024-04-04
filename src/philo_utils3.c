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
		if (time == -1 && (limit < t_mu_s(rules->t_start) - philo->t_meal))
			return ;
		else if (time == 0)
		{
			if ((limit < t_mu_s(rules->t_start)) && !check_fork(philo))
				return ((void)debug_thread_check(philo, "BACK", font(12)));
		}
		else if (time > 0 && (limit < t_mu_s(rules->t_start) - philo->sleep))
			return ;
		usleep(100);
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
	time = t_mu_s(rules->t_start);
	ms = time / 1000;
	if (D_PHI == 1 && !rules->lock[PRINT]->stat)
		print_action(philo, time);
	if (D_PHI == 0 && !rules->lock[PRINT]->stat)
		printf(" %03lld %s philo [%03d] %s %s\n\n", \
		ms, font(i), i, font(0), msg);
	else if (!rules->lock[PRINT]->stat)
		printf(" %03lld [%lld] %s philo [%03d] %s %s\n\n", \
		ms, time, font(i), i, font(0), msg);
	pthread_mutex_unlock(&rules->lock[PRINT]->lock);
}

bool	dead(t_rules *rules, t_philo *philo)
{
	t_ll	time;
	t_ll	dead_meal;
	t_ll	t_aux;

	if (!check_mutex(rules->lock[DEAD]))
	{
		time = t_mu_s(rules->t_start);
		t_aux = (time / 1000) * 1000;
		dead_meal = ((t_aux - philo->t_meal) / 1000) * 1000;
		if (philo->left && philo->n_meal < t_aux)
			dead_meal -= t_aux - philo->n_meal;
		if (dead_meal > rules->t_die)
		{
			if (!check_mutex(rules->lock[PRINT]))
			{
				print_msg(philo, P_DEAD, time);
				lock_mutex(rules->lock[PRINT], true);
				debug_death(philo, rules, t_aux, time);
			}
			return ((void)lock_mutex(rules->lock[DEAD], true), 1);
		}
	}
	return (0);
}

bool	meal_done(t_rules *rules, t_philo *philo, bool check)
{
	bool		status;
	static int	done;

	pthread_mutex_lock(&rules->lock[MEAL]->lock);
	if (check && (philo->n_meals == rules->n_meals))
	{
		done++;
		if (D_PHI == 2)
			printf("%s\t RULES[%d] PhILO_MEALS[%d] [%d]%s\n", \
			warn(0), rules->n_meals, philo->n_meals, philo->id, font(0));
	}
	if (!check && !rules->lock[MEAL]->stat && done == rules->n_philos)
	{
		rules->lock[MEAL]->stat = 1;
		if (D_PHI == 2)
			printf("%s [%d]PhILO_MEALS[%d] | total[%d]%s\n", \
			warn(1), philo->id, philo->n_meals, done, font(0));
	}
	status = rules->lock[MEAL]->stat;
	return ((void)pthread_mutex_unlock(&rules->lock[MEAL]->lock), status);
}
