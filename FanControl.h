/*
 * FanControl.h
 *
 * Created: 2021/02/01 19:07:23
 *  Author: MorimotoYuma
 */ 
// î•—‹@‚Ì•——Ê§Œä‚ğs‚¤.

#ifndef FANCONTROL_H_
#define FANCONTROL_H_

#define F_CPU	16000000UL
#include	<avr/io.h>
#include	<util/delay.h>
typedef		unsigned char	UCHR;
typedef		unsigned short	USHRT;

class FanControl{
	UCHR FanLevel;
public:
	void fanLevelRefresh(void);
	UCHR getFanLevel(void);
};

#endif /* FANCONTROL_H_ */