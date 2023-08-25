/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilizarr <lilizarr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 12:46:39 by lilizarr          #+#    #+#             */
/*   Updated: 2023/08/25 12:48:42 by lilizarr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <unistd.h>
# include <stdbool.h>

# ifndef DEBUG_PHI
#  define DEBUG_PHI 0
# endif

// /* cmd_fuctions.c*/
// void	cmd_exe(t_pipex *d);
// void	cmd(t_pipex *data);
// void	fill_cmd(t_pipex *p_cmd, char **tmp_cmd);
// /* pipex.c */
// int		one_command_pipex_builtin_integration(t_pipex *node);
// void	head_execution(t_pipex *node);
// void	create_child(t_pipex *node);
// void	run_fork(t_pipex **d);
// /* pipex_utils.c*/
// t_pipex	*last_node(t_pipex *data);
// void	pipex_status(t_pipex *d);
// /* fork.c */
// void	execute_last_node(t_pipex *node);
// void	wait_for_child(t_pipex *node);
// void	execute_node_with_child(t_pipex *node);
// /* redirection_files.c */
// void	redirect(t_pipex *parent, t_pipex *current, int idx, int to_fd);
// void	redirect_file(t_pipex *node, t_pipex *node_file);
// void	openfile(t_pipex *node);
// void	handling_files(void (*fun)(t_pipex *), t_pipex *ptr);
// /* redirection_files_helper.c */
// void	fill_t_file(t_pipex *list, int (*in_out)[3], t_file (*file)[2]);
// t_pipex	*ispipe_command(t_pipex *node);
// /* Close_fds.c*/
// void	ft_close_msg(int fd);
// void	close_files(t_pipex *ptr);
// void	close_fds(t_pipex *node, t_pipex *file_node);
// void	status_close(t_pipex *node);
// void	ft_close(t_pipex *node);
// /*  added Maíra*/
// int		pipex_builtin_integration(t_pipex *node);
// /* fork_utils.c*/
// void	depurate_list(t_pipex *node);
// // /* testing utils pipe_list.c */
// void	check_fd(int num, t_pipex *node);
// void	printf_stderr(char *str1, char *str2, int exit_error);
// void	print_variable(char **variable, char *msg);
// void	print_list(t_pipex *print, int opt);
// void	print_node_info(t_pipex *node, int opt);

# define CNRM  "\x1B[0m"
# define CRED  "\x1B[31m"
# define CGRN  "\x1B[32m"
# define CYEL  "\x1B[33m"
# define CBLU  "\x1B[34m"
# define CMAG  "\x1B[35m"
# define CCYN  "\x1B[36m"
# define CWHT  "\x1B[37m"

#endif