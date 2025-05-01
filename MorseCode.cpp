const int ledPin = 13;  // Use built-in LED
const int dotDelay = 200;  // 1 unit = dot
const int dashDelay = dotDelay * 3;  // 3 units = dash
const int charGap = dotDelay * 3;  // Gap between characters
const int wordGap = dotDelay * 7;  // Gap between words

const char* morseTable[] = {
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",   // A-J
  "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",     // K-T
  "..-", "...-", ".--", "-..-", "-.--", "--..",                            // U-Z
  "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...",  // 0-7
  "---..", "----."                                                         // 8-9
};

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("Enter a message to encode into Morse code:");
}

void loop() {
  if (Serial.available()) {
    String message = Serial.readStringUntil('\n');
    message.toUpperCase();

    for (int i = 0; i < message.length(); i++) {
      char c = message.charAt(i);

      if (c == ' ') {
        delay(wordGap);  // Gap between words
      } else if (isAlphaNumeric(c)) {
        int index = (isAlpha(c)) ? c - 'A' : c - '0' + 26;
        const char* morse = morseTable[index];

        for (int j = 0; morse[j] != '\0'; j++) {
          if (morse[j] == '.') {
            blink(dotDelay);
          } else if (morse[j] == '-') {
            blink(dashDelay);
          }
          delay(dotDelay);  // Gap between dots/dashes
        }
        delay(charGap);  // Gap between letters
      }
    }

    Serial.println("✅ Morse code transmission complete!");
  }
}

void blink(int duration) {
  digitalWrite(ledPin, HIGH);
  delay(duration);
  digitalWrite(ledPin, LOW);
  delay(dotDelay);
}
