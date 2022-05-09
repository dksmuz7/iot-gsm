// GSM based IOT device program
// By - Deepak Sagar

// Including software serial library
#include <SoftwareSerial.h>

// Configuring serial port
#define rx_pin 3
#define tx_pin 4
SoftwareSerial gsm(rx_pin,tx_pin);

// Configuring appliances interfacing pin
#define b1_relay 10 // BULB 1
#define b2_relay 11 // BULB 2
#define b3_relay 12 // BULB 3
#define f1_relay 13 // FAN 1


// Variable to store text message
String txt_msg;
String state = "";

void setup(){
    // Configuring the digital output pins
    pinMode(b1_relay, OUTPUT);
    pinMode(b2_relay, OUTPUT);
    pinMode(b3_relay, OUTPUT);
    pinMode(f1_relay, OUTPUT);

    // setting intial state of all the appliances
    digitalWrite(b1_relay, LOW);
    digitalWrite(b2_relay, LOW);
    digitalWrite(b3_relay, LOW);
    digitalWrite(f1_relay, LOW);

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

}

void loop(){
    if(gsm.available()>0){
        txt_msg = gsm.readString();
        Serial.println(txt_msg);
        delay(10);
    }

    bulb_1(txt_msg);
    bulb_2(txt_msg);
    bulb_3(txt_msg);
    fan_1(txt_msg);

}

// Logic for bulb 1
void bulb_1(String txt_msg){
    if(txt_msg.indexOf("b1")>=0 && txt_msg.indexOf("on")>=0){
        // Turning on bulb 1 and save current state
        digitalWrite(b1_relay, HIGH);
        state = "Bulb 1 --> on";
        Serial.println("Bulb 1 --> on");
        txt_msg = "";
    }
    if(txt_msg.indexOf("b1")>=0 && txt_msg.indexOf("off")>=0){
        // Turning on bulb 1 and save current state
        digitalWrite(b1_relay, LOW);
        state = "Bulb 1 --> off";
        Serial.println("Bulb 1 --> off");
        txt_msg = "";
    }
}

// Logic for bulb 2
void bulb_2(String txt_msg){
    if(txt_msg.indexOf("b2")>=0 && txt_msg.indexOf("on")>=0){
        // Turning on bulb 1 and save current state
        digitalWrite(b2_relay, HIGH);
        state = "Bulb 2 --> on";
        Serial.println("Bulb 2 --> on");
        txt_msg = "";
    }
    if(txt_msg.indexOf("b2")>=0 && txt_msg.indexOf("off")>=0){
        // Turning on bulb 2 and save current state
        digitalWrite(b2_relay, LOW);
        state = "Bulb 2 --> off";
        Serial.println("Bulb 2 --> off");
        txt_msg = "";
    }
}

// Logic for bulb 3
void bulb_3(String txt_msg){
    if(txt_msg.indexOf("b3")>=0 && txt_msg.indexOf("on")>=0){
        // Turning on bulb 1 and save current state
        digitalWrite(b3_relay, HIGH);
        state = "Bulb 3 --> on";
        Serial.println("Bulb 3 --> on");
        txt_msg = "";
    }
    if(txt_msg.indexOf("b3")>=0 && txt_msg.indexOf("off")>=0){
        // Turning on bulb 3 and save current state
        digitalWrite(b3_relay, LOW);
        state = "Bulb 3 --> off";
        Serial.println("Bulb 3 --> off");
        txt_msg = "";
    }
}

// Logic for fan 1
void fan_1(String txt_msg){
    if(txt_msg.indexOf("b1")>=0 && txt_msg.indexOf("on")>=0){
        // Turning on fan 1 and save current state
        digitalWrite(f1_relay, HIGH);
        state = "Fan 1 --> on";
        Serial.println("Fan 1 --> on");
        txt_msg = "";
    }
    if(txt_msg.indexOf("f1")>=0 && txt_msg.indexOf("off")>=0){
        // Turning on fan 1 and save current state
        digitalWrite(f1_relay, LOW);
        state = "Fan 1 --> off";
        Serial.println("Fan 1 --> off");
        txt_msg = "";
    }
}

// Logic for all appliances
void all_appliance(String txt_msg){
    if(txt_msg.indexOf("all")>=0 && txt_msg.indexOf("on")>=0){
        // Turning on fan 1 and save current state
        digitalWrite(f1_relay, HIGH);
        digitalWrite(b1_relay, HIGH);
        digitalWrite(b2_relay, HIGH);
        digitalWrite(b3_relay, HIGH);
        state = "ALL --> on";
        Serial.println("ALL --> on");
        txt_msg = "";
    }
    if(txt_msg.indexOf("all")>=0 && txt_msg.indexOf("off")>=0){
        // Turning on fan 1 and save current state
        digitalWrite(f1_relay, LOW);
        digitalWrite(b1_relay, LOW);
        digitalWrite(b2_relay, LOW);
        digitalWrite(b3_relay, LOW);
        state = "ALL --> off";
        Serial.println("ALL --> off");
        txt_msg = "";
    }
}

// Function to send SMS
void send_sms(String msg){
    // setting gsm for text mode
    gsm.print("AT+CMGF=1\r");
    delay(100);

    // initializing mobile number of reciever(TO)
    gsm.println("AT+CMGS = \"+918541986045\"");
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
