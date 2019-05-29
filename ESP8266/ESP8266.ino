void setup()
{
	Serial.begin(9600);
}

void loop()
{
	Serial.write("ESP test...");
	delay(2000);
}