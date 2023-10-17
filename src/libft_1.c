/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:50:46 by lilizarr          #+#    #+#             */
/*   Updated: 2023/10/17 17:53:51 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

long long	generate_rand_num(long long min, long long max)
{
	struct timeval	tv;
	long long		random_num;
	long long		seed;

	gettimeofday(&tv, NULL);
	seed = (long long)tv.tv_sec * 1000000 + (long long)tv.tv_usec;

	seed ^= seed << 13;
	seed ^= seed >> 7;
	seed ^= seed << 17;
	random_num = min + (seed % (max - min + 1));
	if (random_num < 1)
	{
		random_num = (random_num * -1) + 1;
	}
	return (random_num);
}

int	*random_num_array(int min, int size)
{
	int		*array;
	int		i;
	int		j;
	int		random_num;

	array = (int *)malloc(size * sizeof(int));
	i = 0;
	while (i < size)
	{
		j = 0;
		random_num = generate_rand_num(min, size);
		while (j < i)
		{
			if (array[j] == random_num)
				break ;
			j++;
		}
		if (j == i)
		{
			array[i] = random_num;
			i++;
		}
	}
	return (array);
}

int	ft_isdigit(int ch)
{
	if (ch >= '0' && ch <= '9')
		return (1);
	return (0);
}

static long	max_values(long int *num, int *sign, char c)
{
	if (*num > LONG_MAX || ft_isdigit(c))
	{
		if (*sign == 1)
			return (-1);
		else
			return (0);
	}
	return ((*num * *sign));
}

long int	ft_atol(const char *s)
{
	long int	num;
	int			sign;

	num = 0;
	sign = 1;
	if (ft_strlen(s) == 0)
		return (num * sign);
	while (*s != '\0' && (ft_isdigit(*s) || ft_strchr(" +-\t\n\r\v\f", *s) != NULL))
	{
		if (num == 0 && *s == '-')
			sign = -1;
		if (ft_isdigit(*s))
		{
			num = num * 10 + (*s - '0');
			if (num / 100000000000000000 > 10)
				return (max_values(&num, &sign, *(s + 1)));
		}
		else if (num > 0)
			return (num * sign);
		if ((*s == '+' || *s == '-') && ft_strchr(" +-\t\n\r\v\f", *(s + 1)))
			return (0);
		s++;
	}
	return (num * sign);
}
