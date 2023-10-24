/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:29:47 by lilizarr          #+#    #+#             */
/*   Updated: 2023/10/24 11:00:07 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static bool	philo_lock_msg(t_philo *philo, t_philo *caller)
{
	bool	res;

	res = 0;
	philo->action++;
	if (died_msg(philo->d_rules, philo) != 1)
	{
		if (philo->action == 1 && philo->to_lock)
			philo_msg(philo, "has taken a fork", P_FORK);
		else if (philo->action == 2 && philo->to_lock)
			philo_msg(philo, "is    EATING    ", P_EAT);
		else if (philo->action == 3)
			philo_msg(philo, "is   SLEEPING   ", P_SLEEP);
		else if (philo->action == 4)
		{
			philo_msg(philo, "is   THINKING   ", P_THINK);
			philo->action = 0;
		}
	}
	else
		res = 1;
	/* DELETE */
	if (philo->action <= 4 && philo->action >= 0)
	{
		pthread_mutex_lock(&philo->msg.lock);
		if (philo->to_lock)
			fprintf(stderr, " %lld \t\t\t\t\t\t[%d][%d]==> last_meal[%lld] \t action = %d", \
			current_time(philo->d_rules->t_start), philo->id, philo->to_lock->id, philo->t_meal, philo->action);
		else
			fprintf(stderr, " %lld \t\t\t\t\t\t[%d][%d]==> last_meal[%lld] \t action = %d", \
			current_time(philo->d_rules->t_start), caller->id, philo->id, philo->t_meal, philo->action);
		fprintf(stderr, "\n");
		pthread_mutex_unlock(&philo->msg.lock);
	}
	/*/////////*/
	return (res);
}

	// if (lock)
	// 	lock->action++;
	// if (lock)
	// 	philo_actions(lock, rules, NULL);
static bool	philo_actions(t_philo *philo, t_rules *rules, t_philo *lock)
{
	bool	res;

	res = philo_lock_msg(philo, philo);
	if (!res)
	{
		if (philo->action == 1 && lock)
			res = philo_lock_msg(lock, philo);
		if (philo->action == 2 && lock)
		{
			philo->t_meal = philo->time;
			fprintf(stderr, " %lld\t\t\t\t\t\t\t\t[%d] ==> %lld| %lld \t action = %d\n", \
			current_time(philo->d_rules->t_start), philo->id, philo->t_meal, rules->t_die, philo->action);
			res = ft_usleep(rules, philo, rules->t_eat);
		}
		else if (philo->action == 3 && !lock)
			res = ft_usleep(rules, philo, rules->t_sleep);
	}
	else
		res = 1;
	return (res);
}

static bool	check_locks(t_philo *philo, t_philo *right, t_philo *left)
{
	int	res;

	res = 0;
	{
		pthread_mutex_lock(&philo->fork.lock);
		fprintf(stderr, " %lld\t\t\t\t\t\t[%d]{%d}\n", \
		current_time(philo->d_rules->t_start), philo->id, philo->action);
		philo->to_lock = right;
		pthread_mutex_lock(&philo->to_lock->fork.lock);
		if (philo_lock_msg(philo->to_lock, philo) || \
			philo_actions(philo, philo->d_rules, philo->to_lock))
			res = 1;
		pthread_mutex_unlock(&philo->to_lock->fork.lock);
		philo->to_lock = NULL;
		pthread_mutex_unlock(&philo->fork.lock);
	}
	return (res);
}

static void	exe(t_philo *philo)
{
	t_rules	*rules;
	int		i;
	int		res;

	rules = philo->d_rules;
	i = 0;
	while (1)
	// while (i++<10)
	{
		if (!philo->right)
			res = philo_actions(philo, philo->d_rules, NULL);
		else
			res = check_locks(philo, philo->right, philo->left);
		if (res)
		{
			fprintf(stderr, "\t CHECK_LOCK[%d]_res[%d]\n", philo->id, res);
			if (philo->to_lock)
				pthread_mutex_unlock(&philo->to_lock->fork.lock);
			pthread_mutex_unlock(&philo->fork.lock);
			return ;
		}
		else
		{
			if (died_msg(rules, philo))
				return ;
		}
	}
}

void	start_threads(t_philo *philos, t_rules *rules, int *rand_array)
{
	int				i;
	int				res;
	struct timeval	start;

	i = 0;
	gettimeofday(&start, NULL);
	rules->t_start = ((start.tv_sec * 1000) + (start.tv_usec / 1000));
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
		if (pthread_join(philos[rand_array[i]].thread, NULL))
			return ;
		i++;
	}
}
