/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 14:51:35 by lilizarr          #+#    #+#             */
/*   Updated: 2023/10/27 12:58:28 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	ft_error(int id, char *str1, char *str2, int exit_error)
{
	if (exit_error > 0)
		printf("%sError!: ", warn(0));
	if (str1)
		printf("%s from thread: %d", str1, id);
	if (str2)
	{
		printf(" : ");
		printf("%s", str2);
	}
	printf("%s\n", color(0));
}

void	error_thread(void *data, int type)
{
	int	id;

	id = ((t_philo *)data)->id;
	if (type == 0)
		ft_error(id, "on Thread function", NULL, 1);
	else if (type == 1)
		ft_error(id, "on Mutex function ", NULL, 1);
	else if (type == 2)
	{
		id = 0;
		ft_error(id, "on Mutex function ", NULL, 1);
	}
}

static void	check_values(int size, char **argv, int *error)
{
	int	ac;

	ac = 1;
	while (ac < size)
	{
		if (ft_atol(argv[ac]) <= 0 || ft_atol(argv[ac]) > INT_MAX)
		{
			printf("%sValid values (0, INT_MAX]%s\n", warn(0), color(0));
			*error += 1;
			break ;
		}
		ac++;
	}
	if (ft_atol(argv[2]) <= ft_atol(argv[3]) + ft_atol(argv[4]))
	{
		printf("%sError!: time_to_die > time_to_eat + time_to_sleep %s\n", \
		warn(0), color(0));
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
			warn(0), ac, color(0));
		}
		copy = argv[ac];
		if (ft_strchr("+", *copy) || ft_isdigit(*copy))
			copy++;
		while (*copy && ft_isdigit(*copy))
			copy++;
		if (!ft_isdigit(*copy) && *copy != 0 && *error == 0)
		{
			printf("%sError!: Invalid input value%s\n", warn(0), color(0));
			*error += 1;
		}
		ac++;
	}
	check_values(ac, argv, &*error);
}
