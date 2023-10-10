#include <Adafruit_NeoPixel.h>
#include <WiFi.h>
#include <math.h>
#define WIFI_SSID "Mi A3"
#define WIFI_PASS "Davicete20"

extern const int rele_pin = 3;
extern const int dinPin = 4;
extern const int numOfLeds = 256;
extern Adafruit_NeoPixel pixels = Adafruit_NeoPixel(numOfLeds, dinPin, NEO_GRB + NEO_KHZ800);

int centerX = 7;
int centerY = 7;
float radius = 5;
float tam;

void setup() {pinMode(rele_pin, OUTPUT);
  pixels.begin();
  pixels.setBrightness(50);
  digitalWrite(rele_pin, HIGH);
}

void encenderFila(int numLeds, int dinPin, int fila) {
  Adafruit_NeoPixel leds = Adafruit_NeoPixel(numLeds, dinPin, NEO_GRB + NEO_KHZ800);
  if (fila <= 16) {
    int primerLed = (fila * 16) - 16;
    int ultimoLed = fila * 16;
    for (int i = primerLed; i < ultimoLed; i++) {
      leds.setPixelColor(i, leds.Color(64, 64, 64));
      delay(50);
    }
  } else {
  }
}

void apagarFila(int numLeds, int dinPin, int fila) {
  Adafruit_NeoPixel leds = Adafruit_NeoPixel(numLeds, dinPin, NEO_GRB + NEO_KHZ800);
  if (fila <= 16) {
    int primerLed = fila * 16 - 16;
    int ultimoLed = fila * 16;
    for (int i = primerLed; i < ultimoLed; i++) {
      leds.setPixelColor(i, leds.Color(0, 0, 0));
    }
  } else {
  }
}

void lluviaFila(void) {
  int fila = 0;
  for (int i = 0; i < 16; i++) {
    while (fila == 0) {
      fila = random(16);
    }
    if (fila == 1 || fila == 3 || fila == 5 || fila == 7 || fila == 9 || fila == 11 || fila == 13 || fila == 15) {
      for (int i = fila * 16 - 1; i > fila * 16 - 17; i--) {
        pixels.setPixelColor(i, pixels.Color(64, 64, 64));
        pixels.show();
        pixels.setPixelColor(i, pixels.Color(0, 0, 0));
        pixels.show();
      }
    } else {
      int primerLed = (fila * 16) - 16;
      int ultimoLed = fila * 16;
      for (int i = primerLed; i < ultimoLed; i++) {
        pixels.setPixelColor(i, pixels.Color(64, 64, 64));
        pixels.show();
        pixels.setPixelColor(i, pixels.Color(0, 0, 0));
        pixels.show();
      }
    }
    fila = random(16);
  }
}
void encenderTodo() {
  pixels.setBrightness(50);
  pixels.fill(pixels.Color(10, 10, 10), 0, 256);
  pixels.show();
}
void apagarTodo() {
  pixels.fill(pixels.Color(0, 0, 0), 0, 256);
  pixels.show();
}

void drawCenter(int centroX, int centroY) {
  if(centroY%2){
    pixels.setPixelColor((centroY+1)*16-(centroX+1), pixels.Color(0,255,0));
  }else{
    pixels.setPixelColor(centroY * 16 + centroX, pixels.Color(0, 255, 0));
  }
  pixels.show();
}

void drawCoord(int x, int y, uint32_t color){
  if(x>16 || y>16 || x<0 || y<0){
    //out of range
  }else if(y == 1 || y == 3 || y == 5 || y == 7 || y == 9 || y == 11 || y == 13 || y == 15){
    pixels.setPixelColor((y+1)*16-(x+1), color);
  }else{
    pixels.setPixelColor(y * 16 + x, color);
  }
}

void dibujarCirculo(int centerX, int centerY, int radius) {
  for (int y = -16; y < 16; y++) {
    for (int x = -16; x < 16; x++) {
      float distance = sqrt(pow(x,2) + pow(y,2)); // calcular la distancia entre el punto (x, y) y el centro del círculo
      if (distance <= radius+0.5) {
        //float intensity = 1.0 - (distance - radius + 0.5); // calcular la intensidad del pixel para el antialiasing
        drawCoord(x+centerX,y+centerY,pixels.Color(255,255,255));
      } else {
        drawCoord(x+centerX,y+centerY,pixels.Color(0,0,0)); // asignar el color negro al pixel en la posición (x, y) si está fuera del círculo
      }
    }
  }
}
void dibujarCirculo(int centerX, int centerY, int radius, float borde){
  for (int y = -16; y < 16; y++) {
    for (int x = -16; x < 16; x++) {
      float distance = sqrt(pow(x,2) + pow(y,2)); // calcular la distancia entre el punto (x, y) y el centro del círculo
      if (distance <= radius+borde/2 && distance >= radius-borde/2) {
        //float intensity = 1.0 - (distance - radius + 0.5); // calcular la intensidad del pixel para el antialiasing
        drawCoord(x+centerX,y+centerY,pixels.Color(255,255,255));
      } else if (radius+borde/2<radius-borde/2) {
        x=16;
        y=16;
      } else {
        drawCoord(x+centerX,y+centerY,pixels.Color(0,0,0)); // asignar el color negro al pixel en la posición (x, y) si está fuera del círculo
      }
    }
  }
}

void dibujarGota(int centerX, int centerY, float radius, float tam){
  for (int y = -16; y < 16; y++) {
    for (int x = -16; x < 16; x++) {
      float distance = sqrt(pow(x,2) + pow(y,2)); // calcular la distancia entre el punto (x, y) y el centro del círculo
      if (distance <= radius+(-tam*radius+2.5)/2 && distance >= radius-(-tam*radius+2.5)/2) {
        //float intensity = 1.0 - (distance - radius + 0.5); // calcular la intensidad del pixel para el antialiasing
        drawCoord(x+centerX,y+centerY,pixels.Color(round(255*(-0.6*distance+1)),round(255*(-0.6*distance+1)),255));
      } else if (radius+(-0.3*radius+2)/2+tam<radius-(-0.3*radius+2)/2) {
        x=16;
        y=16;
      } else {
        drawCoord(x+centerX,y+centerY,pixels.Color(0,65,65)); // asignar el color negro al pixel en la posición (x, y) si está fuera del círculo
      }
    }
  }
}

void loop() {
  dibujarGota(centerX, centerY, radius, tam);
  pixels.show(); // mostrar los valores de los LEDs en la pantalla
  //delay(100); // esperar medio segundo antes de dibujar la siguiente figura
  if(radius>7){
    centerX = random(0,16);
    centerY = random(0,16);
    radius = 0;
    tam = random(2,5)/10.0;
  }
  radius = radius+(1.7/(radius+1));
}