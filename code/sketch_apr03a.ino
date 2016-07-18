0;
int tracker = 0;
void setup() {
  pinMode(CO,INPUT);
  pinMode(Gas,INPUT);// put your setup code here, to run once:
  Serial.begin(9600); // put your setup code here, to run once:
  lightMeter.begin();
  dht.begin();
  MsTimer2::set(200, readQD);
  MsTimer2::start();
}

void loop() {
 
  Serial.print("gas:");
  Serial.println(gasSensor());
   delay(200);
  Serial.print("co:");
  Serial.println(coSensor());
   delay(200);
  Serial.print("light:");
  Serial.println(lightSensor());
   delay(200);
  Serial.print("temp:");
  Serial.println(tempSensor());
   delay(200);
  Serial.print("humid:");
  Serial.println(humidSensor());
   delay(200);
  Serial.print("counter:");
  Serial.println(counter);
   delay(200);
  Serial.print("tracker:");
  Serial.println(tracker);
   delay(200);
  Serial.println();
}

int gasSensor(){
  int x = analogRead(Gas);
  outputValue = map(x, 0, 1023, 0, 100); 
  return outputValue ;
  }
  
int coSensor(){
  int y = analogRead(CO);
  outputValue1 = map(y, 0, 1023, 0, 100); 
  return outputValue1 ;
  }

uint16_t lightSensor(){
  uint16_t lux = lightMeter.readLightLevel();
  return lux ;
  }

float tempSensor(){
  float t = dht.readTemperature();
  return t;
  }

 float humidSensor(){
  float h = dht.readHumidity();
  return h;
  } 
  
void readQD(){
  //Returns value from the QRE1113 
  //Lower numbers mean more refleacive
  //More than 3000 means nothing was reflected.
  pinMode( QRE1113_Pin, OUTPUT );
  digitalWrite( QRE1113_Pin, HIGH );  
  delayMicroseconds(10);
  pinMode( QRE1113_Pin, INPUT );

  long time = micros();

  //time how long the input is HIGH, but quit after 3ms as nothing happens after that
  while (digitalRead(QRE1113_Pin) == HIGH && micros() - time < 3000); 
  int diff = micros() - time;
  
 if(diff>200){
  i++;
  tracker = 1;
  }
  else{
  i=i;
  tracker = 0;
  }
 counter = i;

}
