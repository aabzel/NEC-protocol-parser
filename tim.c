
#include "tim.h"
#include "nec_fsm.h"

TIM_HandleTypeDef htim3;

void MX_TIM3_Init(void)
{
  TIM_ClockConfigTypeDef sClockSourceConfig;

  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 0;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 840;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  HAL_TIM_Base_Init(&htim3);

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig);
  
  HAL_TIM_Base_Start(&htim3);
  HAL_TIM_Base_Start_IT(&htim3);
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* htim_base)
{
  if(htim_base->Instance==TIM3)
  {
    __TIM3_CLK_ENABLE();
    HAL_NVIC_SetPriority(TIM3_IRQn, 5, 0);// 2 не работает
    HAL_NVIC_EnableIRQ(TIM3_IRQn);
  }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
  if (TIM3 == htim->Instance) {
    tick_soft_timer();
  }
}
