#include <NewPing.h>

#define TRIG_PIN 9
#define ECHO_PIN 10
#define MQ2_PIN A0

#define RED_LED 7
#define GREEN_LED 8
#define BUZZER 6
#define BUTTON_PIN 2

#define MAX_DISTANCE 200
#define MESAFE_ESIK 20
#define GAZ_ESIK 200

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

int mesafe = 0;
int gazDegeri = 0;

bool dokunmaAlarmi = false;
bool sigaraAlarmi = false;

bool sistemAktif = false;
bool oncekiButon = HIGH;

void setup()
{
  Serial.begin(9600);

  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(BUZZER, LOW);

  Serial.println("SISTEM KAPALI - Butona basiniz");
}

void loop()
{
  bool simdikiButon = digitalRead(BUTTON_PIN);

  if (oncekiButon == HIGH && simdikiButon == LOW)
  {
    sistemAktif = !sistemAktif;

    if (sistemAktif)
    {
      Serial.println("SISTEM ACILDI");
    }
    else
    {
      Serial.println("SISTEM KAPANDI");
    }

    delay(200);
  }

  oncekiButon = simdikiButon;

  if (!sistemAktif)
  {
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(BUZZER, LOW);
    return;
  }

  mesafe = sonar.ping_cm();
  gazDegeri = analogRead(MQ2_PIN);

  dokunmaAlarmi = (mesafe > 0 && mesafe < MESAFE_ESIK);
  sigaraAlarmi = (gazDegeri > GAZ_ESIK);

  Serial.print("Mesafe: ");
  Serial.print(mesafe);
  Serial.print(" cm | Gaz: ");
  Serial.println(gazDegeri);

  if (dokunmaAlarmi || sigaraAlarmi)
  {
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(BUZZER, HIGH);

    if (dokunmaAlarmi)
    {
      Serial.println("DOKUNMAYINIZ!");
    }

    if (sigaraAlarmi)
    {
      Serial.println("SIGARA ALGILANDI!");
    }
  }
  else
  {
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(BUZZER, LOW);
  }

  delay(300);
}