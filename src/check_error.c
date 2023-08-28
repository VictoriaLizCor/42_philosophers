/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 14:51:35 by lilizarr          #+#    #+#             */
/*   Updated: 2023/08/28 16:55:37 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	ft_error(void)
{
	printf("Error\n");
	exit(EXIT_FAILURE);
}

void	check_integers(char **argv)
{
	char	*copy;

	while (*argv)
	{
		if (!ft_strlen(*argv))
			ft_error();
		if (ft_atoi(*argv) <= 0 || ft_atoi(*argv) > INT_MAX)
			ft_error();
		copy = *(argv);
		if (ft_strchr("+", *copy) || ft_isdigit(*copy))
			copy++;
		while (*copy && ft_isdigit(*copy))
			copy++;
		if (!ft_isdigit(*copy))
		{
			if (!*copy && !ft_strchr("+", *(copy - 1)))
				argv++;
			else
				ft_error();
		}
	}
}
