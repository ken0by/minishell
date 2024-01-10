/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmonjas- <dmonjas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 17:00:15 by dmonjas-          #+#    #+#             */
/*   Updated: 2023/01/23 10:58:33 by dmonjas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s2;
	size_t	len;

	len = ft_strlen(s1) + 1;
	s2 = malloc(len);
	if (!s2)
		return (0);
	ft_memcpy(s2, s1, len);
	return (s2);
}

/*
a función strdup es una función en el lenguaje de programación 
C que se utiliza para crear una copia de una cadena dada.
La función toma como argumento un puntero a una cadena y 
devuelve un puntero a una nueva cadena que es una copia exacta 
de la cadena original.

La sintaxis para strdup es la siguiente:

Copy code
char *strdup(const char *s);
Donde s es el puntero a la cadena que se desea copiar. 
La función reserva memoria dinámicamente para almacenar la 
copia de la cadena y devuelve un puntero a la nueva cadena.
El usuario es responsable de liberar la memoria asignada 
para la copia una vez que ya no sea necesaria.

Por ejemplo:

char *original = "Hola, mundo!";
char *copia = strdup(original);
En este ejemplo, se asigna memoria para una copia de la 
cadena "Hola, mundo!" y se almacena en la variable copia.
*/