#include <string>
#include <string.h>
#include <iostream>
#include <cmath>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include "CINOSerial_c.h"

using namespace std;

//Setup das configuracoes de taxa de transmissao e porta de comunicacao
CINOSerial::CINOSerial(int baudRate, string porta){
	_baudRate = baudRate;
	_porta = porta;
	
	serial_port = open(porta.c_str(), O_RDWR); //Portas normalmente usadas /dev/ttyUSB0 ou dev/ttyACM0
	if (serial_port < 0) {
		cout<<"Error "<< errno<<" from open: "<< strerror(errno)<<endl;
	}
	
	struct termios tty;
	memset(&tty, 0, sizeof tty);

	// le as configuracoes existentes, e lida com erro se necessario
	if(tcgetattr(serial_port, &tty) != 0) {
		cout<<"Error "<<errno<<" from tcgetattr: "<<strerror(errno)<<endl;
	}
	
	setup_termios(tty);
	
	if(baudRate==115200){
		cfsetispeed(&tty, B115200);
		cfsetospeed(&tty, B115200);
	}else{
		cfsetispeed(&tty, B9600);
		cfsetospeed(&tty, B9600);
	}
	
	
	// Salva as configuracoes do tty, e lida com erro se necessario
	if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
		cout<<"Error "<<errno<<" from tcsetattr: "<<strerror(errno)<<endl;
	}
	
}

//Recebe um caracter da porta serial
char CINOSerial::receber(){
	char read_buf[1];
	memset(&read_buf, '\0', sizeof(read_buf));
	n = read(serial_port, &read_buf, sizeof(read_buf));
	if (n < 0) {
		cout << "Error reading: " << strerror(errno) << endl;
	}else{
		char lida = read_buf[0];
		if(isalnum(lida)){
			ultimoCharRecebido = lida;
		}else{
			if(lida==';'){
				ultimoCharRecebido = ';';
			}
			if(lida=='.'){
				ultimoCharRecebido = '.';
			}
			if(lida=='-'){
				ultimoCharRecebido ='-';
			}
		}
		return (ultimoCharRecebido);
	}
}

//Envia um caracter pela porta serial
void CINOSerial::enviar(char car){
	string s(1, car);
	write(serial_port, s.c_str(), 1);
}

//Envia mais de um caracter pela porta serial
void CINOSerial::enviar(string car, int nbytes){
	//string s(nbytes, car);
	write(serial_port, car.c_str(), nbytes);
}

//Sincronizacao com o outro aparelho da porta serial(E preciso que ele retorne "k")
void CINOSerial::sincronizar(bool verbose){
	while(!connection){
		enviar('i');
		char read_buf[1];
		memset(&read_buf, '\0', sizeof(read_buf));
		n = read(serial_port, &read_buf, sizeof(read_buf));
		if (n < 0) {
			printf("Error reading: %s", strerror(errno));
		}
		if(!connection){
			char lida = read_buf[0];
			if(lida=='k'){
				connection=true;
				if(verbose){
					cout<<"Conexao supimpa!"<<endl;
				}
			}
		}
	}
}

//Paramentros referente a comunicacao como disabilitar o backspace ou definir o tempo de retorno
void CINOSerial::setup_termios(struct termios &tty){
	tty.c_cflag &= ~PARENB;
	tty.c_cflag &= ~CSTOPB; 
	tty.c_cflag |= CS8; 
	tty.c_cflag &= ~CRTSCTS; 
	tty.c_cflag |= CREAD | CLOCAL;
	tty.c_lflag &= ~ICANON;
	tty.c_lflag &= ~ECHO;
	tty.c_lflag &= ~ECHOE;
	tty.c_lflag &= ~ECHONL;
	tty.c_lflag &= ~ISIG;
	tty.c_iflag &= ~(IXON | IXOFF | IXANY);
	tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL);
	tty.c_oflag &= ~OPOST;
	tty.c_oflag &= ~ONLCR;
	tty.c_cc[VTIME] = 10;
	tty.c_cc[VMIN] = 0;
}

//Fecha a porta de comunicação
CINOSerial::~CINOSerial(){
	close(serial_port);
}
