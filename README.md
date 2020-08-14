# CINOSerial_C
**Library for easy serial communication between Arduino and Linux.**
- Index of Linux functions
  - CINOSerial::CINOSerial(int,string)
    Set the Baud Rate and port
  - CINOSerial::sincronizar(bool)
    sync with the other device, verbal confirmation
  - CINOSerial::receber() 
    Return a character from the usb port
  - CINOSerial::enviar(char)
    Send a character through the usb port
  - CINOSerial::enviar(string,int)
    Send a string to the usb port, string, number of bytes
  - CINOSerial::setup_termios(struct termios)
    Setup the communication filter and the timeout
  - CINOSerial::~CINOSerial()
    Close the serial port
    
- Index of Arduino functions
  - CINOSerial::CINOSerial(int)
    Set the Baud Rate
  - CINOSerial::sincronizar(bool)
    sync with the other device, start serial (must be true)
  - CINOSerial::enviar(char)
    Send a character through the usb port
  - CINOSerial::ultimoRecebido()
    Return the last received character
  - CINOSerial::eventoSerial()
    Refreshes the last received character from the usb port
    
By Guilherme Fortunato Miranda and Vitor dos Santos Silva.

**Bilblioteca para a facilitação de comunicação serial entre Arduino e Linux.**
- Indice das funções de linux
  - CINOSerial::CINOSerial(int,string)
    Configura a baud rate e a porta serial
  - CINOSerial::sincronizar(bool)
    Sincroniza-se com o outro dispositivo, confirmação verbal
  - CINOSerial::receber() 
    Retorna o ultimo caracter da porta usb
  - CINOSerial::enviar(char)
    Envia um caracter pela porta usb
  - CINOSerial::enviar(string,int)
    Envia uma string pela porta usb, string, tamanho da string
  - CINOSerial::setup_termios(struct termios)
    Configura o filtro de comunição e o timeout
  - CINOSerial::~CINOSerial()
    Fecha a porta serial
    
- Indice das funções de Arduino
  - CINOSerial::CINOSerial(int)
    Define o baud rate
  - CINOSerial::sincronizar(bool)
    Sincroniza-se com o outro dispositvo, inicia o serial (precisa ser verdadeiro)
  - CINOSerial::enviar(char)
    Envia um caracater pela porta serial
  - CINOSerial::ultimoRecebido()
    Retorna o ultimo caracter recebido
  - CINOSerial::eventoSerial()
    Atualiza o ultimo caracter recebido através da porta usb
    
Feito por Guilherme Fortunato Miranda e Vitor dos Santos Silva.
