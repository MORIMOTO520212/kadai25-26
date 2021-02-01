/****************************************************************************/
/*	TM1637 + 4degit 7Seg LED Display Base Class ��`�t�@�C��					*/
/*																			*/
/*	�{�t�@�C���́CTM1637+4Digit 7Seg LED�ɏ���\�����邽�߂�Base Class ���`	*/
/*	�������̂ł���D															*/
/*																			*/
/*	���R���t�B�O���[�V�������e													*/
/*	�@�ȉ��̓��e�ɂ��āC�ΏۂƂȂ�n�[�h�E�F�A�ɍ��킹�āC���e������������K�v	*/
/*	������D																	*/
/*  (1)CPU�N���b�N��`														*/
/*		�V���{�����FF_CPU		�F�V�X�e���N���b�N���g��(ex.16MH�� 16000000UL)		*/
/*	(2)TM1637��CLK�y��DIO��ڑ�����|�[�g���ύX								*/
/*		�V���{�����F TM_PORT	�FSCL�y��DIO��ڑ�����|�[�g��	�i�o�̓��W�X�^���j	*/
/*					TM_PIN	�FSCL�y��DIO��ڑ�����|�[�g��	�i���̓��W�X�^���j	*/
/*					TM_DDR	�F�f�[�^�������W�X�^��							*/
/*	(3)TM1637��CLK�y��DIO��ڑ�����r�b�g�ʒu									*/
/*					CLK		�FCLK�[�q��ڑ�����|�[�g���̃r�b�g�ʒu(�Y����1�j	*/
/*					DIO		�FDIO�[�q��ڑ�����|�[�g���̃r�b�g�ʒu(�Y����1�j	*/
/*																			*/
/*	�����񎖍�																*/
/*		�ETM1637Disp�֐���CLK�y��DIO������PORT�ɂ���ꍇ�̂ݗ��p�\�ł���D		*/
/*		�ETM1637Disp�֐��͔񃊃G���g�����g�ł���D								*/
/*		�E���C�Z���X��GPL�ɏ�������̂Ƃ���D									*/
/*		�E�R���X�g���N�^����\���p�^�[����C�ӂɕύX�\�����C0����10�܂ł�		*/
/*		�@������0����9�{Blank�Ƃ��Ȃ���numDisp( USHRT num)���\�b�h�͐����		*/
/*		�@���삵�Ȃ��D														*/
/*																			*/
/*											�������ۍH�Ȑ��E��w�@�r������	*/
/****************************************************************************/
/* #000		2021/01/08 ����										�r������		*/
/*																			*/
/* #001		2021/01/09 numDisp( USHRT num)��ǉ�					�r������		*/
/* #002		2021/01/09 �R���X�g���N�^�̕\���p�^�[���o�^�Ή�			�r������		*/
/****************************************************************************/
#ifndef TM1637DISP_H_
#define TM1637DISP_H_

// ��`�y��include
#define	F_CPU	16000000UL			// System Clock Frq.

#include <avr/io.h>					// I/O define
#include <util/delay.h>				// Delay function

typedef	unsigned char	UCHR;
typedef	unsigned short	USHRT;

#define TM_PORT	PORTB				// TM1637��CLK�y��DIO��ڑ����Ă���|�[�g(�o�͑�)
#define TM_PIN	PINB				// TM1637��CLK�y��DIO��ڑ����Ă���|�[�g(���͑�)
#define	TM_DDR	DDRB				// TM1637��CLK�y��DIO��ڑ����Ă���|�[�g�̕������W�X�^��
#define CLK		0b00000001			// CLK�[�q�̃r�b�g�ʒu
#define NCLK	~CLK				// CLK�[�q�̃r�b�g�ʒu���]�l
#define DIO		0b00010000			// DIO�[�q�̃r�b�g�ʒu
#define NDIO	~DIO				// DIO�[�q�̃r�b�g�ʒu���]�l

#define	MODE	0b01000100			// TM1637�̃��[�h�ݒ�f�[�^
#define ADDR	0b11000000			// TM1637�̐擪�A�h���X
#define	DCNT	0b10001111			// TM1637�̃f�B�X�v���C����R�}���h

#define CLK_H	TM_PORT=TM_PIN|CLK	// CLK��High�ɂ���
#define CLK_L	TM_PORT=TM_PIN&NCLK	// CLK��Low�ɂ���
#define DIO_H	TM_PORT=TM_PIN|DIO	// DIO��High�ɂ���
#define DIO_L	TM_PORT=TM_PIN&NDIO	// DIO��Low�ɂ���

#define DLY		100					// PORT�ؑ֌�̑҂�����

// Class ��`
class TM1637Disp{
	UCHR	segPattern[128];		// �Z�O�����g�f�[�^�\���p�^�[��
	UCHR	dispData[4];			// �\���f�[�^
	void	Start_bit( void);		// Start ��Ԃɂ��邽�߂̃��\�b�h
	void	Stop_bit( void);		// Stop ��Ԃɂ��邽�߂̃��\�b�h
	void	send( UCHR);			// 8Bit�̃f�[�^���M�̂��߂̃��\�b�h
  public:
	TM1637Disp(void);				// �R���X�g���N�^�i�f�t�H���g�\���j
	TM1637Disp( UCHR *ptr);			// �R���X�g���N�^�i�\���p�^�[���t�j#002
	void	numDisp( UCHR *ptr);	// �\�����\�b�h
	void	numDisp( USHRT num);	// �\�����\�b�h�i0-9999�̐����j#002
	void	digitDisp( UCHR digit, UCHR data);	// �\�����\�b�h�\���f�B�W�b�g�{�f�[�^
};

#endif /* TM1637DISP_H_ */