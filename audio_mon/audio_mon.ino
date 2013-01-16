#define LEDR1 12
#define LEDG1 8
#define LEDY1 10

int serialIndex = 0;
int peakVal = 0;
char serialBuffer[32];
char serialByte;

void setup() { 
  pinMode(48,OUTPUT);
  digitalWrite(48,HIGH);
  Serial.begin(19200);
}

void loop() {
  while (Serial.available()) {
    serialByte = Serial.read();
    if (serialByte != '\n') {
      serialBuffer[serialIndex] = serialByte;
      serialIndex++;
    }
    if (serialByte == '\n' or serialIndex == 31) {
      parseSerial();
      serialIndex = 0;
      memset(&serialBuffer, 0, 32);
    }
  }
}

void parseSerial() {
  char *s = serialBuffer;
  peakVal = atoi(s);
  analyzePeak();
}

void analyzePeak() {
  clearLED();
  if(peakVal>=30000)
    analogWrite(LEDR1,254);
  if(peakVal>=20000)
    analogWrite(LEDY1,254);
  if(peakVal>=5000)
    analogWrite(LEDG1,254);
}

void clearLED() {
  analogWrite(LEDR1, 0);
  analogWrite(LEDY1, 0);
  analogWrite(LEDG1, 0);
}
