/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmonjas- <dmonjas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:21:49 by dmonjas-          #+#    #+#             */
/*   Updated: 2023/01/25 15:30:00 by dmonjas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nelem, size_t elsize)
{
	void	*dst;

	dst = malloc(nelem * elsize);
	if (dst == 0)
		return (dst);
	ft_bzero(dst, nelem * elsize);
	return (dst);
}

/*
calloc es una función en el lenguaje de programación C que 
se utiliza para asignar memoria de manera dinámica.
Significa "asignación contigua". La función toma dos argumentos: 
el número de elementos a asignar y el tamaño de cada elemento. 
Devuelve un puntero al primer byte de la memoria asignada.

La función calloc se utiliza para asignar un bloque de memoria 
que sea lo suficientemente grande para contener un número especificado 
de elementos, cada uno de un tamaño especificado.
La función inicializa la memoria a cero antes de devolver un puntero a ella. 
Esto es en contraposición a malloc, que asigna memoria pero no la inicializa.

La sintaxis para calloc es la siguiente:

void* calloc(size_t nmemb, size_t size);
Donde nmemb es el número de elementos a ser asignado y 
size es el tamaño de cada elemento. 
La función devuelve un puntero al primer byte del bloque de memoria asignado.

Es importante tener un seguimiento de la memoria asignada con calloc 
para liberarla cuando ya no sea necesaria, para evitar fugas de memoria.

Por ejemplo:

int *ptr = (int *) calloc(5, sizeof(int));
Esto asigna espacio para 5 enteros e inicializa a 0 y devuelve un 
puntero al primer entero.
*/