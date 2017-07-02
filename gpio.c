
#include "gpio.h"

#include "nec_fsm.h"

void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __GPIOE_CLK_ENABLE();

  //IR sensor
  GPIO_InitStruct.Pin = GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 6, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
  
}


/* USER CODE BEGIN 2 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if (GPIO_PIN_9 == GPIO_Pin) {
    GPIO_PinState  PinState;
    enum nec_fsm_inputs fsm_input;
 
    PinState = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_9);
    if (PinState == GPIO_PIN_RESET) {
      HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET);
      fsm_input = NEC_IN_1_RISE;
    }
  
    if (PinState == GPIO_PIN_SET) {
      HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET);
      fsm_input = NEC_IN_0_FALL;
    }
  
    proc_nec_fsm(fsm_input);
  }
}

