#include "get_next_line.h"

char    *ft_strchr(char *str, char a)
{
    int i;

    i = -1;
    while (str[++i] != '\0')
    {
        if (str[i] == a)
            return(&str[i]);
    }
    return (NULL);
}

int     ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0')
        i++;
    return (i);
}

char    *ft_strjoin(char *a, char *b)
{
    char    *tmp;
    int     i;
    int     j;

    tmp = malloc(sizeof(char) * (ft_strlen(a) + ft_strlen(b) + 1));
    if (!tmp)
        return (NULL);
    i = -1;
    j = -1;
    while (a[++i] != '\0')
        tmp[++j] = a[i];
    i = -1;
    while (b[++i] != '\0')
        tmp[++j] = b[i];
    tmp[++j] = '\0';
    return (tmp);
}

char    *ft_substr(char *str, int start, int len)
{
    char    *tmp;
    int leng;
    int i;

    if (!str)
        return (NULL);
    leng = ft_strlen(str);
    if (leng > len)
        tmp = malloc(sizeof(char) * len + 1);
    else
        tmp = malloc(sizeof(char) * leng + 1);
    if (!tmp)
        return (NULL);
    i = -1;
    while (++i < len && str[start + i] != '\0')
    {
        tmp[i] = str[start + i];
    }
    tmp[i] = '\0';
    return (tmp);
}

char    *ft_get_rez(char *ost, int rd)
{
    char    *rezult;

    if (rd > 0)
        rezult = ft_substr(ost, 0, ft_strchr(ost, '\n') - ost + 1);
    else if (rd == -1 || (rd == 0 && *ost == '\0'))
    {
        
        free(ost);
        return (NULL);
    }
    else
        rezult = ft_substr(ost, 0, ft_strlen(ost));   
    return (rezult);
}

char    *get_next_line(int fd)
{
    char        buff[BUFFER_SIZE + 1];
    static char *ost;
    char        *tmp;
    int         rd;
    char        *rez;
    
    if (!ost)
    {
        ost = malloc(sizeof(char));
        *ost = '\0';
    }
    rd = 0;
    if (!ft_strchr(ost, '\n'))
        rd = read(fd, buff, BUFFER_SIZE);
    while (!ft_strchr(ost, '\n') && rd)
    {
        buff[rd] = '\0';
        tmp = ft_strjoin(ost, buff);
        free(ost);
        ost = tmp;
        if (!ft_strchr(ost, '\n'))
            rd = read(fd, buff, BUFFER_SIZE);
    }
    rez = ft_get_rez(ost, rd);
    if (!rez)
    {
        ost = NULL;
        return (NULL);
    }
    tmp = ft_substr(ost, ft_strlen(rez), ft_strlen(ost));
    free(ost);
    ost = tmp;
    return (rez);
}
