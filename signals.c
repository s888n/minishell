/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoutifra <aoutifra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 19:49:26 by srachdi           #+#    #+#             */
/*   Updated: 2023/07/07 10:49:15 by aoutifra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	my_error(char *command, char *errmsg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putstr_fd(" : ", STDERR_FILENO);
	ft_putstr_fd(errmsg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

static void	signal_handler(int signal)
{
	(void)signal;
	ft_putstr_fd("\n\033[1m\033[36mminishell$ \033[0m", STDOUT_FILENO);
	//rl_on_new_line();
	//rl_replace_line("", 0);
	//rl_redisplay();
	g_vars->status = 1;
}

void	main_signal(void)
{
	if (signal(SIGINT, signal_handler) == SIG_ERR \
			|| signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		my_error("signal:", strerror(errno));
	g_vars->status = 1;
}
/*[from SALAH ]:thsi function is used to disable ctrl + c and works along rl_replace_line("", 0) and rl_redisplay() ;REMEMBER TO ENABLE IT BACK */
void disable_ctrl(void)
{
  struct termios term;

  if (tcgetattr(fileno(stdin), &term) == -1)
  {
    perror("tcgetattr");
    exit(1);
  }
  term.c_lflag &= ~ECHOCTL;

  if (tcsetattr(fileno(stdin), TCSANOW, &term) == -1)
  {
    perror("tcsetattr");
    exit(1);
  }
}
void disable_ctrl2(void)
{
  struct termios term;

  if (tcgetattr(fileno(stdin), &term) == -1)
  {
	perror("tcgetattr");
	exit(1);
  }
  term.c_lflag |= ECHOCTL;

  if (tcsetattr(fileno(stdin), TCSANOW, &term) == -1)
  {
	perror("tcsetattr");
	exit(1);
  }
}


void	child_and_heredoc_signal(void)
{
	if (signal(SIGINT, SIG_DFL) == SIG_ERR \
			|| signal(SIGQUIT, SIG_DFL) == SIG_ERR)
		my_error("signal:", strerror(errno));
	g_vars->status = 1;
}
