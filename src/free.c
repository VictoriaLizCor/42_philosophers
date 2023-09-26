/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:39:04 by lilizarr          #+#    #+#             */
/*   Updated: 2023/09/26 16:16:42 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	ft_free_threads(t_philo *philos, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		fprintf(stderr, "\t\t\t\t\t[%d]\n", philos[i].id);
		// if (pthread_mutex_destroy(&philos[i].fork))
		// 	error_thread(&philos[i], 1, errno);
		i++;
	}
	ft_memset(philos, 0, sizeof(t_philo) * (size));
	if (philos)
		free(philos);
}
