/*
 * kadai25-26.cpp
 *
 * Created: 2021/02/01 11:41:07
 * Author : MorimotoYuma
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

#include "SwingControl.h"
#include "FanControl.h"
#include "FanDisplay.h"

int main(void) {
	SwingControl sc; // �T�[�{���[�^�[����
	FanControl fc;   // ���[�^���[�G���R�[�_����
	FanDisp fd;      // 7�Z�O�����gLED����
	
	UCHR temp;
	UCHR fanLevel;
	UCHR swingLevel;
	
	while(1){
		fc.fanLevelRefresh();
		sc.angleRefresh();
		swingLevel = sc.getSwingLevel(); // ��U��̐ݒ�l
		
		fd.FanDisplay(UCHR temp, UCHR fanLevel, UCHR swingLevel);
		_delay_ms(100);
	}
	return 0;
}