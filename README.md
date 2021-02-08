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

// comp 汎用クラス
// comp(a,b)   a と b に整数か浮動小数点数を入れると大きい方を返す.
template <class Type> Type comp(Type a, Type b){
	if(a < b) {
		return b;
	}else{
		return a;
	}
};

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

[FanControl] モーターを制御
#include "DCMotor.h"
DCMotor dcm;
// setLevel(UCHR level);
// 0 - 停止
// 1 - 100
// 2 - 180
// 3 - 260
// 4 - 340
// 5 - 420
dcm.setLevel(5);

[PushSW]
#include "PushSW.h"
Push sw;
sw.waitSwOn();  // スイッチONの状態まで待つ
sw.waitSwOff();	// スイッチOFFの状態まで待つ