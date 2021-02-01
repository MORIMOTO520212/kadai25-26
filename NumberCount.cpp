/****************************************************************************/
/*	NumberCount Class														*/
/*																			*/
/*	�{�t�@�C���́CNumberCount Class �ł���D									*/
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

#include "NumberCount.h"
/****************************************************************/
/* �R���X�g���N�^�i���������j										*/
/* �R���X�g���N�^�̈������Ȃ��ꍇ�́C�ȉ��̐ݒ�l�ƂȂ�				*/
/*		�ő�l�F9												*/
/*		�ŏ��l�F0												*/
/*		�����l�F0												*/
/*		�z  �F�z����i9 -> 0, 0 -> 9)							*/
/****************************************************************/
NumberCount::NumberCount(){
	this->maxNumber = 9;
	this->minNumber = 0;
	this->number = 0;
	this->circulation = 1;
}

/****************************************************************/
/* �R���X�g���N�^�i�����L��j										*/
/* Number(int max, int min, int dflt, int circ)					*/
/* �R���X�g���N�^�̈���������ꍇ�́C������ݒ�l�Ƃ���				*/
/*		�ő�l�Fmax												*/
/*		�ŏ��l�Fmin												*/
/*		�����l�Fdflt												*/
/*		�z  �Fcirc (1:�z����/0:�z�Ȃ�)						*/
/****************************************************************/
NumberCount::NumberCount(int max,int min,int dflt, UCHR circ){
	this->maxNumber = max;
	this->minNumber = min;
	this->number = dflt;
	this->circulation = circ;	
}

void	NumberCount::countInit(void){
	this->number = this->minNumber;					// ���݂̒l�ɍŏ��l������
}

void	NumberCount::countInit( int num){
	this->number = num;								// ���݂̒l�Ɉ����̒l������
}

/****************************************************************/
/* �J�E���^�l�ǂݏo��												*/
/* int NumberCount(void)										*/
/* ���݂̃J�E���^�l��ǂݏo��										*/
/*		�߂�l�F���݂̃J�E���^�l									*/
/****************************************************************/
int		NumberCount::readCounter(){
	this->number += getDisplacement();				// �G���R�[�_�̕ψʂ�ǂݏo���C�J�E���^�l�ɉ��Z����
	if( this->number > this->maxNumber){			// �J�E���^�l���ő�l�𒴂����ꍇ
		if( this->circulation == CIRCULATION){		// �z�w��L��̏ꍇ
			this->number = this->minNumber;			// �@�J�E���^�l�ɍŏ��l���Z�b�g����
		} else{										// �z�w�薳���̏ꍇ
			this->number = this->maxNumber;			// �@�J�E���^�l�ɍő�l���Z�b�g����
		}
	} else if( this->number < this->minNumber){		// �J�E���^�l���ŏ��l�����̏ꍇ
		if( this->circulation == CIRCULATION){		// �z�w��L��̏ꍇ
			this->number = this->maxNumber;			// �@�J�E���^�l�ɍő�l���Z�b�g����
		} else{										// �z�w�薳���̏ꍇ
			this->number = this->minNumber;			// �@�J�E���^�l�ɍŏ��l���Z�b�g����
		}
	}
	return this->number;							// �J�E���^�l��߂�l�Ƃ��Ė߂�
}