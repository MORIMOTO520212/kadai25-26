/****************************************************************************/
/*																			*/
/*		DH11湿温度センサデータ受信 Base Class 定義ファイル						*/
/*																			*/
/*	本ファイルは，DH11湿温度センサより湿度及び温度を受信する Base Class を定義	*/
/*	したものである．															*/
/*																			*/
/*	■コンフィグレーション内容													*/
/*	　以下の内容について，対象となるハードウェアに合わせて，内容を書き換える必要	*/
/*	がある．																	*/
/*  (1)CPUクロック定義														*/
/*		シンボル名：F_CPU		：システムクロック周波数(ex.16MH時 16000000UL)		*/
/*	(2)DH11のSDAを接続するポート名変更											*/
/*		シンボル名： DH11_O	：出力側ポート名									*/
/*					DH11_I	：入力側ポート名									*/
/*					DH11_DDR：データ方向レジスタ名							*/
/*	(3)DH11のDIOを接続するビット位置											*/
/*					SDA		：DIO端子を接続するポート内のビット位置(該当を1）	*/
/*																			*/
/*	■制約事項																*/
/*		・DHT11Read関数を呼び出した後，次にDHT11Read関数を呼び出す迄に2秒以上の	*/
/*		　間隔を空けること．													*/
/*		　DHT11Read関数は非リエントラントである．								*/
/*		・ライセンスはGPLに準じるものとする．									*/
/*																			*/
/*											東京国際工科専門職大学　荒金匡德	*/
/****************************************************************************/
/* #000		2021/01/08 初版										荒金匡德		*/
/* #001     2021/01/09 温度を実数で保持できるよう修正				荒金匡徳		*/
/****************************************************************************/
#ifndef DHT11_H_
#define DHT11_H_

// 定義及びinclude
#define		F_CPU	16000000UL					// CPU Clock Freq.
#include <avr/io.h>								// CPU HW define
#include <util/delay.h>							// Delay Func.
#include <avr/interrupt.h>						// use sei() and cli()

typedef	unsigned char	UCHR;
typedef	unsigned short	USHRT;

#define DH11_O		PORTB						// DH11のSDAがある出力レジスタ@@
#define DH11_I		PINB						// DH11のSDAがある入力レジスタ@@
#define DH11_DDR	DDRB						// DH11のSDAがある方向レジスタ@@
#define SDA			0b00001000					// DH11のSDAポート位置（通常）@@
#define	NSDA		~SDA						// DH11のSDAポート位置（補数）
#define SDA_H		DH11_O = DH11_I |SDA		// SDA端子に'H'を出力
#define SDA_L		DH11_O = DH11_I & NSDA		// SDA端子に'L'を出力
#define	SDA_OUT		DH11_DDR = DH11_DDR | SDA	// SDA端子を出力ポートに設定
#define SDA_IN		DH11_DDR = DH11_DDR & NSDA	// SDA端子を入力ポートに設定
#define WAIT_SDA_H	while(( DH11_I & SDA) == 0)	// SDA端子が'H'になるまで待つ
#define WAIT_SDA_L	while(( DH11_I & SDA) != 0)	// SDA端子が'L'になるまで待つ

// Class 定義
class DHT11
{
	float	temperature;						// 温度データ（実数）#001
	UCHR	temperature_H;						// 温度データ（小数点以上）
	UCHR	temperature_L;						// 温度データ（小数点未満）
	UCHR	humidity_H;							// 湿度データ（小数点以上）
	UCHR	humidity_L;							// 湿度データ（小数点未満）
  public:
	DHT11(void);								// コンストラクタ
	int		DHT11Read( void);					// 温湿度データ受信メソッド
	float	getTemperature(void);				// 温度データ（実数）読出し #001
	UCHR	getTemperature_H(void);				// 温度データ（小数点以上）読出し
	UCHR	getTemperature_L(void);				// 温度データ（小数点未満）読出し
	UCHR	getHumidity_H(void);				// 湿度データ（小数点以上）読出し
	UCHR	getHumidity_L(void);				// 湿度データ（小数点未満）読出し
};

#endif /* DHT11_H_ */