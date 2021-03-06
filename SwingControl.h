/*
 * SwingControl.h
 *
 * Created: 2021/02/01 19:08:38
 *  Author: MorimotoYuma
 */ 


#ifndef SWINGCONTROL_H_
#define SWINGCONTROL_H_

#define	F_CPU	16000000UL

#include <avr/io.h>
#include <util/delay.h>

typedef	unsigned char	UCHR;
typedef	unsigned short	USHRT;

class SwingControl{
	UCHR swingLevel;
	UCHR swingAngle;
public:
	SwingControl();
	void angleRefresh(void);  // 更新
	UCHR getSwingLevel(void); // 首振りの設定値を返す
};

#endif /* SWINGCONTROL_H_ */