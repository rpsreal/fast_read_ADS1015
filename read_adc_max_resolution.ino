#include <Wire.h>
// ESP8266
// +-0.5ms   Read DIF VOLTAGE ADC pins (AIN0 and AIN1)
//        0 = -2.048V      2048 = 0V       4095 = +2.048V              1 bit = 1mV
// READ DIFFERENCIAL VOLTAGE (A0 <-> A1) 12bits RESOLUTION FOR SINAL -2.048V -> +2.048V
// ABOUT: https://learn.adafruit.com/adafruit-4-channel-adc-breakouts/signal-connections
//        https://cdn-shop.adafruit.com/datasheets/ads1015.pdf


int16_t i2caddress=0x48;
uint16_t ADC;

uint16_t config0 = 0x0003  | // NOT Assert ALERT/RDY after one conversions
                   0x0000  | // NOT Latching Comparator
                   0x0000  | // Alert/Rdy active low   (default val)
                   0x0000  | // Traditional comparator (default val)
                   0x00C0  | // 3300 samples per second (default)
                   0x0100  | // Single-shot mode (default)
                   0x0400  | // (0x0200) +/-4.096V range = Gain 1  || (0x0400) // +/-2.048V range = Gain 2 (default)
                   0x0000  | // (0x4000) Single-ended AIN0 || (0x0000) Differential P = AIN0, N = AIN1 (default)
                   0x8000;   // Set 'start single-conversion' bit
                   // CODES: https://github.com/rpsreal/Adafruit_ADS1X15/blob/master/Adafruit_ADS1015.h
                   
void writei2c(uint8_t address, uint16_t registo) {
  Wire.beginTransmission(address);
  Wire.write(0x01);
  Wire.write((uint8_t)(registo>>8));
  Wire.write((uint8_t)(registo & 0xFF));
  Wire.endTransmission();
}
uint16_t readi2c(uint8_t address, uint8_t reg) { 
  Wire.beginTransmission(address);
  Wire.write(reg);                       // ADS1015_REG_POINTER_CONVERT
  Wire.endTransmission();
  Wire.requestFrom(address, (uint8_t)2);
  return ((Wire.read() << 8) | Wire.read());
}
uint16_t readADC(uint16_t config) { // Função para a Leitura de um pino do ADC (recebe os registos de configuração)
  writei2c(i2caddress, config); // escrever registo no ADC - registo para pedido de leitura num pino do ADC
  delayMicroseconds(1);                    // tempo de espera para a comunicação seja terminada
  while ((readi2c(i2caddress, 0x01) & 0x8000) == 0);  // Espera que o config register OS bit mude para 1 (conversão concluida) 
  return (readi2c(i2caddress, 0x00) >> 4);          // Retorna o valor lido do pino do ADC
}

void setup(){
  Wire.pins(0, 2);
  Wire.begin(0, 2);
  Wire.setClock(3400000); // fast mode i2c (400000) || high speed mode (3400000)
  Serial.begin(115200);
    while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("START"); Serial.print("\n");
}

void loop(){
    ADC=readADC(config0);
    Serial.print("A0 = "); Serial.println(ADC);
}