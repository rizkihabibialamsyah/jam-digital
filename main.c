#include <mega328.h>
#include <delay.h>
#include "mux.h"

int jj, mm, dd;
int mode, set;

// Atur nilai awal register TCNT1 untuk periode interupsi 1 detik (49911)
#define TCNT_HIGH 0xC2
#define TCNT_LOW 0xF7

void init_int(void) {
	// Atur prescaler menjadi 1024
	TIMSK1 = 0b1;
	TCCR1B = 0b101;
	
    TCNT1L = TCNT_LOW;
	TCNT1H = TCNT_HIGH; 
    
    //SET FALLING EDGE PADA INT0 dan INT1
	EICRA=(1<<ISC11)|(0<<ISC10)|(1<<ISC01)|(0<<ISC00); 
	
	//ENABLE INT0 dan INT1
	EIMSK=(1<<INT1) | (1<<INT0); 
	
	//SET INT0 AND INT1 FLAG 
	EIFR=(1<<INTF1) | (1<<INTF0); 
	
	
	// Aktifkan interupsi
	#asm("sei")
}

void main(void) {
	// Inisiasi Interupsi
	init_int();
	
	// Set pin ke LED 7-segment menjadi OUTPUT dan tombol menjadi INPUT 
	DDRD = 0b111110011;
	DDRB = 0b111111;
    
    PORTD |= 0b1100;  
    
    // Inisiasi mode dan set 0 (kondisi tidak terjadi interupsi)
	mode = 0;
	set = 0;
	
	// USART initialization
    // USART disabled
    UCSR0B = (0 << RXCIE0) | (0 << TXCIE0) | (0 << UDRIE0) | (0 << RXEN0) | (0 << TXEN0) | (0 << UCSZ02) | (0 << RXB80) | (0 << TXB80);
    
    
	while (1) {
        if (!mode) {
			if (!set) {
				// Menampilkan menit dan detik
				show(1, (mm / 10));	
				delay_ms(5);
				show(2, (mm % 10));	
				delay_ms(5);
				show(3, (dd / 10));	
				delay_ms(5);
				show(4, (dd % 10));	
				delay_ms(5);
			}
			else {
				// Pengaturan detik
				if (dd == 59) {
					mm = (mm + 1) % 60;
				}
				dd = (dd+1)%60;	
				set = 0;
			}
        }
        else {
			if (!set) {
				// Menampilkan jam
				show(3, (jj / 10));	
				delay_ms(5);
				show(4, (jj % 10));	
				delay_ms(5);
			}
			else {
				// Pengaturan jam
				jj = (jj + 1) % 24;
                set = 0;
			}
        }
	}
	
}

interrupt [TIM1_OVF] void timer1_ovf_isr(void) {
    TCNT1L = TCNT_LOW;
    TCNT1H = TCNT_HIGH;
	
	// Penyesuaian menit dan jam
	if (dd == 59) {
		if (mm == 59) {
			jj = (jj + 1) % 24;
		}
		mm = (mm + 1) % 60;
	}
	
	// Penambahan dan penyesuaian detik
	dd = (dd+1)%60;		
}

interrupt [EXT_INT0] void ext_int0_isr(void)
{
    mode = !mode;
}

interrupt [EXT_INT1] void ext_int1_isr(void)
{
    set = 1;
}
