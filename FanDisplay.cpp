/*
 * FanDisp.cpp
 *
 * Created: 2021/02/01 19:09:40
 *  Author: MorimotoYuma
 */ 
#include "FanDisplay.h"
TM1637Disp disp;

// comp �ėp�N���X
// comp(a,b)   a �� b �ɐ��������������_��������Ƒ傫������Ԃ�.
template <class Type> Type comp(Type a, Type b){ // �����g��Ȃ�
	if(a < b) {
		return b;
		}else{
		return a;
	}
};

void FanDisp::FanDisplay(UCHR temp, UCHR fanLevel, UCHR swingLevel){
	// ���x, ���ʃ��x��, ��U�背�x��
	UCHR data[4] = {10, 10, 10, 10}; // ���l�z��f�[�^
	data[2] = (int)temp%10;
	data[3] = (int)temp/10;
	disp.numDisp(data);
}