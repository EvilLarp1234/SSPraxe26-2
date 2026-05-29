/**
 * @author Matej Franek
 * @brief Knihovna pro ovládání LEDek
 * @date 29.5.2026
 * @version 1
*/

#include <stdint.h>
#include "MKL25Z4.h"
#include "ledfun.h"
/************************************************
 * Funkce pro ovládání LEDek
************************************************/
void set_led(uint32_t cislo_led, Stav state){

	/** @param cislo_led: 1-8
	 *  @param state: ON/OFF
	 * 	@return: empty
	 * 1-4 jsou na portu B a 5-8 jsou na portu C
	 * 1-4 jsou zapojeny na pinech 8-11 a 5-8 jsou zapojeny na pinech 10-13
	 */
	uint32_t pinsB[4]={8,9,10,11};
	uint32_t pinsC[4]={10,11,12,13};
			//PORTB
			if(cislo_led<5){
            	if(state == ON){
            	    GPIOB->PDOR &= ~(1 << pinsB[cislo_led-1]); //zapnout
            	}
				else{
            	    GPIOB->PDOR |= (1 << pinsB[cislo_led-1]);  //vypnout
            	}

			}
			else if (cislo_led>4&&cislo_led<9)
			{        
				if(state == ON){
                	GPIOC->PDOR &= ~(1 << pinsC[cislo_led-5]); //zapnout
            	} 
				else{
                	GPIOC->PDOR |= (1 << pinsC[cislo_led-5]);  //vypnout
				}
			}
			else{
				return;
			}

}
void initilize_led(){
	/**
	 * @brief Inicializace LEDek
	 * @return: empty
	 * inicializace portu B a C pro 8 led
	 * 1-4 jsou na portu B a 5-8 jsou na portu C
	 * 1-4 jsou zapojeny na pinech 8-11 a 5-8 jsou zapojeny na pinech 10-13
	 * pro zapnutí ledky je potřeba nastavit pin jako output a zapsat do něj 0, pro vypnutí je potřeba zapsat 1
	 * pro nastavení jako output je potřeba zapsat 1 do PDDR a pro nastavení muxu je potřeba zapsat 1 do PCR[pin] na bit 8
	 * pro vypnutí ledky je potřeba zapsat 1 do PDOR a pro zapnutí je potřeba zapsat 0 do PDOR
	 * 
	 */
	//prvni 4 ledky 1-4

	//led 1
	PORTB->PCR[8]|=(1<<8);//PCR[8] znamena je cislo ktere jde za portb na diagramu |=(1<<8) zapisujeme do mux at je GPIO
	GPIOB->PDDR|=(1<<8);//PDDR|=(1<<8) zapisujeme ze chceme aby byl pin 8 jako output a 8 znamena ktery pin
	GPIOB->PDOR|=(1<<8);//PDOR&=~(1<<8) pouzivame inverzni logiku protoze pin dodava stejne napeti takze ~1 z toho udela 0 a pin nedodava napeti a umoznuje tak prutok napeti  

	//led2
	PORTB->PCR[9]|=(1<<8);
	GPIOB->PDDR|=(1<<9);
	GPIOB->PDOR|=(1<<9);

	//led 3
	PORTB->PCR[10]|=(1<<8);
	GPIOB->PDDR|=(1<<10);
	GPIOB->PDOR|=(1<<10);


	//led 4
	PORTB->PCR[11]|=(1<<8);
	GPIOB->PDDR|=(1<<11);
	GPIOB->PDOR|=(1<<11);
	//druhe 4 ledky 5-8
	
	//led 5
	PORTC->PCR[10]|=(1<<8);
	GPIOC->PDDR|=(1<<10);
	GPIOC->PDOR|=(1<<10);

	//led 6
	PORTC->PCR[11]|=(1<<8);
	GPIOC->PDDR|=(1<<11);
	GPIOC->PDOR|=(1<<11);

	//led 7
	PORTC->PCR[12]|=(1<<8);
	GPIOC->PDDR|=(1<<12);
	GPIOC->PDOR|=(1<<12);

	//led 8
	PORTC->PCR[13]|=(1<<8);
	GPIOC->PDDR|=(1<<13);
	GPIOC->PDOR|=(1<<13);
	}
void led_test(){
	/** @brief Testování LEDek
	 *  @return: empty
	 * projde všechny ledky a zapne je a vypne, pro lepší viditelnost mezi tím je heavyFunction která způsobí zpoždění
	*/

	GPIOB->PDOR&=~(1<<8);
	GPIOB->PDOR&=~(1<<9);
	GPIOB->PDOR&=~(1<<10);
	GPIOB->PDOR&=~(1<<11);
	GPIOC->PDOR&=~(1<<10);
	GPIOC->PDOR&=~(1<<11);
	GPIOC->PDOR&=~(1<<12);
	GPIOC->PDOR&=~(1<<13);
	heavyFunction();
	GPIOB->PDOR|=(1<<8);
	GPIOB->PDOR|=(1<<9);
	GPIOB->PDOR|=(1<<10);
	GPIOB->PDOR|=(1<<11);
	GPIOC->PDOR|=(1<<10);
	GPIOC->PDOR|=(1<<11);
	GPIOC->PDOR|=(1<<12);
	GPIOC->PDOR|=(1<<13);
	}
void vykresli(uint8_t cislo){
	/** @brief Vykreslení čísla na LEDky
	 *  @param cislo: číslo které chceme vykreslit, musí být mezi 0-255
	 *  pro vykreslení čísla se používá binární reprezentace, kde každý bit odpovídá jedné ledce
	 *  pokud je bit 1, tak se ledka zapne, pokud je bit 0, tak se ledka vypne
	 *  @return: empty
	 */
	for (uint8_t i = 0; i < 8; i++)
	{
		if((cislo&(1<<i))!=0){
			set_led(i+1,ON);
		}
	}
}
__attribute__((optimize("O0"))) void heavyFunction() 
{
	/** @brief Funkce pro vytvoření zpoždění pomocí smyčky, která se vykoná 2 miliony krát
	 *  @return: empty
	 */
    for(int i = 0;i < 2000000; i++){}
}