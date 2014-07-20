/*




NASR ALLAH Mounir <nasrallah.mounir@gmail.com, http://mounirnasrallah.com>

*/
#include <PduEncoder.h>

#define APN "Free";
#define BAUD_RATE 19200



void initalisation_gprs_shield(SoftwareSerial* _gprs_shield){
  
  // Active les resultat et le mode verbose
  _gprs_shield.print("AT+CMEE=2"); 

  // Fréquence à 19200
  _gprs_shield.print("AT+IPR=");        
  _gprs_shield.print(BAUD_RATE);
  
  //Selection du réseau
  _gprs_shield.print("AT+WS46=12");     
  _gprs_shield.print("AT+COPS?");
  _gprs_shield.print("+COPS: 0,0,'");
  _gprs_shield.print(APN);
  _gprs_shield.print("'");
 
}


void send_message_text_mode(SoftwareSerial* _gprs_shield, char* _number, char* _msg){
  
  // Configuration Mode texte
   _gprs_shield.print("AT+CMGF=1\r");
   _gprs_shield.println("AT+CSMP=17,167,0,240");
   
   // Numéro de téléphone
   _gprs_shield.print("AT + CMGS = \"");
   _gprs_shield.print(_number);
   _gprs_shield.print("\"<CR>";
   _gprs_shield.print(_msg);        
   _gprs_shield.print((char)26);    //Code ASCII de CTRL+Z
  
}

void send_message_pdu_mode(SoftwareSerial* _gprs_shield, char* _number, char* _msg){
  String PDU_STRING;
  PduEncoder PDU;
  
  PDU.setSender(_number);
  PDU.setText(_msg);
 
  PDU_STRING = PDU.encode();
  int pdulenght = ((resultingPDU.length()/2) - 1);
  
  _gprs_shield.print("AT+CMGF=0\r");
  
  
   
}

void send_message_pdu_mode_HDU(SoftwareSerial* _gprs_shield, char* _number, char* _msg){
   _gprs_shield.print("AT+CMGF=0\r");
}

