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
	SwingControl sc; // サーボモーター制御
	FanControl fc;   // ロータリーエンコーダ制御
	FanDisp fd;      // 7セグメントLED制御
	
	UCHR temp;
	UCHR fanLevel;
	UCHR swingLevel;
	
	while(1){
		fc.fanLevelRefresh(); // ロータリーエンコーダ, DCモーター, 湿温度センサー
		sc.angleRefresh();    // サーボモーター
		temp       = fc.getTemperature(); // 温度取得
		fanLevel   = fc.getFanLevel();    // 風量レベル取得
		swingLevel = sc.getSwingLevel();  // 首振りの設定値取得
		fd.FanDisplay(temp, fanLevel, swingLevel);
		_delay_ms(100);
	}
	return 0;
}