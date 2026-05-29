#include <stdint.h>
#include "seed.h"
#include "MKL25Z4.h"


uint32_t generuj_32bit_adc_seed(void) {
    /** @brief Generuje 32bitový náhodný seed pomocí ADC0
     *  @return 32bitový náhodný seed
     * Tento algoritmus využívá ADC k získání náhodných bitů z šumu na neobsazeném kanálu.
     * Pro získání 32bitového seedu provádí 32 konverzí a z každé konverze získá 1 nejméně stabilní bit, který posouvá do výsledného seedu.
     */
    uint32_t vysledny_seed = 0;
    
    // 1. Povolení hodin pro ADC0
    SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;
    
    // 2. Konfigurace ADC (16-bitový režim)
    ADC0->CFG1 = ADC_CFG1_ADIV(2) | ADC_CFG1_MODE(3) | ADC_CFG1_ADICLK(0); 
    
    // Použijeme neobsazený kanál (např. kanál 26 je vnitřní teplotní senzor nebo nechat volný pin)
    // Na volném pinu je šum ještě větší.
    for (int i = 0; i < 32; i++) {
        ADC0->SC1[0] = ADC_SC1_ADCH(26); // Spuštění konverze
        
        while (!(ADC0->SC1[0] & ADC_SC1_COCO_MASK)); // Čekání na dokončení
        
        uint32_t raw_hodnota = ADC0->R[0];
        uint32_t nejnizsi_bit = raw_hodnota & 1; // Vezmeme pouze 1 nejméně stabilní bit
        
        // Posuneme dosavadní seed o 1 bit a přidáme nový náhodný bit
        vysledny_seed = (vysledny_seed << 1) | nejnizsi_bit;
    }
    
    // Xorshift nesmí mít seed 0
    if (vysledny_seed == 0) vysledny_seed = 0x12345678;
    
    return vysledny_seed;
}