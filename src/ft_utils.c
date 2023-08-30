/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:29:47 by lilizarr          #+#    #+#             */
/*   Updated: 2023/08/30 16:43:22 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

long long	current_timestamp(t_rules *rules)
{
	long long	miliseconds;

	gettimeofday(&rules->t_end, NULL);
	miliseconds = ((rules->t_end.tv_sec - rules->t_start.tv_sec) * 1000LL + \
	(rules->t_end.tv_usec - rules->t_start.tv_usec) * 0.001);
	return (miliseconds);
}

// int	foo(void)
// {
// 	return (0);
// }

// t_hello	hello(void)
// {
// 	t_hello	a_hello;

// 	a_hello.some_function = &foo;
// 	return (a_hello);
// }
// int	main(void)
// {
// 	t_hello	a_hello;

// 	a_hello = hello();
// 	printf("Print hello: %d\n", a_hello.some_function());
// 	return (0);
// }

// handling_files(close_files, node);
// void	handling_files(void (*fun)(t_pipex *), t_pipex *ptr)
// {
// 	t_pipex	*last;

// 	last = last_node(ptr);
// 	while (last->previous)
// 	{
// 		if (last->f_inout > -1)
// 			fun(last);
// 		last = last->previous;
// 	}
// }

void	*ft_free(char **str)
{
	int		i;

	i = 0;
	while (str[i] != 0)
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}
