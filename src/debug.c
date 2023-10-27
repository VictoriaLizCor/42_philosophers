/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:20:38 by lilizarr          #+#    #+#             */
/*   Updated: 2023/10/27 16:33:26 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>


void	print_action(t_philo *philo, t_philo *caller)
{
	if (DEBUG_PHI == 0 && !died_msg(philo->d_rules, philo))
		return ;
	if (philo->action >= 0 && philo->action <= 4)
	{
		pthread_mutex_lock(&philo->msg.lock);
		if (philo->to_lock)
			fprintf(stderr, \
			" %lld \t\t\t\t\t\t[%d][%d]{%d} => meal[%lld] \t sleep[%lld]\n", \
			current_time(philo->d_rules->t_start), philo->id, \
			caller->id, philo->action, philo->t_meal, philo->t_sleep);
		else
			fprintf(stderr, \
			" %lld \t\t\t\t\t\t[%d][%d]{%d} => meal[%lld] \t sleep[%lld]\n", \
			current_time(philo->d_rules->t_start), caller->id, \
			philo->id, philo->action, philo->t_meal, philo->t_sleep);
		pthread_mutex_unlock(&philo->msg.lock);
	}
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
			philo->t_meal, philo->t_sleep);
		else
			fprintf(stderr, \
			" %lld \t\t\t\t\t\t*[%d]{%d} => meal[%lld] \t sleep[%lld]\n", \
			current_time(rules->t_start), philo->id, philo->action, \
			philo->t_meal, philo->t_sleep);
	}
}
