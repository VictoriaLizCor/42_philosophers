/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:29:47 by lilizarr          #+#    #+#             */
/*   Updated: 2023/10/19 17:50:49 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	philo_actions(t_philo *philo, t_rules *rules, int col, int ext)
{
	if (died_msg(philo->d_rules, philo, philo->id))
		return (1);
	if (philo->action <= 4 && philo->action >= 0)
	{
		fprintf(stderr, "\t\t\t\t\t\t\t[%d][%d]==> last_meal[%lld] \t action = %d", \
		ext, col, philo->t_meal, philo->action);
		if (philo->to_lock)
			fprintf(stderr, "\t to_lock_id=%d\n", philo->to_lock->id);
		fprintf(stderr, "\n");
	}
	philo->action++;
	if (philo->action == 1 && philo->to_lock)
		philo_actin_msg(philo->t_current, col, "has taken a fork", P_FORK);
	else if (philo->action == 2 && philo->to_lock)
	{
		philo_actin_msg(philo->t_current, col, "is   EATING    ", P_EAT);
		philo->t_meal = philo->t_current;
		fprintf(stderr, "\t\t\t\t\t\t\t\t\t[%d] ==> %lld| %lld \n", \
		philo->id, philo->t_meal, rules->t_die);
		usleep(rules->t_eat * 1000);
	}
	else if (philo->action == 3 && !philo->to_lock)
	{
		philo_actin_msg(philo->t_current, col, "is  SLEEPING   ", P_SLEEP);
		usleep(rules->t_sleep * 1000);
	}
	else if (philo->action == 4 && !philo->to_lock)
		philo_actin_msg(philo->t_current, col, "is  THINKING   ", P_THINK);
	return (0);
}

int	check_locks(t_philo *philo, t_philo *right, t_philo *left)
{
	int	res;

	res = 0;
	pthread_mutex_lock(&philo->fork.lock);
	if (right)
	{
		pthread_mutex_lock(&right->fork.lock);
		philo->to_lock = right;
		if (philo_actions(philo, philo->d_rules, philo->id, philo->id) || \
		philo_actions(philo->to_lock, philo->d_rules, philo->to_lock->id, philo->id) || \
		philo_actions(philo->to_lock, philo->d_rules, philo->to_lock->id, philo->id))
		{
			res = 1;
		}
		pthread_mutex_unlock(&philo->to_lock->fork.lock);
		philo->to_lock = NULL;
	}
	else if (!right && philo_actions(philo, philo->d_rules, philo->id, philo->id))
	{
		res = 1;
	}
	pthread_mutex_unlock(&philo->fork.lock);
	return (res);
}

static void	exe(t_philo *philo)
{
	t_rules	*rules;
	int		i;

	rules = philo->d_rules;
	i = 0;
	while (1)
	{
		// pthread_mutex_lock(&rules->lock_flags.lock);
		// if (rules->lock_flags.stat)
		// {
		// 	philo_actin_msg(philo->t_current, i, "      DIED    ", P_DEAD);
		// }
		// pthread_mutex_unlock(&rules->lock_flags.lock);
		// if (died_msg(philo->d_rules, philo, philo->id))
		// 	return ;
		if (check_locks(philo, philo->right, philo->left))
			return ;
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
		philos[rand_array[i]].t_start = rules->t_start;
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
