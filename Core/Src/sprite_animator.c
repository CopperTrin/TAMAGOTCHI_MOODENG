/*
 * sprite_animator.c
 *
 *  Created on: Oct 4, 2025
 *      Author: Acer
 */


#include "sprite_animator.h"
#include "ILI9341_STM32_Driver.h"
#include "ILI9341_GFX.h"

void SpriteAnimator_Init(SpriteAnimator_t* anim,
                         const uint16_t** frames,
                         uint8_t frameCount,
                         uint16_t x, uint16_t y,
                         uint16_t w, uint16_t h,
                         uint32_t frameDelay)
{
    anim->frames = frames;
    anim->frameCount = frameCount;
    anim->x = x;
    anim->y = y;
    anim->w = w;
    anim->h = h;
    anim->currentFrame = 0;
    anim->frameDelay = frameDelay;
    anim->lastFrameTime = 0;
}

void SpriteAnimator_Update(SpriteAnimator_t* anim, uint32_t currentTime)
{
    if (currentTime - anim->lastFrameTime >= anim->frameDelay) {
        anim->currentFrame = (anim->currentFrame + 1) % anim->frameCount;
        anim->lastFrameTime = currentTime;
    }
}

void ILI9341_Draw_PartImage(const uint16_t* image, uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
    ILI9341_Set_Address(x, y, x + w - 1, y + h - 1);

    ILI9341_Write_Command(0x2C);
    for (uint32_t i = 0; i < w * h; i++)
    {
        ILI9341_Write_Data(image[i] >> 8);
        ILI9341_Write_Data(image[i] & 0xFF);
    }
}

void SpriteAnimator_Draw(SpriteAnimator_t* anim)
{
	ILI9341_Draw_PartImage((uint16_t*)anim->frames[anim->currentFrame], anim->x, anim->y, anim->w, anim->h);
}
