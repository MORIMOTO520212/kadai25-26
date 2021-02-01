/****************************************************************************/
/*	Push Switch Base Class													*/
/*																			*/
/*	本ファイルは，Push Switch の Base Class を定義したものである．				*/
/*																			*/
/*	■制約事項																*/
/*  　・ライセンスはGPLに準じるものとする．										*/
/*																			*/
/*											東京国際工科専門職大学　荒金匡德	*/
/****************************************************************************/
/* #000		2021/01/17 初版										荒金匡德		*/
/****************************************************************************/
#include "PushSW.h"

PushSW::PushSW(void){
	CHK_PORT |= CHK_BIT;			// Pull UP
	CHK_DDR &= NCHK_BIT;			// SW Port を入力に設定
	this->swState = SW_OFF;			// SW の初期状態をSW_OFFに設定
}

/****************************************************************/
/* スイッチ状態取得												*/
/* int getSwState(void)											*/
/* チャタリングチェックを行いながらスイッチの状態を取得する			*/
/*		戻り値：SW_ON(0)		:　スイッチON状態						*/
/*			   SW_OFF(1)	:　スイッチOFF状態					*/
/*			   SW_IND(-1)	:　スイッチ状態不明					*/
/****************************************************************/
int		PushSW::getSwState(void){
	int	res = SW_IND;								// スイッチ状態（初期値は不明にしておく）
	UCHR	portCondition = (CHK_PORT & CHK_BIT);	// PORT状態保存
	_delay_ms(CHATT_TIM);							// チャタリングチェックディレイ
	if( portCondition == (CHK_PORT & CHK_BIT)){		// 再度PORT状態が同じなら,PORT状態確定
		if( portCondition == CHK_BIT){				// PORTがHなら，
			res = SW_OFF;							// SW = OFF
		} else{										// PORTがLなら，
			res = SW_ON;							// SW = ON
		}
	} else {										// ディレイ中にポート状態が変わった場合
		portCondition ^= CHK_BIT;					// 前回のPORT状態の反転値を現在の状態にする
		_delay_ms(CHATT_TIM);						// 再度チャタリングチェックディレイ
		if( portCondition == (CHK_PORT & CHK_BIT)){	// 再度PORT状態が同じなら，PORT状態確定
			if( portCondition == CHK_BIT){			// PORTがHなら，
				res = SW_OFF;						// SW = OFF
			} else{									// PORTがLなら，
				res = SW_ON;						// SW = ON
			}
		}
	}
	return res;										// PORT状態を返す．
}

/****************************************************************/
/* スイッチオフ待ち												*/
/* void waitSwOff(void)											*/
/* スイッチがOFF状態になるまで待つ（OFF状態になったら本関数を抜ける	*/
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
/* スイッチオン待ち												*/
/* void waitSwOn(void)											*/
/* スイッチがON状態になるまで待つ（ON状態になったら本関数を抜ける		*/
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