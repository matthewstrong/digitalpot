/**
 * Boston Scientific Proprietary
 * Copyright 2020 by Boston Scientific or its affiliates. All rights reserved.
 */

const int PWM_PIN = 9; // OUTPUT Voltage Pin

// Read and parse Serial input
uint8_t ReadInput();
// Convert ASCII string to integer value
uint8_t str_to_uint8(char* str, int len);

void setup()
{
    Serial.setTimeout(10); // 10ms timeout
    Serial.begin(115200);  // Fastest supported speed
    pinMode(PWM_PIN, OUTPUT); // Enable output pin
}

void loop()
{
    if (Serial.available() > 0)
    {
        // Read Serial input
        uint8_t val = ReadInput();
        Serial.println("Input: " + String(val));
        
      	float voltage = 5.0*val/255;
        Serial.println("Output voltage: " + String(voltage, 2));
        
      	// Modify the output voltage
      	analogWrite(PWM_PIN, val);
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
uint8_t ReadInput()
{
    const int BUFF_SIZE = 3;
    static char buffer[BUFF_SIZE];
	
    memset(buffer, 0, BUFF_SIZE);
    int nbytes = Serial.readBytes(buffer, BUFF_SIZE);
    return str_to_uint8(buffer, nbytes);
}
