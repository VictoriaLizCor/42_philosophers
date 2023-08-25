/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 12:49:11 by lilizarr          #+#    #+#             */
/*   Updated: 2023/08/25 12:57:12 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static	void	print_intro(void)
{
	printf("\n%s     . . . . . .    \n  ..         42..", CCYN);
	printf("\n ..             ..\n");
	printf(".     .. ..      ..\n..   .      .    ..\n");
	printf("..   .   .   .   ..\n");
	printf(" ..    ..    .   ..\n  ..        .    .\n");
	printf("    .. .. ..    ..\n\n%s", CNRM);
}

int	main(int argc, char *argv[], char *env[])
{
	print_intro();
	return (0);
}
/*
number_of_philosophers
time_to_die (in milliseconds):
time_to_eat (in milliseconds):
time_to_sleep (in milliseconds):
number_of_times_each_philosopher_must_eat
** the simulation stops when a philosopher dies.

Each philosopher has a number ranging from 1 to number_of_philosophers.
*/
