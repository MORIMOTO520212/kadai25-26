# kadai25-26
## 自動首振り扇風機

 FanControl.h
 FanControl.cpp
 SwingControl.h
 SwingControl.cpp
 FanDisplay.h
 FanDisplay.cpp
 main.cpp

 2pin - SA
 3pin - SB
 4pin - Push SW
 8pin - TM1637(CLK)
 9pin - DC Motor
 10pin - Servo Motor
 11pin - DHT11(SDA)
 12pin - TM1637(DIO)

 ## 使い方

[FanDisplay] ディスプレイ表示
// [FanDisp]
// dispData[4]
// fanDisplay(UCHR temp, UCHR fanLevel, UCHR swingLevel)

#include "TM1637Disp.h"

int a = 2;
int b = 4;
float c = 1.7;
float d = 1.1;
UCHR data[4] = {10, 10, 10, 10}; // 数値配列データ
TM1637Disp disp;

while(1) {
	data[0] = a;
	data[1] = b;
	data[3] = comp(a,b);
	disp.numDisp(data);
	_delay_ms(1000);
		
	data[0] = (UCHR)comp(c,d) | 0x80; // 0x80でピリオドを表示.
	data[1] = (UCHR) (comp(c,d) * 10.0) % 10;
	data[3] = 10;
	disp.numDisp(data);
	_delay_ms(1000);
}

[FanControl] プロペラを制御 ロータリーエンコーダの呼び出し
#include "FanControl.h"
FanControl FC;
FC.fanLevelRefresh();

[PushSW]
#include "PushSW.h"
PushSW sw;
sw.waitSwOn();  // スイッチONの状態まで待つ
sw.waitSwOff();	// スイッチOFFの状態まで待つ


[SwingControl]
#include "SwingControl.h"
SwingControl SC;
while(1){ // 100msごとに割り込み処理？
	SC.angleRefresh();
	_delay_ms(100);
}
