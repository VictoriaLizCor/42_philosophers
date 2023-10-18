/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:29:47 by lilizarr          #+#    #+#             */
/*   Updated: 2023/10/18 17:39:12 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	take_eat(t_philo *philo, t_rules *rules, int i)
{
	if (died_msg(rules, philo, philo->id) == 1 || !philo->to_lock)
		return ;
	printf(" %lld\tphilo %s [%03d] %s %s has taken a fork %s\n", \
	current_time(rules), color(i), i, color(0), P_FORK, color(0));
	if (died_msg(rules, philo, philo->id) == 1)
		return ;
	printf(" %lld\tphilo %s [%03d] %s %s is    EATING     %s\n", \
	current_time(rules), color(i), i, color(0), P_EAT, color(0));
	philo->t_meal = current_time(rules);
	fprintf(stderr, "\t\t\t\t\t\t\t\t\t[%d] ==> %lld| %lld \n", \
	philo->id, philo->t_meal, rules->t_die);
	usleep(rules->t_eat * 1000);
}

static void	sleep_think(t_philo *philo, t_rules *rules, int i)
{
	if (died_msg(rules, philo, philo->id) == 1)
		return ;
	printf(" %lld\tphilo %s [%03d] %s %s is   SLEEPING    %s\n", \
	current_time(rules), color(i), i, color(0), P_SLEEP, color(0));
	if (died_msg(rules, philo, philo->id) == 1)
		return ;
	printf(" %lld\tphilo %s [%03d] %s %s is   THINKING    %s\n", \
	current_time(rules), color(i), i, color(0), P_THINK, color(0));
	usleep(rules->t_sleep * 1000);
}

void	philo_actions(t_philo *philo, t_rules *rules, int col)
{
	if (died_msg(rules, philo, philo->id))
		return ;
	if (philo->action == 1 && philo->to_lock)
		philo_actin_msg(current_time(rules), col, "has taken a fork", P_FORK);
	else if (philo->action == 2 && philo->to_lock)
	{
		philo_actin_msg(current_time(rules), col, "is   EATING    ", P_EAT);
		philo->t_meal = current_time(rules);
		fprintf(stderr, "\t\t\t\t\t\t\t\t\t[%d] ==> %lld| %lld \n", \
		philo->id, philo->t_meal, rules->t_die);
		usleep(rules->t_eat * 1000);
	}
	else if (philo->action == 3 && !philo->to_lock)
	{
		philo_actin_msg(current_time(rules), col, "is  SLEEPING   ", P_SLEEP);
		usleep(rules->t_sleep * 1000);
	}
	else if (philo->action == 4 && !philo->to_lock)
		philo_actin_msg(current_time(rules), col, "is  THINKING   ", P_THINK);
	philo->action++;
	if (philo->action > 4)
		philo->action = 1;
}

void	check_locks(t_philo *philo, t_philo *right, t_philo *left)
{
	if (!right || !left)
		return ;
	pthread_mutex_lock(&philo->fork.lock);
	philo_actions(philo, philo->d_rules, philo->id);
	if (!philo->fork.stat)
	{
		philo->fork.stat = true;
		if (!philo->to_lock)
		{
			pthread_mutex_lock(&right->fork.lock);
			if (!right->fork.stat)
			{
				right->fork.stat = true;
				philo->to_lock = right;
				// philo->to_lock->action += 2;
				philo_actions(philo->to_lock, philo->d_rules, philo->to_lock->id);
				// philo->to_lock->action++;
				// died_msg(philo->d_rules, philo, philo->id);
				// died_msg(philo->d_rules, philo->to_lock, philo->to_lock->id);
			}
			else
			{
				philo->to_lock->fork.stat = false;
				fprintf(stderr, "\t\t\t\t\t %s[%d][%d] unlock%s\n", color(philo->id), philo->id, philo->to_lock->id, color(0));
			}
			pthread_mutex_unlock(&philo->to_lock->fork.lock);
		}
	}
	else
	{
		philo->fork.stat = false;
		fprintf(stderr, "\t\t\t\t\t %s[%d][%d] unlock%s\n", color(philo->id), philo->id, philo->id, color(0));
	}
	// philo_actions(philo, philo->d_rules, philo->id);
	pthread_mutex_unlock(&philo->fork.lock);
}

static void	exe(t_philo *philo)
{
	t_rules	*rules;
	int		i;

	rules = philo->d_rules;
	i = 0;
	while (i++ < 10)
	{
		if (died_msg(rules, philo, philo->id))
			return ;
		check_locks(philo, philo->right, philo->left);
		philo_actions(philo, rules, philo->id);
		// philo->to_lock = NULL;
	}
}

void	start_threads(t_philo *philos, t_rules *rules, int *rand_array)
{
	int				i;
	int				res;
	struct timeval	start;

	i = 0;
	gettimeofday(&start, NULL);
	rules->t_start = (start.tv_sec * 1000) + (start.tv_usec / 1000);
	while (i < rules->n_philos)
	{
		res = pthread_create(&philos[rand_array[i]].thread, NULL, \
		(void *)exe, &philos[rand_array[i]]);
		if (res)
			error_thread(&philos[rand_array[i]], 0, errno);
		i++;
	}
	i = 0;
	while (i < rules->n_philos)
	{
		pthread_join(philos[rand_array[i]].thread, NULL);
		i++;
	}
}
