/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:46:49 by pablalva          #+#    #+#             */
/*   Updated: 2024/10/03 15:48:56 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;

	p = malloc(size * nmemb);
	if (p == NULL)
		return (NULL);
	ft_memset(p, 0, size * nmemb);
	return (p);
}

/*int	main(void)
{
   char *replica;
   char *original;
   size_t nmemb;

   nmemb = 10;
   replica = ft_calloc(, );
   original = calloc( , );
   printf("%p\n", replica);
   printf("%p\n", original);

   return(0);
}*/