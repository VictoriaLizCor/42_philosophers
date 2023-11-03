/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:20:38 by lilizarr          #+#    #+#             */
/*   Updated: 2023/11/03 12:04:41 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>


void	print_action(t_philo *philo, t_philo *caller)
{
	t_philo	philo_tmp;

	philo_tmp = *philo;
	if (DEBUG_PHI == 0 && !died_msg(philo_tmp.rules, philo))
		return ;
	if (philo_tmp.action >= 0 && philo_tmp.action <= 4)
	{
		pthread_mutex_lock(&philo_tmp.msg.lock);
		if (philo_tmp.to_lock && !died_msg(philo_tmp.rules, &philo_tmp))
			fprintf(stderr, \
			" %lld \t\t\t\t\t\t[%d][%d]{%d} => meal[%lld] \t sleep[%lld]\n", \
			current_time(philo_tmp.rules->t_start), philo_tmp.id, \
			philo_tmp.id, philo_tmp.action, philo_tmp.t_meal, philo_tmp.sleep);
		else if (!died_msg(philo_tmp.rules, &philo_tmp))
			fprintf(stderr, \
			" %lld \t\t\t\t\t\t[%d][%d]{%d} => meal[%lld] \t sleep[%lld]\n", \
			current_time(philo_tmp.rules->t_start), caller->id, \
			philo_tmp.id, philo_tmp.action, philo_tmp.t_meal, philo_tmp.sleep);
		pthread_mutex_unlock(&philo_tmp.msg.lock);
	}
}

void	debug_thread_check(t_philo *philo, char *msg)
{
	if (DEBUG_PHI == 0)
		return ;
	fprintf(stderr, " %lld\t\t\t\t\t\t\t\t\t\t\t\t[%d]{%d} %s\n", \
	current_time(philo->rules->t_start), philo->id, philo->action, msg);
}

void	print_ft_usleep(t_philo *philo, long long time, int opt)
{
	if (DEBUG_PHI == 0)
		return ;
	if (philo->time >= philo->t_meal + time && opt == 2)
		fprintf(stderr, " %lld\t\t\t\t[%d]DONE Eating\n", \
		current_time(philo->rules->t_start), philo->id);
	if (philo->time >= philo->sleep + time && opt == 3)
		fprintf(stderr, " %lld\t\t\t\t[%d]DONE Sleeping\n", \
		current_time(philo->rules->t_start), philo->id);
}

void	print_death_action(t_philo *philo, t_rules *rules, long long time)
{
	if (DEBUG_PHI == 0)
		return ;
	fprintf(stderr, "\t\t\t\t\t\t\t*[%d] ==> [%lld || %lld / %lld]\n", \
	philo->id, philo->t_meal, time, rules->t_die);
	if (philo->action <= 4 && philo->action >= 0)
	{
		if (philo->to_lock)
			fprintf(stderr, \
			" %lld \t\t\t\t\t\t*[%d]{%d} => meal[%lld] \t sleep[%lld]\n", \
			current_time(rules->t_start), philo->id, philo->action, \
			philo->t_meal, philo->sleep);
		else
			fprintf(stderr, \
			" %lld \t\t\t\t\t\t*[%d]{%d} => meal[%lld] \t sleep[%lld]\n", \
			current_time(rules->t_start), philo->id, philo->action, \
			philo->t_meal, philo->sleep);
	}
}
