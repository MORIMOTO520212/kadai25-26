#ifndef DCMOTOR_H_
#define DCMOTOR_H_

#define F_CPU	16000000UL
#include	<avr/io.h>
#include	<util/delay.h>
typedef		unsigned char	UCHR;
typedef		unsigned short	USHRT;

class DCMotor
{
	UCHR	level;						// ���[�^��]���x(1-5)
	public:
	DCMotor(void);
	void	setLevel( UCHR level);		// ���[�^��]���x�ݒ�
	void	setOntime( UCHR onTime);	// PWM ON���Ԑݒ�
};

#endif /* DCMOTOR_H_ */