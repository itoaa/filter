// #include <Arduino.h>

#include "Filter.h"
#include <stdio.h>

 Filter MyFilter;
 
void setup() {
 
}

void loop() {
  // put your main code here, to run repeatedly:
}

int main()
{
  MyFilter.addValue(3300);
  MyFilter.addValue(3400);
  MyFilter.addValue(3297);
  MyFilter.addValue(3301);
  MyFilter.addValue(3280);

    printf("Hello World from PlatformIO!\n");
    int16_t i = MyFilter.getAverage();
    printf("%d\n",i);
    printf("Hello World from PlatformIO!\n");
    printf("Hello World from PlatformIO!\n");

    return 0;
}