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
	if (time == -1)
		debug_thread_check(philo, "\t\t EAT");
	else if (time == 0)
		debug_thread_check(philo, "\t\t THINK");
	else
		debug_thread_check(philo, "\t\t SLEEP");
	while (1)
	{
		// print_ft_usleep(rules, philo, time, limit);
		if (died_msg(rules, philo) || meal_done(rules, philo, false))
			return ;
		if (time == -1)
		{
			if (t_mu_s(rules->t_start) > rules->t_eat + philo->t_meal)
				return ;
		}
		else
		{
			if (time == 0 && (check_fork(philo)))
				return ;
			else if (time > 0 && (limit < t_mu_s(rules->t_start) - time))
				return ;
		}
		usleep(10);
	}
}
// else if (t_mu_s(rules) > philo->t_meal + limit * rules->t_sleep)
// limit++;
//rules->t_eat < t_mu_s(rules) - philo->t_meal

void	philo_msg(t_philo *philo, char *msg)
{
	int		i;
	t_rules	*rules;
	t_ll	time;

	rules = philo->rules;
	pthread_mutex_lock(&rules->lock[MSG]->lock);
	i = philo->id;
	time = t_mu_s(rules->t_start);
	if (!rules->lock[MSG]->stat)
	{
		if (!died_msg(rules, philo) || !meal_done(rules, philo, false))
		{
			print_action(philo);
			print_msg(philo, msg, time);
		}
		else
			rules->lock[MSG]->stat = true;
	}
	pthread_mutex_unlock(&rules->lock[MSG]->lock);
}

bool	died_msg(t_rules *rules, t_philo *philo)
{
	bool	died;
	t_ll	starve;
	t_ll	current_time;
	int		i;

	i = philo->id;
	pthread_mutex_lock(&rules->lock[DEAD]->lock);
	if (!rules->lock[DEAD]->stat)
	{
		current_time = time_ms(philo);
		starve = current_time - philo->t_meal;
		if (starve > (rules->t_die))
		{
			rules->lock[DEAD]->stat = 1;
			print_msg(philo, P_DEAD, current_time);
			debug_death(philo, rules, current_time);
		}
	}
	died = rules->lock[DEAD]->stat;
	pthread_mutex_unlock(&rules->lock[DEAD]->lock);
	return (died);
}
// printf(" %lld\tphilo %s [%03d] %s %s\n\n", 
// current_time / 1000, color(i), i, color(0), P_DEAD);

bool	meal_done(t_rules *rules, t_philo *philo, bool check)
{
	bool	done;

	if (rules->n_philos == 1)
		return (0);
	pthread_mutex_lock(&rules->lock[MEAL]->lock);
	if (check && philo->n_meals == 0 && rules->n_meals > 0)
	{
		rules->n_meals--;
		printf("%s\t RULES[%d] PhILO_MEALS[%d] [%d]%s\n", \
		warn(0), rules->n_meals, philo->n_meals, philo->id, color(0));
	}
	if (!check && rules->n_meals == 0 && !rules->lock[MEAL]->stat)
	{
		rules->lock[MEAL]->stat = 1;
		printf("%s [%d]PhILO_MEALS[%d]%s\n", \
		warn(1), philo->id, philo->n_meals, color(0));
	}
	done = rules->lock[MEAL]->stat;
	return ((void)pthread_mutex_unlock(&rules->lock[MEAL]->lock), done);
}

void	destroy_mutex(t_philo *philos, t_rules *rules)
{
	int	i;

	i = 0;
	if (philos)
	{
		while (i < rules->n_philos)
		{
			if (pthread_mutex_destroy(&philos[i].fork.lock))
				error_thread(&philos[i], 1);
			memset(&philos[i], 0, sizeof(t_philo));
			i++;
		}
	}
	i = 0;
	while (i < N_MUTEX)
	{
		if (rules->lock[i])
		{
			if (pthread_mutex_destroy(&rules->lock[i]->lock))
				error_thread(NULL, 2);
			free(rules->lock[i]);
		}
		i++;
	}
	if (pthread_mutex_destroy(&rules->dead.lock))
		error_thread(NULL, 2);
	free(rules->lock);
}
