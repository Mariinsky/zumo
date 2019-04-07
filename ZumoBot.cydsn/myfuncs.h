#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "LSM303D.h"
#include "Motor.h"
#include <stdlib.h>




void startBlink (int ammount, int onTimeMs,int offTimeMs);
/**Starts to blink the blue led on Zumo. Takes in ammount of blinks,
time of led on in ms and delay while the led is swithced off
*/
void startBlink (int ammount, int onTimeMs,int offTimeMs) {
    for (int i = 0; i < ammount; i++){
        BatteryLed_Write(1);
        vTaskDelay(onTimeMs);
        BatteryLed_Write(0);
        vTaskDelay(offTimeMs);
    }
} 

//battery level//
float getBatterVoltage(long runningNumber)
{
    ADC_Battery_Start();        
    int16 adcresult = 0;
    float volts = 0.0;
        
    ADC_Battery_StartConvert(); // start sampling
        if(ADC_Battery_IsEndConversion(ADC_Battery_WAIT_FOR_RESULT)) {   // wait for ADC converted value
            adcresult = ADC_Battery_GetResult16(); // get the ADC value (0 - 4095)
            // convert value to Volts
            // you need to implement the conversion
            volts = adcresult / 546.0;
            printf("\n%li: Battery volatage is: %.2fv", runningNumber, volts);
                 
            return volts;  
         
        }
    return volts;
 }   

// Weeek 2 assignment 2
void askAge() {
    TickType_t xStart, xEnd, xResult;
    int age;
    printf("\nWhat is your age? ");
    xStart = xTaskGetTickCount();
    scanf("%d", &age);
    xEnd = xTaskGetTickCount();
    xResult = xEnd - xStart;
    //printf("It took you %d", xResult);
    if (xResult <= 3000) {
        if(age < 22) {
            printf("Super fast dude!");
        }
        else if(age < 51) {
            printf("be quick or be dead");
        }
         else{
            printf("Still going strong");
        }
    } else if (xResult <= 5000) {
        if(age < 22) {
            printf("Se mdeiocre.");
        }
        else if(age < 51) {
            printf("you\'re so average.");
        }
         else{
            printf("You are doing ok for your age.");
        }
    } else {
        if(age < 22) {
            printf("My granny is faster than you!");
        }
        else if(age < 51) {
            printf("Have you been smoking something illegal?");
        }
         else{
            printf("Do they still allow you to drive?");
        }
    }
}
struct accData_ readAcc (int delay) {
    struct accData_ data;
    LSM303D_Read_Acc(&data);
    vTaskDelay(delay);
    return data;

}
void bumperCar () {
    
      // set speed to zero to stop motors
            
    while(1) {
            struct accData_ data = readAcc(50);
            motor_forward(0,0);
            int x = rand() % 3;
            switch(x) {
                case 0:
                motor_turn(200,150,100);
                break;
                case 1:
                motor_turn(150,200,100);
                break;
                case 2:
                motor_turn(200,198,100);
                break;
            }
                 // moving forward
            if (data.accX < -3000 || data.accY < -3000) {
                motor_forward(0,0);
                motor_backward(100,200);
                int i = rand() % 2;
                if (i==0) {
                    motor_turn(100,0,1200);
                } else { 
                    motor_turn(0,100,1200);
                }
                
            }
                                           
    }
}
//direction 1 turn to left
void motor_hardTurn(int direction,uint8 l_speed, uint8 r_speed, uint32 delay)
{
    switch (direction) {
        case '1': 
        MotorDirLeft_Write(1);     
        MotorDirRight_Write(0);
        break;
        case '2':
        MotorDirLeft_Write(0);     
        MotorDirRight_Write(1);
        break;
    }
    PWM_WriteCompare1(l_speed); 
    PWM_WriteCompare2(r_speed); 
    vTaskDelay(delay);
}
    


