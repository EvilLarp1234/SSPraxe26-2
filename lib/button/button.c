/**
 * @author Matej Franek
 * @brief knihovna pro inicializaci tlacitek
 * @date 29.5.2026
 * @version 1
*/

#include "button.h"
#include "MKL25Z4.h"
void buttoninit(){
	/** @brief Inicializace tlačítek
	 *  @return: empty
	 */
	PORTA->PCR[4]|=0b1010<<16;
	PORTA->PCR[5]|=0b1010<<16;
	PORTA->PCR[2]|=0b1010<<16;
	PORTA->PCR[3]|=0b1010<<16;
	//button 1
	PORTA->PCR[4]|=0b1010<<16;
	PORTA->PCR[4]|=1<<8;
    GPIOA->PDDR&=~(1<<4);


	//button 2
	PORTA->PCR[5]|=0b1010<<16;
	PORTA->PCR[5]|=1<<8;
    GPIOA->PDDR&=~(1<<5);

	
	
	//button 3
	PORTA->PCR[12]|=0b1010<<16;
	PORTA->PCR[12]|=1<<8;
    GPIOA->PDDR&=~(1<<12);
	
	
	//button 4
	PORTA->PCR[13]|=0b1010<<16;
	PORTA->PCR[13]|=1<<8;
    GPIOA->PDDR&=~(1<<13);


}