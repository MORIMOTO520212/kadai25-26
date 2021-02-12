/*
 * SwingControl.cpp
 *
 * Created: 2021/02/01 19:08:24
 *  Author: MorimotoYuma
 */
/*
	・main.cppでangleRefreshを100msごとに呼び出して1°ずつ回転させる。
	・swingLevelは0, 1, 2, 3の値が入る
	[回転角度]
	0 - stop
	1 - 43 ~ 87°
	2 - 21 ~ 109°
	3 -  0 ~ 130°
*/

#include "SwingControl.h"

#include "PushSW.h"
#include "ServoMotor.h"

PushSW sw;
ServoMotor sm;

SwingControl::SwingControl(){ // 初期値
	this->swingLevel = 0;
}

void SwingControl::angleRefresh(void){
	UCHR s = 1; // 1-加算, -1-減算
	if(0 == sw.getSwState()){ // スイッチで判別する
		sw.waitSwOff();
		this->swingLevel ++;
		if(4 == this->swingLevel) this->swingLevel = 0;
	}
	
	if(1 == this->swingLevel){ // 43 ~ 87°
		if(43 == this->swingAngle) s = 1;
		if(87 == this->swingAngle) s = -1;
	}
	if(2 == this->swingLevel){ // 21 ~ 109°
		if(21 == this->swingAngle) s = 1;
		if(109 == this->swingAngle) s = -1;
	}
	if(3 == this->swingLevel){ //  0 ~ 130°
		if(0 == this->swingAngle) s = 1;
		if(109 == this->swingAngle) s = -1;
	}
	this->swingAngle += s;
	if(0 == this->swingLevel){
		this->swingAngle = 65; // 中央
	}
	sm.setAngle(this->swingAngle);
}
UCHR SwingControl::getSwingLevel(void){ // 首振りの設定値を返す　表示に使う
	return this->swingLevel;
}