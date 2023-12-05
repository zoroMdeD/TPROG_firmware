/**
  ******************************************************************************
  * @file    cmd_timer.c	
  * @brief   
  * @author  nchernov
  * @version 1.0
  * @date    Dec 5, 2023
  ******************************************************************************
  * @attention
  ******************************************************************************
  */

#include "cmd_timer.h"

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;

/*----------------------------------------------------------------------------*/
void INIT_TIMER(uint8_t number, uint8_t channel, uint32_t freq, uint8_t fill_factor)
{
    // Определение таймера
    switch (number) {
        case 1:
            htim.Instance = TIM1;
            break;
        case 2:
            htim.Instance = TIM2;
            break;
        case 3:
            htim.Instance = TIM3;
            break;
        case 4:
            htim.Instance = TIM4;
            break;
        default:
            return;
    }
	// необходимо вычислить значения предделителя и периода, чтобы обеспечить заданную частоту на выходе ШИМ
	uint32_t period = 1, prescale = 0;
    uint32_t SysClock = HAL_RCC_GetSysClockFreq() / 2;     // тактирование таймера
    // для упрощения, период будет увеличиваться на порядок каждый раз, пока не подбереться нужный предделитель
    // эта шляпа может коряво работать с частотами маленькими, типа десятые Гц, но тут минимум 1 Гц.
    do
    {
    	period *= 10;
        prescale = SysClock / (period * freq);
    } while (prescale > 65000);


}
