/****************************************************************************/
/*																			*/
/*		DH11�����x�Z���T�f�[�^��M Base Class ��`�t�@�C��						*/
/*																			*/
/*	�{�t�@�C���́CDH11�����x�Z���T��莼�x�y�щ��x����M���� Base Class ���`	*/
/*	�������̂ł���D															*/
/*																			*/
/*	���R���t�B�O���[�V�������e													*/
/*	�@�ȉ��̓��e�ɂ��āC�ΏۂƂȂ�n�[�h�E�F�A�ɍ��킹�āC���e������������K�v	*/
/*	������D																	*/
/*  (1)CPU�N���b�N��`														*/
/*		�V���{�����FF_CPU		�F�V�X�e���N���b�N���g��(ex.16MH�� 16000000UL)		*/
/*	(2)DH11��SDA��ڑ�����|�[�g���ύX											*/
/*		�V���{�����F DH11_O	�F�o�͑��|�[�g��									*/
/*					DH11_I	�F���͑��|�[�g��									*/
/*					DH11_DDR�F�f�[�^�������W�X�^��							*/
/*	(3)DH11��DIO��ڑ�����r�b�g�ʒu											*/
/*					SDA		�FDIO�[�q��ڑ�����|�[�g���̃r�b�g�ʒu(�Y����1�j	*/
/*																			*/
/*	�����񎖍�																*/
/*		�EDHT11Read�֐����Ăяo������C����DHT11Read�֐����Ăяo������2�b�ȏ��	*/
/*		�@�Ԋu���󂯂邱�ƁD													*/
/*		�@DHT11Read�֐��͔񃊃G���g�����g�ł���D								*/
/*		�E���C�Z���X��GPL�ɏ�������̂Ƃ���D									*/
/*																			*/
/*											�������ۍH�Ȑ��E��w�@�r������	*/
/****************************************************************************/
/* #000		2021/01/08 ����										�r������		*/
/* #001     2021/01/09 ���x�������ŕێ��ł���悤�C��				�r������		*/
/****************************************************************************/
#ifndef DHT11_H_
#define DHT11_H_

// ��`�y��include
#define		F_CPU	16000000UL					// CPU Clock Freq.
#include <avr/io.h>								// CPU HW define
#include <util/delay.h>							// Delay Func.
#include <avr/interrupt.h>						// use sei() and cli()

typedef	unsigned char	UCHR;
typedef	unsigned short	USHRT;

#define DH11_O		PORTB						// DH11��SDA������o�̓��W�X�^@@
#define DH11_I		PINB						// DH11��SDA��������̓��W�X�^@@
#define DH11_DDR	DDRB						// DH11��SDA������������W�X�^@@
#define SDA			0b00001000					// DH11��SDA�|�[�g�ʒu�i�ʏ�j@@
#define	NSDA		~SDA						// DH11��SDA�|�[�g�ʒu�i�␔�j
#define SDA_H		DH11_O = DH11_I |SDA		// SDA�[�q��'H'���o��
#define SDA_L		DH11_O = DH11_I & NSDA		// SDA�[�q��'L'���o��
#define	SDA_OUT		DH11_DDR = DH11_DDR | SDA	// SDA�[�q���o�̓|�[�g�ɐݒ�
#define SDA_IN		DH11_DDR = DH11_DDR & NSDA	// SDA�[�q����̓|�[�g�ɐݒ�
#define WAIT_SDA_H	while(( DH11_I & SDA) == 0)	// SDA�[�q��'H'�ɂȂ�܂ő҂�
#define WAIT_SDA_L	while(( DH11_I & SDA) != 0)	// SDA�[�q��'L'�ɂȂ�܂ő҂�

// Class ��`
class DHT11
{
	float	temperature;						// ���x�f�[�^�i�����j#001
	UCHR	temperature_H;						// ���x�f�[�^�i�����_�ȏ�j
	UCHR	temperature_L;						// ���x�f�[�^�i�����_�����j
	UCHR	humidity_H;							// ���x�f�[�^�i�����_�ȏ�j
	UCHR	humidity_L;							// ���x�f�[�^�i�����_�����j
  public:
	DHT11(void);								// �R���X�g���N�^
	int		DHT11Read( void);					// �����x�f�[�^��M���\�b�h
	float	getTemperature(void);				// ���x�f�[�^�i�����j�Ǐo�� #001
	UCHR	getTemperature_H(void);				// ���x�f�[�^�i�����_�ȏ�j�Ǐo��
	UCHR	getTemperature_L(void);				// ���x�f�[�^�i�����_�����j�Ǐo��
	UCHR	getHumidity_H(void);				// ���x�f�[�^�i�����_�ȏ�j�Ǐo��
	UCHR	getHumidity_L(void);				// ���x�f�[�^�i�����_�����j�Ǐo��
};

#endif /* DHT11_H_ */