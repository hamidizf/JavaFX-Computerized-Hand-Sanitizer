JavaFX-Computerized-Hand-Sanitizer

INTRODUCTION:

The goal of this project to create a sanitizer dispenser that works both automatically (depending on data gathered from obstacle avoidance sensor) and manually. It also includes a TFT LCD on which the steps of hand sanitizing will be displayed. 

CONTEXT:

The outbreak of COVID-19 has emphasized the significance of personal hygiene, and the need for an efficient hand sanitization. This project aims to design an automated hand sanitizer dispenser with a TFT LCD display, which guides users through the process of proper hand sanitization, as it is an essential action in protecting against COVID-19.

COMPONENTS LIST:

• Two Arduino Uno boards

• A Servo motor

• An obstacle avoidance sensor

• A TFT LCD

• Jumper wires(male to female)

• A soap container 

PROCEDURE:

Looking at the codes, two programming languages are used in this project, Java and C++.
The code on IntelliJ, which is written in Java, starts by importing some libraries (fazecast has
been downloaded from maven, and related libraries (SDK) have been added to the project
structure initially). Later on, the ports for each of the boards are defined in the primary stage
method. The related buttons, one to control servo and 9 to control the LCD (showing the steps in
the order or each of them separately), are created afterwards. Finally, the code for the live graph
is included. In order to control the automatic system, both outputSreams (outputStream and
outputStream2) should be added to our Datacontroller so they can be used in the package where
we define an if statement to send some bytes to the Arduino IDE in response to the data given by
the sensor (if a hand is detected, Java will send 200 byte values to the Grove beginner kit which
is responsible for the servo motor and 80 byte values to the other board which is responsible for
the LCD in order to applying the sanitizer and showing the images on the display). It is also
noteworthy that I got inspiration from labH and labI for coding of this part.

Two source codes1,2 have been used and modified for Arduino coding. Since two separate
boards are connected to the laptop, it is needed to open two separate Arduino programs where
each control one of the boards. On the one connected to Grove beginner board, the code for the
servo motor is written. That is where the sensor gathers data(using digitalread function which is
faster and less accurate compared to analogread) and sends them to IntelliJ. IntelliJ uses the data
for the live graph and also sends byte values back to the Arduino if it is needed (if the button for 
the servo is pressed or a hand is detected). By receiving specific byte values, Arduino orders the
motor to rotate.

Second Arduino contains the code for the LCD. Based on the modifications, when
the byte value received from java is 101 or 80, the LCD starts to display images in the
order (images exist on a SD card connected to the LCD). Additionally, some if statements
have been defined so that if a button related to an image is pressed on IntelliJ, the TFT
display shows that image. For instance, if button number 6 is pressed, the LCD will
display the 6th step of hand sanitizing, or if the button Start is pressed, the LCD starts
showing all the steps in the order.

Recourses:

1. Dmf313.ir. Published 2016. Accessed April 13, 2021.
https://dmf313.ir/%D9%BE%D8%B1%D9%88%DA%98%D9%87-%D8%A2%D9%85%D9%88%D8%B2%D8%B4-%D8%B1%D8%A7%D9%87-%D8%A7%D9%86%D8%AF%D8%A7%D8%B2%DB%8C-lcd-tft-2-4-inch-%D8%A8%D8%A7-%D8%A2%D8%B1%D8%AF%D9%88%DB%8C%D9%86%D9%88/

2. Viral Dodhia. Arduino Automatic Soap Dispenser. Viral Science. Published March 21, 2020.
Accessed April 13, 2021. https://www.viralsciencecreativity.com/post/arduino-automatic-soapdispenser

3. Eric Prandovszky • Laboratory Technologist
Department of Electrical Engineering and Computer Science
Lassonde School of Engineering
