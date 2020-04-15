/*
 * socket.h
 *
 *  Created on: 15 abr. 2020
 *      Author: utnso
 */

#ifndef SOCKET_H_
#define SOCKET_H_

typedef enum
{
	CADENA = 1,
}op_code;

typedef struct
{
	int size;
	void* stream;
} t_buffer;

typedef struct
{
	op_code codigo_operacion;
	t_buffer* buffer;
} t_paquete;



#endif /* SOCKET_H_ */
