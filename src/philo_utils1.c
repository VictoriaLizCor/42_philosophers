/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:29:47 by lilizarr          #+#    #+#             */
/*   Updated: 2023/10/23 10:36:21 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static bool	philo_lock_msg(t_philo *philo, t_philo *caller, t_philo *locked)
{
	bool	res;

	pthread_mutex_lock(&philo->msg.lock);
	/* DELETE */
	if (philo->action <= 4 && philo->action >= 0)
	{
		if (caller)
			fprintf(stderr, "\t\t\t\t\t\t[%d][%d]==> last_meal[%lld] \t action = %d", \
			philo->id, caller->id, philo->t_meal, philo->action);
		else
			fprintf(stderr, "\t\t\t\t\t\t[%d][%d]==> last_meal[%lld] \t action = %d", \
			philo->id, philo->id, philo->t_meal, philo->action);
		if (philo->to_lock)
			fprintf(stderr, "\t to_lock_id=%d\n", philo->to_lock->id);
		fprintf(stderr, "\n");
	}
	/*/////////*/
	res = 0;
	philo->action++;
	if (died_msg(philo->d_rules, philo) != 1)
	{
		if (philo->to_lock)
		{
			if (philo->action == 1)
				philo_msg(philo, "has taken a fork", P_FORK);
			if (philo->action == 2)
				philo_msg(philo, "is    EATING    ", P_EAT);
		}
		else if (!philo->to_lock)
		{
			if (philo->action == 3)
				philo_msg(philo, "is   SLEEPING   ", P_SLEEP);
			if (philo->action == 4)
				philo_msg(philo, "is   THINKING   ", P_THINK);
		}
	}
	else
		res = 1;
	pthread_mutex_unlock(&philo->msg.lock);
	return (res);
}

static bool	philo_actions(t_philo *philo, t_rules *rules, t_philo *lock)
{
	bool	res;

	res = 0;
	res = philo_lock_msg(philo, lock, philo);
	if (lock)
		philo_actions(lock, rules, NULL);
	if (philo->action == 1 && lock)
		res = philo_lock_msg(lock, philo, NULL);
	else if (philo->action == 2 && lock)
	{
		res = philo_lock_msg(lock, philo, NULL);
		philo->t_meal = philo->time;
		fprintf(stderr, "\t\t\t\t\t\t\t\t[%d] ==> %lld| %lld \t action = %d\n", \
		philo->id, philo->t_meal, rules->t_die, philo->action);
		res = ft_usleep(philo->d_rules, philo, rules->t_eat);
	}
	else if (philo->action == 3 && !philo->to_lock)
		res = ft_usleep(philo->d_rules, philo, rules->t_sleep);
	else if (philo->action == 4 && !philo->to_lock)
		philo->action = 0;
	return (res);
}

static bool	check_locks(t_philo *philo, t_philo *right, t_philo *left)
{
	int	res;

	res = 0;
	pthread_mutex_lock(&philo->fork.lock);
	if (right)
	{
		pthread_mutex_lock(&right->fork.lock);
		philo->to_lock = right;
		if (philo_actions(philo, philo->d_rules, philo->to_lock))
			res = 1;
		pthread_mutex_unlock(&philo->to_lock->fork.lock);
		philo->to_lock = NULL;
	}
	else if (!right && philo_actions(philo, philo->d_rules, NULL))
		res = 1;
	pthread_mutex_unlock(&philo->fork.lock);
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
	// while (i++<10)w
	{
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
