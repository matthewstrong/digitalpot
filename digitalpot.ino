/**
 * Boston Scientific Proprietary
 * Copyright 2020 by Boston Scientific or its affiliates. All rights reserved.
 */

const int PWM_PIN_OnOff = 9; // OUTPUT Voltage Pin for on off
const int PWM_PIN_Pressure = 10; // OUTPUT Voltage Pin for pressure
const int PWM_PIN_Flow = 11; // OUTPUT Voltage Pin for flow

// Read and parse Serial input
uint8_t ReadInput();
// Convert ASCII string to integer value
uint8_t str_to_uint8(char* str, int len);

void setup()
{
    Serial.setTimeout(10); // 10ms timeout
    Serial.begin(115200);  // Fastest supported speed
    pinMode(PWM_PIN_OnOff, OUTPUT); // Enable output pin
    pinMode(PWM_PIN_Pressure, OUTPUT); // Enable output pin
    pinMode(PWM_PIN_Flow, OUTPUT); // Enable output pin
}

void loop()
{
    if (Serial.available() > 0)
    {
        // Read Serial input
        uint8_t val = 0;
        char prefix = '0';
       
        ReadInput(val, prefix);
        Serial.println("Input: " + String(val));
        float voltage = 5.0*val/255;
        Serial.println("Output voltage: " + String(voltage, 2));
        if (prefix == 'O')
        {
          // Modify the output voltage
          analogWrite(PWM_PIN_OnOff, val);
        }
        else if (prefix == 'P')
        {
          // Modify the output voltage
          analogWrite(PWM_PIN_Pressure, val);
        }
        else if (prefix == 'F')
        {
          // Modify the output voltage
          analogWrite(PWM_PIN_Flow, val);
        }
    }
}

// Convert ASCII string to integer value
uint8_t str_to_uint8(char* str, int len)
{
    // Initialize result
    int res = 0;
    //uint8_t res = 0;
 
    // Iterate through input and perform atoi conversion
    for (int i = 0; i < len; ++i)
        res = res * 10 + str[i] - '0';
 
    // Handle overflow and set result
    res = min(res, 255);
    res = max(res, 0);
      
    // return result.
    return res;
}

// Read and parse Serial input
void ReadInput(uint8_t& val, char & prefix)
{
    const int BUFF_SIZE = 4;
    static char buffer[BUFF_SIZE];
  
    memset(buffer, 0, BUFF_SIZE);
    int nbytes = Serial.readBytes(buffer, BUFF_SIZE);
    prefix = buffer[0];
    val = str_to_uint8(buffer+1, nbytes-1);
}
