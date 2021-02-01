/*
 * kadai25-26.cpp
 *
 * Created: 2021/02/01 11:41:07
 * Author : MorimotoYuma
 */ 
#include <avr/io.h>
#include "TM1637Disp.h"

// comp �ėp�N���X
// comp(a,b)   a �� b �ɐ��������������_��������Ƒ傫������Ԃ�.
template <class Type> Type comp(Type a, Type b){
	if(a < b) {
		return b;
	}else{
		return a;
	}
};

int main(void) {
	int a = 2;
	int b = 4;
	float c = 1.7;
	float d = 1.1;
	UCHR data[4] = {10, 10, 10, 10};
	TM1637Disp disp;
	while(1) {
		data[0] = a;
		data[1] = b;
		data[3] = comp(a,b);
		disp.numDisp(data);
		_delay_ms(1000);
		
		data[0] = (UCHR)comp(c,d) | 0x80;          // 0x80�Ńs���I�h��\��.
		data[1] = (UCHR) (comp(c,d) * 10.0) % 10;
		data[3] = 10;
		disp.numDisp(data);
		_delay_ms(1000);
	}
	return 0;
}

