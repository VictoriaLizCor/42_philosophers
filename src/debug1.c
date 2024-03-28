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

void	debug_thread_check(t_philo *philo, char *msg, char *col)
{
	t_ll	time;
	t_ll	ms;

	if (D_PHI == 0)
		return ;
	if (!check_mutex(philo->rules->lock[DEAD]))
	{
		time = t_mu_s(philo->rules->t_start);
		ms = time / (t_ll)1000;
		pthread_mutex_lock(&philo->rules->lock[PRINT]->lock);
		printf(" %03lld [%lld]\t\t\t\t\t\t\t\t\t\t%s %s %s-> [%d]{%d}\n", \
		ms, time, col, msg, font(0), philo->id, philo->action);
		pthread_mutex_unlock(&philo->rules->lock[PRINT]->lock);
	}
}

void	print_usleep(t_rules *rules, t_philo *philo, t_ll time, t_ll tmp)
{
	t_philo		philo_tmp;
	t_ll		current;
	t_ll		ms;

	if (D_PHI != 1)
		return ;
	philo_tmp = *philo;
	current = t_mu_s(rules->t_start);
	if (!check_mutex(rules->lock[DEAD]))
	{
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

void	debug_death(t_philo *philo, t_rules *rules, t_ll xtime, t_ll rtime)
{
	t_ll	starve;
	int		i;
	t_ll	ptime;
	t_ll		m_aux;

	if (D_PHI == 0)
		return ;
	i = philo->id;
	ptime = t_mu_s(philo->t_start);
	m_aux = (philo->t_meal / 1000) * 1000;
	printf("\t\t\tREAL TIME =\t\t[%lld]\n", rtime);
	printf("\t\t\tREAL TIME =\t\t[%lld]\n", xtime);
	printf("\t\t\tT_DEAD =\t\t[%lld]\n", rules->t_die);
	printf("\t\t\tP_MEAL =\t\t[%lld]\t\tP_SLEEP[%lld]\n", philo->t_meal, philo->sleep);
	printf("\t\t\tM_AUX =\t\t[%lld]\n", m_aux);
	printf("\n\t\t\tPHILO TIME =\t\t[%lld]\n", ptime);
	printf("\n");
	starve = rtime - (philo->t_meal);
	printf("\t\t\tREAL TIME - last_meal = [%lld] > [%lld] = {%d}\n", \
	starve, rules->t_die, starve > rules->t_die);
	starve =  ptime - m_aux;
	printf("\t\t\tREAL TIME - m_aux.    = [%lld] > [%lld] = {%d}\n", \
	starve, rules->t_die, starve > rules->t_die);
	starve = ptime - (philo->t_meal);
	printf("\t\t\tPHILO TIME - last_meal = [%lld] > [%lld] = {%d}\n", \
	starve, rules->t_die, starve > rules->t_die);
	printf("\n\t\t\tREAL TIME - last_meal = [%lld] > [%lld] = {%d}\n", \
	starve, rules->t_die, starve > rules->t_die);
	starve = ((ptime - philo->t_meal) / 1000) * 1000;
	printf("\t\t\tPHI TIME - last_meal = [%lld] > [%lld] = {%d}\n", \
	starve, rules->t_die, starve > rules->t_die);
	// printf("\t\t\tP_MEAL + DEAD =\t\t[%lld]\n", philo->t_meal + rules->t_die);
	// printf("\t\t\tSTARVE - TIME =\t\t[%lld]\n", \
	// starve - time);
	// printf("\n\t\t\t STARVE =\t\t[%lld]\n", time - philo->t_meal);
	// printf("\t\t\t TIME - P_MEAL - EXTRA =\t[%lld]\n", \
	// time - philo->t_meal - philo->t_extra);
	printf("\t\t\t T_EXTRA =\t\t[%lld]\n", philo->t_extra);
	printf("\n\n\t\t\t T_EXTRA =\t\t[%lld]\n", rules->extra);
	printf("\n\n\t\t\t t_start =\t\t[%lld]\n", rules->t_start);
	printf("\n\n\t\t\t current =\t\t[%lld]\n", get_time());
	printf("\n\n\t\t\t current =\t\t[%lld]\n", get_time() - philo->r_meal);
	// printf("\t\t\tT_DEAD + T_EXTRA=\t\t[%lld]\n", rules->t_die + philo->t_extra);
	// printf("\n\t\t\tCURRENT =\t\t[%lld]\n", time);
	// printf("\t\t\tTIME - (starve + DEAD)=\t[%lld]\n", time - (starve));
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
