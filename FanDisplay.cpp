/*
 * FanDisp.cpp
 *
 * Created: 2021/02/01 19:09:40
 *  Author: MorimotoYuma
 */ 
#include "FanDisplay.h"
TM1637Disp disp;

// comp 汎用クラス
// comp(a,b)   a と b に整数か浮動小数点数を入れると大きい方を返す.
template <class Type> Type comp(Type a, Type b){ // 多分使わない
	if(a < b) {
		return b;
		}else{
		return a;
	}
};

void FanDisp::FanDisplay(UCHR temp, UCHR fanLevel, UCHR swingLevel){
	// 温度, 風量レベル, 首振りレベル
	UCHR data[4] = {10, 10, 10, 10}; // 数値配列データ
	data[2] = (int)temp%10;
	data[3] = (int)temp/10;
	disp.numDisp(data);
}