/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:20:38 by lilizarr          #+#    #+#             */
/*   Updated: 2023/11/14 16:41:02 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	print_action(t_philo *philo, t_ll time)
{
	t_philo	philo_tmp;

	if (D_PHI != 1)
		return ;
	philo_tmp = *philo;
	if (!check_mutex(philo->rules->lock[DEAD]))
		printf(\
		" %03lld [%lld]\t\t\t\t[%d][%d]{%d} => meal[%d|%d][%lld] \t sleep[%lld]\n", \
		time / 1000, time, philo_tmp.id, philo_tmp.id, philo_tmp.action, \
		philo_tmp.n_meals, philo_tmp.rules->n_meals, philo_tmp.t_meal, \
		philo_tmp.sleep);
}

void	debug_thread_check(t_philo *tmp, char *msg, char *col)
{
	t_ll	time;
	t_ll	ms;
	t_philo	philo;

	philo = *tmp;
	if (D_PHI != 1 || check_mutex(philo.rules->lock[DEAD]))
		return ;
	pthread_mutex_lock(&philo.rules->lock[PRINT]->lock);
	time = t_mu_s(philo.rules->t_start);
	ms = time / (t_ll)1000;
	if (!philo.rules->lock[PRINT]->stat)
		printf(" %03lld [%lld]\t\t\t\t\t\t%s %s %s-> philo [%03d]{%d}\n", \
		ms, time, col, msg, font(0), philo.id, philo.action);
	pthread_mutex_unlock(&philo.rules->lock[PRINT]->lock);
}

void	print_usleep(t_rules *rules, t_philo *philo, t_ll time, t_ll tmp)
{
	t_philo		philo_tmp;
	t_ll		current;
	t_ll		ms;

	if (D_PHI != 1)
		return ;
	philo_tmp = *philo;
	if (!check_mutex(rules->lock[DEAD]))
	{
		current = t_mu_s(rules->t_start);
		ms = current / (t_ll)1000;
		if (time == -1 && rules->t_eat < current - philo_tmp.t_meal)
			printf(\
			" %lld [%lld]\t\t\t\t\t\t\t\t\t\t%s[%d][%d] DONE Eating%s\n", \
			ms, current, font(2), philo->id, philo->action, font(0));
		else if (time > 0 && tmp < current - time)
			printf(\
			" %lld [%lld]\t\t\t\t\t\t\t\t\t\t%s[%d][%d] DONE Sleeping%s\n", \
			ms, current, font(10), philo->id, philo->action, font(0));
		else if (time == 0 && \
		!check_fork(philo->right) && !check_fork(philo->left))
			printf(\
			" %lld [%lld]\t\t\t\t\t\t\t\t\t\t%s[%d][%d] DONE Thinking%s\n", \
			ms, current, font(12), philo->id, philo->action, font(0));
	}
}

void	debug_death(t_philo *philo, t_rules *rules, t_ll t_aux, t_ll rtime)
{
	t_ll	dead_meal;
	t_philo	left;

	if (D_PHI == 0 || check_mutex(rules->lock[DEAD]))
		return ;
	printf("\n\t\t\tTURN =\t\t[%lld]\n", (rtime / rules->t_eat) * rules->t_eat);
	printf("\n\t\t\tACTION =\t\t[%d]\n", philo->action);
	printf("\t\t\tREAL TIME =\t\t[%lld]\n", rtime);
	printf("\t\t\tP_MEAL =\t\t[%lld]\t\tP_SLEEP[%lld]\n", philo->t_meal, philo->sleep);
	printf("\t\t\tNEXT MEAL =\t\t[%lld] \t WAKEUP [%lld]\n", \
	philo->n_meal, philo->sleep + rules->t_sleep);
	printf("\n");
	if (philo->left)
	{
		left = *philo->left;
		printf("\t\t\t[%d]LEFT P_MEAL= \t[%lld]\n", left.id, left.t_meal);
		printf("\t\t\t[%d]LEFT UNLOCKL=\t[%lld]\n", \
		left.id, left.t_meal + left.rules->t_eat - 10);
	}
	printf("\t\t\tT_AUX TIME =\t\t[%lld]\n", t_aux);
	printf("\n");
	dead_meal = ((t_aux - philo->t_meal) / 1000) * 1000;
	printf("\t\t\tDEAD MEAL =\t\t[%lld]\n", dead_meal);
	printf("\n\t\t\t EXTRA = %lld \n", rules->extra);
}

void	print_neightbor(t_rules *rules, t_philo *tmp)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = tmp;
	while (i < rules->n_philos)
	{
		if (philos[i].left && philos[i].right)
		{
			printf("philo L %d  philo M %d [%p]|| philo R %d \n", \
			philos[i].left->id, philos[i].id, &philos[i], philos[i].right->id);
		}
		else
			printf("philo L %p | philo M %d || philo R %p\n", \
			philos[i].left, philos[i].id, philos[i].right);
		i++;
	}
	printf("\n");
}
