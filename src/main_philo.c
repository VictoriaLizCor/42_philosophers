/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 12:49:11 by lilizarr          #+#    #+#             */
/*   Updated: 2023/08/28 11:22:03 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	main(int argc, char *argv[], char *env[])
{
	print_intro();
	return (0);
}
/*
number_of_philosophers = forks
time_to_die (in milliseconds):
time_to_eat (in milliseconds):
time_to_sleep (in milliseconds):
number_of_times_each_philosopher_must_eat
** the simulation stops when a philosopher dies.

◦ timestamp_in_ms X has taken a fork ◦ timestamp_in_ms X is eating
◦ timestamp_in_ms X is sleeping
◦ timestamp_in_ms X is thinking
◦ timestamp_in_ms X died

** Each philosopher has a number ranging from 1 to number_of_philosophers.
** To prevent philosophers from duplicating forks, \
	you should protect the forks state with a mutex for each of them.
--- MANDATORY:
memset
printf
malloc
free
write,
usleep
gettimeofday
pthread_create
pthread_detach
pthread_join
pthread_mutex_init
pthread_mutex_destroy
pthread_mutex_lock
pthread_mutex_unlock


--- BONUS:
fork
kill
exit
waitpid
sem_open
sem_close
sem_post
sem_wait
sem_unlink

*/
