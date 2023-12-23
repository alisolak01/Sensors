/*
 * basic_demo.ino
 * Driver for DIGITAL I2C HUMIDITY AND TEMPERATURE SENSOR
 *  
 * Copyright (c) 2018 Seeed Technology Co., Ltd.
 * Website    : www.seeed.cc
 * Author     : downey
 * Create Time: June 2018
 * Change Log :
 *
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "Seeed_LDC1612.h"

LDC1612 sensor(0x2A);


void setup()
{
    Serial.begin(115200);
    delay(100);
    Serial.println("start!");

   // pinMode(2, INPUT);

    //attachInterrupt(digitalPinToInterrupt(2),read_values,RISING);
    

    sensor.init();

    if(sensor.single_channel_config(CHANNEL_1))
    {
        Serial.println("can't detect sensor!");
        while(1);
    }


}


u32 result_channel1=0;




void loop()
{
    
    

    // /*shows the status of sensor.*/
    // //sensor.get_sensor_status();

    // /*Get channel 0 result and parse it.*/
    // sensor.get_channel_result(CHANNEL_1,&result_channel1);

    // /*sensor result value.you can make a lot of application according to its changes.*/
    // // if(0!=result_channel1)
    // // {
    //     Serial.print("result_channel0 is ");
    //     Serial.println(result_channel1);
    // // }
    
    // delay(100);

    // Serial.println(read_values());
    Serial.println(read_values());

    delay(10);

    if(Serial.available() > 1){

    }
    
}

u32 read_values(){
  sensor.get_channel_result(CHANNEL_1, &result_channel1);
  return result_channel1;
}

