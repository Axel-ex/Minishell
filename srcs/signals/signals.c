
#include "../../includes/minishell.h"

//void rl_replace_line(const char *text, int clear_undo);


// void	signals(int sig)
// {
// 	if (sig == 1)
// 	{
// 		signal(SIGINT, back_to_prompt);
// 		signal(SIGQUIT, SIG_IGN);
// 	}
// 	if (sig == 2)
// 	{
// 		signal(SIGINT, ctrl_c);
// 		signal(SIGQUIT, back_slash);
// 	}
// 	if (sig == 3)
// 	{
// 		printf("exit\n");
// 		exit(0);
// 	}
// }

// void	back_to_prompt(int sig)
// {
// 	sh()->exit_status = 142;
// 	write(1, "\n", 1);
// 	rl_replace_line("", 0);
// 	rl_on_new_line();
// 	rl_redisplay();
// 	(void)sig;
// }

void	ctrl_c(int sig)
{
	sh()->exit_status = 142;
	write(1, "\n", 1);
	(void)sig;
}

void	back_slash(int sig)
{
	sh()->exit_status = 131;
	printf("Quit teste (crash)\n");
	(void)sig;
}
