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
	time = t_mu_s(philo->rules->t_start);
	ms = time / (t_ll)1000;
	if (!check_mutex(philo->rules->lock[MSG]))
	{
		printf(" %03lld [%lld]\t\t\t\t\t\t\t\t\t\t%s %s %s-> [%d]{%d}\n", \
		ms, time, col, msg, font(0), philo->id, philo->action);
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

void	debug_death(t_philo *philo, t_rules *rules, t_ll time)
{
	t_ll	dead_extra;
	t_ll	starve;
	int		i;

	if (D_PHI == 0)
		return ;
	i = philo->id;
	printf("\t\t\t%s DEAD *[%d]{%d}\t\t%s\n", font(i), i, philo->action, font(0));
	dead_extra = rules->t_die + philo->t_extra;
	starve = philo->t_meal + rules->t_die;
	printf("\t\t\tRULES CURRENT =\t\t[%lld]\n", t_mu_s(rules->t_start));
	printf("\t\t\tCURRENT =\t\t[%lld]\n", time);
	printf("\t\t\tT_DEAD =\t\t[%lld]\n", rules->t_die);
	printf("\t\t\tP_MEAL =\t\t[%lld]\t\tP_SLEEP[%lld]\n", philo->t_meal, philo->sleep);
	printf("\n\t\t\tP_EXTRA =\t\t[%lld]\n", philo->t_extra);
	printf("\t\t\tP_MEAL =\t\t[%lld]\n", philo->t_meal);
	printf("\n\t\t\tCURRENT =\t\t[%lld]\n", time);
	printf("\t\t\tP_MEAL + DEAD =\t\t[%lld]\n", philo->t_meal + rules->t_die);
	printf("\t\t\tTIME - (P_MEAL + DEAD)=\t[%lld]\n", time - \
	(philo->t_meal + rules->t_die));
	printf("\n\t\t\tCURRENT =\t\t[%lld]\n", time);
	starve = philo->t_meal - rules->extra;
	printf("\t\t\tCURRENT =\t\t[%lld]\n", time);
	printf("\t\t\tstarve + DEAD =\t\t[%lld]\n", starve + rules->t_die);
	printf("\t\t\tTIME - (starve + DEAD)=\t[%lld]\n", time - \
	(starve + rules->t_die));
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
