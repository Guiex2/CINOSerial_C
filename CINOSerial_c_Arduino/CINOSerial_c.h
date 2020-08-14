#ifndef CINOSerial_c_h
#define CINOSerial_c_h

#include "Arduino.h"

class CINOSerial{
	public:
		CINOSerial(int baudRate);
		void sincronizar(bool startSerial=false);
		void enviar(char n);
		char ultimoRecebido();
		void eventoSerial();
		
	private:
		int _baudRate;
		char ultimoChar = 'v';
};

#endif
