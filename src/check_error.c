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
		printf("%sERROR: ", warn(0));
	else if (exit_error == 0)
		printf("%s", color(0));
	else
		printf("%s", warn(1));
	if (id > 0 && str1)
		printf("%s from Thread: [%d]", str1, id);
	else if (id == 0 && str1)
		printf("%s", str1);
	else
		printf("*[%d] '%s'", id * -1, str1);
	if (str2)
	{
		printf(": ");
		printf("%s", str2);
	}
	printf("%s\n", color(0));
}

void	error_thread(void *data, int type)
{
	int	id;

	if (data)
		id = ((t_philo *)data)->id;
	if (type == 0)
		ft_error(id, "on Thread function", NULL, 1);
	else if (type == 1)
		ft_error(id, "on Mutex function ", NULL, 1);
	else if (type == 2)
	{
		id = 0;
		ft_error(id, "on Mutex destroy function ", NULL, 1);
	}
}

static void	check_values(char *cpy, int ac, char **argv, int *err)
{
	static bool	check;

	if ((*cpy == 0 && \
	(ft_atol(argv[ac]) < 1 || ft_atol(argv[ac]) > INT_MAX)) || *cpy != 0)
		*err += 1;
	if (*err == 1 && check == 0)
	{
		ft_error(0, "Invalid input values", NULL, 1);
		check = true;
		ft_error(0, "Valid values", " [1, 2147483647]", -1);
		ft_error(0, "Valid", \
		"\n ./philo [1]philosophers [2]die [3]eat [4]sleep [5]must_eat", 0);
	}
	if ((*cpy == 0 && \
	(ft_atol(argv[ac]) < 1 || ft_atol(argv[ac]) > INT_MAX)) || *cpy != 0)
		ft_error(-1 * ac, argv[ac], NULL, 1);
}

void	check_arguments(char **argv, int *err)
{
	char	*copy;
	int		ac;

	ac = 1;
	while (argv[ac])
	{
		copy = argv[ac];
		if (ft_strchr("+", *copy) || ft_isdigit(*copy))
			copy++;
		while (*copy && ft_isdigit(*copy))
			copy++;
		check_values(copy, ac, argv, err);
		ac++;
	}
	if (*err == 0 && ft_atol(argv[2]) <= ft_atol(argv[3]) + ft_atol(argv[4]))
	{
		ft_error(0, "Invalid input values", NULL, 1);
		ft_error(0, "Valid", \
		"\n ./philo [1]philosophers [2]die [3]eat [4]sleep [5]must_eat", 0);
		ft_error(0, "[2]time_to_die > [3]time_to_eat + [4]time_to_sleep", \
		NULL, 1);
		ft_error(0, "i.e. 1", "\n\t./philo 5 400 200 100", -1);
		ft_error(0, "i.e. 2", "\n\t./philo 5 400 200 100 4", -1);
		++*err;
	}
}
