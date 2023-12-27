/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:23:58 by lilizarr          #+#    #+#             */
/*   Updated: 2023/12/27 11:44:34 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

t_ll	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	t.tv_sec *= 1e6;
	t.tv_usec += t.tv_sec;
	return ((t_ll)t.tv_usec);
}

// rules->t_start = ((start.tv_sec * 1000) + ((long)start.tv_usec / 1000));
t_ll	time_ms(t_philo *philo)
{
	t_ll	ms;
	t_ll	t;
	t_rules	*rules;

	rules = philo->rules;
	pthread_mutex_lock(&rules->lock_time.lock);
	t = (get_time());// / (t_ll)1000;
	ms = (t) - philo->t_start;
	pthread_mutex_unlock(&rules->lock_time.lock);
	return (ms);
}

t_ll	r_ms(t_rules *rules)
{
	t_ll	ms;
	t_ll	t;

	pthread_mutex_lock(&rules->lock_time.lock);
	t = (get_time());// / (t_ll)1000;
	ms = (t) - rules->t_start;
	pthread_mutex_unlock(&rules->lock_time.lock);
	return (ms);
}

bool	check_time(t_philo *philo, t_ll t1, t_ll t2)
{
	bool	res;
	t_ll	current;

	res = time_ms(philo) > t1 + (t2);
	return (res);
}

void	debug_ms(t_rules *rules, char **argv)
{
	// if (D_PHI == 0)
	// {
	// 	rules->t_die = (t_ll)ft_atol(argv[2]);
	// 	rules->t_eat = (t_ll)ft_atol(argv[3]);
	// 	rules->t_sleep = (t_ll)ft_atol(argv[4]);
	// }
	// else
	{
		rules->t_die = (t_ll)ft_atol(argv[2]) * (t_ll)1000;
		rules->t_eat = (t_ll)ft_atol(argv[3]) * (t_ll)1000;
		rules->t_sleep = (t_ll)ft_atol(argv[4]) * (t_ll)1000;
	}
}
