#include <paj7620.h>
#include <Gesture.h>


/*
    Notice: When you want to recognize the Forward/Backward gestures, your gestures' reaction time must less than GES_ENTRY_TIME(0.8s).
        You also can adjust the reaction time according to the actual circumstance.
*/
#define GES_REACTION_TIME		500				// You can adjust the reaction time according to the actual circumstance.
#define GES_ENTRY_TIME			800				// When you want to recognize the Forward/Backward gestures, your gestures' reaction time must less than GES_ENTRY_TIME(0.8s). 
#define GES_QUIT_TIME			1000

paj7620 Gesture;

void setup() {
    Serial.begin(9600);
    while(!Serial) {
        delay(100);
    }
    Serial.println("\nPAJ7620U2 TEST DEMO: Recognize 9 gestures.");
    
    if(Gesture.init()) {
        Serial.println("PAJ7620U2 initialization failed");
    } else {
        Serial.println("PAJ7620U2 initialization success");
    }
    Serial.println("Please input your gestures:\n");
}

void loop() {
    paj7620_gesture_t result;
    if (Gesture.getResult(result)) {
        switch (result) {
        case UP:
            delay(GES_ENTRY_TIME);
            Gesture.getResult(result);
            if (result == PUSH) {
                Serial.println("Forward");
                delay(GES_QUIT_TIME);
            } else if (result == POLL) {
                Serial.println("Backward");
                delay(GES_QUIT_TIME);
            } else {
                Serial.println("Up");
            }
            break;
        case DOWN:
            delay(GES_ENTRY_TIME);
            Gesture.getResult(result);
            if (result == PUSH) {
                Serial.println("Forward");
                delay(GES_QUIT_TIME);
            } else if (result == POLL) {
                Serial.println("Backward");
                delay(GES_QUIT_TIME);
            } else {
                Serial.println("Down");
            }
            break;
        case LEFT:
            delay(GES_ENTRY_TIME);
            Gesture.getResult(result);
            if (result == PUSH) {
                Serial.println("Forward");
                delay(GES_QUIT_TIME);
            } else if (result == POLL) {
                Serial.println("Backward");
                delay(GES_QUIT_TIME);
            } else {
                Serial.println("Left");
            }
            break;
        case RIGHT:
            delay(GES_ENTRY_TIME);
            Gesture.getResult(result);
            if (result == PUSH) {
                Serial.println("Forward");
                delay(GES_QUIT_TIME);
            } else if (result == POLL) {
                Serial.println("Backward");
                delay(GES_QUIT_TIME);
            } else {
                Serial.println("Right");
            }
            break;
        case PUSH:
            Serial.println("Forward");
            delay(GES_QUIT_TIME);
            break;
        case POLL:
            Serial.println("Backward");
            delay(GES_QUIT_TIME);
            break;
        case CLOCKWISE:
            Serial.println("Clockwise");
            break;
        case ANTI_CLOCKWISE:
            Serial.println("anti-clockwise");
            break;
        case WAVE:
            Serial.println("wave");
            break;
        default:
            break;
        }
    }
    delay(100);
}