#include <SPI.h>
#include <MFRC522.h>  // библиотека "RFID".
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);
unsigned long uidDec, uidDecTemp;  // для храниения номера метки в десятичном формате
bool flag = false;
void setup() {
  pinMode(6, OUTPUT);  // Объявляем пин реле как выход
  digitalWrite(6, HIGH);
  Serial.begin(9600);
  Serial.println("Waiting for card...");
  SPI.begin();         //  инициализация SPI / Init SPI bus.
  mfrc522.PCD_Init();  // инициализация MFRC522 / Init MFRC522 card.
}
void loop() {
  // Поиск новой метки
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  // Выбор метки
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  uidDec = 0;
  // Выдача серийного номера метки.
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    uidDecTemp = mfrc522.uid.uidByte[i];
    uidDec = uidDec * 256 + uidDecTemp;
  }
  Serial.println("Card UID: ");
  Serial.println(uidDec);  // Выводим UID метки в консоль.
  if (uidDec == 1666656694) {
    if (flag == false) {
      digitalWrite(6, 0);
      flag = true;
      delay(1000);
    } else {
      digitalWrite(6, 1);
      flag = false;
      delay(1000);
    }
  }
}