/****************************************************************************/
/*	NumberCount Class														*/
/*																			*/
/*	本ファイルは，NumberCount Class である．									*/
/*																			*/
/*	■コンフィグレーション内容													*/
/*	　特になし																*/
/*																			*/
/*	■制約事項																*/
/*  　・ライセンスはGPLに準じるものとする．										*/
/*																			*/
/*											東京国際工科専門職大学　荒金匡德	*/
/****************************************************************************/
/* #000		2021/01/17 初版										荒金匡德		*/
/****************************************************************************/

#include "NumberCount.h"
/****************************************************************/
/* コンストラクタ（引数無し）										*/
/* コンストラクタの引数がない場合は，以下の設定値となる				*/
/*		最大値：9												*/
/*		最小値：0												*/
/*		初期値：0												*/
/*		循  環：循環あり（9 -> 0, 0 -> 9)							*/
/****************************************************************/
NumberCount::NumberCount(){
	this->maxNumber = 9;
	this->minNumber = 0;
	this->number = 0;
	this->circulation = 1;
}

/****************************************************************/
/* コンストラクタ（引数有り）										*/
/* Number(int max, int min, int dflt, int circ)					*/
/* コンストラクタの引数がある場合は，引数を設定値とする				*/
/*		最大値：max												*/
/*		最小値：min												*/
/*		初期値：dflt												*/
/*		循  環：circ (1:循環あり/0:循環なし)						*/
/****************************************************************/
NumberCount::NumberCount(int max,int min,int dflt, UCHR circ){
	this->maxNumber = max;
	this->minNumber = min;
	this->number = dflt;
	this->circulation = circ;	
}

void	NumberCount::countInit(void){
	this->number = this->minNumber;					// 現在の値に最小値を入れる
}

void	NumberCount::countInit( int num){
	this->number = num;								// 現在の値に引数の値を入れる
}

/****************************************************************/
/* カウンタ値読み出し												*/
/* int NumberCount(void)										*/
/* 現在のカウンタ値を読み出す										*/
/*		戻り値：現在のカウンタ値									*/
/****************************************************************/
int		NumberCount::readCounter(){
	this->number += getDisplacement();				// エンコーダの変位を読み出し，カウンタ値に加算する
	if( this->number > this->maxNumber){			// カウンタ値が最大値を超えた場合
		if( this->circulation == CIRCULATION){		// 循環指定有りの場合
			this->number = this->minNumber;			// 　カウンタ値に最小値をセットする
		} else{										// 循環指定無しの場合
			this->number = this->maxNumber;			// 　カウンタ値に最大値をセットする
		}
	} else if( this->number < this->minNumber){		// カウンタ値が最小値未満の場合
		if( this->circulation == CIRCULATION){		// 循環指定有りの場合
			this->number = this->maxNumber;			// 　カウンタ値に最大値をセットする
		} else{										// 循環指定無しの場合
			this->number = this->minNumber;			// 　カウンタ値に最小値をセットする
		}
	}
	return this->number;							// カウンタ値を戻り値として戻す
}