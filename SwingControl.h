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
	UCHR swingLevel = 0;
	UCHR swingAngle = 90; // ’†‰›
public:
	void angleRefresh(void);
	UCHR getSwingLevel(void);
};

#endif /* SWINGCONTROL_H_ */