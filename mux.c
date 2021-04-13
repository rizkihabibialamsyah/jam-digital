#include <mega328.h>

// Fungsi untuk multiplexing 7-segment sesuai dengan digit dan bilangan yang ditampilkan
void show(int dig, int num) {
	// Penyesuaian register sesuai bilangan
    if (num == 0) {
        PORTD = 0b00001100;
        PORTB = 0b000101;
    } 
    else if (num == 1) {        
        PORTD = 0b00011110;
        PORTB = 0b11101;
    }
    else if (num == 2) {
        PORTD = 0b00011100;
        PORTB = 0b000110;
    } 
    else if (num == 3) {
        PORTD = 0b00011100;
        PORTB = 0b010100;
    } 
    else if (num == 4) {
        PORTD = 0b00001110;
        PORTB = 0b011100;
    }
    else if (num == 4) {
        PORTD = 0b00001110;
        PORTB = 0b011100;
    }
    else if (num == 5) {
        PORTD = 0b10001100;
        PORTB = 0b010100;
    } 
    else if (num == 6) {
        PORTD = 0b10001100;
        PORTB = 0b000100;
    }
    else if (num == 7) {        
        PORTD = 0b00011100;
        PORTB = 0b011101;
    }
    else if (num == 8) {
        PORTD = 0b00001100;
        PORTB = 0b000100;
    }
    else if (num == 9) {
        PORTD = 0b00001100;
        PORTB = 0b010100;
    }
    
    // Penyesuaian register sesuai digit
    if (dig == 1) {
        PORTD |= (1 << 0);
    }
    else if (dig == 2) {
        PORTD |= (1 << 5);
    }
    else if (dig == 3) {
        PORTD |= (1 << 6);
    }
	else {
		PORTB |= (1 << 5);
	}
}