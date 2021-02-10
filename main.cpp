/*
 * kadai25-26.cpp
 *
 * Created: 2021/02/01 11:41:07
 * Author : MorimotoYuma.
 */ 
/*
	[1.CPU電源投入時の設定]
	風量レベル1
	首振り停止
	
	[2.表示]
	※温度表示：温度を整数で表示する．（０?４０°の範囲）
	１０の位が０ならば１０の位はブランク表示とする．
	１の位には小数点も表示する．
	※風量表示：温度連動の場合は「０．」
	レベル１?５の場合はそれぞれ「１．」?「５．」
	を表示する．
	※首振りモード：
	停止の場合は「０．」
	６０°，１２０°，１８０°の場合はそれぞれ
	「１．」「２．」「３．」を表示する．

	[3.風量調節]
	起動時は風量レベル1．ロータリーエンコーダのつまみを右に回す毎に１ずつ
	レベルを上げる．レベル５の状態で右に回してもレベル5の状態を保持すること．
	逆にロータリーエンコーダのつまみを左に回す毎にレベルを下げる．
	レベル0（温度連動）の状態から左に回してもレベル0の状態を保持すること．
	※レベル0時の温度と風量の関係
	22°以下：レベル1風量23?25℃：レベル2風量
	26?28℃：レベル3風量29?31℃：レベル4風量
	32℃以上：レベル5風量
	
	[4.首振り]
	起動時は首振り無し．
	Push SWを1度押下すると，正面を中心に60°の範囲でサーボモータによる
	首振りを行う．
	再度Push SWを押下すると，正面を中心に120°の範囲での首振り，
	再度Push SW を押下すると，正面を中心に180°の範囲での首振り，
	再度Push SW を押下すると，首振り停止となる．
	以下，Push SWを押下する度に，上記を繰り返す．
*/
#include <avr/io.h>
#include <avr/interrupt.h>

#include "SwingControl.h"
#include "TM1637Disp.h"


int main(void) {
	UCHR dispData[4] = {10, 10, 10, 10}; // 初期値
	TM1637Disp disp;
	SwingControl SC;
	
	while(1){
		SC.angleRefresh();
		dispData[3] = SC.getSwingLevel();
		disp.numDisp(dispData);
		_delay_ms(1000);
	}
	return 0;
}