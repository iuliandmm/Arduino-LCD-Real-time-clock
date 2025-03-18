#include <Wire.h>
#include <RTClib.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>


RTC_DS3231 rtc;

// LCD-ul Nokia 5110 cu pinii corecti (4, 5, 6, 7, 8)
Adafruit_PCD8544 lcd = Adafruit_PCD8544(4, 5, 6, 7, 8);  // CLK, DIN, DC, CE, RST

void setup() {
  
  Serial.begin(115200);

  
  Wire.begin();

  // Inițializăm LCD-ul Nokia 5110
  lcd.begin();
  lcd.setContrast(50);  // Ajustează contrastul, poți schimba valoarea pentru claritate
  lcd.clearDisplay();
  lcd.display();

  // Verificăm dacă RTC-ul este conectat corect
  if (!rtc.begin()) {
    Serial.println("Nu am găsit RTC");
    lcd.setCursor(0, 0);
    lcd.print("Eroare RTC!");
    lcd.display();
    while (1); // Oprim programul dacă nu este găsit RTC-ul
  }

  // Setăm RTC-ul la ora de compilare (opțional)
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  Serial.println("RTC setat la timpul de compilare.");
}

void loop() {
  // Obținem data și ora curentă de la RTC
  DateTime now = rtc.now();

  // Ștergem ecranul înainte de fiecare actualizare
  lcd.clearDisplay();

  // Afișăm data pe primul rând
  lcd.setCursor(0, 0);
  lcd.print("Data: ");
  lcd.setCursor(0, 10);
  lcd.print(now.day(), DEC);
  lcd.print("-");
  lcd.print(now.month(), DEC);
  lcd.print("-");
  lcd.print(now.year(), DEC);

  // Lăsăm spațiu între data și ora 
  lcd.setCursor(0, 5);  
  lcd.print("             "); 

  // Afișăm ora 
  lcd.setCursor(0,20);  
  lcd.print("Ora: ");
  lcd.print(now.hour(), DEC);
  lcd.print(":");
  lcd.print(now.minute(), DEC);
  lcd.print(":");
  lcd.print(now.second(), DEC);

  lcd.setCursor(0,40);
  lcd.print("DUMITRU IULIAN");

  // Actualizăm display-ul
  lcd.display();

  delay(1000);  // Așteptăm 1 secundă pentru a actualiza
}


