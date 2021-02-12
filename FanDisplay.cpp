/*
 * FanDisp.cpp
 *
 * Created: 2021/02/01 19:09:40
 *  Author: MorimotoYuma
 */ 
#include "FanDisplay.h"

#include "TM1637Disp.h"

TM1637Disp disp;

void FanDisp::FanDisplay(UCHR temp, UCHR fanLevel, UCHR swingLevel){
	// 温度, 風量レベル, 首振りレベル
	UCHR data[4] = {10, 10, 10, 10}; // 数値配列データ
	data[0] = (int)temp%10;
	data[1] = (int)temp/10;
	data[2] = fanLevel;
	data[3] = swingLevel;
	disp.numDisp(data);
}