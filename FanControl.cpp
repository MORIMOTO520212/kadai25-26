/*
 * FanControl.cpp
 *
 * Created: 2021/02/01 19:07:09
 *  Author: MorimotoYuma
 */
/*
	扇風機の風量制御を行う.
	温度で風量調節, ロータリーエンコーダを読みだして風量調節

	22°以下：レベル1風量
	23?25℃：レベル2風量
	26?28℃：レベル3風量
	29?31℃：レベル4風量
	32℃以上：レベル5風量
*/

#include "FanControl.h"
#include "NumberCount.h"
#include "DHT11.h"
#include "DCMotor.h"


DHT11 TandH;    // 温湿度センサー
DCMotor DCM;    // モーター制御
NumberCount nc; // ロータリーエンコーダ制御

void FanControl::fanLevelRefresh(void){
	if(!nc.readCounter()){          // ロータリーエンコーダが0のとき
		if(!TandH.DHT11Read()){		// 温湿度センサから値を取得
			if(32 <= TandH.getTemperature_H()){
				this->FanLevel = 5;
			}else if(29 <= TandH.getTemperature_H()){
				this->FanLevel = 4;
			}else if(26<= TandH.getTemperature_H()){
				this->FanLevel = 3;
			}else if(23<= TandH.getTemperature_H()){
				this->FanLevel = 2;
			}else if(22 <= TandH.getTemperature_H()){
				this->FanLevel = 1;
			}
		}else{ this->FanLevel = 0; }
			
	}else{
		this->FanLevel = nc.readCounter();
	}
	DCM.setLevel(this->FanLevel);
}
UCHR FanControl::getFanLevel(void){ // 風量を返す
	return this->FanLevel;
}
UCHR FanControl::getTemperature(void){
	if(!TandH.DHT11Read()){
		return TandH.getTemperature_H();
	}
	return 0;
}