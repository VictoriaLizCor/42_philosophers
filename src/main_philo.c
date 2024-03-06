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
	memset(*philos, 0, sizeof(t_philo) * (size));
	while (i < size)
	{
		(*philos + i)->id = i + 1;
		(*philos + i)->action = 2;
		(*philos + i)->n_meals = rules->n_meals;
		(*philos + i)->rules = rules;
		(*philos + i)->t_aux = rules->t_eat;
		(*philos + i)->t_extra = T_DIED_EXTRA;
		if (pthread_mutex_init(&(*philos + i)->fork.lock, NULL) != 0)
			printf("%sError in mutex init %s\n", warn(0), color(0));
		i++;
	}
	init_neightbor(*philos, size - 1);
}

static void	init_rules(t_rules *rules, char **argv)
{
	int		i;

	i = 0;
	// rules->lock = (t_mutex *)malloc (sizeof(t_mutex) * ((size_t)N_MUTEX));
	// memset(rules, 0, sizeof(t_rules));
	rules->lock = (t_mutex **)malloc(sizeof(t_mutex *) * (size_t)N_MUTEX);
	if (!rules->lock)
		rules->lock = NULL;
	rules->n_philos = (int)ft_atol(argv[1]);
	rules->t_die = (t_ll)ft_atol(argv[2]) * (t_ll)1000;
	rules->t_eat = (t_ll)ft_atol(argv[3]) * (t_ll)1000;
	rules->t_sleep = (t_ll)ft_atol(argv[4]) * (t_ll)1000;
	while (i < N_MUTEX)
	{
		rules->lock[i] = malloc(sizeof(t_mutex));
		rules->lock[i]->stat = false;
		if (pthread_mutex_init(&rules->lock[i]->lock, NULL) != 0)
			printf("%sError in mutex init %s\n", warn(0), color(0));
		i++;
	}
	if (argv[5])
		rules->n_meals = ft_atol(argv[5]);
}

static void	begin_hunger_games(char **argv)
{
	t_rules			rules;
	t_philo			*philos;
	int				*rand_array;
	int				i;

	i = 0;
	init_rules(&rules, argv);
	init_philos(&rules, &philos, rules.n_philos);
	rand_array = random_non_repetive_values(0, rules.n_philos, rules.n_philos);
	while (i < rules.n_philos)
		fprintf(stderr, "%d ", rand_array[i++] + 1);
	usleep(50);
	fprintf(stderr, "\n");
	start_threads(philos, &rules, rand_array);
	free(rand_array);
	destroy_mutex(philos, &rules);
	memset(philos, 0, sizeof(t_philo) * rules.n_philos);
	free(philos);
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
			begin_hunger_games(argv);
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
