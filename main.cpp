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
	SwingControl sc; // サーボモーター制御
	FanControl fc;   // ロータリーエンコーダ制御
	FanDisp fd;      // 7セグメントLED制御
	
	UCHR temp;
	UCHR fanLevel;
	UCHR swingLevel;
	
	while(1){
		fc.fanLevelRefresh();
		sc.angleRefresh();
		swingLevel = sc.getSwingLevel(); // 首振りの設定値
		
		fd.FanDisplay(UCHR temp, UCHR fanLevel, UCHR swingLevel);
		_delay_ms(100);
	}
	return 0;
}