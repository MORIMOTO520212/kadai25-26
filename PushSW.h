/****************************************************************************/
/*	Push Switch Base Class													*/
/*																			*/
/*	本ファイルは，Push Switch の Base Class を定義したものである．				*/
/*																			*/
/*	■コンフィグレーション内容													*/
/*	　以下の内容について，対象となるハードウェアに合わせて，内容を書き換える必要	*/
/*	がある．																	*/
/*  (1)CPUクロック定義														*/
/*		シンボル名：F_CPU		：システムクロック周波数(ex.16MH時 16000000UL)		*/
/*	(2)SWを接続するポート名変更												*/
/*		シンボル名： CHK_PORT：SWを接続するポート名	（入力レジスタ名）		*/
/*					CHK_DDR	：データ方向レジスタ名							*/
/*					CHK_BIT	：SWを接続するポート内のビット位置(該当を1）		*/
/*			　		CHATT_TIM：チャタリングチェック時間(ms)					*/
/*																			*/
/*	■制約事項																*/
/*  　・ライセンスはGPLに準じるものとする．										*/
/*																			*/
/*											東京国際工科専門職大学　荒金匡德	*/
/****************************************************************************/
/* #000		2021/01/17 初版										荒金匡德		*/
/****************************************************************************/


#ifndef PUSHSW_H_
#define PUSHSW_H_

#define	F_CPU	16000000UL			// System Clock Frq.

#include <avr/io.h>					// I/O define
#include <util/delay.h>				// Delay function

typedef	unsigned char	UCHR;
typedef	unsigned short	USHRT;

#define CHK_PORT	PIND
#define CHK_DDR		DDRD
#define CHK_BIT		0b00010000
#define NCHK_BIT	~CHK_BIT
#define CHATT_TIM	20
#define	SW_ON		0
#define SW_OFF		1
#define SW_IND		-1
class PushSW{
	int		swState;			// SW 状態（ON:0/OFF:1/不定:-1)
  public:
	PushSW();					// コンストラクタ
	int		getSwState(void);	// スイッチ状態読み出し
	void	waitSwOff(void);	// スイッチOFFの状態まで待つ
	void	waitSwOn(void);	// スイッチONの状態まで待つ
};

#endif /* PUSHSW_H_ */