/* Copyright 2018, DSI FCEIA UNR - Sistemas Digitales 2
 *    DSI: http://www.dsi.fceia.unr.edu.ar/
 * Copyright 2018, Gustavo Muro
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

/*==================[inclusions]=============================================*/

#include "SD2_board.h"
#include "board.h"
#include "time.h"
#include "fsl_debug_console.h"

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

static uint32_t ms_100 = 100;

/*==================[internal functions declaration]=========================*/

/*==================[internal functions definition]==========================*/

int main(void)
{
	BOARD_BootClockRUN();
	board_init();
	BOARD_InitDebugConsole();
	time_init();

	/* systick cada 1 ms */
	SysTick_Config((SystemCoreClock / 1000U));

	uint32_t transcurrido;

	// Resetear el módulo
	time_restart();

	while (1)
	{
		// Mido 100ms para verificar el funcionamiento
		if(ms_100 == 0)
		{
			// Obtiene el tiempo transcurrido desde el último reseteo
			transcurrido = time_elapsed_us();

			// Vuelvo a medir para verificar repetibilidad
			ms_100 = 100;
			time_restart();
		}
	}
}

void SysTick_Handler(void)
{
	if(ms_100)
		ms_100 --;
}
