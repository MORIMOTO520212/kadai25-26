#include "ServoMotor.h"

// �R���X�g���N�^
ServoMotor::ServoMotor(void){
	DDRB |= 0b00000100;				// PD6���o�͂ɐݒ�
	TCCR1A |= 0b00100011;			// OC0A 10�r�b�g����PWM����
	TCCR1B = 0b00001100;			// ������256
	OCR1B = 95;						// ���[�^�p�x���Z���^�Ɏw��
}

void	ServoMotor::setAngle(UCHR angle){
	if( angle >130){				// �T�[�{���[�^�ی�
		angle = 130;
	}
	OCR1B = (USHRT)angle + 30;
}