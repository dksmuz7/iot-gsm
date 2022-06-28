// GSM based IOT device program
// By - Deepak Sagar

// Including software serial library
#include <SoftwareSerial.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

// Configuring serial port
#define rx_pin 2
#define tx_pin 3
SoftwareSerial gsm(rx_pin,tx_pin);

// Configuring appliances interfacing pin
#define b1_relay 4 // BULB 1
#define b2_relay 5 // BULB 2
#define b3_relay 6 // BULB 3
#define f1_relay 7 // FAN 1

// Speed Controller
#define mode1 11   // Speed for 15 - 20 deg celsius (Min speed)
#define mode2 10   // Speed for 20 - 25 deg celsius
#define mode3 9  // Speed for 25 - 30 deg celsius
#define mode4 8  // Speed for > 30 deg celsius (Max Speed)

// Configuring temperature pin
#define outPin 12
#define DHTTYPE DHT11
DHT_Unified dht(outPin,DHTTYPE); // Creating DHT object(instance)

// Defining stair led pin
#define stairLed_pin 13

// Defining pir pin to take input from the pir sensor
#define pir_pin A2
int pirState = LOW;            
int pirSensVal = 0;
int isPirActive = 0;

// Variable to store text message
String txt_msg;
String state = "";
String fanState = "OFF";

void setup(){
    // Configuring the digital output pins
    pinMode(b1_relay, OUTPUT);
    pinMode(b2_relay, OUTPUT);
    pinMode(b3_relay, OUTPUT);
    pinMode(f1_relay, OUTPUT);

    // Configuring different pin mode for speed controller
    pinMode(mode1,OUTPUT);
    pinMode(mode2,OUTPUT);
    pinMode(mode3,OUTPUT);
    pinMode(mode4,OUTPUT);

    // Configuring Pir signal pin to detect motion
    pinMode(pir_pin,INPUT);
    pinMode(stairLed_pin,OUTPUT); // Configuring stair led pin

    // setting intial state of all the appliances
    digitalWrite(b1_relay, HIGH);
    digitalWrite(b2_relay, HIGH);
    digitalWrite(b3_relay, HIGH);
    digitalWrite(f1_relay, HIGH);

    // Setting initial state of all the speed controller relay
    digitalWrite(mode1,HIGH);
    digitalWrite(mode2,HIGH);
    digitalWrite(mode3,HIGH);
    digitalWrite(mode4,HIGH);

    // Serial communication initialization
    Serial.begin(9600);
    Serial.println("Welcome !");
    gsm.begin(9600);
    
    // time to let connect gsm to a network
    delay(5000);
    Serial.println("GSM is ready...");

    // Command to set gsm to text mode
    gsm.print("AT+CMGF=1\r");
    delay(100);

    // Set module to send text data
    gsm.print("AT+CNMI=2,2,0,0,0\r");
    delay(100);

    // Initiating Temperature Sensor (DHT11);
    dht.begin();
    sensor_t sensor;
    dht.temperature().getSensor(&sensor);
    delay(sensor.min_delay/1000);

}

void loop(){
    if(gsm.available()>0){
        txt_msg = gsm.readString();
        Serial.println(txt_msg);
        delay(10);
    }

    bulb_1(txt_msg);
    delay(10);
    bulb_2(txt_msg);
    delay(10);
    bulb_3(txt_msg);
    delay(10);
    fan_1(txt_msg);
    delay(10);
    all_appliance(txt_msg);
    delay(10);
    activatePir(txt_msg);
    delay(10);
    if(isPirActive) motionLed();
    else digitalWrite(stairLed_pin,LOW);
    delay(10);
    speedControl();
    delay(10);

    // send_sms("GSM is Ready..."/);

}

// Logic for bulb 1
void bulb_1(String txt_msg){
    if(txt_msg.indexOf("b1")>=0 && txt_msg.indexOf("on")>=0){
        // Turning on bulb 1 and save current state
        digitalWrite(b1_relay, LOW);
        state = "Bulb 1 --> on";
        Serial.println("Bulb 1 --> on");
        txt_msg = "";
    }
    if(txt_msg.indexOf("b1")>=0 && txt_msg.indexOf("off")>=0){
        // Turning on bulb 1 and save current state
        digitalWrite(b1_relay, HIGH);
        state = "Bulb 1 --> off";
        Serial.println("Bulb 1 --> off");
        txt_msg = "";
    }
}

// Logic for bulb 2
void bulb_2(String txt_msg){
    if(txt_msg.indexOf("b2")>=0 && txt_msg.indexOf("on")>=0){
        // Turning on bulb 1 and save current state
        digitalWrite(b2_relay, LOW);
        state = "Bulb 2 --> on";
        Serial.println("Bulb 2 --> on");
        txt_msg = "";
    }
    if(txt_msg.indexOf("b2")>=0 && txt_msg.indexOf("off")>=0){
        // Turning on bulb 2 and save current state
        digitalWrite(b2_relay, HIGH);
        state = "Bulb 2 --> off";
        Serial.println("Bulb 2 --> off");
        txt_msg = "";
    }
}

// Logic for bulb 3
void bulb_3(String txt_msg){
    if(txt_msg.indexOf("b3")>=0 && txt_msg.indexOf("on")>=0){
        // Turning on bulb 1 and save current state
        digitalWrite(b3_relay, LOW);
        state = "Bulb 3 --> on";
        Serial.println("Bulb 3 --> on");
        txt_msg = "";
    }
    if(txt_msg.indexOf("b3")>=0 && txt_msg.indexOf("off")>=0){
        // Turning on bulb 3 and save current state
        digitalWrite(b3_relay, HIGH);
        state = "Bulb 3 --> off";
        Serial.println("Bulb 3 --> off");
        txt_msg = "";
    }
}

// Logic for fan 1
void fan_1(String txt_msg){
    if(txt_msg.indexOf("f1")>=0 && txt_msg.indexOf("on")>=0){
        // Turning on fan 1 and save current state
        digitalWrite(f1_relay, LOW);
        state = "Fan 1 --> on";
        Serial.println("Fan 1 --> on");
        txt_msg = "";
        fanState = "ON";
    }
    if(txt_msg.indexOf("f1")>=0 && txt_msg.indexOf("off")>=0){
        // Turning on fan 1 and save current state
        digitalWrite(f1_relay, HIGH);
        state = "Fan 1 --> off";
        Serial.println("Fan 1 --> off");
        txt_msg = "";
        fanState = "OFF";
    }
}

// Logic for all appliances
void all_appliance(String txt_msg){
    if(txt_msg.indexOf("all")>=0 && txt_msg.indexOf("on")>=0){
        // Turning on fan 1 and save current state
        digitalWrite(f1_relay, LOW);
        digitalWrite(b1_relay, LOW);
        digitalWrite(b2_relay, LOW);
        digitalWrite(b3_relay, LOW);
        state = "ALL --> on";
        Serial.println("ALL --> on");
        txt_msg = "";
        fanState = "ON";
    }
    if(txt_msg.indexOf("all")>=0 && txt_msg.indexOf("off")>=0){
        // Turning on fan 1 and save current state
        digitalWrite(f1_relay, HIGH);
        digitalWrite(b1_relay, HIGH);
        digitalWrite(b2_relay, HIGH);
        digitalWrite(b3_relay, HIGH);
        state = "ALL --> off";
        Serial.println("ALL --> off");
        txt_msg = "";
        fanState = "OFF";
    }
}

void modeSelect(float temp){
    // Mode 1 min speed mode
    if(temp <= 25) {
        digitalWrite(mode2,HIGH);
        digitalWrite(mode3,HIGH);
        digitalWrite(mode4,HIGH);
        digitalWrite(mode1,HIGH);
    }
    if(temp>25 && temp <=29){
        digitalWrite(mode2,HIGH);
        digitalWrite(mode3,HIGH);
        digitalWrite(mode4,HIGH);
        digitalWrite(mode1,LOW);
    }

    // Mode 2 
    if(temp>29 && temp <=33){
        digitalWrite(mode1,HIGH);
        digitalWrite(mode3,HIGH);
        digitalWrite(mode4,HIGH);
        digitalWrite(mode2,LOW);
    }
    
    // Mode 3
    if(temp > 33 && temp <= 37){
        digitalWrite(mode1,HIGH);
        digitalWrite(mode2,HIGH);
        digitalWrite(mode4,HIGH);
        digitalWrite(mode3,LOW);
    }
    
    // Mode 4 max speed mode
    if(temp > 37){
        digitalWrite(mode1,HIGH);
        digitalWrite(mode2,HIGH);
        digitalWrite(mode3,HIGH);
        digitalWrite(mode4,LOW);
    }
}

void speedControl(){
    if(fanState == "ON"){
        sensors_event_t event;
        dht.temperature().getEvent(&event);
        if(isnan(event.temperature)){
            Serial.println(F("Error reading temperature"));
        }
        else {
            modeSelect(event.temperature);
            Serial.print("Temperature = ");
            Serial.println(event.temperature);
        }
    }

    if(fanState == "OFF"){
        digitalWrite(mode1,HIGH);
        digitalWrite(mode2,HIGH);
        digitalWrite(mode3,HIGH);
        digitalWrite(mode4,HIGH);
    }
}

// Motion Led Control PIR Sensor
void motionLed(){
    pirSensVal = digitalRead(pir_pin);   
    if (pirSensVal == HIGH) {           
        digitalWrite(stairLed_pin, HIGH);   
        delay(100); // Delay of led is 1 sec             
        
        if (pirState == LOW) {
            Serial.println(" Motion detected "); 
            pirState = HIGH;
        }
    } 
    else {
        digitalWrite(stairLed_pin, LOW);
        delay(100);             
        
        if (pirState == HIGH){
            Serial.println("The action/ motion has stopped");
            pirState = LOW;
        }
    }
}

// Activate PIR sensor to detect motion
void activatePir(String msg){
    if(txt_msg.indexOf("pir=on")>=0){
        isPirActive = 1;
        state = "PIR --> active";
        Serial.println("PIR --> active");
        txt_msg = "";
    }
    if(txt_msg.indexOf("pir=off")>=0){
        isPirActive = 0;
        state = "PIR --> deactive";
        Serial.println("PIR --> deactive");
        txt_msg = "";
    }
}

// Function to send SMS
void send_sms(String msg){
    // setting gsm for text mode
    gsm.print("AT+CMGF=1\r");
    delay(100);

    // initializing mobile number of reciever(TO)
    gsm.println("AT+CMGS = \"+919504393742\""); // Replace mobile number with yours
    delay(100);

    // Sending message
    gsm.println(msg);
    delay(100);

    // Message end command (ctrl+z == 26 ASCII value)
    gsm.println((char)26);
    delay(100);
    gsm.println();
    
    delay(5000); // Time delay to send message
}
