#include "moodeng.h"
#include <stdbool.h>
#include "rng.h"

void Moodeng_Init(Moodeng_t* moodeng) {
    moodeng->happy = 2;
    moodeng->weight = 5;
    moodeng->hunger = 2;
    moodeng->poopCount = 0;
    moodeng->poopRate = 0.0f; 
    moodeng->isSick = false;
    moodeng->healRate = 0.5f;
    moodeng->discipline = 3;
    moodeng->isTried = false;
    moodeng->evolution = 0;
    moodeng->isAlive = true;
    moodeng->emotion = NORMAL;
    moodeng->nextDecayHappy = Moodeng_GenerateRandomNumber(moodeng, 60, 90);
    moodeng->nextDecayHunger = Moodeng_GenerateRandomNumber(moodeng, 45, 75);
    moodeng->nextPoopTime = Moodeng_GenerateRandomNumber(moodeng, 10, 30);
    moodeng->nextSickTime = NULL;
    moodeng->nextHurtTime = NULL;
    moodeng->nextDirtyTime = NULL;
    moodeng->nextSleepyTime = 480;
}

int Moodeng_GenerateRandomNumber(Moodeng_t* moodeng, int start, int end) {
    uint32_t randomNum;
    HAL_RNG_GenerateRandomNumber(&hrng, &randomNum);
    return start + (randomNum % (end - start + 1));
}

bool inRangeInt(int value, int min, int max) {
    return value >= min && value <= max;
}

bool inRangeFloat(float value, float min, float max) {
    return value >= min && value <= max;
}

void setHappy(Moodeng_t* moodeng, int emotion) {
    if (inRangeInt(emotion, 0, 4)) 
        moodeng->happy = emotion;
}

void setWeight(Moodeng_t* moodeng, int value) {
    if (inRangeInt(value, 5, 99)) 
        moodeng->weight = value;
}

void setHunger(Moodeng_t* moodeng, int value) {
    if (inRangeInt(value, 0, 4)) 
        moodeng->hunger = value;
}

void setPoopCount(Moodeng_t* moodeng, int value) {
    if (inRangeInt(value, 0, 6)) 
        moodeng->poopCount = value;
}

void setPoopRate(Moodeng_t* moodeng, float value) {
    if (inRangeFloat(value, 0.0f, 1.0f)) 
        moodeng->poopRate = value;
} 

void setIsSick(Moodeng_t* moodeng, bool value) {
    moodeng->isSick = value;
}

void setHealRate(Moodeng_t* moodeng, float value) {
    if (inRangeFloat(value, 0.0f, 1.0f)) 
        moodeng->healRate = value;
}

void setDiscipline(Moodeng_t* moodeng, int value) {
    if (inRangeInt(value, 0, 6))
        moodeng->discipline = value;
}

void setIsTried(Moodeng_t* moodeng, bool value) {
    moodeng->isTried = value;
}

void setEvolution(Moodeng_t* moodeng, int value) {
    if (inRangeInt(value, 0, 2))
        moodeng->evolution = value;
}

void setEmotion(Moodeng_t* moodeng, Emotion_t value) {
    moodeng->emotion = value;
}

float Moodeng_FeedingChange(Moodeng_t* moodeng) {
    return moodeng->discipline * 0.17f;
}

float Moodeng_SickChange(Moodeng_t* moodeng) {
    return moodeng->weight * 0.15f + moodeng->poopCount * 0.1f + moodeng->isTried * 0.15f + (20.0f - moodeng->happy * 0.05f) + (20.0f - moodeng->hunger * 0.05f);
}

float Moodeng_PlayingChange(Moodeng_t* moodeng) {
    return moodeng->discipline * 0.22f - moodeng->weight * 0.4f;
}
