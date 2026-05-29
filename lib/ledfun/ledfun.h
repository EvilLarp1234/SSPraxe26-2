#ifndef LEDFUN_H
#define LEDFUN_H

typedef enum {
	ON=0,
	OFF=1
}Stav;
void heavyFunction();
void initilize_led();
void set_led(uint32_t cislo_led,Stav state);
void led_test();
void vykresli(uint8_t cislo);
#endif
