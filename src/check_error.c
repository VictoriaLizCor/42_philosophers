/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 14:51:35 by lilizarr          #+#    #+#             */
/*   Updated: 2023/08/30 13:17:47 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	ft_error(char *str1, char *str2, int exit_error)
{
	if (exit_error > 0)
		printf("%sError!: ", CRED);
	if (str1)
		printf("%s", str1);
	if (str2)
	{
		printf(" : ");
		printf("%s", str2);
	}
	printf("%s\n", CNRM);
}

/*
should be <= 10000 and >= 60 ms.
[1] number_of_philosophers = forks
[2] time_to_die (in milliseconds)>  time_to_eat + time_to_sleep.
[3] time_to_eat (in milliseconds):
[4] time_to_sleep (in milliseconds):
[5] number_of_times_each_philosopher_must_eat
*/
void	check_values(int size, char **argv, int *error)
{
	int	ac;

	ac = 1;
	while (ac < size)
	{
		if (ft_atol(argv[ac]) <= 0 || ft_atol(argv[ac]) > INT_MAX)
		{
			printf("%sValid values (0, INT_MAX]%s\n", CRED, CNRM);
			*error += 1;
			break ;
		}
		ac++;
	}
	if (ft_atol(argv[2]) < ft_atol(argv[3]) + ft_atol(argv[4]))
	{
		printf("%sError!: time_to_die > time_to_eat + time_to_sleep %s\n", \
		CRED, CNRM);
		*error += 1;
	}
}

void	check_arguments(char **argv, int *error)
{
	char	*copy;
	int		ac;

	ac = 1;
	*error = 0;
	while (argv[ac])
	{
		if (!ft_strlen(argv[ac]))
		{
			printf("%sError!: arg[%d] : Invalid input value%s\n", \
			CRED, ac, CNRM);
		}
		copy = argv[ac];
		if (ft_strchr("+", *copy) || ft_isdigit(*copy))
			copy++;
		while (*copy && ft_isdigit(*copy))
			copy++;
		if (!ft_isdigit(*copy) && *copy != 0 && *error == 0)
		{
			printf("%sError!: Invalid input value%s\n", CRED, CNRM);
			*error += 1;
		}
		ac++;
	}
	check_values(ac, argv, &*error);
}
