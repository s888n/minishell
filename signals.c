
#include "minishell.h"

/*the problem of ^C and ^\ is from the outdated readline library , also it should automaticly display:  minishell*/
void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		write(2, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}
/*in main mode == 0 , in heredoc or child mode == 1*/
void	set_signal(int mode)
{
	if (mode == 0)
	{
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	if(mode == 1)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		g_vars->status = 1;//should we even change this , since it shouldn't work anyway
	}
}

void disable_ctrl(int mode)
{
  struct termios term;

  tcgetattr(STDOUT_FILENO, &term);
	if (mode == 0)
		term.c_lflag &= ~(ECHOCTL);
	else if (mode == 1)
		term.c_lflag |= ECHOCTL;
  tcsetattr(STDOUT_FILENO, TCSANOW, &term);
}