#define IN1 13
#define IN2 15
#define IN3 14
#define IN4 2

void setup() {
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
}

void loop() {
    // Motor A forward
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);

    // Motor B forward
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    delay(1000);

    // Motor A backward
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);

    // Motor B backward
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    delay(1000);

    // Stop motors
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    delay(1000);
}
