/****************************************************************************/
/*	TM1637 + 4degit 7Seg LED Display Base Class 定義ファイル					*/
/*																			*/
/*	本ファイルは，TM1637+4Digit 7Seg LEDに情報を表示するためのBase Class を定義	*/
/*	したものである．															*/
/*																			*/
/*	■コンフィグレーション内容													*/
/*	　以下の内容について，対象となるハードウェアに合わせて，内容を書き換える必要	*/
/*	がある．																	*/
/*  (1)CPUクロック定義														*/
/*		シンボル名：F_CPU		：システムクロック周波数(ex.16MH時 16000000UL)		*/
/*	(2)TM1637のCLK及びDIOを接続するポート名変更								*/
/*		シンボル名： TM_PORT	：SCL及びDIOを接続するポート名	（出力レジスタ名）	*/
/*					TM_PIN	：SCL及びDIOを接続するポート名	（入力レジスタ名）	*/
/*					TM_DDR	：データ方向レジスタ名							*/
/*	(3)TM1637のCLK及びDIOを接続するビット位置									*/
/*					CLK		：CLK端子を接続するポート内のビット位置(該当を1）	*/
/*					DIO		：DIO端子を接続するポート内のビット位置(該当を1）	*/
/*																			*/
/*	■制約事項																*/
/*		・TM1637Disp関数はCLK及びDIOが同一PORTにある場合のみ利用可能である．		*/
/*		・TM1637Disp関数は非リエントラントである．								*/
/*		・ライセンスはGPLに準じるものとする．									*/
/*		・コンストラクタから表示パターンを任意に変更可能だが，0から10までは		*/
/*		　数字の0から9＋BlankとしないとnumDisp( USHRT num)メソッドは正常に		*/
/*		　動作しない．														*/
/*																			*/
/*											東京国際工科専門職大学　荒金匡德	*/
/****************************************************************************/
/* #000		2021/01/08 初版										荒金匡德		*/
/*																			*/
/* #001		2021/01/09 numDisp( USHRT num)を追加					荒金匡徳		*/
/* #002		2021/01/09 コンストラクタの表示パターン登録対応			荒金匡徳		*/
/****************************************************************************/
#ifndef TM1637DISP_H_
#define TM1637DISP_H_

// 定義及びinclude
#define	F_CPU	16000000UL			// System Clock Frq.

#include <avr/io.h>					// I/O define
#include <util/delay.h>				// Delay function

typedef	unsigned char	UCHR;
typedef	unsigned short	USHRT;

#define TM_PORT	PORTB				// TM1637のCLK及びDIOを接続しているポート(出力側)
#define TM_PIN	PINB				// TM1637のCLK及びDIOを接続しているポート(入力側)
#define	TM_DDR	DDRB				// TM1637のCLK及びDIOを接続しているポートの方向レジスタ名
#define CLK		0b00000001			// CLK端子のビット位置
#define NCLK	~CLK				// CLK端子のビット位置反転値
#define DIO		0b00010000			// DIO端子のビット位置
#define NDIO	~DIO				// DIO端子のビット位置反転値

#define	MODE	0b01000100			// TM1637のモード設定データ
#define ADDR	0b11000000			// TM1637の先頭アドレス
#define	DCNT	0b10001111			// TM1637のディスプレイ制御コマンド

#define CLK_H	TM_PORT=TM_PIN|CLK	// CLKをHighにする
#define CLK_L	TM_PORT=TM_PIN&NCLK	// CLKをLowにする
#define DIO_H	TM_PORT=TM_PIN|DIO	// DIOをHighにする
#define DIO_L	TM_PORT=TM_PIN&NDIO	// DIOをLowにする

#define DLY		100					// PORT切替後の待ち時間

// Class 定義
class TM1637Disp{
	UCHR	segPattern[128];		// セグメントデータ表示パターン
	UCHR	dispData[4];			// 表示データ
	void	Start_bit( void);		// Start 状態にするためのメソッド
	void	Stop_bit( void);		// Stop 状態にするためのメソッド
	void	send( UCHR);			// 8Bitのデータ送信のためのメソッド
  public:
	TM1637Disp(void);				// コンストラクタ（デフォルト表示）
	TM1637Disp( UCHR *ptr);			// コンストラクタ（表示パターン付）#002
	void	numDisp( UCHR *ptr);	// 表示メソッド
	void	numDisp( USHRT num);	// 表示メソッド（0-9999の整数）#002
	void	digitDisp( UCHR digit, UCHR data);	// 表示メソッド表示ディジット＋データ
};

#endif /* TM1637DISP_H_ */