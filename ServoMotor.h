/****************************************************************************/
/*	Servo Motor Base Class ��`�t�@�C��										*/
/*																			*/
/*	�{�t�@�C���́CServo Motor�ɉ�]�p�x��ݒ肷�邽�߂�Base Class ���`			*/
/*	�������̂ł���D															*/
/*																			*/
/*	���R���t�B�O���[�V�������e													*/
/*	�@�ȉ��̓��e�ɂ��āC�ΏۂƂȂ�n�[�h�E�F�A�ɍ��킹�āC���e������������K�v	*/
/*	������D																	*/
/*																			*/
/*	�����񎖍�																*/
/*		�EPWM�M����Timer0�i16Bit Timer)�ō�肾���Ă��邽�߁C�K��PB2�ɐڑ�����	*/
/*		  �g�p���邱�ƁD														*/
/*		�EServoMotor�֐��̓��G���g�����g�ł��邪�C�f�o�C�X�A�N�Z�X�𔺂����ߋ���	*/
/*		  �ɒ��ӂ��邱�ƁD													*/
/*		�E���C�Z���X��GPL�ɏ�������̂Ƃ���D									*/
/*																			*/
/*											�������ۍH�Ȑ��E��w�@�r������	*/
/****************************************************************************/
/* #000		2021/01/26 ����										�r������		*/
/****************************************************************************/
#ifndef SERVOMOTOR_H_
#define SERVOMOTOR_H_

#define F_CPU	16000000UL
#include	<avr/io.h>
#include	<util/delay.h>
typedef		unsigned char	UCHR;
typedef		unsigned short	USHRT;

class	ServoMotor{
  public:
  ServoMotor();							// �R���X�g���N�^
	void	setAngle( UCHR angle);		// �p�x�ݒ胁�\�b�h
};

#endif /* SERVOMOTOR_H_ */