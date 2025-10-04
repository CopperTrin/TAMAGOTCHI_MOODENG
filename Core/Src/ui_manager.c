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

SpriteAnimator_t idleAnim;
SpriteAnimator_t eatAnim;
SpriteAnimator_t playAnim;

void UIManager_Init(UIManager_t* ui)
{
    static const uint16_t* idleFrames[] = { idle1, idle2, idle3 };
//    static const uint16_t* feedFrames[] = { eat1, eat2, eat3 };
//    static const uint16_t* playFrames[] = { play1, play2, play3 };

    SpriteAnimator_Init(&idleAnim, idleFrames, 3, 30, 70, 180, 180, 300);
//    SpriteAnimator_Init(&eatAnim, feedFrames, 3, 80, 60, 160, 120, 200);
//    SpriteAnimator_Init(&playAnim, playFrames, 3, 80, 60, 160, 120, 250);

    ui->menuState = MENU_MAIN;
    ui->activeAnim = &idleAnim;
}

void UIManager_SetState(UIManager_t* ui, MenuState_t newState)
{
    ui->menuState = newState;

    switch (newState) {
        case MENU_FEED: ui->activeAnim = &eatAnim; break;
        case MENU_PLAY: ui->activeAnim = &playAnim; break;
        default:        ui->activeAnim = &idleAnim; break;
    }

    ILI9341_Fill_Screen(BLACK);
}

void UIManager_Update(UIManager_t* ui, uint32_t currentTime)
{
    SpriteAnimator_Update(ui->activeAnim, currentTime);
}

void UIManager_Draw(UIManager_t* ui)
{
    SpriteAnimator_Draw(ui->activeAnim);

    // Optional: Draw UI icons or stats
//    ILI9341_Draw_Text("HP:10", 5, 5, WHITE, 1, BLACK);
//    ILI9341_Draw_Text("Mood:10", 5, 20, WHITE, 1, BLACK);
}
