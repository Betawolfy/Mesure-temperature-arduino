/* Afficher la température sur un écran LCD - Grove - LCD RGB Backlight - Temperature Sensor V1.1/1.2
 *  Vincent Marais | 29/12/2021
 *  github: https://github.com/Betawolfy
 *  le Grove - LCD RGB Backlight doit être connecté sur le port I2C
 */

//ci dessous, les librairies nessesaire pour que le code fonctionne.

#include <Wire.h>
#include "rgb_lcd.h" // doit être installé: https://github.com/Seeed-Studio/Grove_LCD_RGB_Backlight/archive/master.zip
#include <math.h>
 
//configuration du Grove - LCD RGB Backlight : dans cette exemple: l'écran sera rouge.
rgb_lcd lcd;

const int colorR = 255;
const int colorG = 0;
const int colorB = 0;
const int B = 4275;               //  Valeur B de la thermistance
const int R0 = 100000;            // R0 = 100k
const int pinTempSensor = A0;     // le capteur de thempérature est connecté sur A0
  
#if defined(ARDUINO_ARCH_AVR)
#define debug  Serial
#elif defined(ARDUINO_ARCH_SAMD) ||  defined(ARDUINO_ARCH_SAM)
#define debug  SerialUSB
#else
#define debug  Serial
#endif

void setup() {
// Partie du Temperature Sensor V1.1/1.2
    
    Serial.begin(9600);

// Partie du Grove - LCD RGB Backlight

  // définir le nombre de colonnes et de lignes de l'écran LCD (nombre de colonnes, nombres de ligne)
    lcd.begin(16, 2);

    lcd.setRGB(colorR, colorG, colorB);

    // définir un message sur l'écran LCD. Ici, la température désiré.
    lcd.print("mesure temp v1");

    delay(1000);

}

void loop() {
  
//Partie du Temperature Sensor V1.1/1.2  
  int a = analogRead(pinTempSensor);
 
    float R = 1023.0/a-1.0;
    R = R0*R;
 
    float temperature = 1.0/(log(R/R0)/B+1/298.15)-273.15; // définition de la variable "temperature" via l'opération du code. 
    Serial.print("temperature = "); 
    Serial.println(temperature); // la valeur de la température est affiché dans le moniteur série

// partie pour le Grove - LCD RGB Backlight
  // placer le curseur à la colonne 0, ligne 1
    // (remarque : la ligne 1 est la deuxième ligne, puisque le comptage commence par 0) :
    lcd.setCursor(0, 1);
    // affichage de la température sous la forme "temp pièce:" <variable> "°" "C"
    lcd.print(temperature);
    lcd.print(char(223));
    lcd.print("C");
    
    delay(100); // le programme ce répète tout les 100 ms   
}
/* code utilisé: 
 *  Wikiseeed : https://wiki.seeedstudio.com/Grove-LCD_RGB_Backlight/
 *              https://wiki.seeedstudio.com/Grove-Temperature_Sensor_V1.2/
 * Travail réalisé pour un TP
 */
