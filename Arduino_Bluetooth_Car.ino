//Mario Şarkısı

int delays[] = { 150,300,300,100,300,550,575, };
int Tone1[] = { 660,660,660,510,660,770,380, };
int Tone2[] = { 100,100,100,100,100,100,100, };

//L298N Bağlantısı   
const int motorA1 = 3;  // L298N'in IN1 Girişi 
const int motorA2 = 4;  // L298N'in IN2 Girişi 
const int motorB1 = 5; // L298N'in IN3 Girişi 
const int motorB2 = 6;  // L298N'in IN4 Girişi 


int i = 0; //Döngüler için atanan rastgele bir değişken
int j = 0; //Döngüler için atanan rastgele bir değişken
int state; //Bluetooth cihazından gelecek sinyalin değişkeni
int vSpeed = 255;     // Standart Hız, 0-255 arası bir değer alabilir
int r1 = 11;
int r2 = 12;
int BuzzerPin = 13;
;
void setup() {
	// Pinlerimizi belirleyelim
	pinMode(r1, OUTPUT);
	pinMode(r2, OUTPUT);
	pinMode(BuzzerPin, OUTPUT);
	pinMode(motorA1, OUTPUT);
	pinMode(motorA2, OUTPUT);
	pinMode(motorB1, OUTPUT);
	pinMode(motorB2, OUTPUT);
	// 9600 baud hızında bir seri port açalım
	Serial.begin(9600);

}

void loop()
{
	for (int a = 0; i < 7; i++)
	{
		tone(BuzzerPin, Tone1[i], Tone2[i]);
		delay(delays[i]);
	}


	// if(digitalRead(BTState)==LOW) { state='S'; }  //Stops car when bluetooth is disconnected.

	  
	if (Serial.available() > 0)  // Read serial data and put it in state variable
	{
		state = Serial.read();
	}

	// 4 speed levels that can be adjusted from the application. (Values should be between 0-255)
	if (state == '0') {
		vSpeed = 0;
	}
	else if (state == '1') {
		vSpeed = 100;
	}
	else if (state == '4') {
		vSpeed = 180;
	}
	else if (state == '7') {
		vSpeed = 200;
	}
	else if (state == 'q') {
		vSpeed = 255;
	}

	/***********************Forward****************************/
	if (state == 'F') {
		analogWrite(motorA1, vSpeed); analogWrite(motorA2, 0);
		analogWrite(motorB1, 0);      analogWrite(motorB2, 0);
	}
	/**********************Forward Left************************/
	else if (state == 'G') {
		analogWrite(motorA1, vSpeed); analogWrite(motorA2, 0);
		analogWrite(motorB1, 200);    analogWrite(motorB2, 0);
	}
	/**********************Forward Right************************/
	else if (state == 'I') {
		analogWrite(motorA1, vSpeed); analogWrite(motorA2, 0);
		analogWrite(motorB1, 0);      analogWrite(motorB2, 200);
	}
	/***********************Reverse****************************/
	else if (state == 'B') {
		analogWrite(motorA1, 0);   analogWrite(motorA2, vSpeed);
		analogWrite(motorB1, 0);   analogWrite(motorB2, 0);
	}
	/**********************Reverse Left************************/
	else if (state == 'H') {
		analogWrite(motorA1, 0);   analogWrite(motorA2, vSpeed);
		analogWrite(motorB1, 200); analogWrite(motorB2, 0);
	}
	/**********************Reverse Right************************/
	else if (state == 'J') {
		analogWrite(motorA1, 0);   analogWrite(motorA2, vSpeed);
		analogWrite(motorB1, 0);   analogWrite(motorB2, 200);
	}
	/***************************Left*****************************/
	else if (state == 'L') {
		analogWrite(motorA1, 0);   analogWrite(motorA2, 0);
		analogWrite(motorB1, 200); analogWrite(motorB2, 0);
	}
	/***************************Right*****************************/
	else if (state == 'R') {
		analogWrite(motorA1, 0);   analogWrite(motorA2, 0);
		analogWrite(motorB1, 0);   analogWrite(motorB2, 200);
	}

	/************************Stop*****************************/
	else if (state == 'S') {
		analogWrite(motorA1, 0);  analogWrite(motorA2, 0);
		analogWrite(motorB1, 0);  analogWrite(motorB2, 0);
	}
	/************************Buzzer On*****************************/
	else if (state == 'V') {
		analogWrite(BuzzerPin, 255);
	}
	/************************Buzzer Off*****************************/
	else if (state == 'v') {
		analogWrite(BuzzerPin, 0);
	}
	/************************Lights On*****************************/
	else if (state == 'W') {

		analogWrite(r1, 255);
		digitalWrite(r2, 255);
	}
	/************************Lights Off*****************************/
	else if (state == 'w') {
		analogWrite(r1, 0);
		analogWrite(r2, 0);
	}
}
