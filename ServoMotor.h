/****************************************************************************/
/*	Servo Motor Base Class 定義ファイル										*/
/*																			*/
/*	本ファイルは，Servo Motorに回転角度を設定するためのBase Class を定義			*/
/*	したものである．															*/
/*																			*/
/*	■コンフィグレーション内容													*/
/*	　以下の内容について，対象となるハードウェアに合わせて，内容を書き換える必要	*/
/*	がある．																	*/
/*																			*/
/*	■制約事項																*/
/*		・PWM信号をTimer0（16Bit Timer)で作りだしているため，必ずPB2に接続して	*/
/*		  使用すること．														*/
/*		・ServoMotor関数はリエントラントであるが，デバイスアクセスを伴うため競合	*/
/*		  に注意すること．													*/
/*		・ライセンスはGPLに準じるものとする．									*/
/*																			*/
/*											東京国際工科専門職大学　荒金匡德	*/
/****************************************************************************/
/* #000		2021/01/26 初版										荒金匡德		*/
/****************************************************************************/
#ifndef SERVOMOTOR_H_
#define SERVOMOTOR_H_

#define F_CPU	16000000UL
#include	<avr/io.h>
#include	<util/delay.h>
typedef		unsigned char	UCHR;
typedef		unsigned short	USHRT;

class	ServoMotor{
  public:
  ServoMotor();							// コンストラクタ
	void	setAngle( UCHR angle);		// 角度設定メソッド
};

#endif /* SERVOMOTOR_H_ */