/*
 * FanDisp.h
 *
 * Created: 2021/02/01 19:09:59
 *  Author: MorimotoYuma
 */ 


#ifndef FANDISP_H_
#define FANDISP_H_

#define F_CPU	16000000UL
#include	<util/delay.h>
typedef		unsigned char	UCHR;
typedef		unsigned short	USHRT;

class FanDisp{
public:
	void FanDisplay(UCHR temp, UCHR fanLevel, UCHR swingLevel);
};

#endif /* FANDISP_H_ */