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
	// ���x, ���ʃ��x��, ��U�背�x��
	UCHR data[4] = {10, 10, 10, 10}; // ���l�z��f�[�^
	data[0] = (int)temp%10;
	data[1] = (int)temp/10;
	data[2] = fanLevel;
	data[3] = swingLevel;
	disp.numDisp(data);
}