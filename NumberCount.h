/****************************************************************************/
/*	NumberCount Class														*/
/*																			*/
/*	本ファイルは，NumberCount Class を定義したものである．						*/
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

#ifndef NUMBERCOUNT_H_
#define NUMBERCOUNT_H_

#include "RotaryEncoder.h"

#define	CIRCULATION		1
#define NON_CIRCULATION	0

class NumberCount : public RotaryEncoder{
	int		number;							// 現在の値
	int		maxNumber;						// 最大値
	int		minNumber;						// 最小値
	UCHR	circulation;					// 1:数値を循環させる
  public:
	NumberCount();							// コンストラクタ（標準）
	NumberCount(int max,int min,int dflt, UCHR circ);// コンストラクタ（設定値付き）
	void	countInit(void);				// 現在の値を初期化する（0で初期化）
	void	countInit(int num);				// 現在の値を初期化する（指定値で初期化）
	int		readCounter();					// 現在の値を読み出す
};

#endif /* NUMBERCOUNT_H_ */