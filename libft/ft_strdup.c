/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:19:18 by pablalva          #+#    #+#             */
/*   Updated: 2024/10/01 12:06:53 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dest;
	int		i;

	i = ft_strlen(s);
	dest = malloc((i + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	ft_memcpy(dest, s, (i + 1));
	return (dest);
}
/*int main(void)
{
	const char s[20] = "cocacola";
	ft_strdup(s);
	printf("%s",dest);
	free(dest);
	return (0);
}*/