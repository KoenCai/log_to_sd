#ifndef _RING_BUFFER_H_
#define _RING_BUFFER_H_

#include <string.h>

#ifndef	TRUE
	#define TRUE (1 == 1)
#endif

#ifndef	FALSE
	#define FALSE (1 == 0)
#endif

#ifndef	NULL
	#define NULL (void *)0					
#endif
	
typedef unsigned char 				INT8U;
typedef signed char					INT8S;
typedef unsigned short 				INT16U;
typedef signed short				INT16S;
typedef unsigned int 				INT32U;
typedef signed int					INT32S;
typedef unsigned long long 			INT64U;
typedef signed long long 			INT64S;


typedef struct RING_BUFFER
{
	INT8U *buf;
	INT16U now;
	INT16U end;	
	INT16U size;
}ring_buffer_t;


void ring_buffer_creat(ring_buffer_t *ring_buffer, INT8U *p, INT16U size);

void ring_buffer_write_byte(ring_buffer_t *ring_buffer, INT8U dat);

INT8U ring_buffer_read_byte(ring_buffer_t *ring_buffer, INT8U *val);

INT16U ring_buffer_read_only(ring_buffer_t *ring_buffer, INT8U *buf, INT16U start, INT16U len);

INT16U ring_buffer_delet(ring_buffer_t *ring_buffer, INT16U len);

void ring_buffer_reset(ring_buffer_t *ring_buffer);

INT16U ring_buffer_get_length(ring_buffer_t *ring_buffer);


#endif







