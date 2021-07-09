#include "libft.h"

void	ft_putnbr_fd(int num, int fd)
{
	if (num < 0)
	{
		num *= -1;
		write(fd, "-", 1);
	}
	if (num > 9)
		ft_putnbr_fd(num / 10, fd);
	write(fd, &"0123456789"[num % 10], 1);
}
