/****************************************************************************/
/*	Rotary Encoder read Base Class ��`�t�@�C��								*/
/*																			*/
/*	�{�t�@�C���́CRotary Encoder reader �� Base Class ���`�������̂ł���D	*/
/*	�������̂ł���D															*/
/*																			*/
/*	���R���t�B�O���[�V�������e													*/
/*	�@���ɖ����D																*/
/*																			*/
/*	�����񎖍�																*/
/*	�@�E�{ class �ł�Rotary Encoder ��ENC_A��PD2(IRQ0)�ɁCENC_B��PD3�ɐڑ�����	*/
/*  �@�E�{ class �ł�IRQ0�𗘗p���邽�߁C�����ɕ����̃C���X�^���X�����͏o���Ȃ��D	*/
/*  �@�E���C�Z���X��GPL�ɏ�������̂Ƃ���D										*/
/*																			*/
/*											�������ۍH�Ȑ��E��w�@�r������	*/
/****************************************************************************/
/* #000		2021/01/15 ����										�r������		*/
/****************************************************************************/

#ifndef ROTARYENCODER_H_
#define ROTARYENCODER_H_

// ��`�y��include
#define	F_CPU	16000000UL			// System Clock Frq.

#include <avr/io.h>					// I/O define
#include <util/delay.h>				// Delay function
#include <avr/interrupt.h>

typedef	unsigned char	UCHR;
typedef	unsigned short	USHRT;

class RotaryEncoder{
	int	displacement;				// �G���R�[�_�o�͕ψ�(�E:1/�s��:0/��:-1�j
  public:
	RotaryEncoder();				// �R���X�g���N�^
	int	getDisplacement();			// �ψʓǏo&�N���A
};


#endif /* ROTARYENCODER_H_ */