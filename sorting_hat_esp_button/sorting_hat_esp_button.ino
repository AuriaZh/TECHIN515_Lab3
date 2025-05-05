#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "sorting_hat_model.h"

// OLED 屏幕配置
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Button 引脚（适配 ESP32-WROOM）
#define BUTTON_A  32
#define BUTTON_B  33
#define BUTTON_C  25
#define BUTTON_D  26

// 问题和选项内容
const char* questions[] = {
    "1. What do you value?",
    "2. Someone cheats?",
    "3. Favorite subject?",
    "4. Face challenges?",
    "5. Friends say you're?",
    "6. Mystery book?",
    "7. Preferred pet?",
    "8. Solve problems?",
    "9. Friends you like?",
    "10. Dream career?"
};

const char* options[][4] = {
    {"A) Bravery", "B) Loyalty", "C) Intelligence", "D) Ambition"},
    {"A) Call out", "B) Let go", "C) Tell teacher", "D) Gain from it"},
    {"A) Defense", "B) Herbology", "C) Charms", "D) Potions"},
    {"A) Head-on", "B) Team up", "C) Plan first", "D) Outsmart"},
    {"A) Bold", "B) Kind", "C) Smart", "D) Clever"},
    {"A) Read now", "B) Check safe", "C) Study it", "D) Use it"},
    {"A) Owl", "B) Toad", "C) Cat", "D) Phoenix"},
    {"A) Act fast", "B) Compromise", "C) Analyze", "D) Outsmart"},
    {"A) Adventurous", "B) Loyal", "C) Thoughtful", "D) Powerful"},
    {"A) Auror", "B) Healer", "C) Scholar", "D) Minister"}
};

int responses[10] = {0};
int questionIndex = 0;
Eloquent::ML::Port::DecisionTree clf;

void setup() {
    Serial.begin(115200);

    // 初始化 OLED（使用默认 GPIO21/22）
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println("⚠️ OLED init failed. Check wiring.");
        while (true);  // 卡死
    }

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(10, 10);
    display.println("Sorting Hat Ready!");
    display.display();
    delay(1500);

    // 初始化按钮
    pinMode(BUTTON_A, INPUT_PULLUP);
    pinMode(BUTTON_B, INPUT_PULLUP);
    pinMode(BUTTON_C, INPUT_PULLUP);
    pinMode(BUTTON_D, INPUT_PULLUP);

    showQuestion();
}

void loop() {
    checkButtons();
}

void showQuestion() {
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println(questions[questionIndex]);

    for (int i = 0; i < 4; i++) {
        display.setCursor(10, 20 + (i * 10));
        display.println(options[questionIndex][i]);
    }

    display.display();
}

void checkButtons() {
    bool pressed = false;

    while (!pressed) {
        if (digitalRead(BUTTON_A) == LOW) {
            responses[questionIndex] = 1;
            pressed = true;
        } else if (digitalRead(BUTTON_B) == LOW) {
            responses[questionIndex] = 2;
            pressed = true;
        } else if (digitalRead(BUTTON_C) == LOW) {
            responses[questionIndex] = 3;
            pressed = true;
        } else if (digitalRead(BUTTON_D) == LOW) {
            responses[questionIndex] = 4;
            pressed = true;
        }
        delay(20);
    }

    // 等待按钮松开
    while (digitalRead(BUTTON_A) == LOW ||
           digitalRead(BUTTON_B) == LOW ||
           digitalRead(BUTTON_C) == LOW ||
           digitalRead(BUTTON_D) == LOW) {
        delay(20);
    }

    nextQuestion();
}

void nextQuestion() {
    questionIndex++;
    if (questionIndex < 10) {
        showQuestion();
    } else {
        classifyHouse();
    }
}

void classifyHouse() {
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(10, 10);
    display.println("Sorting...");
    display.display();
    delay(1000);

    float features[10];
    for (int i = 0; i < 10; i++) features[i] = (float)responses[i];

    int house = clf.predict(features);

    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0, 20);
    display.print("House:\n");
    switch (house) {
        case 0: display.println("Gryffindor"); break;
        case 1: display.println("Hufflepuff"); break;
        case 2: display.println("Ravenclaw"); break;
        case 3: display.println("Slytherin"); break;
        default: display.println("Unknown"); break;
    }

    display.display();

    Serial.println("✅ Sorting complete!");
    Serial.print("Predicted House: ");
    switch (house) {
        case 0: Serial.println("Gryffindor"); break;
        case 1: Serial.println("Hufflepuff"); break;
        case 2: Serial.println("Ravenclaw"); break;
        case 3: Serial.println("Slytherin"); break;
    }
}
