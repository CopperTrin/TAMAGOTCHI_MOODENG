/*
 * ui_manager.c
 *
 *  Created on: Oct 4, 2025
 *      Author: Acer
 */


#include "ui_manager.h"
#include "pet_sprites.h" // include sprite data arrays
#include "ILI9341_STM32_Driver.h"
#include "ILI9341_GFX.h"
#include "stdbool.h"

SpriteAnimator_t idleAnim;
SpriteAnimator_t sleepAnimDay;
SpriteAnimator_t sleepAnimNight;
SpriteAnimator_t eatAnim;
SpriteAnimator_t playAnim;

extern ADC_HandleTypeDef hadc1;  // From main.c or auto-generated MX_ADC1_Init()
extern UART_HandleTypeDef huart3;

void UIManager_Init(UIManager_t* ui)
{
    static const uint16_t* idleFrames[] = { idle1, idle2, idle3 };
    static const uint16_t* sleepFramesDay[] = { sleep_day1, sleep_day2 };
    static const uint16_t* sleepFramesNight[] = { sleep_night1, sleep_night2 };
//    static const uint16_t* feedFrames[] = { eat1, eat2, eat3 };
//    static const uint16_t* playFrames[] = { play1, play2, play3 };

    SpriteAnimator_Init(&idleAnim, idleFrames, 3, 30, 70, 180, 180, 300);
    SpriteAnimator_Init(&sleepAnimDay, sleepFramesDay, 2, 30, 70, 180, 180, 300);
    SpriteAnimator_Init(&sleepAnimNight, sleepFramesNight, 2, 30, 70, 180, 180, 300);
//    SpriteAnimator_Init(&eatAnim, feedFrames, 3, 80, 60, 160, 120, 200);
//    SpriteAnimator_Init(&playAnim, playFrames, 3, 80, 60, 160, 120, 250);

    ui->menuState = MENU_MAIN;
    ui->activeAnim = &idleAnim;
    ui->selectedState = MENU_MAIN;
    ui->isLightOn = true; // Default day
    ui->lightLevel = 0;
}

void UIManager_SetState(UIManager_t* ui, MenuState_t newState)
{
    ui->menuState = newState;

    switch (newState) {
        case MENU_FEED: ui->activeAnim = &eatAnim; break;
        case MENU_SLEEP:
            if (ui->isLightOn) ui->activeAnim = &sleepAnimDay;
            else ui->activeAnim = &sleepAnimNight;
            break;
        default:        ui->activeAnim = &idleAnim; break;
    }

    ILI9341_Fill_Screen(BLACK);
}

void UIManager_Update(UIManager_t* ui, uint32_t currentTime)
{

    // If currently in sleep menu, react to LDR
    if (ui->menuState == MENU_SLEEP) {

        // Read LDR ADC1
        HAL_ADC_Start(&hadc1);
        while ( HAL_ADC_PollForConversion(&hadc1, 100) != HAL_OK ) {}
        if (HAL_ADC_PollForConversion(&hadc1, 100) == HAL_OK) {
        	/* light on around 800 | light off around 2000+ */
            ui->lightLevel = HAL_ADC_GetValue(&hadc1);
        }
        HAL_ADC_Stop(&hadc1);

        // Determine light status (adjust threshold for your LDR circuit)
        bool newLightState = (ui->lightLevel < 1500); // Example threshold

        if (newLightState != ui->isLightOn)
        {
            ui->isLightOn = newLightState;
            // ✅ Reuse same function
            UIManager_SetState(ui, MENU_SLEEP);

            // Optional UART debug
            char msg[128];
            int n = snprintf(msg, sizeof(msg),
                             "Light change: %lu | isLightOn=%d\r\n",
                             (unsigned long)ui->lightLevel, ui->isLightOn);
            HAL_UART_Transmit(&huart3, (uint8_t*)msg, n, HAL_MAX_DELAY);
        }
    }

    // Update animation normally
    if (ui->activeAnim)
        SpriteAnimator_Update(ui->activeAnim, currentTime);
}

void UIManager_Draw(UIManager_t* ui)
{
	// Draw active animation (if any)
	    if (ui->activeAnim != NULL) {
	        SpriteAnimator_Draw(ui->activeAnim);
	    }

	    // Show current confirmed state (active menu)
	    ILI9341_Draw_Text("Current:", 5, 10, WHITE, 2, BLACK);
	    switch (ui->menuState) {
	        case MENU_MAIN:     ILI9341_Draw_Text("Main", 120, 10, YELLOW, 2, BLACK); break;
	        case MENU_FEED:     ILI9341_Draw_Text("Feed", 120, 10, YELLOW, 2, BLACK); break;
	        case MENU_PLAY:     ILI9341_Draw_Text("Play", 120, 10, YELLOW, 2, BLACK); break;
	        case MENU_SLEEP:    ILI9341_Draw_Text("Sleep", 120, 10, YELLOW, 2, BLACK); break;
	        case MENU_CLEAN:    ILI9341_Draw_Text("Clean", 120, 10, YELLOW, 2, BLACK); break;
	        case MENU_MEDICINE: ILI9341_Draw_Text("Medicine", 120, 10, YELLOW, 2, BLACK); break;
	        default:            ILI9341_Draw_Text("Unknown", 120, 10, RED, 2, BLACK); break;
	    }

	    // Show selected (highlighted but not confirmed yet)
	    ILI9341_Draw_Text("Selected:", 5, 40, WHITE, 2, BLACK);
	    switch (ui->selectedState) {
	        case MENU_MAIN:     ILI9341_Draw_Text("Main", 120, 40, CYAN, 2, BLACK); break;
	        case MENU_FEED:     ILI9341_Draw_Text("Feed", 120, 40, CYAN, 2, BLACK); break;
	        case MENU_PLAY:     ILI9341_Draw_Text("Play", 120, 40, CYAN, 2, BLACK); break;
	        case MENU_SLEEP:    ILI9341_Draw_Text("Sleep", 120, 40, CYAN, 2, BLACK); break;
	        case MENU_CLEAN:    ILI9341_Draw_Text("Clean", 120, 40, CYAN, 2, BLACK); break;
	        case MENU_MEDICINE: ILI9341_Draw_Text("Medicine", 120, 40, CYAN, 2, BLACK); break;
	        default:            ILI9341_Draw_Text("Unknown", 120, 40, RED, 2, BLACK); break;
	    }
    // Optional: Draw UI icons or stats
//    ILI9341_Draw_Text("HP:10", 5, 5, WHITE, 1, BLACK);
//    ILI9341_Draw_Text("Mood:10", 5, 20, WHITE, 1, BLACK);
}
