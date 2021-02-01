#include "DCMotor.h"
// CCMotor Class �R���X�g���N�^
DCMotor::DCMotor(){
	level = 0;
	DDRB |= 0b00000010;							// OC1A���o�̓|�[�g�ɐݒ�
	TCCR1A |= 0b10000011;						// ����PWM����
	TCCR1B = 0b00001100;						// 8����
	OCR1A = 100;									// �����lduty4%�ɐݒ�
}
// ���[�^���x�ݒ�
void	DCMotor::setLevel( UCHR level){			// ���[�^���x�ݒ�
	USHRT	levelTbl[6] = {0,100,180,260,340,420};
	if( level > 5){								// �͈͊O�̒l���ݒ肳�ꂽ�ꍇ
		level = 5;								// �ő僌�x����ݒ�
	}
	this->level = level;						// ���[�^���x���x����ۑ�
	OCR1A = levelTbl[(int)level];					// duty ��ݒ�
}

// PWM ON���Ԑݒ�i���x���x���ł͂Ȃ�PWM��duty�𒼐ڐݒ肷��D
void	DCMotor::setOntime( UCHR onTime){
	OCR1A = onTime;
}