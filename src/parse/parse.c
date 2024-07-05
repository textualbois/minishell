/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrusu <mrusu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:29:47 by mrusu             #+#    #+#             */
/*   Updated: 2024/07/05 16:08:18 by mrusu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	add_token(t_data *data, char *value, t_tokentype type)
{
	data->tokens = realloc(data->tokens, (data->token_count + 1) * sizeof(t_token));
	data->tokens[data->token_count].value = ft_strdup(value);
	data->tokens[data->token_count].type = type;
	data->token_count++;
}

int	tokenize(t_data *data, char *input) {
	int i = 0;
	char buffer[1024];
	int buf_index = 0;

    while (input[i]) {
        if (is_special_char(input[i])) {
            if (buf_index > 0) {
                buffer[buf_index] = '\0';
                add_token(data, buffer, T_WORD);
                buf_index = 0;
            }
            if (input[i] == '|')
                add_token(data, "|", T_PIPE);
            else if (input[i] == '<')
                add_token(data, "<", T_REDIRECT_IN);
            else if (input[i] == '>')
                add_token(data, ">", T_REDIRECT_OUT);
        } else {
            buffer[buf_index++] = input[i];
        }
        i++;
    }
    if (buf_index > 0) {
        buffer[buf_index] = '\0';
        add_token(data, buffer, T_WORD);
    }
    return 1;
}

int	parse_tokens(t_data *data) 
{
	t_command *current_cmd = NULL;
	int i;

	for (i = 0; i < data->token_count; i++) {
		if (data->tokens[i].type == T_WORD) {
			if (!current_cmd) {
                current_cmd = create_command();
                add_arg_to_command(current_cmd, data->tokens[i].value);
            } else {
                add_arg_to_command(current_cmd, data->tokens[i].value);
            }
        } else if (data->tokens[i].type == T_PIPE) {
            add_command_to_data(data, current_cmd);
            current_cmd = NULL;
        } else if (is_redirection_token(data->tokens[i].type)) {
            i++;
            handle_redirection(current_cmd, data->tokens[i - 1].type, data->tokens[i].value);
        }
    }
    if (current_cmd) {
        add_command_to_data(data, current_cmd);
	}
	return 1;
}

int	is_redirection_token(t_tokentype type)
{
    return	(type == T_REDIRECT_IN || type == T_REDIRECT_OUT ||
			type == T_REDIRECT_APPEND || type == T_HEREDOC);
}

int	handle_redirection(t_command *cmd, t_tokentype type, char *file)
{
	if (type == T_REDIRECT_IN)
		cmd->input_file = ft_strdup(file);
	else if (type == T_REDIRECT_OUT)
		cmd->output_file = ft_strdup(file);
	else if (type == T_REDIRECT_APPEND)
	{
		cmd->output_file = ft_strdup(file);
		cmd->append_output = 1;
	}
	else if (type == T_HEREDOC)
		cmd->heredoc_delimiter = ft_strdup(file);
	return (1);
}