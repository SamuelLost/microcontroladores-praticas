
//
//  Copyright (c) 2012-2013 Andrew Payne <andy@payne.org>
//

// From uart.c
void UART0_IRQHandler() __attribute__((interrupt("IRQ")));
int uart_write(char *p, int len);
int uart_write_err(char *p, int len);
int uart_read(char *p, int len);
void uart_init(int baud_rate);

// From delay.c
void delay(unsigned int ms);

// ring.c
typedef struct {
    volatile uint16_t head;
    volatile uint16_t tail;
    volatile uint16_t size;
    volatile uint8_t data[];
} RingBuffer;

void buf_reset(RingBuffer *buf, int size);
int buf_len(const RingBuffer *buf);
int buf_isfull(const RingBuffer *buf);
int buf_isempty(const RingBuffer *buf);
uint8_t buf_get_byte(RingBuffer *buf);
void buf_put_byte(RingBuffer *buf, uint8_t val);

int advance(uint16_t i, uint16_t size);
