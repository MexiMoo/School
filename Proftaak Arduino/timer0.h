/*
 * timer0.h
 *
 * Created: 22-2-2023 16:22:31
 *  Author: rasmsmee
 */ 


#ifndef TIMER0_H_
#define TIMER0_H_

#define OCR0_CALL_COMPENSATION 9

void timer0_Start(void);
void timer0_Init(void);
void timer0_Delay100us(void);
void timer0_DelayN100us(uint32_t number);
void timer0_SetCompareValue(uint8_t count);

void InitTimer(void);
void delayms(uint32_t milliSeconds);

#endif /* TIMER0_H_ */