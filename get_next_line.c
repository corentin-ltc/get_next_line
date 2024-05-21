
#define BUFFER_SIZE 500
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int     ft_strlen(char *str)
{
        int i;

        i = 0;
        while(str[i])
                i++;
        return (i);
}

char	*ft_strdup(char *src)
{
	char	*dest;
	int		i;

	dest = malloc(sizeof(char) * ft_strlen(src) + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

int     stashcheck(char *stash)
{
        long    i;

        i = 0;
        while (stash[i])
        {
                if (stash[i] == '\n');
                        return (i);
                i++;
        }
        return (0);
}

char    *get_next_line(int fd)
{
        char       buffer[BUFFER_SIZE];
        static char     *stash;
        int              sz;
        long             i;
        long            j;
        char    *nextline;


        sz = read(fd, buffer, BUFFER_SIZE);
        buffer[sz] = 0;
        stash = ft_strdup(buffer);
        if(!stash)
                return (NULL);
        while (!stashcheck(stash))
        {
                nextline = ft_strdup(stash);
                free(stash);
                read(fd, buffer, BUFFER_SIZE);
                buffer[sz] = 0;
                stash = malloc(sizeof(char) * (ft_strlen(nextline) + sz + 1));
                i = 0;
                while (nextline[i])
                {
                        stash[i] = nextline[i];
                        i++;
                }
                j = 0;
                while (buffer[j])
                {
                        stash[i + j] = buffer[j];
                        j++;
                }
                free(nextline);
        }
        i = 0;
        while (stash[i] && stash[i] != '\n')
                i++;
        nextline = malloc(sizeof(char) * (i + 1));
        while (stash[i] && stash[i] != '\n')
        {
                nextline[i] = stash[i];
                i++;
        }
        nextline[i] = 0;
        return (nextline);
}

int main(int argc, char **argv)
{
        int     fd;

        if (argc != 2)
        {
                printf("No argument");
                return (0);
        }
        fd = open(argv[1], O_RDONLY);
        printf("%s", get_next_line(fd));
}











