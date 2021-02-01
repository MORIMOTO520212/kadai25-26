/****************************************************************************/
/*	Push Switch Base Class													*/
/*																			*/
/*	�{�t�@�C���́CPush Switch �� Base Class ���`�������̂ł���D				*/
/*																			*/
/*	���R���t�B�O���[�V�������e													*/
/*	�@�ȉ��̓��e�ɂ��āC�ΏۂƂȂ�n�[�h�E�F�A�ɍ��킹�āC���e������������K�v	*/
/*	������D																	*/
/*  (1)CPU�N���b�N��`														*/
/*		�V���{�����FF_CPU		�F�V�X�e���N���b�N���g��(ex.16MH�� 16000000UL)		*/
/*	(2)SW��ڑ�����|�[�g���ύX												*/
/*		�V���{�����F CHK_PORT�FSW��ڑ�����|�[�g��	�i���̓��W�X�^���j		*/
/*					CHK_DDR	�F�f�[�^�������W�X�^��							*/
/*					CHK_BIT	�FSW��ڑ�����|�[�g���̃r�b�g�ʒu(�Y����1�j		*/
/*			�@		CHATT_TIM�F�`���^�����O�`�F�b�N����(ms)					*/
/*																			*/
/*	�����񎖍�																*/
/*  �@�E���C�Z���X��GPL�ɏ�������̂Ƃ���D										*/
/*																			*/
/*											�������ۍH�Ȑ��E��w�@�r������	*/
/****************************************************************************/
/* #000		2021/01/17 ����										�r������		*/
/****************************************************************************/


#ifndef PUSHSW_H_
#define PUSHSW_H_

#define	F_CPU	16000000UL			// System Clock Frq.

#include <avr/io.h>					// I/O define
#include <util/delay.h>				// Delay function

typedef	unsigned char	UCHR;
typedef	unsigned short	USHRT;

#define CHK_PORT	PIND
#define CHK_DDR		DDRD
#define CHK_BIT		0b00010000
#define NCHK_BIT	~CHK_BIT
#define CHATT_TIM	20
#define	SW_ON		0
#define SW_OFF		1
#define SW_IND		-1
class PushSW{
	int		swState;			// SW ��ԁiON:0/OFF:1/�s��:-1)
  public:
	PushSW();					// �R���X�g���N�^
	int		getSwState(void);	// �X�C�b�`��ԓǂݏo��
	void	waitSwOff(void);	// �X�C�b�`OFF�̏�Ԃ܂ő҂�
	void	waitSwOn(void);	// �X�C�b�`ON�̏�Ԃ܂ő҂�
};

#endif /* PUSHSW_H_ */