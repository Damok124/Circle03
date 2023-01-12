#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

int	ft_strlen(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

typedef struct s_lst{
	char			*str;
	//char			**strs;
	int				n;
	//int				*p;
	struct s_lst	*next;
}					t_lst;

void	ft_modif(t_lst *lst)
{
	t_lst	*new;

	new = (t_lst *)malloc(sizeof(t_lst));
	new->str = NULL;
	new->n = 250;
	new->next = NULL;
	lst->str[0] = 'B';
	lst->n = 150;
	lst->next = new;
}


void	ft_trafic(t_lst *lst)
{
	while (lst)
	{
		lst->n *= 2;
		lst = lst->next;
	}
}

//////

ssize_t	ft_count_strs(const char *s, char c)
{
	ssize_t	n;
	ssize_t	i;

	n = 0;
	i = 0;
	while (s && s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			n++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (n);
}

void	ft_true_split(char const *s, char **strs, char c, ssize_t len)
{
	ssize_t	i;
	ssize_t	j;
	ssize_t	a;

	a = 0;
	i = 0;
	j = 0;
	while (s[i] && a < len)
	{
		while (s[i + j] && s[i + j] == c)
			i++;
		while ((s[i + j] && s[i + j] != c))
			j++;
		if (s[i + j] == c || s[i + j] == 0)
			strs[a] = ft_substr(s, i, j);
		a++;
		i = i + j;
		j = 0;
	}
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	ssize_t	len;

	strs = NULL;
	if (s)
	{
		len = ft_count_strs(s, c);
		strs = (char **)malloc(sizeof(char *) * (len + 1));
		if (!strs)
			return (NULL);
		strs[len] = NULL;
		ft_true_split(s, strs, c, len);
	}
	return (strs);
}

int	main(void)
{
	t_lst *lst;
	char	**test;
	char	*str;
	//int	tab[2];

	test = (char **)malloc(sizeof(char *) * 5);
	test[4] = NULL;
	lst = (t_lst *)malloc(sizeof(t_lst));
	lst->str = (char *)malloc(sizeof(char) * 8);
	lst->str[0] = 'b';
	lst->str[1] = 'o';
	lst->str[2] = 'n';
	lst->str[3] = ' ';
	lst->str[4] = '\t';
	lst->str[5] = 'u';
	lst->str[6] = 'r';
	lst->str[7] = '\0';
	str = getenv("PATH");
	test[0] = lst->str;
	test[1] = lst->str;
	test[2] = lst->str;
	test[3] = lst->str;
	//ft_modif(lst);
	//ft_trafic(lst);
	//printf("%d, %s\n", lst->n, lst->str);
	//printf("%d, %s\n", lst->next->n, lst->next->str);
	//tab[0] = 5;
	//tab[1] = tab[0] * 5;
	//printf("%d %d\n", tab[0], tab[1]);
	printf("%s\n", lst->str);//bonjour
	//lst->str[3] = '\0';
	lst->str = lst->str + 3;
	printf("%s\n", lst->str);//jour
	printf("%s\n", str);
	printf("%p %p\n", lst->str, str);
	printf("test :%d\n", ft_strlen(test));
	test = ft_split_set(lst->str, " \t");
	free(lst->str - 3);
	free(lst);
	//verif si transmettre un lst** est nécessaire
	//verif si un str déplacé permet toujours de le free ou non
	return (0);
}
