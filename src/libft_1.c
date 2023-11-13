/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 16:50:46 by lilizarr          #+#    #+#             */
/*   Updated: 2023/11/13 14:37:56 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

long long	current_time(t_rules *rules)
{
	time_t			ms;
	time_t			t1;
	time_t			t2;
	struct timeval	current;

	pthread_mutex_lock(&rules->lock_time.lock);
	gettimeofday(&current, NULL);
	t1 = (long)current.tv_sec * 1000;
	t2 = (long long)current.tv_usec / 1000;
	ms = (t1 + t2) - rules->t_start;
	if (ms < 0)
		ms = 0;
	pthread_mutex_unlock(&rules->lock_time.lock);
	return (ms);
}

size_t	ft_strlen(const char *str)
{
	size_t	cnt;

	cnt = 0;
	while (str[cnt])
		cnt++;
	return (cnt);
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
