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
	while (!died_msg(rules, philo))
	{
		print_ft_usleep(philo, time, limit);
		if (time == -1)
		{
			if (died_msg(rules, philo->to_lock) || \
				rules->t_eat < t_mu_s(rules) - philo->t_meal)
				return ;
			else if (t_mu_s(rules) > philo->t_meal + limit * rules->t_sleep)
			{
				lock_msg(philo->to_lock, philo);
				philo->to_lock->action = 2;
				usleep(50);
				lock_msg(philo->to_lock, philo);
				limit++;
			}
		}
		else if (limit < t_mu_s(rules) - time)
			return ;
		usleep(100);
	}
}
// philo_msg(philo->to_lock, "is   THINKING  X", P_THINK, philo);
// usleep(50);
// philo_msg(philo->to_lock, "is   SLEEPING  X", P_SLEEP, philo);
// philo->sleep = t_mu_s(philo->rules);
// philo->to_lock->action = 3;
// if (cnt < rules->t_eat / rules->t_sleep && \
// 			rules->t_sleep > philo->t_meal - cnt * rules->t_sleep)
// fprintf(stderr, "\t\t\t%lld [%lld] %lld [%lld] {%d}\n", \
// cnt * rules->t_sleep , t_mu_s(rules) - philo->to_lock->sleep, \
// t_mu_s(rules) / 1000, (cnt * (philo->to_lock->sleep / 1000)), \
// philo->id);
// philo_msg(philo->to_lock, "is   THINKING  X", P_THINK, philo);
// philo_msg(philo->to_lock, "is   SLEEPING  X", P_SLEEP, philo);
// time_ms(philo) / 1000 > (cnt * (rules->t_sleep) / 1000)
// t_mu_s(rules) > time + cnt * rules->t_sleep

void	philo_msg(t_philo *philo, char *msg, char *msg_color, t_philo *cal)
{
	int	i;

	pthread_mutex_lock(&philo->rules->lock_msg.lock);
	print_action(philo, cal); 
	i = philo->id;
	if (!died_msg(philo->rules, philo))
	{
		philo->time = t_mu_s(philo->rules);
		printf(" %lld\tphilo %s [%03d] %s %s %s %s\n\n", \
		philo->time / 1000, color(i), i, color(0), msg_color, msg, color(0));
	}
	pthread_mutex_unlock(&philo->rules->lock_msg.lock);
	return ;
}

bool	died_msg(t_rules *rules, t_philo *philo)
{
	bool	died;
	t_ll	check_meal;
	t_ll	current_time;

	died = false;
	pthread_mutex_lock(&rules->lock_flags.lock);
	if (!rules->lock_flags.stat)
	{
		current_time = t_mu_s(rules);
		check_meal = current_time - philo->t_meal;
		if (rules->t_die < check_meal)
		{
			rules->lock_flags.stat = 1;
			died = true;
			printf(" %lld\tphilo %s [%03d] %s %s %s %s\n", \
			current_time / 1000, color(philo->id), philo->id, color(0), \
			P_DEAD, "      DIED      ", color(0));
			debug_death(philo, rules, current_time, check_meal);
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
philo->pair tell if process starts with odd or even id
*/
void	wait_all(t_rules *rules, t_philo *philo, bool limit, int size)
{
	static int	sum;

	while (1)
	{
		pthread_mutex_lock(&rules->lock_count.lock);
		if (!limit++)
			sum += philo->id;
		if (sum == size && !rules->lock_count.stat)
		{
			rules->t_start = get_time();
			rules->pair = !(philo->id % 2);
			rules->lock_count.stat = 1;
			if (rules->t_sleep > rules->t_eat)
				rules->t_aux = rules->t_sleep;
			fprintf(stderr, "\t\t\tLAST[%d]{%d}\n", philo->id, rules->pair);
		}
		if (rules->lock_count.stat)
			break ;
		pthread_mutex_unlock(&rules->lock_count.lock);
	}
	philo->t_start = rules->t_start;
	pthread_mutex_unlock(&rules->lock_count.lock);
}
			// fprintf(stderr, "\t\t\tLAST[%d]{%d}\n", philo->id, rules->pair);
			// if (philo-> left)
			// 	fprintf(stderr, "\t\tLEFT{%d} action[ %d ]\n", philo->left->id, philo->action);
	// fprintf(stderr, "\t{%d} action[ %d ]\n", philo->id, philo->action);

