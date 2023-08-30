/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_function_call.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 11:55:21 by lilizarr          #+#    #+#             */
/*   Updated: 2023/08/30 15:26:46 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

typedef struct s_hello
{
	int	(*some_function)();
}	t_hello;

int	foo(void)
{
	return (0);
}

t_hello	hello(void)
{
	t_hello	a_hello;

	a_hello.some_function = &foo;
	return (a_hello);
}

int	main(void)
{
	t_hello	a_hello;

	a_hello = hello();
	printf("Print hello: %d\n", a_hello.some_function());
	return (0);
}
