/****************************************************************************/
/*	Push Switch Base Class													*/
/*																			*/
/*	�{�t�@�C���́CPush Switch �� Base Class ���`�������̂ł���D				*/
/*																			*/
/*	�����񎖍�																*/
/*  �@�E���C�Z���X��GPL�ɏ�������̂Ƃ���D										*/
/*																			*/
/*											�������ۍH�Ȑ��E��w�@�r������	*/
/****************************************************************************/
/* #000		2021/01/17 ����										�r������		*/
/****************************************************************************/
#include "PushSW.h"

PushSW::PushSW(void){
	CHK_PORT |= CHK_BIT;			// Pull UP
	CHK_DDR &= NCHK_BIT;			// SW Port ����͂ɐݒ�
	this->swState = SW_OFF;			// SW �̏�����Ԃ�SW_OFF�ɐݒ�
}

/****************************************************************/
/* �X�C�b�`��Ԏ擾												*/
/* int getSwState(void)											*/
/* �`���^�����O�`�F�b�N���s���Ȃ���X�C�b�`�̏�Ԃ��擾����			*/
/*		�߂�l�FSW_ON(0)		:�@�X�C�b�`ON���						*/
/*			   SW_OFF(1)	:�@�X�C�b�`OFF���					*/
/*			   SW_IND(-1)	:�@�X�C�b�`��ԕs��					*/
/****************************************************************/
int		PushSW::getSwState(void){
	int	res = SW_IND;								// �X�C�b�`��ԁi�����l�͕s���ɂ��Ă����j
	UCHR	portCondition = (CHK_PORT & CHK_BIT);	// PORT��ԕۑ�
	_delay_ms(CHATT_TIM);							// �`���^�����O�`�F�b�N�f�B���C
	if( portCondition == (CHK_PORT & CHK_BIT)){		// �ēxPORT��Ԃ������Ȃ�,PORT��Ԋm��
		if( portCondition == CHK_BIT){				// PORT��H�Ȃ�C
			res = SW_OFF;							// SW = OFF
		} else{										// PORT��L�Ȃ�C
			res = SW_ON;							// SW = ON
		}
	} else {										// �f�B���C���Ƀ|�[�g��Ԃ��ς�����ꍇ
		portCondition ^= CHK_BIT;					// �O���PORT��Ԃ̔��]�l�����݂̏�Ԃɂ���
		_delay_ms(CHATT_TIM);						// �ēx�`���^�����O�`�F�b�N�f�B���C
		if( portCondition == (CHK_PORT & CHK_BIT)){	// �ēxPORT��Ԃ������Ȃ�CPORT��Ԋm��
			if( portCondition == CHK_BIT){			// PORT��H�Ȃ�C
				res = SW_OFF;						// SW = OFF
			} else{									// PORT��L�Ȃ�C
				res = SW_ON;						// SW = ON
			}
		}
	}
	return res;										// PORT��Ԃ�Ԃ��D
}

/****************************************************************/
/* �X�C�b�`�I�t�҂�												*/
/* void waitSwOff(void)											*/
/* �X�C�b�`��OFF��ԂɂȂ�܂ő҂iOFF��ԂɂȂ�����{�֐��𔲂���	*/
/****************************************************************/
void	PushSW::waitSwOff( void){
	while(1){
		while((CHK_PORT & CHK_BIT) == 0);
		_delay_ms(CHATT_TIM);
		if((CHK_PORT & CHK_BIT) != 0 ){
			break;
		}
	}
}

/****************************************************************/
/* �X�C�b�`�I���҂�												*/
/* void waitSwOn(void)											*/
/* �X�C�b�`��ON��ԂɂȂ�܂ő҂iON��ԂɂȂ�����{�֐��𔲂���		*/
/****************************************************************/
void	PushSW::waitSwOn(void){
	while(1){
		while((CHK_PORT & CHK_BIT) != 0);
		_delay_ms(CHATT_TIM);
		if((CHK_PORT & CHK_BIT) == 0 ){
			break;
		}		
	}
}