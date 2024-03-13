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

void	print_action(t_philo *philo)
{
	t_philo	philo_tmp;
	int		sum;

	if (D_PHI == 0)
		return ;
	philo_tmp = *philo;
	sum = philo->time % (philo->rules->t_eat + philo->rules->t_sleep);
	if (!died_msg(philo_tmp.rules, &philo_tmp))
		printf( \
		" %03lld [%lld]\t\t\t\t[%d][%d]{%d} => meal[%lld] \t sleep[%lld]\n", \
		t_mu_s(philo_tmp.rules) / 1000, t_mu_s(philo_tmp.rules), philo_tmp.id, \
		philo_tmp.id, philo_tmp.action, philo_tmp.t_meal, philo_tmp.sleep);
}

void	debug_thread_check(t_philo *philo, char *msg)
{
	if (D_PHI == 0)
		return ;
	if (!died_msg(philo->rules, philo))
	{
		printf(" %03lld [%lld]\t\t\t\t\t\t\t\t %s -> [%d]{%d}\n", \
		t_mu_s(philo->rules) / 1000, t_mu_s(philo->rules), \
		msg, philo->id, philo->action);
	}
}

void	print_ft_usleep(t_rules *rules, t_philo *philo, t_ll time, t_ll tmp)
{
	t_philo		philo_tmp;
	t_ll		current;

	if (D_PHI == 0)
		return ;
	philo_tmp = *philo;
	pthread_mutex_lock(&rules->lock[MSG]->lock);
	current = time_ms(&philo_tmp);
	if (!died_msg(rules, philo) || !meal_done(rules, philo, false))
	{
		if (time == -1 && rules->t_eat < current - philo_tmp.t_meal)
			printf( \
			" %lld [%lld]\t\t\t\t\t\t\t\t\t\t[%d][%d] DONE Eating\n", \
			current / 1000, current, philo->id, philo->right->id);
		else if (time >= 0 && tmp < current - time)
			printf( \
			" %lld [%lld]\t\t\t\t\t\t\t\t\t\t[%d][%d] DONE Sleeping\n", \
			current / 1000, current, philo->id, philo->id);
	}
	pthread_mutex_unlock(&rules->lock[MSG]->lock);
}

void	debug_death(t_philo *philo, t_rules *rules, t_ll time, t_ll check_meal )
{
	// if (D_PHI == 0)
	// {
	// 	printf( \
	// 	"\t\t\t\t\t\t\t*[%d]{%d} => meal[%lld | %lld] \tsleep[%lld| %lld]\n", \
	// 	philo->id, philo->action, philo->t_meal, \
	// 	time, philo->sleep, time);
	// 	printf("\t\t\t\t\t\t\t*[%d] ==> [%lld || %lld / %lld]\n", \
	// 	philo->id, philo->t_meal, death, rules->t_die / (t_ll)1000);
	// }
	// else
	{
		printf( \
		"\t\t\t\t\t*[%d]{%d} => meal[%lld | %lld] \tsleep[%lld| %lld]\n", \
		philo->id, philo->action, philo->t_meal, time, philo->sleep, time);
		printf("\t\t\t\t\t*[%d] ==> [%lld || %lld - %lld] = %lf\n", \
		philo->id, philo->t_meal, check_meal, rules->t_die, \
		(double)(check_meal - rules->t_die) / 1000);
	}
}

void	print_msg(t_rules *rules, t_philo *tmp)
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
