#include "ServoMotor.h"

// コンストラクタ
ServoMotor::ServoMotor(void){
	DDRB |= 0b00000100;				// PD6を出力に設定
	TCCR1A |= 0b00100011;			// OC0A 10ビット高速PWM動作
	TCCR1B = 0b00001100;			// 分周比256
	OCR1B = 95;						// モータ角度をセンタに指定
}

void	ServoMotor::setAngle(UCHR angle){
	if( angle >130){				// サーボモータ保護
		angle = 130;
	}
	OCR1B = (USHRT)angle + 30;
}