/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:50:46 by lilizarr          #+#    #+#             */
/*   Updated: 2023/10/18 12:07:15 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = c;
		i++;
	}
	return (s);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (!(*s) && !c)
		return ((char *)s);
	return (NULL);
}

long long	generate_rand_num(long long min, long long max)
{
	struct timeval	tv;
	long long		seed;

	gettimeofday(&tv, NULL);
	seed = (long long)tv.tv_sec * 1000000 + (long long)tv.tv_usec;
	seed ^= seed << 13;
	seed ^= seed >> 7;
	seed ^= seed << 17;
	return (min + (seed % (max - min + 1)));
}

int	val_exist(long long num, int arr[], int size)
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

int	*random_non_repetive_values(int min, int size)
{
	int		*array;
	int		i;
	int		random_num;

	array = (int *)malloc(size * sizeof(int));
	ft_memset(array, -1, sizeof(int) * (size));
	i = 0;
	random_num = -1;
	while (i < size)
	{
		while (val_exist(random_num, array, i))
		{
			while (1)
			{
				random_num = generate_rand_num(min, size -1);
				if (random_num > -1)
					break ;
			}
		}
		array[i] = random_num;
		i++;
	}
	return (array);
}
