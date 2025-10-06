#ifndef __TIMER_H
#define __TIMER_H

typedef struct {
    int hour;
    int minute;
    int second;
} Clock_t;

extern Clock_t gameClock;

void Timer_Init(void);          // ตั้งค่า Timer หรือ SysTick
void Timer_Update(void);        // เรียกทุก 1 วินาทีเพื่ออัปเดตเวลา
void Timer_Reset(void);         // รีเซ็ตเวลา

#endif