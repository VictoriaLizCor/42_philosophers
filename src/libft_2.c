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

char	*font(int idx)
{
	char	**s_color;

	s_color = (char *[]){
		"\x1B[0m", \
		"\x1B[48;5;255m\x1B[38;5;1m", \
		"\x1B[41m", \
		"\x1B[48;5;255m\x1B[38;5;2m", \
		"\x1B[42m", \
		"\x1B[48;5;255m\x1B[38;5;3m", \
		"\x1B[43m", \
		"\x1B[48;5;255m\x1B[38;5;4m", \
		"\x1B[44m", \
		"\x1B[48;5;255m\x1B[38;5;5m", \
		"\x1B[45m", \
		"\x1B[48;5;255m\x1B[38;5;6m", \
		"\x1B[46m", \
		"\x1B[48;5;255m\x1B[38;5;8m", \
		"\x1B[48;5;8m\x1B[38;5;255m", \
		"\x1B[48;5;255m\x1B[38;5;208m", \
		"\x1B[48;5;208m\x1B[38;5;255m", \
	};
	if (idx > 16)
		idx = (idx % 16);
	return (s_color[idx]);
}

char	*warn(int idx)
{
	char	**s_color;

	s_color = (char *[]){
		"\x1B[31m", \
		"\x1B[32m", \
	};
	return (s_color[idx]);
}

static long	generate_rand_num(long min, long max)
{
	unsigned long long	seed;

	seed = (unsigned long long)get_time();
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

/*
  ** @brief:Create an array of non repetitive random numbers.
  **
  ** @param[in]: min value to start.
  ** @param[in]: max value to end.
  ** @param[in]: size of the array.
  ** @return     array
  ** file :libft2.c
*/
int	*random_values(int min, int max, int size)
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
