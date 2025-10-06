/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f7xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f7xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "ui_manager.h"  // <-- Include for MenuState_t and UIManager_t
#include "timer.h"
#include "moodeng.h"
extern Clock_t gameClock;
extern Moodeng_t moodeng;

typedef enum {
    MEAL = 0,
    SNACK
} Food_t;
Food_t foodSelected = MEAL;

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
//extern PetState_t currentState;
//extern PetState_t selectNextState;
extern bool shouldClearScreen;

extern UIManager_t ui;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern DMA_HandleTypeDef hdma_adc1;
extern TIM_HandleTypeDef htim1;
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M7 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F7xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f7xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles EXTI line0 interrupt.
  */
void EXTI0_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI0_IRQn 0 */

  /* USER CODE END EXTI0_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
  /* USER CODE BEGIN EXTI0_IRQn 1 */

  // (B) YELLOW: Cycle only the highlighted (unconfirmed) menu
  switch (ui.menuState) {
	  case MENU_MAIN:     
      ui.selectedState = (ui.selectedState + 1) % 6;
      break;
	  case MENU_FEED:     
      if (foodSelected == MEAL) foodSelected = SNACK;
      else foodSelected = MEAL;
      break;
	  case MENU_PLAY:     
      if(Moodeng_Minigame(&moodeng, 0)) {
        ui.activeAnim = &miniGameCorrectAnim;
        moodeng.happy += 2;
      }
      else {
        ui.activeAnim = &miniGameWrongAnim;
        moodeng.happy++;
      }
      moodeng.weight--;
      moodeng.emotion = NORMAL;
      break;
	  case MENU_SLEEP: 
      //Moodeng_Sleep(&moodeng);
      break;
	  case MENU_CLEAN:    
      ui.activeAnim = &cleanAnim;
      moodeng.poopCount--;
      break;
	  case MENU_MEDICINE: 
      ui.activeAnim = &medicineAnim;
      Moodeng_Heal(&moodeng);
      break;
	  default:
      break;
	}
  shouldClearScreen = true;

  /* USER CODE END EXTI0_IRQn 1 */
}

/**
  * @brief This function handles EXTI line3 interrupt.
  */
void EXTI3_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI3_IRQn 0 */

  /* USER CODE END EXTI3_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_3);
  /* USER CODE BEGIN EXTI3_IRQn 1 */

  // (A) RED: Reset selection and confirmed menu to MAIN
  if(ui.menuState != MENU_MAIN){
    UIManager_SetState(&ui, MENU_MAIN);
    shouldClearScreen = true;
  }
  else if (ui.menuState == MENU_MAIN){
    if(moodeng.emotion != SILLY) moodeng.happy--;
    else if(moodeng.emotion == SILLY) {
      moodeng.discipline++;
      moodeng.emotion = SCOLDED;
    }
  }
  /* USER CODE END EXTI3_IRQn 1 */
}

/**
  * @brief This function handles EXTI line[9:5] interrupts.
  */
void EXTI9_5_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI9_5_IRQn 0 */

  /* USER CODE END EXTI9_5_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_5);
  /* USER CODE BEGIN EXTI9_5_IRQn 1 */

  // (C) BLUE: Confirm selection → set active menu
  switch (ui.menuState) {
	  case MENU_MAIN:     
      if(ui.selectedState == MENU_MAIN){
        if(Moodeng_Check_Feed(&moodeng)) UIManager_SetState(&ui, ui.selectedState);
        else {
          ui.activeAnim = &stubbornAnim;
        }
      }
      else if (ui.selectedState == MENU_PLAY){
        if(Moodeng_Check_Play(&moodeng)) UIManager_SetState(&ui, ui.selectedState);
        else{
          ui.activeAnim = &stubbornAnim;
        }
      }
      else {
        UIManager_SetState(&ui, ui.selectedState);
      }
      shouldClearScreen = true;
      break;
	  case MENU_FEED:     
      if(foodSelected == MEAL){
        ui.activeAnim = &feedMealAnim;
        moodeng.hunger += 2;
        moodeng.weight += 2;
        moodeng.poopRate += 0.4;
      }
      else if(foodSelected == SNACK){
        ui.activeAnim = &feedSnackAnim;
        moodeng.happy += 2;
        moodeng.weight += 4;
        moodeng.poopRate += 0.4;
      }
      moodeng.emotion = NORMAL;
      break;
	  case MENU_PLAY:     
      if(Moodeng_Minigame(&moodeng, 1)) {
        ui.activeAnim = &miniGameCorrectAnim;
        moodeng.happy += 2;
      }
      else {
        ui.activeAnim = &miniGameWrongAnim;
        moodeng.happy++;
      }
      moodeng.weight--;
      moodeng.emotion = NORMAL;
      break;
	  default:
      break;
	}
  /* USER CODE END EXTI9_5_IRQn 1 */
}

/**
  * @brief This function handles TIM1 update interrupt and TIM10 global interrupt.
  */
void TIM1_UP_TIM10_IRQHandler(void)
{
  /* USER CODE BEGIN TIM1_UP_TIM10_IRQn 0 */

  /* USER CODE END TIM1_UP_TIM10_IRQn 0 */
  HAL_TIM_IRQHandler(&htim1);
  /* USER CODE BEGIN TIM1_UP_TIM10_IRQn 1 */
  Timer_Update(&gameClock);
  /* USER CODE END TIM1_UP_TIM10_IRQn 1 */
}

/**
  * @brief This function handles EXTI line[15:10] interrupts.
  */
void EXTI15_10_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI15_10_IRQn 0 */

  /* USER CODE END EXTI15_10_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_10);
  /* USER CODE BEGIN EXTI15_10_IRQn 1 */

  /* USER CODE END EXTI15_10_IRQn 1 */
}

/**
  * @brief This function handles DMA2 stream0 global interrupt.
  */
void DMA2_Stream0_IRQHandler(void)
{
  /* USER CODE BEGIN DMA2_Stream0_IRQn 0 */

  /* USER CODE END DMA2_Stream0_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_adc1);
  /* USER CODE BEGIN DMA2_Stream0_IRQn 1 */

  /* USER CODE END DMA2_Stream0_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
