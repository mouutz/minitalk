#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include "../libft/libft.h"
#define BUFFER_SIZE 1000

void	ft_output(int sig, int *len, int *pid, siginfo_t *info)
{
	static int		bit_char = 0;
	static int		ct_bit = 0;
	static char		buf[BUFFER_SIZE + 1];

	bit_char = bit_char + ((sig == SIGUSR1) << ct_bit);
	ct_bit++;
	if (ct_bit == 8)
	{
		buf[++(*len)] = (char)bit_char;
		if (bit_char == '\0' || *len >= BUFFER_SIZE)
		{
			if (*len >= 0)
				write(STDOUT_FILENO, buf, *len + ('\0' != bit_char));
			*len = -1;
			if (bit_char == '\0')
			{
				*pid = 0;
				kill(info->si_pid, SIGUSR1);
			}
		}
		bit_char = 0;
		ct_bit = 0;
	}
}

void	ft_server(int sig, siginfo_t *info, void *ctx)
{
	static int		len = -1;
	static pid_t	pid = 0;

	if (pid == 0)
		pid = info->si_pid;
	else if (pid != info->si_pid)
	{
		kill(info->si_pid, SIGUSR2);
		sleep(2);
		pid = 0;
		len = -1;
		return ;
	}
	ft_output(sig, &len, &pid, info);
	(void)ctx;
}

void	ft_exec_sigaction(struct sigaction *sa_sig)
{
	if (sigaction(SIGUSR1, sa_sig, NULL) < 0)
		exit(1);
	if (sigaction(SIGUSR2, sa_sig, NULL) < 0)
		exit(1);
}

int	main(void)
{
	struct sigaction	sa_sig;
	pid_t				pid;

	pid = getpid();
	ft_putstr_fd("Server PID: ", STDOUT_FILENO);
	ft_putnbr_fd(pid, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	sigemptyset(&sa_sig.sa_mask);
	sa_sig.sa_sigaction = ft_server;
	sa_sig.sa_flags = SA_SIGINFO;
	ft_exec_sigaction(&sa_sig);
	while (1)
		pause();
	return (0);
}
