/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 16:43:25 by lilizarr          #+#    #+#             */
/*   Updated: 2023/09/20 17:44:58 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	print_intro(void)
{
	printf("\n%s     . . . . . .    \n  ..         42..", color(0));
	printf("\n ..             ..\n");
	printf(".     .. ..      ..\n..   .      .    ..\n");
	printf("..   .   .   .   ..\n");
	printf(" ..    ..    .   ..\n  ..        .    .\n");
	printf("    .. .. ..    ..\n\n%s", color(0));
}

char	*color(int idx)
{
	char	**s_color;

	s_color = (char *[]){
		"\x1B[0m", \
		"\x1B[31m", \
		"\x1B[32m", \
		"\x1B[33m", \
		"\x1B[34m", \
		"\x1B[35m", \
		"\x1B[36m", \
		"\x1B[40m", \
		"\x1B[41m", \
		"\x1B[42m", \
		"\x1B[43m", \
		"\x1B[44m", \
		"\x1B[45m", \
		"\x1B[46m", \
		"\x1B[47m", \
		"\x1B[48;5;0m\x1B[38;5;245m", \
	};
	if (idx > 15)
		idx = idx % 15;
	return (s_color[idx]);
}
