/*
 * ui_manager.h
 *
 *  Created on: Oct 4, 2025
 *      Author: Acer
 */

#ifndef INC_UI_MANAGER_H_
#define INC_UI_MANAGER_H_

#include "sprite_animator.h"
#include "ILI9341_GFX.h"

typedef enum {
    MENU_MAIN,
    MENU_FEED,
    MENU_PLAY,
    MENU_SLEEP,
    MENU_CLEAN,
    MENU_MEDICINE
} MenuState_t;

typedef struct {
    MenuState_t menuState;
    SpriteAnimator_t* activeAnim;
} UIManager_t;

void UIManager_Init(UIManager_t* ui);
void UIManager_SetState(UIManager_t* ui, MenuState_t newState);
void UIManager_Update(UIManager_t* ui, uint32_t currentTime);
void UIManager_Draw(UIManager_t* ui);

#endif /* INC_UI_MANAGER_H_ */
