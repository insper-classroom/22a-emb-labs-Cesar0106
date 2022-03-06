#include <asf.h>

#include "gfx_mono_ug_2832hsweg04.h"
#include "gfx_mono_text.h"
#include "sysfont.h"

#define LED_PIO      PIOC
#define LED_PIO_ID   ID_PIOC
#define LED_IDX      8
#define LED_IDX_MASK (1 << LED_IDX)

// Configuracoes dos botões
//Botão Placa Grande
#define BUT_PIO      PIOA
#define BUT_PIO_ID   ID_PIOA
#define BUT_IDX  11
#define BUT_IDX_MASK (1 << BUT_IDX)
//Considerar esses pinos conectados na EXT1
//Botão 1
#define BUT1_PIO           PIOD
#define BUT1_PIO_ID        ID_PIOD
#define BUT1_PIO_IDX       28
#define BUT1_PIO_IDX_MASK (1u << BUT1_PIO_IDX)

//Botão 2
#define BUT2_PIO           PIOC
#define BUT2_PIO_ID        ID_PIOC
#define BUT2_PIO_IDX       31
#define BUT2_PIO_IDX_MASK (1u << BUT2_PIO_IDX) 

//Botão 3
#define BUT3_PIO           PIOA
#define BUT3_PIO_ID        ID_PIOA
#define BUT3_PIO_IDX       19
#define BUT3_PIO_IDX_MASK (1u << BUT3_PIO_IDX)


/* flag */
volatile char but_flag;

void but_callback (void) {
	if (pio_get(BUT_PIO, PIO_INPUT, BUT_IDX_MASK)) {
		but_flag = 1;
		} else {
		but_flag = 0;
	}
}

void pisca_led(int n, int t){
	for (int i=0;i<n;i++){
		pio_clear(LED_PIO, LED_IDX_MASK);
		delay_ms(t);
		pio_set(LED_PIO, LED_IDX_MASK);
		delay_ms(t);
	}
}


int main (void)
{
	board_init();
	sysclk_init();
	delay_init();

  // Init OLED
	gfx_mono_ssd1306_init();
  
  // Escreve na tela um circulo e um texto
	gfx_mono_draw_filled_circle(20, 16, 16, GFX_PIXEL_SET, GFX_WHOLE);
  gfx_mono_draw_string("mundo", 50,16, &sysfont);

  /* Insert application code here, after the board has been initialized. */
	while(1)
	{
		if (but_flag) {
			pisca_led(30,200);
			but_flag = 0;
		}
		pmc_sleep(SAM_PM_SMODE_SLEEP_WFI);
	}
}
