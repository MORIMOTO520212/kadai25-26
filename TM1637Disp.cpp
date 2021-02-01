/****************************************************************************/
/*	TM1637 + 4degit 7Seg LED Display Base Class								*/
/*																			*/
/*	�{�t�@�C���́CTM1637+4Digit 7Seg LED�ɏ���\�����邽�߂�Base Class ���`	*/
/*	�������̂ł���D															*/
/*																			*/
/*	�����񎖍�																*/
/*		�ETM1637Disp�֐���CLK�y��DIO������PORT�ɂ���ꍇ�̂ݗ��p�\�ł���D		*/
/*		�ETM1637Disp�֐��͔񃊃G���g�����g�ł���D								*/
/*		�E���C�Z���X��GPL�ɏ�������̂Ƃ���D									*/
/*																			*/
/*											�������ۍH�Ȑ��E��w�@�r������	*/
/****************************************************************************/
/* #000		2021/01/08 ����										�r������		*/
/* #002		2021/01/09 �R���X�g���N�^�̕\���p�^�[���o�^�Ή�			�r������		*/
/*																			*/
/****************************************************************************/
#include "TM1637Disp.h"

// �R���X�g���N�^�i�f�t�H���g�\���j
TM1637Disp::TM1637Disp(void){
	TM_DDR |= CLK|DIO;				// CLK�|�[�gDIO�|�[�g���o�͂ɐݒ�
	// 7�Z�OLED�\���p�^�[���f�t�H���g�l�ݒ�i 0-9, Blank �j
	this->segPattern[0]  = 0x3F;			// 0
	this->segPattern[1]  = 0x06;			// 1
	this->segPattern[2]  = 0x5B;			// 2
	this->segPattern[3]  = 0x4F;			// 3
	this->segPattern[4]  = 0x66;			// 4
	this->segPattern[5]  = 0x6D;			// 5
	this->segPattern[6]  = 0x7D;			// 6
	this->segPattern[7]  = 0x07;			// 7
	this->segPattern[8]  = 0x7F;			// 8
	this->segPattern[9]  = 0x6F;			// 9
	this->segPattern[10] = 0x00;			// Blank

}

// �R���X�g���N�^�i�\���p�^�[���t�j�����̎w���A�h���X����0xFF�܂ł�\���p�^�[���Ƃ��ēǍ�
TM1637Disp::TM1637Disp( UCHR *ptr){			// #002
	TM_DDR |= CLK|DIO;				// CLK�|�[�gDIO�|�[�g���o�͂ɐݒ�

	// 7�Z�OLED�\���p�^�[���ݒ�
	UCHR *dest = &(this->segPattern[0]);	// �\���p�^�[���i�[��擪�A�h���X
	for( int i=0; i<128; i++){				// �ő�128Byte�ǂݍ���
		if( *ptr == 0xFF){					// �f�[�^�I���Ȃ�Ǎ�������������
			break;
		}
		*dest++ = *ptr++;					// �f�[�^��1Byte �R�s�[����
	}
}
///////////////////////////////////////////////////////////
//
//    TM1637 4��7�Z�O�����gLED�\���p�֐�
//    �ďo�`���Fvoid		num_disp( UCHR *ptr);
//
//    �����FUCHR *ptr  :  �\���f�[�^���������f�[�^�̐擪�A�h���X
//                        (�\���f�[�^��4�o�C�g���̕\���R�[�h)
//						  �\���f�[�^1�o�C�g�̒l��0x00?0x7F�Ƃ���
//    �߂�l�F�Ȃ�
//
//�@�@�@�\�F�����Ŏ󂯎����4�o�C�g�̃������ɓ����Ă���f�[�^��
//         4��7�Z�O�����gLED�ɕ\������D
//         �A���C��L�\��������.��t������ꍇ�́C�R�[�h��0x80��
//         ���Z����D
//
///////////////////////////////////////////////////////////
void	TM1637Disp::numDisp( UCHR *ptr){

	TM_DDR |= CLK|DIO;								// CLK�|�[�gDIO�|�[�g���o�͂ɐݒ�
	Start_bit();									// Start bit ���M
	send(MODE);										// ���[�h���M
	Stop_bit();										// Stop bit ���M

	for( int i = 0; i < 4; i++){					// 4������Loop
		Start_bit();								// START Bit ���M
		send(ADDR + i);								// �\���G���A�̃A�h���X���M
		if( *ptr >= 0x80){							// �h�b�g��t������ꍇ
			send(this->segPattern[(int)(*ptr-0x80)]|0x80);// �h�b�g�̃Z�O�����g��t���������𑗐M
			} else {								// �h�b�g��t�����Ȃ��ꍇ
			send(this->segPattern[(int)*ptr]);			// �h�b�g�Ȃ��̕\�����𑗐M
		}
		Stop_bit();									// STOP Bit ���M
		ptr++;										// �\������i�߂�
	}

	Start_bit();									// STOP Bit ���M
	send(DCNT);										// Display Control Command ���M
	Stop_bit();										// STOP Bit ���M
}

///////////////////////////////////////////////////////////
//
//    TM1637 4��7�Z�O�����gLED�\���p�֐�(1���̂ݕ\���j
//    �ďo�`���Fvoid		digitdisp( UCHR digit, UCHR data);
//
//    �����FUCHR digit  :  �\�����錅�i1�ԍ���0�C1�ԉE��3�Ƃ���j
//         UCHR data   :  �\������f�[�^�ԍ�
//    �߂�l�F�Ȃ�
//
//�@�@�@�\�F�����Ŏ󂯎����degit����data�Ŏw�肳�ꂽ�\�����s��
//         �A���C��L�\��������.��t������ꍇ�́C�R�[�h��0x80��
//         ���Z����Ddigit�Ŏw�肳�ꂽ�ȊO�̌��́C���̂܂ܕ\����
//         �p������D
//
///////////////////////////////////////////////////////////
void	TM1637Disp::digitDisp( UCHR digit, UCHR data){

	TM_DDR |= CLK|DIO;								// CLK�|�[�gDIO�|�[�g���o�͂ɐݒ�
	Start_bit();									// Start bit ���M
	send(MODE);										// ���[�h���M
	Stop_bit();										// Stop bit ���M

	Start_bit();									// START Bit ���M
	send(ADDR + digit);								// �\���G���A�̃A�h���X���M
	if( data >= 0x80){								// �h�b�g��t������ꍇ
		send(this->segPattern[(int)(data-0x80)]|0x80);// �h�b�g�̃Z�O�����g��t���������𑗐M
	} else {										// �h�b�g��t�����Ȃ��ꍇ
		send(this->segPattern[(int)data]);			// �h�b�g�Ȃ��̕\�����𑗐M
	}
	Stop_bit();										// STOP Bit ���M

	Start_bit();									// STOP Bit ���M
	send(DCNT);										// Display Control Command ���M
	Stop_bit();										// STOP Bit ���M
}

///////////////////////////////////////////////////////////
//
//    TM1637 4��7�Z�O�����gLED�\���p�֐� #002
//    �ďo�`���Fvoid		num_disp( USHRT num);
//
//    �����FUSHRT num  :  �\���f�[�^�i0-9999)
//    �߂�l�F�Ȃ�
//
//�@�@�@�\�F�����Ŏ󂯎����0-9999�̒l��4��7�Z�O�����gLED�ɕ\������D
//
///////////////////////////////////////////////////////////
void	TM1637Disp::numDisp( USHRT num){
	UCHR	data[4];								// �\���p�f�[�^�o�b�t�@
	int		digit = 1000;
	for( int i=0; i<3; i++){						// 4-2���ڂ܂ł̐��������߂�
		data[i] = num / digit;						// 1�����̐��������߂�
		num %= digit;								// num �ɗ]��̐������Ă���
		digit /= 10;								// ���ɋ��߂錅��p��
	}
	data[3] = num;									// 1���ڂ̐�����ۑ�����
	if(data[0] == 0){								// 4���ڂ�0�Ȃ�
		data[0] = 10;								//�@Blank �ɂ���
		if(data[1] == 0){							// �X��3���ڂ�0�Ȃ�
			data[1] = 10;							// �@Blank �ɂ���
			if(data[2] == 0){						// �X��2���ڂ�0�Ȃ�
				data[2] = 10;						// �@Blank �ɂ���
			}
		}
	}
	numDisp(&data[0]);								// 4���\�����s��			
}

///////////////////////////////////////////////////////////
//		START Bit ���M�֐�
///////////////////////////////////////////////////////////
void	TM1637Disp::Start_bit( void){
	CLK_H;											// CLK��HIGH
	_delay_us(DLY);
	DIO_H;											// DIO��HIGH
	_delay_us(DLY);
	DIO_L;											// DIO��LOW
	_delay_us(DLY);
}

///////////////////////////////////////////////////////////
//		STOP Bit ���M�֐�
///////////////////////////////////////////////////////////
void	TM1637Disp::Stop_bit( void){
	DIO_L;											// DIO��LOW
	_delay_us(DLY);
	CLK_H;											// CLK��HIGH
	_delay_us(DLY);
	DIO_H;											// DIO��HIGH
	_delay_us(DLY);
}

///////////////////////////////////////////////////////////
//		Byte data ���M�֐�
///////////////////////////////////////////////////////////
void	TM1637Disp::send( UCHR	data){
	for( int i=0; i<8; i++){						// 8Bit�f�[�^���o�Ȃ̂�8��Loop����D
		CLK_L;										// CLK��LOW���o��
		_delay_us(DLY);
		if( (data & 0x01) == 0){					// �o�̓f�[�^��0�̎�
			DIO_L;									//�@ DIO��LOW���o��
		} else{										// �o�̓f�[�^��1�̎�
			DIO_H;									// �@DIO��HIGH���o��
		}
		_delay_us(DLY);
		CLK_H;										// CLK��HIGH���o��
		_delay_us(DLY);
		data >>= 1;									// �o�̓f�[�^��1�r�b�g�E�V�t�g
	}
	// ACK�҂�
	CLK_L;
	_delay_us(DLY);
	// CLK��HIGH�ɂ���ACK����
	CLK_H;											// CLK��HIGH���o��
	_delay_us(DLY);
	DIO_L;											// DIO��LOW���o��
	_delay_us(DLY);
	CLK_L;											// CLK��LOW���o��
	_delay_us(DLY);
}