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
		debug_thread_check(philo, "\t\t EAT", 0);
	else
		debug_thread_check(philo, "\t\t SLEEP", 1);
	while (1)
	{
		print_ft_usleep(philo, time, limit);
		if (died_msg(rules, philo) || meal_done(rules, philo, false))
			return ;
		if (time == -1)
		{
			if (died_msg(rules, philo->to_lock) || \
				rules->t_eat < t_mu_s(rules) - philo->t_meal)
				return ;
			else if (t_mu_s(rules) > philo->t_meal + limit * rules->t_sleep)
			{
				lock_msg(philo->to_lock, philo);
				philo->to_lock->action = 2;
				lock_msg(philo->to_lock, philo);
				limit++;
			}
		}
		else if (limit < t_mu_s(rules) - time)
			return ;
		usleep(100);
	}
}

void	philo_msg(t_philo *philo, char *msg, char *msg_color, t_philo *cal)
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
		print_action(philo, cal);
		printf(" %lld\tphilo %s [%03d] %s %s %s %s\n\n", \
		philo->time / 1000, color(i), i, color(0), msg_color, msg, color(0));
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
	pthread_mutex_unlock(&rules->lock[MEAL]->lock);
	return (done);
}

// bool	died_msg(t_rules *rules, t_philo *philo)
// {
// 	bool	died;
// 	t_ll	check_meal;
// 	t_ll	current_time;

// 	pthread_mutex_lock(&rules->dead.lock);
// 	if (!rules->dead.stat)
// 	{
// 		current_time = t_mu_s(rules);
// 		check_meal = current_time - philo->t_meal;
// 		if (rules->t_die < check_meal)
// 		{
// 			rules->dead.stat = 1;
// 			printf(" %lld\tphilo %s [%03d] %s %s %s %s\n", \
// 			current_time / 1000, color(philo->id), philo->id, color(0), \
// 			P_DEAD, "      DIED      ", color(0));
// 			debug_death(philo, rules, current_time, check_meal);
// 		}
// 	}
// 	died = rules->dead.stat;
// 	pthread_mutex_unlock(&rules->dead.lock);
// 	return (died);
// }
bool	died_msg(t_rules *rules, t_philo *philo)
{
	bool	died;
	t_ll	check_meal;
	t_ll	current_time;

	died = false;
	pthread_mutex_lock(&rules->lock[DEAD]->lock);
	if (!rules->lock[DEAD]->stat)
	{
		current_time = t_mu_s(rules);
		check_meal = current_time - philo->t_meal;
		if (rules->t_die < check_meal)
		{
			rules->lock[DEAD]->stat = 1;
			died = true;
			printf(" %lld\tphilo %s [%03d] %s %s %s %s\n", \
			current_time / 1000, color(philo->id), philo->id, color(0), \
			P_DEAD, "      DIED      ", color(0));
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
