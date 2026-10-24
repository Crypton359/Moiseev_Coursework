// Подключение датчиков
const int PIN_MQ2 = A0;
const int PIN_PIR = 2;
const int PIN_SW = 3;

// Тестовый режим
const int PIN_TEST_SW = 4;

// Исполнительные устройства
const int PIN_RELAY = 7;
const int PIN_LED = 8;

// Порог концентрации газа
const float THRESHOLD = 50.0;

// Состояние тревоги
bool alarm = false;

// Режим тестирования
float testCO = 30.0;

// Период опроса - 5 секунд
const int T = 5000;

// Номер измерения
unsigned long n = 0;

void setup() {
  Serial.begin(9600);
  pinMode(PIN_PIR, INPUT);
  pinMode(PIN_SW, INPUT_PULLUP);
  pinMode(PIN_TEST_SW, INPUT_PULLUP);

  pinMode(PIN_RELAY, OUTPUT);
  pinMode(PIN_LED, OUTPUT);

  // Начальное состояние
  digitalWrite(PIN_RELAY, LOW);
  digitalWrite(PIN_LED, LOW);
}

void loop() {
  // Получение тестовой концентрации
    if (Serial.available() > 0) {
      String command = Serial.readStringUntil('\n');
      command.trim();

      if (command.startsWith("SET ")) {
        float value = command.substring(4).toFloat();

        if (value >= 0 && value <= 300) {
          testCO = value;
        }
      }
    }


  n++;

  // Считываем состояние переключателя режима
  bool testMode = !digitalRead(PIN_TEST_SW);

  //Считывание датчика газа
  int raw = analogRead(PIN_MQ2);
  float s1 = 300.0 * raw / 1023.0;

  // Используем тестовое значение, если включён тестовый режим
  if (testMode) {
    s1 = testCO;
  }

  //Считывание датчика движения
  int s2 = digitalRead(PIN_PIR);

  //Считывание положения ворот
  int s3 = !digitalRead(PIN_SW);

  //Вывод показаний
  Serial.print("DATA n=");
  Serial.print(n);

  Serial.print(" s1=");
  Serial.print(s1, 2);

  Serial.print(" s2=");
  Serial.print(s2);

  Serial.print(" s3=");
  Serial.print(s3);

  Serial.print(" mode=");
  Serial.println(testMode ? "TEST" : "AUTO");

  // Проверяем концентрацию газа
  bool danger = s1 > THRESHOLD;

  if (danger && !alarm) {
    //Концентрация превысила порог
    alarm = true;

    digitalWrite(PIN_RELAY, HIGH);
    digitalWrite(PIN_LED, HIGH);

    Serial.print("EVENT n=");
    Serial.print(n);
    Serial.print(" type=THRESHOLD");
    Serial.println(testMode ? " mode=TEST" : " mode=AUTO");
  }
  else if (!danger && alarm) {
    // Концентрация вернулась в норму
    alarm = false;

    digitalWrite(PIN_RELAY, LOW);
    digitalWrite(PIN_LED, LOW);

    Serial.print("EVENT n=");
    Serial.print(n);
    Serial.print(" type=NORMAL");
    Serial.println(testMode ? " mode=TEST" : " mode=AUTO");
  }

  delay(T);
}
