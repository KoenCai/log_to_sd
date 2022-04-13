#include "ring_buffer.h"
#include "app_util_platform.h"

static void ring_buffer_enter_critical(void)
{
//	enter_critical();
//	__disable_irq();
	CRITICAL_REGION_ENTER();
	
}

static void ring_buffer_exit_critical(void)
{
//	exit_critical();
//	__enable_irq();
	CRITICAL_REGION_EXIT();
}
//__enable_irq();
static INT16U ring_buffer_self_add(INT16U index, INT16U max_size)
{
	return ((index+1)%max_size);
}


static INT16U ring_buffer_add(INT16U a, INT16U b, INT16U max_size)
{
	return ((a+b)%max_size);
}

void ring_buffer_reset(ring_buffer_t *ring_buffer)
{
	ring_buffer->now = 0;
	ring_buffer->end = ring_buffer->now;
	
	if(NULL == ring_buffer->buf) return;
	
	memset((void*)ring_buffer->buf, 0, ring_buffer->size);	
}

void ring_buffer_creat(ring_buffer_t *ring_buffer, INT8U *p, INT16U size)
{
	ring_buffer->buf = NULL;
	ring_buffer->now = 0;
	ring_buffer->end = ring_buffer->now;
	ring_buffer->size = size;
	
	if(NULL == p) return;
	
	ring_buffer->buf = p;
	memset((void*)ring_buffer->buf, 0, ring_buffer->size);
}

void ring_buffer_write_byte(ring_buffer_t *ring_buffer, INT8U dat)
{
	INT16U temp_in = 0;
    
	ring_buffer_enter_critical();
	temp_in = ring_buffer_self_add(ring_buffer->now, ring_buffer->size);
	if(temp_in != ring_buffer->end)				
	{
		ring_buffer->buf[ring_buffer->now] = dat;
		ring_buffer->now = temp_in;
	}
	ring_buffer_exit_critical();
}

INT8U ring_buffer_read_byte(ring_buffer_t *ring_buffer, INT8U *val)
{ 
	ring_buffer_enter_critical();
	if(ring_buffer->end != ring_buffer->now)
	{
		*val = ring_buffer->buf[ring_buffer->end];				
		ring_buffer->end = ring_buffer_self_add(ring_buffer->end, ring_buffer->size);			
		ring_buffer_exit_critical();
		return 0;
	}
	ring_buffer_exit_critical();
	return 1;
}


INT16U ring_buffer_get_length(ring_buffer_t *ring_buffer)
{
	INT16U len = 0;
    
	ring_buffer_enter_critical();
	len = (ring_buffer->now + ring_buffer->size - ring_buffer->end) % ring_buffer->size;		
	ring_buffer_exit_critical();
	return len;
}


INT16U ring_buffer_read_only(ring_buffer_t *ring_buffer, INT8U *buf, INT16U start, INT16U len)
{
	INT16U read_len = ring_buffer_get_length(ring_buffer);
	INT16U start_index = 0;
	INT16U cycle = 0;
	
	if(start >= read_len) return 0;	
	
	if(read_len >= (start + len))			
	{
		read_len = len;
	}
	else
	{
		read_len = read_len - start;		
	}
	ring_buffer_enter_critical();
	start_index = ring_buffer_add(start, ring_buffer->end, ring_buffer->size);
	ring_buffer_exit_critical();	
	for(cycle=0; cycle<read_len ;cycle++)
	{
		ring_buffer_enter_critical();
		buf[cycle] = ring_buffer->buf[start_index];
		start_index = ring_buffer_self_add(start_index, ring_buffer->size);
		ring_buffer_exit_critical();
	}
	return read_len;
}


INT16U ring_buffer_delet(ring_buffer_t *ring_buffer, INT16U len)
{
	INT16U read_len = ring_buffer_get_length(ring_buffer);
    
	ring_buffer_enter_critical();
	if(read_len <= len)					
	{
		ring_buffer->end = ring_buffer->now;
		ring_buffer_exit_critical();
		return read_len;
	}
	ring_buffer->end = ring_buffer_add(ring_buffer->end, len, ring_buffer->size);
	ring_buffer_exit_critical();
	return len;
}










