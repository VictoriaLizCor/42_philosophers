/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:50:46 by lilizarr          #+#    #+#             */
/*   Updated: 2023/11/14 16:38:24 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static long	generate_rand_num(long min, long max)
{
	struct timeval	tv;
	long			seed;

	gettimeofday(&tv, NULL);
	seed = (long)tv.tv_sec * 1000000 + (long)tv.tv_usec;
	seed ^= seed << 13;
	seed ^= seed >> 7;
	seed ^= seed << 17;
	return (min + (seed % (max - min + 1)));
}

static int	val_exist(long num, int arr[], int size)
{
	int	i;

	i = 0;
	while (i <= size)
	{
		if (arr[i] == num)
			return (1);
		i++;
	}
	return (0);
}

int	*random_non_repetive_values(int min, int max, int size)
{
	int		*array;
	int		i;
	int		random_num;

	array = (int *)malloc(size * sizeof(int));
	memset(array, min - 1, sizeof(int) * (size));
	i = 0;
	random_num = min - 1;
	while (i < size)
	{
		while (val_exist(random_num, array, i))
		{
			while (1)
			{
				random_num = (int)generate_rand_num(min, max - 1);
				if (random_num < 0 && random_num < min)
					random_num *= -1;
				if (random_num >= min && random_num <= max - 1)
					break ;
			}
		}
		array[i] = random_num;
		i++;
	}
	return (array);
}
