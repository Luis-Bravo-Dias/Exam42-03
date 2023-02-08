#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

int	ft_putstr(char *s)
{
	int	c;
	int	counter;

	c = 0;
	counter = 0;
	if (!s)
		return (ft_putstr("(null)"));
	while (s[c] != '\0')
	{
		write(1, &s[c], 1);
		counter++;
		c++;
	}
	return (counter);
}

int	ft_putnbr(int nbr)
{
	char	c;
	int		counter;

	counter = 0;
	if (nbr == -2147483648)
	{
		counter += ft_putstr("-2147483648");
		return (counter);
	}
	if (nbr < 0)
	{
		nbr *= -1;
		write(1, "-", 1);
		counter++;
	}
	if (nbr >= 10)
	{
		counter += ft_putnbr(nbr / 10);
		counter += ft_putnbr(nbr % 10);
	}
	else
	{
		c = nbr + '0';
		write(1, &c, 1);
		counter++;
	}
	return (counter);
}

int	ft_putnbr_base(long long int nbr, char *base, int nbase)
{
	int	counter;

	counter = 0;
	if (nbr >= nbase)
	{
		counter += ft_putnbr_base(nbr / nbase, base, nbase);
		counter += ft_putnbr_base(nbr % nbase, base, nbase);
	}
	else
	{
		write(1, &base[nbr % nbase], 1);
		counter++;
	}
	return (counter);
}

static int	convert(int i, const char *input, va_list args)
{
	int	c;

	c = 0;
	if (input[i + 1] == 's')
		c += ft_putstr(va_arg(args, char *));
	else if (input[i + 1] == 'd')
		c += ft_putnbr(va_arg(args, int));
	else if (input[i + 1] == 'x')
		c += ft_putnbr_base(va_arg(args, unsigned int), "0123456789abcdef", 16);
	return (c);
}

int	ft_printf(const char *input, ...)
{
	va_list	args;
	int		i;
	int		counter;

	 i = 0;
	 counter = 0;
	 va_start(args, input);
	 if (!input)
	 	return (0);
	while (input[i])
	{
		if (input[i] == '%')
		{
			counter += convert(i, input, args);
			i++;
		}
		else
		{
			write(1, &input[i], 1);
			counter++;
		}
		i++;
	}
	va_end(args);
	return (counter);
}