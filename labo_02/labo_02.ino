const int ledPins[] = {8, 9, 10, 11};  // Tableau des leds
int potentiometerPin = A1;          // pin du potentiomètre 
int potentiometerValue = 0;          // valeur du potentiomètre
const int boutonPin = 2;            // pin du bouton
unsigned long previousMillis = 0;   // 
const long interval = 1000;         // l'intervalle qui s'appliquera sur le bouton

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);  // DELs
  }
  pinMode(boutonPin, INPUT_PULLUP);   // Bouton
}

void loop() {
  leds();
  button();
}




void leds(){
  potentiometerValue = analogRead(potentiometerPin);
  int potentio_convertie = map(potentiometerValue, 0, 1023, 0, 20);

  if (potentio_convertie == 0) {
    digitalWrite(ledPins[0], LOW);
    digitalWrite(ledPins[1], LOW);
    digitalWrite(ledPins[2], LOW);
    digitalWrite(ledPins[3], LOW);
  } else if (potentio_convertie < 5){
    digitalWrite(ledPins[0], HIGH);
    digitalWrite(ledPins[1], LOW);
    digitalWrite(ledPins[2], LOW);
    digitalWrite(ledPins[3], LOW);
  } else if (potentio_convertie < 10) {
    digitalWrite(ledPins[0], HIGH);
    digitalWrite(ledPins[1], HIGH);
    digitalWrite(ledPins[2], LOW);
    digitalWrite(ledPins[3], LOW);
  } else if (potentio_convertie < 15) {
    digitalWrite(ledPins[0], HIGH);
    digitalWrite(ledPins[1], HIGH);
    digitalWrite(ledPins[2], HIGH);
    digitalWrite(ledPins[3], LOW);
  } else {
    digitalWrite(ledPins[0], HIGH);
    digitalWrite(ledPins[1], HIGH);
    digitalWrite(ledPins[2], HIGH);
    digitalWrite(ledPins[3], HIGH);
  }
}

void button(){
  int potentio_convertie = map(potentiometerValue, 0, 1023, 0, 100);  // affichage de la valeur du potentiomètre sur 100
  int potentio_convertie_affichage = map(potentiometerValue, 0, 1023, 0, 20); // affichage sur 20 comme dans l'énoncé
  int valueBouton = digitalRead(boutonPin);   // bouton
  unsigned long currentMillis = millis();   

  // affichage
  char tab[20];
  if (valueBouton == 0){    // l'affichage se fait juste quand la valeur du bouton est de 0 (bouton appuyé)
    if (currentMillis - previousMillis >= interval) { // pour éviter les rebonds
      previousMillis = currentMillis;

      Serial.print("[");  // affichage

      for (int i = 0; i < 20; i++){       
        if (i >= potentio_convertie_affichage){
          tab[i] = {'.'};
        } else {
          tab[i] = {'#'};
        }
        tab[20] = '\0'; // Assurer que le tableau est bien terminé comme chaîne de caractères
      }

      Serial.print(tab);
      Serial.print("] "); 
      Serial.print(potentio_convertie);
      Serial.println(" %");
    }
  } 
  

}