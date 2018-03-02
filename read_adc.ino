#include <Wire.h>
// +-1ms   Read 2 ADC pins (AIN0 and AIN1)
//         1650 = 3,3V         0 = 0V        1 bit = 2mV
int16_t i2caddress=0x48;
uint16_t AIN0, AIN1;

uint16_t config0 = 0x0003  | // NOT Assert ALERT/RDY after one conversions
                   0x0000  | // NOT Latching Comparator
                   0x0000  | // Alert/Rdy active low   (default val)
                   0x0000  | // Traditional comparator (default val)
                   0x00C0  | // 3300 samples per second (default)
                   0x0100  | // Single-shot mode (default)
                   0x0200  | // +/-4.096V range = Gain 1
                   0x4000  | // Single-ended AIN0
                   0x8000;   // Set 'start single-conversion' bit
uint16_t config1 = 0x0003  | // NOT Assert ALERT/RDY after one conversions
                   0x0000  | // NOT Latching Comparator
                   0x0000  | // Alert/Rdy active low   (default val)
                   0x0000  | // Traditional comparator (default val)
                   0x00C0  | // 3300 samples per second (default)
                   0x0100  | // Single-shot mode (default)
                   0x0200  | // +/-4.096V range = Gain 1
                   0x5000  | // Single-ended AIN1
                   0x8000;   // Set 'start single-conversion' bit

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
  delayMicroseconds(20);                    // tempo de espera para a comunicação seja terminada
  while ((readi2c(i2caddress, 0x01) & 0x80) == 0);  // Espera que o config register OS bit mude para 1 (conversão concluida) 
  return (readi2c(i2caddress, 0x00) >> 4);          // Retorna o valor lido do pino do ADC
}



void setup(){
  Wire.begin();
  Wire.setClock(400000); // fast mode i2c
  Serial.begin(115200);
    while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("START"); Serial.print("\n");
}

void loop(){
    AIN0=readADC(config0);
    AIN1=readADC(config1);
    Serial.print("ADC0: "); Serial.print(AIN0); 
    Serial.print(" ADC1: "); Serial.print(AIN1);
    Serial.print("\n");
 }
