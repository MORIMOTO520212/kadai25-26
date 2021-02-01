/****************************************************************************/
/*	TM1637 + 4degit 7Seg LED Display Base Class								*/
/*																			*/
/*	本ファイルは，TM1637+4Digit 7Seg LEDに情報を表示するためのBase Class を定義	*/
/*	したものである．															*/
/*																			*/
/*	■制約事項																*/
/*		・TM1637Disp関数はCLK及びDIOが同一PORTにある場合のみ利用可能である．		*/
/*		・TM1637Disp関数は非リエントラントである．								*/
/*		・ライセンスはGPLに準じるものとする．									*/
/*																			*/
/*											東京国際工科専門職大学　荒金匡德	*/
/****************************************************************************/
/* #000		2021/01/08 初版										荒金匡德		*/
/* #002		2021/01/09 コンストラクタの表示パターン登録対応			荒金匡徳		*/
/*																			*/
/****************************************************************************/
#include "TM1637Disp.h"

// コンストラクタ（デフォルト表示）
TM1637Disp::TM1637Disp(void){
	TM_DDR |= CLK|DIO;				// CLKポートDIOポートを出力に設定
	// 7セグLED表示パターンデフォルト値設定（ 0-9, Blank ）
	this->segPattern[0]  = 0x3F;			// 0
	this->segPattern[1]  = 0x06;			// 1
	this->segPattern[2]  = 0x5B;			// 2
	this->segPattern[3]  = 0x4F;			// 3
	this->segPattern[4]  = 0x66;			// 4
	this->segPattern[5]  = 0x6D;			// 5
	this->segPattern[6]  = 0x7D;			// 6
	this->segPattern[7]  = 0x07;			// 7
	this->segPattern[8]  = 0x7F;			// 8
	this->segPattern[9]  = 0x6F;			// 9
	this->segPattern[10] = 0x00;			// Blank

}

// コンストラクタ（表示パターン付）引数の指すアドレスから0xFFまでを表示パターンとして読込
TM1637Disp::TM1637Disp( UCHR *ptr){			// #002
	TM_DDR |= CLK|DIO;				// CLKポートDIOポートを出力に設定

	// 7セグLED表示パターン設定
	UCHR *dest = &(this->segPattern[0]);	// 表示パターン格納先先頭アドレス
	for( int i=0; i<128; i++){				// 最大128Byte読み込む
		if( *ptr == 0xFF){					// データ終了なら読込を完了させる
			break;
		}
		*dest++ = *ptr++;					// データを1Byte コピーする
	}
}
///////////////////////////////////////////////////////////
//
//    TM1637 4桁7セグメントLED表示用関数
//    呼出形式：void		num_disp( UCHR *ptr);
//
//    引数：UCHR *ptr  :  表示データが入ったデータの先頭アドレス
//                        (表示データは4バイト分の表示コード)
//						  表示データ1バイトの値は0x00?0x7Fとする
//    戻り値：なし
//
//　　機能：引数で受け取った4バイトのメモリに入っているデータを
//         4桁7セグメントLEDに表示する．
//         但し，上記表示文字に.を付加する場合は，コードに0x80を
//         加算する．
//
///////////////////////////////////////////////////////////
void	TM1637Disp::numDisp( UCHR *ptr){

	TM_DDR |= CLK|DIO;								// CLKポートDIOポートを出力に設定
	Start_bit();									// Start bit 送信
	send(MODE);										// モード送信
	Stop_bit();										// Stop bit 送信

	for( int i = 0; i < 4; i++){					// 4桁分のLoop
		Start_bit();								// START Bit 送信
		send(ADDR + i);								// 表示エリアのアドレス送信
		if( *ptr >= 0x80){							// ドットを付加する場合
			send(this->segPattern[(int)(*ptr-0x80)]|0x80);// ドットのセグメントを付加した情報を送信
			} else {								// ドットを付加しない場合
			send(this->segPattern[(int)*ptr]);			// ドットなしの表示情報を送信
		}
		Stop_bit();									// STOP Bit 送信
		ptr++;										// 表示桁を進める
	}

	Start_bit();									// STOP Bit 送信
	send(DCNT);										// Display Control Command 送信
	Stop_bit();										// STOP Bit 送信
}

///////////////////////////////////////////////////////////
//
//    TM1637 4桁7セグメントLED表示用関数(1桁のみ表示）
//    呼出形式：void		digitdisp( UCHR digit, UCHR data);
//
//    引数：UCHR digit  :  表示する桁（1番左を0，1番右を3とする）
//         UCHR data   :  表示するデータ番号
//    戻り値：なし
//
//　　機能：引数で受け取ったdegit桁にdataで指定された表示を行う
//         但し，上記表示文字に.を付加する場合は，コードに0x80を
//         加算する．digitで指定された以外の桁は，そのまま表示を
//         継続する．
//
///////////////////////////////////////////////////////////
void	TM1637Disp::digitDisp( UCHR digit, UCHR data){

	TM_DDR |= CLK|DIO;								// CLKポートDIOポートを出力に設定
	Start_bit();									// Start bit 送信
	send(MODE);										// モード送信
	Stop_bit();										// Stop bit 送信

	Start_bit();									// START Bit 送信
	send(ADDR + digit);								// 表示エリアのアドレス送信
	if( data >= 0x80){								// ドットを付加する場合
		send(this->segPattern[(int)(data-0x80)]|0x80);// ドットのセグメントを付加した情報を送信
	} else {										// ドットを付加しない場合
		send(this->segPattern[(int)data]);			// ドットなしの表示情報を送信
	}
	Stop_bit();										// STOP Bit 送信

	Start_bit();									// STOP Bit 送信
	send(DCNT);										// Display Control Command 送信
	Stop_bit();										// STOP Bit 送信
}

///////////////////////////////////////////////////////////
//
//    TM1637 4桁7セグメントLED表示用関数 #002
//    呼出形式：void		num_disp( USHRT num);
//
//    引数：USHRT num  :  表示データ（0-9999)
//    戻り値：なし
//
//　　機能：引数で受け取った0-9999の値を4桁7セグメントLEDに表示する．
//
///////////////////////////////////////////////////////////
void	TM1637Disp::numDisp( USHRT num){
	UCHR	data[4];								// 表示用データバッファ
	int		digit = 1000;
	for( int i=0; i<3; i++){						// 4-2桁目までの数字を求める
		data[i] = num / digit;						// 1桁分の数字を求める
		num %= digit;								// num に余りの数を入れておく
		digit /= 10;								// 次に求める桁を用意
	}
	data[3] = num;									// 1桁目の数字を保存する
	if(data[0] == 0){								// 4桁目が0なら
		data[0] = 10;								//　Blank にする
		if(data[1] == 0){							// 更に3桁目も0なら
			data[1] = 10;							// 　Blank にする
			if(data[2] == 0){						// 更に2桁目も0なら
				data[2] = 10;						// 　Blank にする
			}
		}
	}
	numDisp(&data[0]);								// 4桁表示を行う			
}

///////////////////////////////////////////////////////////
//		START Bit 送信関数
///////////////////////////////////////////////////////////
void	TM1637Disp::Start_bit( void){
	CLK_H;											// CLKをHIGH
	_delay_us(DLY);
	DIO_H;											// DIOをHIGH
	_delay_us(DLY);
	DIO_L;											// DIOをLOW
	_delay_us(DLY);
}

///////////////////////////////////////////////////////////
//		STOP Bit 送信関数
///////////////////////////////////////////////////////////
void	TM1637Disp::Stop_bit( void){
	DIO_L;											// DIOをLOW
	_delay_us(DLY);
	CLK_H;											// CLKをHIGH
	_delay_us(DLY);
	DIO_H;											// DIOをHIGH
	_delay_us(DLY);
}

///////////////////////////////////////////////////////////
//		Byte data 送信関数
///////////////////////////////////////////////////////////
void	TM1637Disp::send( UCHR	data){
	for( int i=0; i<8; i++){						// 8Bitデータ送出なので8回Loopする．
		CLK_L;										// CLKにLOWを出力
		_delay_us(DLY);
		if( (data & 0x01) == 0){					// 出力データが0の時
			DIO_L;									//　 DIOにLOWを出力
		} else{										// 出力データが1の時
			DIO_H;									// 　DIOにHIGHを出力
		}
		_delay_us(DLY);
		CLK_H;										// CLKにHIGHを出力
		_delay_us(DLY);
		data >>= 1;									// 出力データを1ビット右シフト
	}
	// ACK待ち
	CLK_L;
	_delay_us(DLY);
	// CLKをHIGHにしてACK解除
	CLK_H;											// CLKにHIGHを出力
	_delay_us(DLY);
	DIO_L;											// DIOにLOWを出力
	_delay_us(DLY);
	CLK_L;											// CLKにLOWを出力
	_delay_us(DLY);
}