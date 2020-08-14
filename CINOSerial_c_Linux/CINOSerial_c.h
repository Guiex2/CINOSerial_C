#ifndef CINOSerial_h
#define CINOSerial_h

#include <string>
#include <string.h>
#include <iostream>
#include <cmath>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>

using namespace std;

class CINOSerial{
	public:
		CINOSerial(int baudRate, string porta);
		~CINOSerial();
		char receber();
		void enviar(char car);
		void enviar(string car, int nbytes);
		void sincronizar(bool verbose = false);
	private:
		void setup_termios(struct termios &tty);
		
		int _baudRate;
		std::string _porta;
		int serial_port;
		bool connection=false;
		int n;
		char ultimoCharRecebido = 'v';
		
};

#endif
