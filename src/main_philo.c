/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:22:17 by lilizarr          #+#    #+#             */
/*   Updated: 2023/09/19 13:12:11 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	create_threat(t_philo **philos, int size)
{
	int	err;
	int	i;

	i = 0;
	while (philos[i])
	{
		if (i == 0)
		{
			(*philos)[i].left = philos[size - 1];
			(*philos)[i].right = philos[i + 1];
		}
		else if (i == size - 1)
		{
			(*philos)[i].left = philos[i - 1];
			(*philos)[i].right = philos[0];
		}
		else
		{
			(*philos)[i].left = philos[i - 1];
			(*philos)[i].right = philos[i + 1];
		}
		i++;
	}
}

// *(philos + rules->n_philos) = NULL;
// while (i < rules->n_philos)
// 	{
// 		philos[i]->id = i + 1;
// 		philos[i]->d_rules = rules;
// 		philos[i]->n_to_eat = rules->n_to_eat;
// 		err = pthread_create(&philos[i]->thread, NULL, \
// 		(void *)func, philos[i]);
// 		if (err != 0)
// 			error_thread(philos[i], 0, errno);
// 		i++;
// 	}
		// (*philos + i)->id = i + 1;
		// (*philos + i)->d_rules = rules;
		// (*philos + i)->n_to_eat = rules->n_to_eat;
		// err = pthread_create(&(*philos + i)->thread, NULL, \
		// (void *)func, (*philos + i));
		// if (err != 0)
		// 	error_thread((*philos + i), 0, errno);
		// i++;
static void	init_philos(t_rules *rules, t_philo **philos)
{
	int	i;
	int	err;
	int	j;

	i = 0;
	j = 0;
	*philos = (t_philo *)malloc(sizeof(t_philo) * (rules->n_philos));
	if (!philos)
		philos = NULL;
	ft_memset(*philos, 0, sizeof(t_philo) * (rules->n_philos));
	while (i < rules->n_philos)
	{
		(*philos + i)->id = i + 1;
		(*philos + i)->d_rules = rules;
		(*philos + i)->n_to_eat = rules->n_to_eat;
		err = pthread_create(&(*philos + i)->thread, NULL, \
		(void *)func, (void *)(*philos + i));
		if (err != 0)
			error_thread((*philos + i), 0, errno);
		(*philos + i)->get_time = (void *)current_timestamp;
		i++;
	}
	create_threat(&*philos, rules->n_philos);
}

static void	init_rules(t_rules *rules, char **argv)
{
	printf("eat: %ld | sleep: %ld | die %ld \n", \
	ft_atol(argv[3]), ft_atol(argv[4]), ft_atol(argv[2]));
	rules->n_philos = ft_atol(argv[1]);
	rules->t_die = ft_atol(argv[2]);
	rules->t_eat = ft_atol(argv[3]);
	rules->t_sleep = ft_atol(argv[4]);
	rules->n_to_eat = 0;
	if (argv[5])
		rules->n_to_eat = ft_atol(argv[5]);
}

static void	begin_hunger_games(char **argv)
{
	t_rules		rules;
	t_philo		*philos;

	init_rules(&rules, argv);
	gettimeofday(&rules.t_start, NULL);
	printf("philosophers: %d\n", rules.n_philos);
	init_philos(&rules, &philos);
	printf("\t\t\t--\n");
}
// print_msg(&rules, &philos);
// printf("philo [%d] is %s THINKING %s\n", philos[0].id, P_THINK, CNRM);

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
		printf("%sError: Invalid input %s\n", CRED, CNRM);
		printf("Valid:\n" \
		"./philo number_of_philosophers t_to_die(ms) " \
		"t_to_eat(ms) t_to_sleep(ms) " \
		"[number_of_times_each_philosopher_must_eat]\n");
		printf("%si.e.: 1: ./philo 7 98 23 54%s\n", CGRN, CNRM);
		printf("%si.e.: 2: ./philo 7 98 23 54 3%s\n", CGRN, CNRM);
	}
	return (0);
}
