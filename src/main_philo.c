/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:22:17 by lilizarr          #+#    #+#             */
/*   Updated: 2023/12/04 15:11:22 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	init_philos(t_rules *rules, t_philo **philos, int size)
{
	int	i;

	i = 0;
	*philos = (t_philo *)malloc(sizeof(t_philo) * (size));
	if (!philos)
		philos = NULL;
	memset(*philos, 0, sizeof(t_philo) * (size));
	while (i < size)
	{
		(*philos)[i].id = i + 1;
		(*philos)[i].action = 3;
		(*philos)[i].rules = rules;
		if (pthread_mutex_init(&(*philos + i)->fork.lock, NULL) != 0)
			ft_error(0, "in Mutex init", NULL, 1);
		i++;
	}
	init_neightbor(*philos, size - 1);
}

static void	init_rules_mutexes(t_rules *rules)
{
	int	i;

	i = 0;
	rules->lock = (t_mutex **)malloc(sizeof(t_mutex *) * (size_t)N_MUTEX);
	if (!rules->lock)
		(*rules->error)++;
	while (i < N_MUTEX && !*rules->error)
	{
		rules->lock[i] = (t_mutex *)malloc(sizeof(t_mutex));
		if (!rules->lock[i])
			(*rules->error)++;
		memset(&rules->lock[i]->stat, 0, sizeof(bool));
		if (pthread_mutex_init(&rules->lock[i]->lock, NULL) != 0)
			(*rules->error)++;
		i++;
	}
	if (*rules->error)
		ft_error(0, "in Mutex array", NULL, 1);
}

static void	init_rules(t_rules *rules, char **argv)
{
	rules->n_philos = ft_atol(argv[1]);
	rules->t_die = (t_ll)ft_atol(argv[2]) * (t_ll)1000;
	rules->t_eat = (t_ll)ft_atol(argv[3]) * (t_ll)1000;
	rules->t_sleep = (t_ll)ft_atol(argv[4]) * (t_ll)1000;
	rules->n_meals = -1;
	if (rules->n_philos > 2)
		rules->odd = rules->n_philos % 2;
	if (rules->odd)
		rules->extra = (3 * rules->t_eat);
	if (argv[5])
		rules->n_meals = (t_ll)ft_atol(argv[5]);
	init_rules_mutexes(rules);
}

static void	begin_hunger_games(char **argv, int *error)
{
	t_rules			rules;
	t_philo			*philos;
	int				*ran_val;
	int				i;

	i = 0;
	ran_val = NULL;
	rules.error = error;
	init_rules(&rules, argv);
	init_philos(&rules, &philos, rules.n_philos);
	if (!*rules.error)
	{
		ran_val = random_values(0, rules.n_philos, rules.n_philos);
		start_threads(philos, &rules, ran_val);
		free(ran_val);
	}
	destroy_mutex(philos, &rules);
	if (philos)
	{
		memset(philos, 0, sizeof(t_philo) * rules.n_philos);
		free(philos);
	}
}

int	main(int argc, char **argv, char **env)
{
	int	error;

	env++;
	error = 0;
	if (argc == 5 || argc == 6)
	{
		check_arguments(argv, &error);
		if (!error)
			begin_hunger_games(argv, &error);
	}
	else
	{
		ft_error(0, " Invalid input", NULL, ++error);
		ft_error(0, "Valid", \
		"\n ./philo philosophers die(ms) eat(ms) sleep(ms) must_eat", 0);
		ft_error(0, "i.e. 1", "\n\t./philo 5 400 200 100", -1);
		ft_error(0, "i.e. 2", "\n\t./philo 5 400 200 100 4", -1);
	}
	printf("\n");
	if (error)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
