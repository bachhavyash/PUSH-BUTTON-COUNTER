#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int buttonPin = 2;  
const int dhtPin = 7;     

DHT dht(dhtPin, DHT11);

LiquidCrystal_I2C lcd(0x27, 16, 2); 

int buttonState = 0;      
int lastButtonState = 0;  
int count = 0;           

unsigned long lastDebounceTime = 0; 
unsigned long debounceDelay = 50;   
void setup() {
  
  Serial.begin(9600);
  
  dht.begin();
  
  pinMode(buttonPin, INPUT);

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Press count: ");
  lcd.setCursor(0, 1);
  lcd.print("Temperature: ");
}

void loop() {
 
  int reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    lastDebounceTime = millis(); 
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == HIGH) {
        count++;  // Increment the counter
        Serial.print("Button pressed ");
        Serial.print(count);
        Serial.println(" times.");
      }
    }
  }

  
  lastButtonState = reading;

  float temperature = dht.readTemperature(); 
  float humidity = dht.readHumidity();       

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

 
  lcd.setCursor(12, 0);
  lcd.print(count);

  lcd.setCursor(12, 1);
  lcd.print(temperature);
  lcd.print(" C");

 
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" C, Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  
  delay(1000);
}
