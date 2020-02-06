/*
 * mod_nostdio.c
 *
 *  Created on: Mar 7, 2014
 *      Author: fabianrcm
 */
#include "mod_nostdio.h"

//const uint16_t FactorMult[5]={1,10,100,1000,10000};
const uint32_t FactorMult[11]={1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000,1000000000};


uint8_t putString(char *var,uint8_t start_pos,char message []){
	uint8_t i = 0;
	while(message[i] != 0){
		var[start_pos+i]=message[i];
		i++;
	}
	var[start_pos+i]=0;
	return start_pos+i;
}

uint8_t putFloat(char *var,uint8_t start_pos,float var_float,uint8_t dig_bdot,uint8_t dig_adot){
	char dig;
	uint16_t var16_1=0;
	var16_1=(uint16_t)var_float;
	start_pos=putInt16(var,start_pos,var16_1,dig_bdot);
	var[start_pos]=46;//dot
	start_pos++;
	var_float=var_float-(float)((uint16_t)(var_float));
	while(dig_adot){
		var_float=var_float*10;
		dig=(char)(var_float);
		var_float=var_float-(float)((uint16_t)(var_float));
		var[start_pos]=intToChar(dig);start_pos++;
		dig_adot--;
	}
	var[start_pos]=0;
	return start_pos;
}
uint8_t putInt8(char *var,uint8_t start_pos,uint8_t var_int,uint8_t dig_bdot){
	char dig=0,k=0;
	uint16_t div=0, var16_1=0, var16_2=0;
	while(dig_bdot){
		div=FactorMult[dig_bdot-1];
		var16_1=var_int-var16_2;
		dig=(char)(var16_1/div);
		var16_2=dig*div+var16_2;
		if(dig==0 && k==0 && dig_bdot>1)
			var[start_pos]=32;// 0 = void space
		else{
			k=1;
			var[start_pos]=intToChar(dig);
		}
		dig_bdot--;start_pos++;;
	}
	var[start_pos]=0;
	return start_pos;
}

uint8_t putInt16(char *var,uint8_t start_pos,uint16_t var_int,uint8_t dig_bdot){
	char dig=0,k=0;
	uint16_t div=0, var16_1=0, var16_2=0;
	while(dig_bdot){
		div=FactorMult[dig_bdot-1];
		var16_1=var_int-var16_2;
		dig=(char)(var16_1/div);
		var16_2=dig*div+var16_2;
		if(dig==0 && k==0 && dig_bdot>1)
			var[start_pos]=48;// 0 = void space
		else{
			k=1;
			var[start_pos]=intToChar(dig);
		}
		dig_bdot--;start_pos++;
	}
	var[start_pos]=0;
	return start_pos;
}


uint8_t printFloat(char *var,float var_float,uint8_t FractDigit){
	//char dig;
	uint16_t var_int=0;
	uint8_t cVar=0;


	if(var_float < 0.0){
		var_float *= -1;
		var[0] = '-';var++;
	}
	var_int=(uint16_t)var_float;
	cVar=printInt16(var,var_int);//cVar++;


	if(FractDigit == 0){
		cVar++;
		var[cVar] = 0;
		return cVar;
	}

	var[cVar] = 46;cVar++;
	while (FractDigit){
		var_float = 10.0*(var_float - (float)((uint8_t)var_float));
		var[cVar] = (char)(var_float)+48;
		cVar++;
		FractDigit--;
	}
	var[cVar] = 0;//cVar++;
	return cVar;
}

uint8_t printInt16(char *var,uint16_t var_int){
	uint8_t cDivs=4, cVar=0;
	char value=0;
	while(cDivs){
		value = (char)(var_int/((uint16_t)FactorMult[cDivs]));
		if(value|cVar){
			var[cVar]=value+48;
			cVar++;
			var_int=var_int-(uint16_t)value*((uint16_t)FactorMult[cDivs]);
		}
		cDivs--;
	}
	value = (char)(var_int);
	var[cVar]=value+48;
	cVar++;
	var[cVar]=0;
	return cVar;
}

uint8_t printInt32(char *var,uint32_t var_int){
	uint8_t cDivs=10, cVar=0;
	char value=0;
	while(cDivs){
		value = (char)(var_int/(FactorMult[cDivs]));
		if(value|cVar){
			var[cVar]=value+48;
			cVar++;
			var_int=var_int-(uint32_t)value*FactorMult[cDivs];
		}
		cDivs--;
	}
	value = (char)(var_int);
	var[cVar]=value+48;
	cVar++;
	var[cVar]=0;
	return cVar;
}





uint8_t putcBuffer(char *pBuffer,uint8_t pBufferPos,char varIn){
	pBuffer[pBufferPos] = varIn;pBufferPos++;
	pBuffer[pBufferPos] = 0;
	return pBufferPos;
}
uint8_t putStringBuffer(char *pBuffer,uint8_t pBufferPos,char var[]){
	pBufferPos = putString(pBuffer,pBufferPos,var);
	return pBufferPos;
}
uint8_t putInt16Buffer(char *pBuffer,uint8_t pBufferPos, uint16_t var){
	pBufferPos += printInt16(&pBuffer[pBufferPos],var);
	return pBufferPos;
}
uint8_t putInt32Buffer(char *pBuffer,uint8_t pBufferPos, uint32_t var){
	pBufferPos += printInt32(&pBuffer[pBufferPos],var);
	return pBufferPos;
}
uint8_t putFloatBuffer(char *pBuffer,uint8_t pBufferPos,float var,uint8_t var1){
	pBufferPos += printFloat(&pBuffer[pBufferPos],var,var1);
	return pBufferPos;
}

