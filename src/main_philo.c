/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:22:17 by lilizarr          #+#    #+#             */
/*   Updated: 2023/10/16 16:45:46 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	init_neightbor(t_philo *philos, int size)
{
	int	i;

	i = 0;
	if (!size)
	{
		philos[i].left = (void *)0;
		philos[i].right = (void *)0;
		return ;
	}
	while (i <= size)
	{
		if (i == 0)
			philo_neightbor(philos, i, size, i + 1);
		else if (i != size)
			philo_neightbor(philos, i, i - 1, i + 1);
		else if (i == size)
			philo_neightbor(philos, i, i - 1, 0);
		i++;
	}
}

static void	init_philos(t_rules *rules, t_philo **philos, int size)
{
	int	i;

	i = 0;
	*philos = (t_philo *)malloc(sizeof(t_philo) * (size));
	if (!philos)
		philos = NULL;
	ft_memset(*philos, 0, sizeof(t_philo) * (size));
	while (i < size)
	{
		(*philos + i)->id = i + 1;
		(*philos + i)->d_rules = rules;
		(*philos + i)->n_to_eat = rules->n_to_eat;
		(*philos + i)->t_meal = 0;
		if (pthread_mutex_init(&(*philos + i)->fork.lock, NULL) != 0)
			printf("%sError in mutex init %s\n", warn(0), color(0));
		(*philos + i)->get_time = &current_time;
		i++;
	}
	init_neightbor(*philos, size - 1);
	print_msg(rules, *philos);
}

static void	init_rules(t_rules *rules, char **argv)
{
	rules->n_philos = ft_atol(argv[1]);
	rules->t_die = ft_atol(argv[2]);
	rules->t_eat = ft_atol(argv[3]);
	rules->t_sleep = ft_atol(argv[4]);
	rules->n_to_eat = 0;
	rules->death_flag.stat = false;
	if (pthread_mutex_init(&rules->death_flag.lock, NULL) != 0)
		printf("%sError in mutex init %s\n", warn(0), color(0));
	if (argv[5])
		rules->n_to_eat = ft_atol(argv[5]);
}

static void	begin_hunger_games(char **argv)
{
	t_rules			rules;
	t_philo			*philos;
	struct timeval	start;

	init_rules(&rules, argv);
	gettimeofday(&start, NULL);
	rules.t_start = (start.tv_sec * 1000) + (start.tv_usec / 1000);
	init_philos(&rules, &philos, rules.n_philos);
	start_threads(philos, rules.n_philos);
	if (philos)
	{
		destroy_mutex(philos, &rules);
		ft_memset(philos, 0, sizeof(t_philo) * rules.n_philos);
		free(philos);
	}
}

int	main(int argc, char **argv, char **env)
{
	int			error;

	env++;
	if (argc == 5 || argc == 6)
	{
		check_arguments(argv, &error);
		if (error)
			return (printf("%d\n", error));
		begin_hunger_games(argv);
	}
	else
	{
		printf("%sError: Invalid input %s\n", warn(0), color(0));
		printf("Valid:\n" \
		"./philo number_of_philosophers t_to_die(ms) " \
		"t_to_eat(ms) t_to_sleep(ms) " \
		"[number_of_times_each_philosopher_must_eat]\n");
		printf("%si.e.: 1: ./philo 7 98 23 54%s\n", warn(1), color(0));
		printf("%si.e.: 2: ./philo 7 98 23 54 3%s\n", warn(1), color(0));
	}
	return (0);
}
