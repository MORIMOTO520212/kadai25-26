/*
 * kadai25-26.cpp
 *
 * Created: 2021/02/01 11:41:07
 * Author : MorimotoYuma
 */ 
#include <avr/io.h>

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
		fc.fanLevelRefresh(); // ���[�^���[�G���R�[�_, DC���[�^�[, �����x�Z���T�[
		sc.angleRefresh();    // �T�[�{���[�^�[
		temp       = fc.getTemperature(); // ���x�擾
		fanLevel   = fc.getFanLevel();    // ���ʃ��x���擾
		swingLevel = sc.getSwingLevel();  // ��U��̐ݒ�l�擾
		fd.FanDisplay(temp, fanLevel, swingLevel);
		_delay_ms(100);
	}
	return 0;
}