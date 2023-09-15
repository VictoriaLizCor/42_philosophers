/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:22:17 by lilizarr          #+#    #+#             */
/*   Updated: 2023/09/15 13:53:10 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

//(*philos + i)
static void	create_threat(t_philo *philos)
{
	int	err;
	int	i;

	i = 0;
	err = philos[0].d_rules->n_philos;
	while (i < err)
	{
		printf(" %d\t", philos[i].id);
		i++;
	}
	// while (philos[i])
	// {
	// 	printf(" %d\t", philos[0].id);
	// 	i++;
	}
	// while (philos[i])
	// {
	// 	err = pthread_create(&philos[i]->thread, NULL, \
	// 	(void *)func, philos[i]);
	// 	if (err != 0)
	// 		error_thread(&(*philos + i)->thread, 0, errno);
	// 	if (i == 0)
	// 	{
	// 		philos[i]->left = (philos[(philos->d_rules->n_philos - 1)]);
	// 		(*philos + i)->right = (*philos + 1);
	// 	}
	// 	else if (i == rules->n_philos - 1)
	// 	{
	// 		(*philos + i)->left = (*philos - 1);
	// 		(*philos + i)->right = (*philos);
	// 	}
	// 	else
	// 	{
	// 		(*philos + i)->left = (*philos + i);
	// 		(*philos + i)->right = (*philos + i + 1);
	// 	}
	// }
}

static void	init_philos(t_rules *rules, t_philo **philos)
{
	int	i;

	i = 0;
	gettimeofday(&rules->t_start, NULL);
	*philos = (t_philo *)malloc(sizeof(t_philo) * (rules->n_philos + 1));
	if (!philos)
		philos = NULL;
	*(philos + rules->n_philos) = NULL;
	while (i < rules->n_philos)
	{
		(*philos + i)->id = i + 1;
		(*philos + i)->d_rules = rules;
		(*philos + i)->n_to_eat = rules->n_to_eat;
		(*philos + i)->get_time = &current_timestamp;
		i++;
	}
	create_threat(&philos);
}

static void	init_rules(t_rules *rules, char **argv)
{
	rules->n_philos = ft_atol(argv[1]);
	rules->t_die = ft_atol(argv[2]);
	rules->t_eat = ft_atol(argv[3]);
	rules->t_sleep = ft_atol(argv[4]);
	rules->n_to_eat = 0;
	if (argv[5])
		rules->n_to_eat = ft_atol(argv[5]);
}

static void	begin_hunger_games(t_rules *rules, char **argv)
{
	int				i;
	t_philo			*philos;

	init_rules(&*rules, argv);
	printf("philosophers: %d\n", rules->n_philos);
	init_philos(&*rules, &philos);
	i = 1;
	usleep(rules->t_sleep * 1000);
	printf(" %lld\t", philos[0].get_time(&*rules));
	printf("%s THINKING %s\n", P_THINK, CNRM);
	usleep(rules->t_sleep * 1000);
	printf(" %lld\t", philos[0].get_time(&*rules));
	printf("%s  EATING  %s\n", P_EAT, CNRM);
	printf(" %lld \t%s SLEEPING %s\n", \
	current_timestamp(&*rules), P_SLEEP, CNRM);
	printf(" %lld \t%s   DIED   %s\n", \
	philos[0].get_time(&*rules), P_DEAD, CNRM);
	printf("\t\t\t--\n");
}

int	main(int argc, char **argv, char **env)
{
	t_rules		rules;
	int			error;

	env++;
	if (argc == 5 || argc == 6)
	{
		check_arguments(argv, &error);
		if (error)
			return (printf("%d\n", error));
		begin_hunger_games(&rules, argv);
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
