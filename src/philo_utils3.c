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
	else
		debug_thread_check(philo, "\t\t SLEEP");
	while (1)
	{
		if (died_msg(rules, philo) || meal_done(rules, philo, false))
			return ;
		print_ft_usleep(rules, philo, time, limit);
		if (time == -1)
		{
			if (t_mu_s(rules) > rules->t_eat + philo->t_meal)
				return ;
		}
		else if ((limit < t_mu_s(rules) - time))
			return ;
		usleep(100);
	}
}
// else if (t_mu_s(rules) > philo->t_meal + limit * rules->t_sleep)
// limit++;

void	philo_msg(t_philo *philo, char *msg)
{
	int		i;
	t_rules	*rules;

	rules = philo->rules;
	pthread_mutex_lock(&rules->lock[MSG]->lock);
	philo->time = t_mu_s(rules);
	i = philo->id;
	rules->lock[MSG]->stat = died_msg(philo->rules, philo) || \
		meal_done(philo->rules, philo, false);
	if (!rules->lock[MSG]->stat)
	{
		print_action(philo);
		if (D_PHI == 0)
			printf(" %lld [%lld]\tphilo %s [%03d] %s %s\n\n", \
			philo->time / 1000, philo->time, color(i), i, color(0), msg);
		else
			printf(" %lld\tphilo %s [%03d] %s %s\n\n", \
			philo->time / 1000, color(i), i, color(0), msg);
	}
	pthread_mutex_unlock(&philo->rules->lock[MSG]->lock);
}

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

bool	died_msg(t_rules *rules, t_philo *philo)
{
	bool	died;
	t_ll	check_meal;
	t_ll	current_time;
	int		i;

	i = philo->id;
	died = false;
	pthread_mutex_lock(&rules->lock[DEAD]->lock);
	if (!rules->lock[DEAD]->stat)
	{
		current_time = time_ms(philo);
		check_meal = current_time - philo->t_meal;
		if (check_meal > (rules->t_die))
		{
			rules->lock[DEAD]->stat = 1;
			died = true;
			printf(" %lld\tphilo %s [%03d] %s %s\n\n", \
			current_time / 1000, color(i), i, color(0), P_DEAD);
			debug_death(philo, rules, current_time, check_meal);
		}
	}
	died = rules->lock[DEAD]->stat;
	pthread_mutex_unlock(&rules->lock[DEAD]->lock);
	return (died);
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
