/****************************************************************************/
/*	Rotary Encoder read Base Class 定義ファイル								*/
/*																			*/
/*	本ファイルは，Rotary Encoder reader の Base Class を定義したものである．	*/
/*	したものである．															*/
/*																			*/
/*	■コンフィグレーション内容													*/
/*	　特に無し．																*/
/*																			*/
/*	■制約事項																*/
/*	　・本 class ではRotary Encoder のENC_AをPD2(IRQ0)に，ENC_BをPD3に接続する	*/
/*  　・本 class ではIRQ0を利用するため，同時に複数のインスタンス生成は出来ない．	*/
/*  　・ライセンスはGPLに準じるものとする．										*/
/*																			*/
/*											東京国際工科専門職大学　荒金匡德	*/
/****************************************************************************/
/* #000		2021/01/15 初版										荒金匡德		*/
/****************************************************************************/

#ifndef ROTARYENCODER_H_
#define ROTARYENCODER_H_

// 定義及びinclude
#define	F_CPU	16000000UL			// System Clock Frq.

#include <avr/io.h>					// I/O define
#include <util/delay.h>				// Delay function
#include <avr/interrupt.h>

typedef	unsigned char	UCHR;
typedef	unsigned short	USHRT;

class RotaryEncoder{
	int	displacement;				// エンコーダ出力変位(右:1/不変:0/左:-1）
  public:
	RotaryEncoder();				// コンストラクタ
	int	getDisplacement();			// 変位読出&クリア
};


#endif /* ROTARYENCODER_H_ */