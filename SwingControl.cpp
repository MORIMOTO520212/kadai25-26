/*
 * SwingControl.cpp
 *
 * Created: 2021/02/01 19:08:24
 *  Author: MorimotoYuma
 */
/*
	�Emain.cpp��angleRefresh��100ms���ƂɌĂяo����1������]������B
	�EswingLevel��0, 1, 2, 3�̒l������
	[��]�p�x]
	0 - stop
	1 - 43 ~ 87��
	2 - 21 ~ 109��
	3 -  0 ~ 130��
*/

#include "SwingControl.h"

#include "PushSW.h"
#include "ServoMotor.h"

PushSW sw;
ServoMotor sm;

SwingControl::SwingControl(){ // �����l
	this->swingLevel = 0;
}

void SwingControl::angleRefresh(void){
	UCHR s = 1; // 1-���Z, -1-���Z
	if(0 == sw.getSwState()){ // �X�C�b�`�Ŕ��ʂ���
		sw.waitSwOff();
		this->swingLevel ++;
		if(4 == this->swingLevel) this->swingLevel = 0;
	}
	
	if(1 == this->swingLevel){ // 43 ~ 87��
		if(43 == this->swingAngle) s = 1;
		if(87 == this->swingAngle) s = -1;
	}
	if(2 == this->swingLevel){ // 21 ~ 109��
		if(21 == this->swingAngle) s = 1;
		if(109 == this->swingAngle) s = -1;
	}
	if(3 == this->swingLevel){ //  0 ~ 130��
		if(0 == this->swingAngle) s = 1;
		if(109 == this->swingAngle) s = -1;
	}
	this->swingAngle += s;
	if(0 == this->swingLevel){
		this->swingAngle = 65; // ����
	}
	sm.setAngle(this->swingAngle);
}
UCHR SwingControl::getSwingLevel(void){ // ��U��̐ݒ�l��Ԃ��@�\���Ɏg��
	return this->swingLevel;
}