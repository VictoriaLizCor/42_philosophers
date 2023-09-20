/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 14:51:35 by lilizarr          #+#    #+#             */
/*   Updated: 2023/09/20 17:23:10 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	ft_error(t_philo *philo, char *str1, char *str2, int exit_error)
{
	if (exit_error > 0)
		printf("%sError!: %d", color(1), philo->id);
	if (str1)
		printf("%s", str1);
	if (str2)
	{
		printf(" : ");
		printf("%s", str2);
	}
	printf("%s\n", color(0));
}

void	error_thread(t_philo *philo, int type, int errnum)
{
	if (type == 0)
		ft_error(philo, "on Thread function", strerror(errnum), 1);
	else
		ft_error(philo, "on Mutex function ", NULL, 1);
}

static void	check_values(int size, char **argv, int *error)
{
	int	ac;

	ac = 1;
	while (ac < size)
	{
		if (ft_atol(argv[ac]) <= 0 || ft_atol(argv[ac]) > INT_MAX)
		{
			printf("%sValid values (0, INT_MAX]%s\n", color(1), color(0));
			*error += 1;
			break ;
		}
		ac++;
	}
	if (ft_atol(argv[2]) < ft_atol(argv[3]) + ft_atol(argv[4]))
	{
		printf("%sError!: time_to_die > time_to_eat + time_to_sleep %s\n", \
		color(1), color(0));
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
			color(1), ac, color(0));
		}
		copy = argv[ac];
		if (ft_strchr("+", *copy) || ft_isdigit(*copy))
			copy++;
		while (*copy && ft_isdigit(*copy))
			copy++;
		if (!ft_isdigit(*copy) && *copy != 0 && *error == 0)
		{
			printf("%sError!: Invalid input value%s\n", color(1), color(0));
			*error += 1;
		}
		ac++;
	}
	check_values(ac, argv, &*error);
}
