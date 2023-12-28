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
bool	ft_usleep(t_rules *rules, t_philo *philo, t_ll cnt, int opt)
{
	while (1)
	{
		if (died_msg(rules, philo))
			return (1); 
		print_ft_usleep(philo, opt);
		if (opt == 2 && philo->to_lock)
		{
			if (died_msg(rules, philo->to_lock))
				return (1);
			else if (time_ms(philo) >= philo->t_meal + rules->t_eat)
				return (died_msg(rules, philo));
			else if (rules->t_sleep > \
				r_ms(rules) - philo->to_lock->sleep + rules->t_sleep)
			{
				fprintf(stderr, "%lld [%lld] {%d}\n", time_ms(philo), \
				(cnt * (philo->to_lock->sleep + rules->t_sleep)), philo->id);
				philo_msg(philo->to_lock, "is   THINKING   ", P_THINK, philo);
				usleep(100);
				philo_msg(philo->to_lock, "is   SLEEPING   ", P_SLEEP, philo);
				philo->to_lock->action = 3;
			}
		}
		else if (time_ms(philo) > (philo->sleep + rules->t_sleep))
			return (died_msg(rules, philo));
		usleep(100);
	}
}
// fprintf(stderr, "%lld [%lld] {%d}\n", time_ms(philo), \
// (cnt * (philo->to_lock->sleep + rules->t_sleep)), philo->id);
// fprintf(stderr, "%lld [%lld] {%d}\n", time_ms(philo),
// (cnt * (philo->to_lock->sleep + rules->t_sleep)), 
// (philo->to_lock->sleep + rules->t_sleep) < time_ms(philo));
// fprintf(stderr, " [%lld][%lld] | %lld --> %lld \n",
// cnt, tmp,time_ms(philo) / (rules->t_sleep * cnt), 
// time_ms(philo) % (rules->t_sleep * cnt));

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
	bool	res;
	t_ll	death;
	t_ll	time;

	res = 0;
	pthread_mutex_lock(&rules->lock_flags.lock);
	if (!rules->lock_flags.stat)
	{
		time = r_ms(rules);
		death = (time - philo->t_meal);
		if (death > rules->t_die + 2000)
		{
			printf(" %lld\tphilo %s [%03d] %s %s %s %s\n", \
			time / 1000, color(philo->id), philo->id, color(0), \
			P_DEAD, "      DIED      ", color(0));
			debug_death(philo, rules, time, death);
			rules->lock_flags.stat = 1;
			res = 1;
		}
	}
	else
		res = 1;
	pthread_mutex_unlock(&rules->lock_flags.lock);
	return (res);
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
			ft_memset(&philos[i], 0, sizeof(t_philo));
			i++;
		}
	}
	if (pthread_mutex_destroy(&rules->lock_flags.lock))
		error_thread(&rules->lock_flags.stat, 2);
	if (pthread_mutex_destroy(&rules->lock_time.lock))
		error_thread(&rules->lock_time.stat, 2);
	if (pthread_mutex_destroy(&rules->lock_msg.lock))
		error_thread(&rules->lock_msg.stat, 2);
	if (pthread_mutex_destroy(&rules->lock_count.lock))
		error_thread(&rules->lock_msg.stat, 2);
}

/*
a
philo->p_start tell if process starts with odd or even id
*/
void	wait_all(t_rules *rules, t_philo *philo, bool tmp, int size)
{
	static int	sum;

	while (1)
	{
		pthread_mutex_lock(&rules->lock_count.lock);
		if (!tmp++)
			sum += philo->id;
		if (sum == size)
		{
			if (!rules->lock_count.stat)
			{
				rules->t_start = get_time();
				rules->pair = !(philo->id % 2);
				fprintf(stderr, "LAST[%d]{%d}\n\n", philo->id, rules->pair);
				rules->lock_count.stat = 1;
			}
			else
				break ;
		}
		pthread_mutex_unlock(&rules->lock_count.lock);
	}
	if (rules->pair && !(philo->id % 2))
		philo->action = 0;
	else if (rules->pair && (philo->id % 2))
		philo->action = 2;
	fprintf(stderr, "{%d} action[ %d ]\n", philo->id, philo->action);
	pthread_mutex_unlock(&rules->lock_count.lock);
}
