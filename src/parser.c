
#include "../inc/minishell.h"

/** compare echo with 5 characters (include \0), otherwise
 * it would be ok when you type echom (4 chars compares only up to o in echo)
 **/
void	cmd_identifier(char **cmd, t_info *info)
{
	if (!strncmp(cmd[0], "echo", 5))
		ft_echo(cmd);
	else if (!strncmp(cmd[0], "exit", 5))
		ft_exit(cmd);
	else if (is_an_executable(cmd[0], info))
		printf("cmd[0] is root_cmd = %s\n", info->root_cmd);
}

/**
 *  @brief the parser goes throu the strings of the lexer one by one and 
 * the temporary struct t_parse_lexer is used. It holds the actual group we are in,
 * the category cat of the categoriser, the falg if the string belongs to a redirect.
 * 
 * @param info 
 */
void	parser(t_info *info) // after lexer.. groups and make space for ptr to group structs and group structs and clean_up
{
	t_parse_lexer a;
	t_parse_lexer *pl;

	pl = &a;
	pl->act_group = 0;
	int i;
	i = -1;
	// //char **cmd;
	add_history(info->prompt);
	// //cmd = ft_split(prompt, ' '); // only delimiting by ‘ ‘, not by tabs for example

	// //input_error_check(cmd); // no function until now
	// //cmd_identifier(cmd, info);
	//if (info->prompt == NULL || *info->prompt == 0)
		// return new line and wait for new command
	info->input_lexer = ft_split_lexer(info->prompt);
	info->num_groups = count_groups(info);
	info->groups = init_groups(info);

	while (info->input_lexer[++i])
	{
		if (!ft_strncmp(info->input_lexer[i], "|", 2))
			pl->act_group++;
		pl->cat = categorize(info->input_lexer[i]);

		// here comes ft_order(cat)
		pl-> is_red = found_save_redirect(pl, info, info->input_lexer[i]);
		found_save_executable(pl, info, info->input_lexer[i]);

		
	}
	print_groups(info->groups, info);
	

}
