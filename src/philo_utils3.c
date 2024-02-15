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

/*
even: t_eat + t_sleep + 100;
even: t_eat * 2 + t_sleep + 100;
*/
bool	ft_usleep(t_rules *rules, t_philo *philo, t_ll cnt, t_ll time)
{
	while (1)
	{
		if (died_msg(rules, philo))
			return (1); 
		print_ft_usleep(philo, time);
		if (time == -1)
		{
			if (died_msg(rules, philo->to_lock))
				return (1);
			else if (rules->t_eat < r_ms(rules) - philo->t_meal)
				return (died_msg(rules, philo));
			else if (cnt * rules->t_sleep < r_ms(rules) - philo->to_lock->sleep)
			{
				fprintf(stderr, " %lld \t\t\t%lld [%lld] %lld [%lld]\n", \
				r_ms(rules), \
				r_ms(rules), r_ms(rules) - rules->t_sleep, \
				cnt * rules->t_sleep, r_ms(rules) - philo->to_lock->sleep);
				lock_msg(philo->to_lock, philo, 0);
			}
			if (cnt * rules->t_sleep < r_ms(rules) - philo->to_lock->sleep)
			{
				fprintf(stderr, " %lld \t\t\t%lld [%lld] %lld [%lld] {%d}\n", \
				r_ms(rules), r_ms(rules) - cnt * rules->t_sleep, \
				cnt * rules->t_sleep, r_ms(rules) - philo->to_lock->sleep, philo->id);
				philo->to_lock->action = 2;
				lock_msg(philo->to_lock, philo, 0);
				cnt++;
			}
		}
		else if (rules->t_sleep < r_ms(rules) - time)
			return (died_msg(rules, philo));
		usleep(100);
	}
}
// fprintf(stderr, "\t\t\t%lld [%lld] %lld [%lld] {%d}\n", \
// cnt * rules->t_sleep , r_ms(rules) - philo->to_lock->sleep, \
// r_ms(rules) / 1000, (cnt * (philo->to_lock->sleep / 1000)), \
// philo->id);
// philo_msg(philo->to_lock, "is   THINKING  X", P_THINK, philo);
// philo_msg(philo->to_lock, "is   SLEEPING  X", P_SLEEP, philo);
// time_ms(philo) / 1000 > (cnt * (rules->t_sleep) / 1000)
// r_ms(rules) > time + cnt * rules->t_sleep

bool	philo_msg(t_philo *philo, char *msg, char *msg_color, t_philo *cal)
{
	int			i;

	pthread_mutex_lock(&philo->rules->lock_msg.lock);
	print_action(philo, cal);
	i = philo->id;
	if (!died_msg(philo->rules, philo))
	{
		philo->time = r_ms(philo->rules);
		printf(" %lld\tphilo %s [%03d] %s %s %s %s\n", \
		philo->time / 1000, color(i), i, color(0), msg_color, msg, color(0));
	}
	pthread_mutex_unlock(&philo->rules->lock_msg.lock);
	return (died_msg(philo->rules, philo));
}

bool	died_msg(t_rules *rules, t_philo *philo)
{
	bool	died;
	t_ll	last_meal;
	t_ll	currentTime;

	died = false;
	pthread_mutex_lock(&rules->lock_flags.lock);
	if (!rules->lock_flags.stat)
	{
		currentTime = r_ms(rules);
		last_meal = currentTime - philo->t_meal;
		if (rules->t_die < last_meal)
		{
			printf(" %lld\tphilo %s [%03d] %s %s %s %s\n", \
			currentTime / 1000, color(philo->id), philo->id, color(0), \
			P_DEAD, "      DIED      ", color(0));
			debug_death(philo, rules, currentTime, last_meal);
			rules->lock_flags.stat = 1;
			died = true;
		}
	}
	else
		died = true;
	pthread_mutex_unlock(&rules->lock_flags.lock);
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
	if (pthread_mutex_destroy(&rules->lock_flags.lock))
		error_thread(NULL, 2);
	if (pthread_mutex_destroy(&rules->lock_time.lock))
		error_thread(NULL, 2);
	if (pthread_mutex_destroy(&rules->lock_msg.lock))
		error_thread(NULL, 2);
	if (pthread_mutex_destroy(&rules->lock_count.lock))
		error_thread(NULL, 2);
	if (pthread_mutex_destroy(&rules->lock_start.lock))
		error_thread(NULL, 2);
}

/*
a
philo->pair tell if process starts with odd or even id
*/
void	wait_all(t_rules *rules, t_philo *philo, bool tmp, int size)
{
	static int	sum;

	while (1)
	{
		pthread_mutex_lock(&rules->lock_count.lock);
		if (!tmp++)
			sum += philo->id;
		if (sum == size && !rules->lock_count.stat)
		{
			rules->t_start = get_time();
			rules->pair = !(philo->id % 2);
			fprintf(stderr, "\t\t\tLAST[%d]{%d}", philo->id, rules->pair);
			if (philo-> left)
				fprintf(stderr, "\t\tLEFT{%d} action[ %d ]\n", philo->left->id, philo->action);
			rules->lock_count.stat = 1;
		}
		else if (rules->lock_count.stat)
			break ;
		pthread_mutex_unlock(&rules->lock_count.lock);
	}
	// if (rules->pair && !(philo->id % 2))
	// 	philo->action = 0;
	// else if (rules->pair && (philo->id % 2))
	// 	philo->action = 2;
	philo->t_start = rules->t_start;
	// fprintf(stderr, "\t{%d} action[ %d ]\n", philo->id, philo->action);
	pthread_mutex_unlock(&rules->lock_count.lock);
}
