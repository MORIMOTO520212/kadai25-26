#include "DCMotor.h"
// CCMotor Class コンストラクタ
DCMotor::DCMotor(){
	level = 0;
	DDRB |= 0b00000010;							// OC1Aを出力ポートに設定
	TCCR1A |= 0b10000011;						// 高速PWM動作
	TCCR1B = 0b00001100;						// 8分周
	OCR1A = 100;									// 初期値duty4%に設定
}
// モータ速度設定
void	DCMotor::setLevel( UCHR level){			// モータ速度設定
	USHRT	levelTbl[6] = {0,100,180,260,340,420};
	if( level > 5){								// 範囲外の値が設定された場合
		level = 5;								// 最大レベルを設定
	}
	this->level = level;						// モータ速度レベルを保存
	OCR1A = levelTbl[(int)level];					// duty を設定
}

// PWM ON時間設定（速度レベルではなくPWMのdutyを直接設定する．
void	DCMotor::setOntime( UCHR onTime){
	OCR1A = onTime;
}