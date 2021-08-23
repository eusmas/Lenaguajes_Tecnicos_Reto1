#include <arduino.h>

#include <SoftwareSerial.h>

int dato, enviar;
int destino, tiempo, inicio, cancelar;

void setup() {
  pinMode(22, INPUT);
  pinMode(23, INPUT);
  pinMode(35, OUTPUT);
  pinMode(36, OUTPUT);
  pinMode(37, OUTPUT);
  
  Serial2.begin(9600);
  Serial3.begin(9600);
}

void loop() {
  if (inicio==1){                       //Envio de dato leido para operacion normal
      Serial2.print(enviar);
      Serial3.print(enviar);
      delay(500);
      inicio=0;
  }
    if (cancelar==1){                   //Envio de dato leido para cancelar operacion
      Serial2.print(enviar);
      Serial3.print(enviar);
      delay(2000);
  }

//_____Lectura de caracter que indica que esta haciendo el motor______

  if(dato=='d'){          //giro a la derecha
    digitalWrite(35,HIGH);
    digitalWrite(36,LOW);
    digitalWrite(37,LOW);
    }
  if(dato=='i'){          //giro a la izquierda
    digitalWrite(35,LOW);
    digitalWrite(36,HIGH);
    digitalWrite(37,LOW);
    }
  if(dato=='f'){          //Banda detenida
    digitalWrite(35,LOW);
    digitalWrite(36,LOW);
    digitalWrite(37,HIGH);
    }
}

void serialEvent3 ()  {         //evento serial para lectura de datos de la banda
  dato= Serial3.read();
  Serial2.print(dato);
}

void serialEvent2 ()  {         //evento serial para lectura de datos introducidos por usuario
  enviar= Serial2.parseInt();

  if(enviar==0){
    cancelar=1;  
    }else{
    cancelar=0;
    destino=enviar/100;
    tiempo=(enviar-(destino*100))/10;
    inicio=enviar-(destino*100)-(tiempo*10);
    }
  delay(400);
}

