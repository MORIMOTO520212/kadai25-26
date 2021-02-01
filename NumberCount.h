/****************************************************************************/
/*	NumberCount Class														*/
/*																			*/
/*	�{�t�@�C���́CNumberCount Class ���`�������̂ł���D						*/
/*																			*/
/*	���R���t�B�O���[�V�������e													*/
/*	�@���ɂȂ�																*/
/*																			*/
/*	�����񎖍�																*/
/*  �@�E���C�Z���X��GPL�ɏ�������̂Ƃ���D										*/
/*																			*/
/*											�������ۍH�Ȑ��E��w�@�r������	*/
/****************************************************************************/
/* #000		2021/01/17 ����										�r������		*/
/****************************************************************************/

#ifndef NUMBERCOUNT_H_
#define NUMBERCOUNT_H_

#include "RotaryEncoder.h"

#define	CIRCULATION		1
#define NON_CIRCULATION	0

class NumberCount : public RotaryEncoder{
	int		number;							// ���݂̒l
	int		maxNumber;						// �ő�l
	int		minNumber;						// �ŏ��l
	UCHR	circulation;					// 1:���l���z������
  public:
	NumberCount();							// �R���X�g���N�^�i�W���j
	NumberCount(int max,int min,int dflt, UCHR circ);// �R���X�g���N�^�i�ݒ�l�t���j
	void	countInit(void);				// ���݂̒l������������i0�ŏ������j
	void	countInit(int num);				// ���݂̒l������������i�w��l�ŏ������j
	int		readCounter();					// ���݂̒l��ǂݏo��
};

#endif /* NUMBERCOUNT_H_ */