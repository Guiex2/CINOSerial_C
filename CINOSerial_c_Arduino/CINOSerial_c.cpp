#include "Arduino.h"
#include "CINOSerial_c.h"


//Define a velocidade de comunicacao da porta serial
CINOSerial::CINOSerial(int baudRate){
	_baudRate = baudRate;
}

//Sincroniza-se com o outro aparelho pela porta serial
void CINOSerial::sincronizar(bool startSerial){
	if(startSerial){
		Serial.begin(_baudRate);
	}
	char charLido;
	bool comecar = false;
	while(!comecar){
		while(Serial.available()>0){
			charLido=Serial.read();
			if(charLido=='i'){
				comecar=true; 
			}else {
			}
		}
	}
	Serial.print('k');
}

//Envia um caracter
void CINOSerial::enviar(char n){
	Serial.print(n);
}

//Retorna o ultimo caracter recebido
char CINOSerial::ultimoRecebido(){
	return ultimoChar;
}

unsigned int i_counter=0;

//Le os caracteres que estao sendo enviados pela porta serial
void CINOSerial::eventoSerial(){
	while(Serial.available()>0){
		char ler = Serial.read();
		if(isAlphaNumeric(ler)){
			ultimoChar = ler;
			if(ler=='i'){
				i_counter++;
				if(i_counter==5){
					Serial.print('k');
					i_counter=0;
				}
			}else{
				i_counter=0;
			}
		}else{
			if(ler==';'){
				ultimoChar = ';';
			}
			if(ler=='.'){
				ultimoChar = '.';
			}
			if(ler=='-'){
				ultimoChar = '-';
			}
		}
	}
}
