
// #define esp8266 Serial2 // por qu la conexion se hace en 16 y 17 tx,rx
// #define CH_PD 4 
// #define speed8266 115200 // This is the speed that worked with my ESP8266
 
// #define DEBUG true

// class wifi 
// { 
//   private:
//      boolean datosLeidos= false;
//      String response="";
//  public:
//  void initSerialEsp()
//  {
//    esp8266.begin(speed8266); 
//         Serial.begin(9600);
//  }
//  void reset_module ()// Pin CH_PD needs a reset before start communication
//  {
//      pinMode(CH_PD, OUTPUT);
//        digitalWrite(CH_PD, LOW);
//      delay(300);
//      digitalWrite(CH_PD, HIGH);
//     }
//     String sendData(String command, const int timeout, boolean debug)
//  {
//        String response = "";
//        esp8266.print(command); //envia comando al modulo 
//        long int time = millis();
//        while ( (time + timeout) > millis())
//        {
//          while (esp8266.available())
//             {
//              // The esp has data so display its output to the serial window
//              char c = esp8266.read(); // read the next character.
//              response += c;
//           }
//        }
//        if (debug)
//        {
//          Serial.print(response);
//        }
      
//      return response;
//  }
//  void serial_check()   //set the number of bytes (characters) available for reading from the serial port
//  {                                           //datos que ya han llegado y se almacenan en el buffer (64 bits)
         
//                  String r ="";
//         int i=0;
//          while (esp8266.available()) 
//          {
//            delay(2);
//            char c = esp8266.read();
//                     r += c;
//            responseComplete = true;
            
//          }       

//          response = r;
//    }
//    boolean WiFiCheck()                                        //Check whether WiFi is connected 
//    {
//              boolean res =false;
//       int t2=millis();
       
//        while(t2+t1>millis())
//        {
//            while(esp8266.available()>0)
//            {
//              if(esp8266.find("WIFI GOT IP"))  // SE LE HA DADO UNA IP 
//              {
//                 res= true;
//              }

//           }
//        }

//        return res ;
//    }
//  void InitConfigWebServer()
//  {
//          sendData("AT+RST\r\n", 2000, DEBUG); // reset
//          sendData("AT+CWJAP=\"eduardo\",\"15170903\"\r\n", 2000, DEBUG); //Connect network
//          delay(3000);
//          sendData("AT+CWMODE=1\r\n", 1000, DEBUG);
//          sendData("AT+CIPSTA=\"192.168.1.253\"\r\n");
//          sendData("AT+CIFSR\r\n", 1000, DEBUG); // Show IP Adress
//          sendData("AT+CIPMUX=1\r\n", 1000, DEBUG); // Multiple conexions
//          sendData("AT+CIPSERVER=1,80\r\n", 1000, DEBUG); // start comm port 80
//  }
//  void detectarClient()
//  {
//      client_request= false;
//      while(client_request==false) //Waitingfor anyclient/browser to initiate the request
//      {
//        serial_check();
//        brow_req();                                         //sub routine to check browser request
//        brow_resp();                                        //sub routine for response from Arduino
//      }
//  }
  
//     void InitWifiModule()
//     {
//      initSerialEsp();
//      reset_module();
//      InitConfigWebServer();
//     }


// };

class NumberBinary
{
    private:
      int BCD[16][4] = {
      
      {0,0,0,0},//0
      {0,0,0,1},//1
      {0,0,1,0},//2
      {0,0,1,1},//3
      {0,1,0,0},//4
      {0,1,0,1},//5
      {0,1,1,0},//6
      {0,1,1,1},//7
      {1,0,0,0},//8
      {1,0,0,1}, //9
     // {0,1,0,1},
      //{1,1,0,1},
      //{0,0,1,1},
      //{1,0,1,1},
      //{0,1,1,1},
      //{1,1,1,1}    
      
      };

    public:

      int getFirstDigit(int max)
      {
        // print a random number from 1 to max
              int   randNumber = random(1, max+1);
                 return randNumber;


      }
      int getSecondDigit()
      {
        return  random(1, 9);
      }

      int getBinary(int number,int index)
      {
           return BCD[number][index];
      }

};

// class temperatura 




class Display_temp
  {  private:
         
         int max =3;  //first medicion
         int pinComienzoDisplay1; 
         int pinComienzoDisplay2; 
         NumberBinary number;

     public:
        void setPines(int p,int p2)
        {
          pinComienzoDisplay1=p;
          pinComienzoDisplay2=p2;
        }


          void initPines( )
             {

               int n = pinComienzoDisplay1;
              for(int a = 0; a <= 4; a++)
              {
                   
                      pinMode(n, OUTPUT);
                       n++;
                    //cada parcela inicialiiza su parcela 
                }  
             }

           
          void generarSalida()
           { 

        

            //los pines tienen que estar consecutivos y son 4 para el codigo bcd
            

               int numero = number.getFirstDigit(max); 
               int pin = pinComienzoDisplay1;

               Serial.print("llego_");

               for(int c = 0; c < 4; c++)
               {      
                     Serial.print(number.getBinary(numero,c));
                     Serial.print("-");
                      if (number.getBinary(numero,c)==1)
                      {
                         digitalWrite(pin,HIGH);
                      }
                      else
                        
                      digitalWrite(pin,LOW);
                      
                     
                      pin++;
               }
                 
                 
                 //otro display

               pin = pinComienzoDisplay2;
               numero = number.getSecondDigit();

               Serial.print("llego2_");

               for(int c = 0; c < 4; c++)
               {
                    if (number.getBinary(numero,c)==1)
                      {
                         digitalWrite(pin,HIGH);
                      }
                      else
                         digitalWrite(pin,LOW);
                    pin++;
               }


          }

          void limpiarDisplay()
           { 
             
               int  pin = pinComienzoDisplay1;
               for(int c = 0; c <4; c++)
               {
                      digitalWrite(pin, LOW);
                      pin++;
               }

              


          }

  } ;//http://www.instructables.com/id/Arduino-and-7-segment-LED-display-driver/


Display_temp temperaturaParcela_1;

Display_temp temperaturaParcela_2;

Display_temp temperaturaParcela_3;

Display_temp temperaturaParcela_4;

class Alarma
{  
   private:
    int pin = 38 ;
    int duration = 1000;
  
    int tonos[5]; //frecuencias

   public:
    generateTonos()
    {
      for (int i = 0; i < 5; i++)
      {

        tonos[i]= random(220, 490);
      }
   
    }

    tocar()
    {
      for (int iTono = 0; iTono < 5; iTono++)
      {
         tone(pin, tonos[iTono],duration);
           delay(1000);
      }
      noTone(pin);
    }

};//https://www.luisllamas.es/reproducir-sonidos-arduino-buzzer-pasivo-altavoz/


Alarma sonido_parcela_1;

Alarma sonido_parcela_2;

Alarma sonido_parcela_3;

Alarma sonido_parcela_4;


class Luz
{
  private :
  int pin ;
  public:
  void setPin(int p)
  {
    pin = p ;
  }

  void initPin()
  {
     pinMode(pin, OUTPUT);

  }

  void encender()
  {
     digitalWrite(pin , HIGH);   // poner el Pin en HIGH
     delay(1000);
  }
  void apagar()
  {
     digitalWrite(pin , LOW);   // poner el Pin en HIGH
     delay(1000);
  }
};


Luz luces_parcela_1;

Luz luces_parcela_2;

Luz luces_parcela_3;

Luz luces_parcela_4;


class ParcelaRiego
{
  private:
    int tiempoLLegada;
    int tiempoRiego;
  public:

  int getTiempoLLegada()
  {
   return tiempoLLegada;
  }

  int getTiempoRiego()
  {
   return tiempoRiego; 
  }

    void setTiempoLLegada(int t)
  {
    tiempoLLegada = t;
  }

  void setTiempoRiego(int t)
  {
    tiempoRiego = t ;
  }

};


//son los tiempos de llegada a la parcela y el tiempo de riego
ParcelaRiego riego_parcela_1;

ParcelaRiego riego_parcela_2;

ParcelaRiego riego_parcela_3;

ParcelaRiego riego_parcela_4;

class Riego
{
   private:
    int pinBomba=10;
    //int pinMotorMov;
    int pinPuenteHIzq =7; // va a la parcela 
    int pinPuenteHDec =5; //regresa a la poscicion inicial 
    ParcelaRiego parcela;
  
   public:
    void setPinBomba(int p)
    {
         pinBomba = p;
    } 

   
    void setPinesPuenteH(int izq,int dec)
    {
         pinPuenteHIzq = izq;
         pinPuenteHDec= dec;
    } 

    void initRiego()
    {
         pinMode(pinBomba, OUTPUT); 
         pinMode(pinPuenteHDec, OUTPUT);
          pinMode(pinPuenteHIzq, OUTPUT);
                    

    }

    void setParcela(ParcelaRiego p)
    {
         parcela = p;
    } 

    void regresarPoscicion()
    { 

      
          int segundos=0;
          while(segundos<parcela.getTiempoLLegada())
          {
                  digitalWrite(pinPuenteHDec, HIGH);
                  
                  segundos++;


                  Serial.print("regresando a posicion 0");
                  Serial.print(parcela.getTiempoLLegada());
         
         }

                digitalWrite(pinPuenteHDec, LOW);

    }

    void encenderBomba()
    {


          int segundos=0;
          while(segundos<parcela.getTiempoRiego())
          {


        Serial.print("regando");
                  digitalWrite(pinBomba, HIGH);
                  delay(15); 
                  segundos++;
         
          }

          digitalWrite(pinBomba, LOW);

    }

    void irPoscicion()
    { 
            int segundos=0;

          while(segundos<parcela.getTiempoLLegada())
          {
               
               digitalWrite(pinPuenteHIzq, HIGH);
               delay(150); 
               segundos++;
          }
              
           digitalWrite(pinPuenteHIzq, LOW);      
        
    }

    void regar()
    {
      //primero ir a poscicion 0 

      //luego ir a parcela 
       irPoscicion();
        //encender bomba
       // encenderBomba();
        //luego regresar a la posicion 0 ;

        delay(200);
      parcela.setTiempoLLegada(parcela.getTiempoLLegada()*8);
      regresarPoscicion();

    }




};

Riego riego; //clase que mueve el motor reductar y enciendela bomba dependiendo de la parcela


//funcion que limpia de todas las parcelas las lecturas de temperatura 

void limpiarTemperaturas()
{
  temperaturaParcela_1.limpiarDisplay();

  temperaturaParcela_2.limpiarDisplay();

  temperaturaParcela_3.limpiarDisplay();

  temperaturaParcela_4.limpiarDisplay();
}

void setup() 
{

     Serial.begin(9600);
     
   //temperaturas
 

  /*
  int pines_display_1[] = {22, 23, 24, 25};
  int pines_display_2[] = {26, 27, 28, 29};
  int pines_display_3[] = {30, 31, 32, 33};
  int pines_display_4[] = {34, 35, 36, 37};
*/
  temperaturaParcela_1.setPines(22,26 );
  temperaturaParcela_2.setPines(22,26 );
  temperaturaParcela_3.setPines(30,37 );
  temperaturaParcela_4.setPines(30,37 );

/*

  temperaturaParcela_1.initPines(1);
  temperaturaParcela_2.initPines(2);
  temperaturaParcela_3.initPines(1);
  temperaturaParcela_4.initPines(2);
  */

    //DECLARAION DE PINES 
    //integrado 7448 para displays
   pinMode(22, OUTPUT);
      pinMode(23, OUTPUT);
       pinMode(24, OUTPUT);
        pinMode(25, OUTPUT);
         pinMode(26, OUTPUT);
          pinMode(27, OUTPUT);
           pinMode(28, OUTPUT);
            pinMode(29, OUTPUT);
             pinMode(30, OUTPUT);
              pinMode(31, OUTPUT);
               pinMode(32, OUTPUT); 
                pinMode(33, OUTPUT);
                 pinMode(34, OUTPUT);
                  pinMode(35, OUTPUT);
                   pinMode(36, OUTPUT);
                    pinMode(37, OUTPUT);

  //el pin del sonido es 38

 //empieza declaracion de pines de luces

     luces_parcela_1.setPin(39);

     luces_parcela_2.setPin(40);

     luces_parcela_3.setPin(41);

     luces_parcela_4.setPin(42);

     //declaro los pines
     
     luces_parcela_1.initPin();

     luces_parcela_2.initPin();

     luces_parcela_3.initPin();

     luces_parcela_4.initPin();
  
    
    //tiempo 

    riego_parcela_1.setTiempoLLegada(2);
    riego_parcela_2.setTiempoLLegada(25);
    riego_parcela_3.setTiempoLLegada(55);
    riego_parcela_4.setTiempoLLegada(80);   


    riego_parcela_1.setTiempoRiego(9);

    riego_parcela_2.setTiempoRiego(10);

    riego_parcela_3.setTiempoRiego(6);

    riego_parcela_4.setTiempoRiego(5);
    

     
      riego.initRiego();      


                
                  

}

void loop() 
{

  String option= "";


  //si la coomunicacion por serial (consola ) esta disponible
  if(Serial.available()>0)
  {
    //leemos la opcion enviada

    option=Serial.readString();
    
    //lectura de temperaturas
    if(option=="temp_1") 
    {
      limpiarTemperaturas();
       temperaturaParcela_1.generarSalida(); 
    }
    else
    {
         
         if(option=="temp_2") 
         {
         limpiarTemperaturas();
           temperaturaParcela_2.generarSalida(); 
         }else
         {
      
         if(option=="temp_3") 
             {
              limpiarTemperaturas();
                temperaturaParcela_3.generarSalida(); 
                 }
                 else
                 {

                if(option=="temp_4") 
                  {
                      limpiarTemperaturas();
                          temperaturaParcela_4.generarSalida(); 
                }
                 }
         }

    }


   //alarmas 

    if(option=="alarma_1") 
    {
       
          sonido_parcela_1.generateTonos();
          sonido_parcela_1.tocar();
    }
    else
    {
      if (option=="alarma_2")
      {
              
         
              sonido_parcela_2.generateTonos();
              sonido_parcela_2.tocar();
      }
      else
      {
        if (option=="alarma_3")
        {
          
             sonido_parcela_3.generateTonos();
               sonido_parcela_3.tocar();
        }
        else
        {
          if (option=="alarma_4")
          {
            
                  sonido_parcela_4.generateTonos();
                  sonido_parcela_4.tocar();
          }
        }
      } 
    }

//luces

    if(option=="luces_1") 
    { 
         luces_parcela_1.encender();
    }
    else
    {
      if (option=="luces_2")
      {
              
         luces_parcela_2.encender();
      }
      else
      {
        if (option=="luces_3")
        {
          
             luces_parcela_3.encender();
        }
        else
        {
          if (option=="luces_4")
          {
            
                  luces_parcela_4.encender();;
          }
        }
      } 
    }

    if (option=="luces_apagar_1")
          {
            
                  luces_parcela_1.apagar();;
          }

//riego


//luces

    if(option=="riego_1") 
    { 
          riego.setParcela(riego_parcela_1);
         riego.regar();
    }
    else
    {
      if (option=="riego_2")
      {
                      riego.setParcela(riego_parcela_2);  
         riego.regar();
      }
      else
      {
        if (option=="riego_3")
        {
                    riego.setParcela(riego_parcela_3);
             riego.regar();
        }
        else
        {
          if (option=="riego_4")
          {
                                  riego.setParcela(riego_parcela_4); 
                  riego.regar();
          }
        }
      } 
    }
  

  }

      

   
}