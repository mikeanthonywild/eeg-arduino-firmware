void setup() {
  Serial.begin(9600);
  while(!Serial.available()){}
}

int i = 0;

void loop() {
  Serial.print(i++);
  Serial.println("Hello World\n"); 
  while(Serial.read() == 's'){while(Serial.read() != 's'){}}
}
