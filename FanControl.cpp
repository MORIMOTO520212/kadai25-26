/*
 * FanControl.cpp
 *
 * Created: 2021/02/01 19:07:09
 *  Author: MorimotoYuma
 */
/*
	��@�̕��ʐ�����s��.
	���x�ŕ��ʒ���, ���[�^���[�G���R�[�_��ǂ݂����ĕ��ʒ���

	22���ȉ��F���x��1����
	23?25���F���x��2����
	26?28���F���x��3����
	29?31���F���x��4����
	32���ȏ�F���x��5����
*/

#include "FanControl.h"
#include "DHT11.h"
#include "DCMotor.h"


DHT11 TandH;
DCMotor DCM;
UCHR dispData[4];
void FanControl::fanLevelRefresh(void){

	if(!TandH.DHT11Read()){		// �����x�Z���T����l���擾
		if(32 <= TandH.getTemperature_H()){
			this->FanLevel = 5;
		}else if(29 <= TandH.getTemperature_H()){
			this->FanLevel = 4;
		}else if(26<= TandH.getTemperature_H()){
			this->FanLevel = 3;
		}else if(23<= TandH.getTemperature_H()){
			this->FanLevel = 2;
		}else if(22 <= TandH.getTemperature_H()){
			this->FanLevel = 1;
		}
	}else{
		this->FanLevel = 0;
	}
	DCM.setLevel(this->FanLevel);
}
UCHR FanControl::getFanLevel(void){ // ���ʂ�Ԃ�
	return this->FanLevel;
}