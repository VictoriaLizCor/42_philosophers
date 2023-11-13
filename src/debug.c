/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:20:38 by lilizarr          #+#    #+#             */
/*   Updated: 2023/11/13 16:45:56 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	print_action(t_philo *philo, t_philo *caller)
{
	t_philo	philo_tmp;
	int		sum;

	philo_tmp = *philo;
	sum = philo->time % (philo->rules->t_eat + philo->rules->t_sleep);
	if (D_PHI == 0 && !died_msg(philo_tmp.rules, philo))
		return ;
	if (philo_tmp.action >= 0 && philo_tmp.action <= 4)
	{
		if (odd_philo(philo) && !died_msg(philo_tmp.rules, &philo_tmp))
			fprintf(stderr, \
			" %lld \t\t\t\t\t\t[%d][%d]{%d} => meal[%lld] \t sleep[%lld] \t {%d}\n", \
			current_time(philo_tmp.rules), philo_tmp.id, philo_tmp.id, \
			philo_tmp.action, philo_tmp.t_meal, philo_tmp.sleep, sum);
		else if (philo_tmp.to_lock && !died_msg(philo_tmp.rules, &philo_tmp))
			fprintf(stderr, \
			" %lld \t\t\t\t\t\t[%d][%d]{%d} => meal[%lld] \t sleep[%lld]\n", \
			current_time(philo_tmp.rules), philo_tmp.id, \
			philo_tmp.id, philo_tmp.action, philo_tmp.t_meal, philo_tmp.sleep);
		else if (!died_msg(philo_tmp.rules, &philo_tmp))
			fprintf(stderr, \
			" %lld \t\t\t\t\t\t[%d][%d]{%d} => meal[%lld] \t sleep[%lld]\n", \
			current_time(philo_tmp.rules), caller->id, \
			philo_tmp.id, philo_tmp.action, philo_tmp.t_meal, philo_tmp.sleep);
	}
}

void	debug_thread_check(t_philo *philo, char *msg)
{
	if (D_PHI == 0)
		return ;
	fprintf(stderr, " %lld\t\t\t\t\t\t\t\t\t\t\t\t[%d]{%d} %s\n", \
	current_time(philo->rules), philo->id, philo->action, msg);
}

void	print_ft_usleep(t_philo *philo, int opt)
{
	t_philo		philo_tmp;
	long long	current;

	if (D_PHI == 0)
		return ;
	philo_tmp = *philo;
	pthread_mutex_lock(&philo->rules->lock_msg.lock);
	current = current_time(philo->rules);
	if (opt == 2 && current >= philo_tmp.t_meal + philo->rules->t_eat)
		fprintf(stderr, " %lld\t\t\t[%d] DONE Eating\n", current, philo->id);
	else if (opt == 3 && current > philo_tmp.sleep + philo->rules->t_sleep)
		fprintf(stderr, " %lld\t\t\t[%d] DONE Sleeping\n", current, philo->id);
	pthread_mutex_unlock(&philo->rules->lock_msg.lock);
}

void	print_death_action(t_philo *philo, t_rules *rules, long long time)
{
	if (D_PHI == 0)
		return ;
	if (philo->action <= 4 && philo->action >= 0)
	{
		fprintf(stderr, \
		"\t\t\t\t\t\t\t*[%d]{%d} => meal[%lld | %lld] \tsleep[%lld| %lld]\n", \
		philo->id, philo->action, philo->t_meal, \
		current_time(rules), philo->sleep, current_time(rules));
	}
	fprintf(stderr, "\t\t\t\t\t\t\t*[%d] ==> [%lld || %lld / %lld]\n", \
	philo->id, philo->t_meal, time, rules->t_die);
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
