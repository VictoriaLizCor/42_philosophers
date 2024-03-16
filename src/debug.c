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
	if (!check_mutex(philo->rules->lock[MSG]))
		printf(\
		" %03lld [%lld]\t\t\t\t[%d][%d]{%d} => meal[%lld] \t sleep[%lld]\n", \
		time / 1000, time, philo_tmp.id, philo_tmp.id, \
		philo_tmp.action, philo_tmp.t_meal, philo_tmp.sleep);
}

void	debug_thread_check(t_philo *philo, char *msg, char *col)
{
	t_ll	time;
	t_ll	ms;

	if (D_PHI != 1)
		return ;
	time = t_mu_s(philo->rules->t_start);
	ms = time / (t_ll)1000;
	if (!check_mutex(philo->rules->lock[MSG]))
	{
		printf(" %03lld [%lld]\t\t\t\t\t\t\t\t\t\t%s %s %s-> [%d]{%d}\n", \
		ms, time, col, msg, color(0), philo->id, philo->action);
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
	if (!check_mutex(rules->lock[MSG]))
	{
		ms = current / (t_ll)1000;
		if (time == -1 && rules->t_eat < current - philo_tmp.t_meal)
			printf(\
			" %lld [%lld]\t\t\t\t\t\t\t\t\t\t%s[%d][%d] DONE Eating%s\n", \
			ms, current, color(2), philo->id, philo->action, color(0));
		else if (time > 0 && tmp < current - time)
			printf(\
			" %lld [%lld]\t\t\t\t\t\t\t\t\t\t%s[%d][%d] DONE Sleeping%s\n", \
			ms, current, color(10), philo->id, philo->action, color(0));
		else if (time == 0 && (check_fork(philo)))
			printf(\
			" %lld [%lld]\t\t\t\t\t\t\t\t\t\t%s[%d][%d] DONE Thinking%s\n", \
			ms, current, color(12), philo->id, philo->action, color(0));
	}
}

void	debug_death(t_philo *philo, t_rules *rules, t_ll time, t_ll starve)
{
	t_ll	dead_extra;

	if (D_PHI == 0)
		return ;
	dead_extra = rules->t_die + philo->t_extra;
	printf("\t\t%sPHILOEXTRA [%lld]%s\n", color(15), philo->t_extra, color(0));
	printf(\
	"\t\t\t*[%d]{%d} => meal[%lld | %lld] \tsleep[%lld| %lld]\n", \
	philo->id, philo->action, philo->t_meal, time, philo->sleep, time);
	printf("\t\t\t*[%d] ==> [%lld || %lld - %lld] = %lf\n", \
	philo->id, philo->t_meal, dead_extra, starve, \
	(double)(dead_extra - starve) / 1000);
	printf("\t\t\tT_DEAD = \t\t[%lld]\n", rules->t_die);
	printf("\t\t\tDEAD EXTRA= \t\t[%lld]\n", dead_extra);
	printf("\t\t\tLAST MEAL = \t\t[%lld]\n", philo->t_meal);
	printf("\t\t\tTIME - lAST MEAL = \t[%lld]\n", starve);
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
