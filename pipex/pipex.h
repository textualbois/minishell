/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 00:24:50 by isemin            #+#    #+#             */
/*   Updated: 2024/07/09 15:34:58 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "../libft/libft.h"

# ifndef READ_END
#  define READ_END 0
# endif
# ifndef WRITE_END
#  define WRITE_END 1
# endif
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif
# ifndef CHILD
#  define CHILD 0
# endif
# ifndef ANY_CHILD
#  define ANY_CHILD -1
# endif

// pipex.c
int		pipex(int argc, char **argv, char **envp);

// get_path.c
char	**get_path(char **envp);
char	*get_full_path(char *cmd, char **env_paths);

// utils.c
void	*clear_arr(char **res_arr);
size_t	ft_arrlen(char **arr);
char	**ft_map_s2a(char **arr, char *str, \
					char *(*f)(const char*, const char*));
void	remove_chars(char *str, char *c);

//utils2.c
int		ft_str_end_wit(const char *s1, const char *s2);

//command_parser.c
char	**parse_args(char *cmd);

//error.c
void	perror_exit(int exit_code, char *error_message);
int		perror_return(int return_value, char *error_message);
void	werror_exit(int exit_code, char *error_message, int fd);
int		werror_return(int return_value, char *error_message, int fd);

// executioner.c
int		execute_args(int argc, char **argv, char **path, char **envp);
int		execute_args_h_doc(int argc, char **argv, char **path, char **envp);

// manage_fd.c
int		set_fds(int fd_array[3][2], int cmd_number, \
				int cmd_number_limit, char **argv);
int		set_fds_h_doc(int fd_array[3][2], int cmd_number, \
						int cmd_number_limit, char **argv);
void	close_fds_parent(int fd_array[3][2], int cmd_number, \
						int cmd_number_limit);
void	close_all(int fd_array[3][2]);

// manage_fd_helpers.c
int		setup_initial_read_fd(int fd_array[][2], char **argv);
int		redirect_input(int fd_array[][2], int cmd_num);
int		redirect_out(int fd_array[][2], int cmd_num, \
					int cmd_num_lim, char **argv);
int		redirect_out_h_doc(int fd_array[][2], int cmd_num, \
						int cmd_num_lim, char **argv);

// here_doc.c
int		here_doc(int argc, char **argv, char **env_paths, char **envp);

// get_next_line.c
char	*get_next_line(int fd, int clear_stash);

#endif
