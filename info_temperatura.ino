#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <DHT_U.h>

int sensor = 2;
int temp, humedad;
LiquidCrystal_I2C lcd(0x27,16,2);

DHT dht (sensor, DHT11);

float rAux = 10000.0;
float vcc = 5.0;
float beta = 3977.0;
float temp0 = 298.0;
float r0 = 10000.0;

// Variables usadas en el cálculo
float vm = 0.0;
float rntc = 0.0;
float temperaturaK = 0.0;

void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.init();
  lcd.backlight();          // Activar luz de fondo 
  lcd.clear();              // Borrar 

}

void loop() {

  // Lectura de humedad y temperatura, almacenados en 'humedad' y 'temp'
  humedad = dht.readHumidity();
  temp = dht.readTemperature();

  // Bloque de cálculo
  vm=(vcc / 1024)*( analogRead(0) );                //Calcular tensión en la entrada
  rntc = rAux / ((vcc/vm)-1);                       //Calcular la resistencia de la NTC
  temperaturaK = beta/(log(rntc/r0)+(beta/temp0));  //Calcular la temperatura en Kelvin
  //Restar 273 para pasar a grados celsus
  Serial.println(temperaturaK - 273);

  // Impresion por serial, para corroborar info
  Serial.print("Temperatura: ");
  Serial.println(temp);
  Serial.print("Humedad: ");
  Serial.println(humedad);  
  delay(1000);

  // Impresion por pantalla
  lcd.setCursor(0,0);       // coordenadas LCD (x,y)
  lcd.print("TEMPERATURA: ");   // Temperatura obtenida por sensor DHT11
  lcd.setCursor(12,0);       // coordenadas LCD (x,y)
  lcd.print(temp); 
  lcd.setCursor(14,0);
  lcd.print("'C");

  lcd.setCursor(0,1);       // coordenadas LCD (x,y)
  lcd.print("HUMEDAD: ");   // Humedad obtenida por sensor DHT11 
  lcd.setCursor(9,1);       // coordenadas LCD (x,y)
  lcd.print(humedad);
  lcd.setCursor(11,1);
  lcd.print("%");

  delay(2500);
  lcd.clear();

  // Impresion y refresco de caracteres
  lcd.setCursor(0,0);       // coordenadas LCD (x,y)
  lcd.print("TEMPERATURA: ");   // Temperatura obtenida por sensor DHT11
  lcd.setCursor(12,0);       // coordenadas LCD (x,y)
  lcd.print(temp);
  lcd.setCursor(14,0);
  lcd.print("'C");
  
  lcd.setCursor(0,1);       // coordenadas LCD (x,y)
  lcd.print("TEMP: ");   // Temperatura obtenida por cálculo (sensor ntc) 
  lcd.setCursor(6,1);       // coordenadas LCD (x,y)
  lcd.print(temperaturaK - 280);
  lcd.setCursor(11,1);
  lcd.print(" 'C");

  delay(2500);
  lcd.clear();

}
