#include <SPI.h>
#include <SD.h>
#define SD_CS 10
#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
//(int CS=A3, int RS=A2, int WR=A1, int RD=A0, int RST=A4)
MCUFRIEND_kbv tft(A3, A2, A1, A0, A4);
#define BLACK 0x0000
#define NAVY 0x000F
#define DARKGREEN 0x03E0
#define DARKCYAN 0x03EF
#define MAROON 0x7800
#define PURPLE 0x780F
#define OLIVE 0x7BE0
#define LIGHTGREY 0xC618
#define DARKGREY 0x7BEF
#define BLUE 0x001F
#define GREEN 0x07E0
#define CYAN 0x07FF
#define RED 0xF800
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF
#define ORANGE 0xFD20
#define GREENYELLOW 0xAFE5
#define PINK 0xF81F
void setup() {
  Serial.begin(9600);
 tft.reset();
 uint16_t identifier = tft.readID();
 tft.begin(0x9340);
if (!SD.begin(SD_CS)) {
 return;
 }

 tft.reset();
 uint16_t Identifier = tft.readID();
 if (Identifier == 0xEFEF) Identifier = 0x9341;
 tft.begin(Identifier);
}
void loop() {
 const auto receivedData = Serial.read();

 if ((receivedData==101)||(receivedData==80)){ // if hand is detected pr the button is pressed show steps
Steps();
 }
 else{
  FirstImage(); //show the first image
 }
 if(receivedData==100){ // if button 1 is pressed show first image
    tft.setRotation(1);
 ShowBMP24BIT("1.bmp", 0, 0);
  delay(1000);
 }
 if(receivedData==99){// if button 2 is pressed show 2nd image
  tft.setRotation(1);
 ShowBMP24BIT("2.bmp", 0, 0);
 delay(500);
 }
 if(receivedData==98){// if button 3 is pressed show 3rd image
  tft.setRotation(1);
 ShowBMP24BIT("3.bmp", 0, 0);
  delay(1000);
 }
 if(receivedData==121){// if button 4 is pressed show 4th image
  tft.setRotation(1);
 ShowBMP24BIT("4.bmp", 0, 0);
  delay(1000);
 }
  if(receivedData==102){
  tft.setRotation(1);
 ShowBMP24BIT("5.bmp", 0, 0);
  delay(1000);
 }
  if(receivedData==103){
  tft.setRotation(1);
 ShowBMP24BIT("6.bmp", 0, 0);
  delay(1000);
 }
  if(receivedData==104){
  tft.setRotation(1);
 ShowBMP24BIT("7.bmp", 0, 0);
  delay(1000);
 }
  if(receivedData==105){
  tft.setRotation(1);
 ShowBMP24BIT("8.bmp", 0, 0);
  delay(1000);
 }
 
 

}

void Steps() {
  tft.setRotation(1);

 ShowBMP24BIT("2.bmp", 0, 0);
delay(1500);
 ShowBMP24BIT("3.bmp", 0, 0);
delay(1500);
 ShowBMP24BIT("4.bmp", 0, 0);
delay(1500);
 ShowBMP24BIT("5.bmp", 0, 0);
 delay(1500);
 ShowBMP24BIT("6.bmp", 0, 0);
  delay(1500);
  ShowBMP24BIT("7.bmp", 0, 0);
 delay(1500);
  ShowBMP24BIT("8.bmp", 0, 0);
 delay(1500);
}
void FirstImage() {
tft.setRotation(1);
 ShowBMP24BIT("1.bmp", 0, 0);

}
  

void ShowBMP24BIT(char *filename, int x, int y) {
 File bmpFile;
 int bmpWidth, bmpHeight; // W+H in pixels
 uint8_t bmpDepth; // Bit depth (currently must be 24)
 uint32_t bmpImageoffset; // Start of image data in file
 uint32_t rowSize; // Not always = bmpWidth; may have padding
 uint8_t sdbuffer[60]; // pixel in buffer (R+G+B per pixel)
 uint16_t lcdbuffer[20]; // pixel out buffer (16-bit per pixel)
 uint8_t buffidx = sizeof(sdbuffer); // Current position in sdbuffer
 boolean goodBmp = false; // Set to true on valid header parse
 boolean flip = true; // BMP is stored bottom-to-top
 int w, h, row, col;
 uint8_t r, g, b;
 uint32_t pos = 0, startTime = millis();
 uint8_t lcdidx = 0;
 boolean first = true;
 uint32_t DataShow;
 if ((x >= tft.width()) || (y >= tft.height())) return;
 //Serial.println();
 //Serial.print(F("Loading image '"));
 //Serial.print(filename);
 //Serial.println('\'');
 // Open requested file on SD card
 if ((bmpFile = SD.open(filename)) == NULL) {
 //Serial.println(F("File not found"));
 return;
 }
 // Parse BMP header
 if (read16(bmpFile) == 0x4D42) { // BMP signature
 DataShow = read32(bmpFile);
 //Serial.println(F("File size: ")); Serial.println(DataShow);
 (void)read32(bmpFile); // Read & ignore creator bytes
 bmpImageoffset = read32(bmpFile); // Start of image data
 //Serial.print(F("Image Offset: ")); Serial.println(bmpImageoffset, DEC);
 // Read DIB header
 DataShow = read32(bmpFile);
 //Serial.print(F("Header size: ")); Serial.println(DataShow);
 bmpWidth = read32(bmpFile);
 bmpHeight = read32(bmpFile);
 if (read16(bmpFile) == 1) { // # planes -- must be '1'
 bmpDepth = read16(bmpFile); // bits per pixel
 //Serial.print(F("Bit Depth: ")); Serial.println(bmpDepth);
 if ((bmpDepth == 24) && (read32(bmpFile) == 0)) { // 0 = uncompressed
 goodBmp = true; // Supported BMP format -- proceed!
 //Serial.print(F("Image size: "));
 //Serial.print(bmpWidth);
 //Serial.print('x');
 //Serial.println(bmpHeight);
 // BMP rows are padded (if needed) to 4-byte boundary
 rowSize = (bmpWidth * 3 + 3) & ~3;
 // If bmpHeight is negative, image is in top-down order.
 // This is not canon but has been observed in the wild.
 if (bmpHeight < 0) {
 bmpHeight = -bmpHeight;
 flip = false;
 }
 // Crop area to be loaded
 w = bmpWidth;
 h = bmpHeight;
 if ((x + w - 1) >= tft.width()) w = tft.width() - x;
 if ((y + h - 1) >= tft.height()) h = tft.height() - y;
 // Set TFT address window to clipped image bounds
 tft.setAddrWindow(x, y, x + w - 1, y + h - 1);
 for (row = 0; row < h; row++) { // For each scanline...
 // Seek to start of scan line. It might seem labor-
 // intensive to be doing this on every line, but this
 // method covers a lot of gritty details like cropping
 // and scanline padding. Also, the seek only takes
 // place if the file position actually needs to change
 // (avoids a lot of cluster math in SD library).
 if (flip) // Bitmap is stored bottom-to-top order (normal BMP)
 pos = bmpImageoffset + (bmpHeight - 1 - row) * rowSize;
 else // Bitmap is stored top-to-bottom
 pos = bmpImageoffset + row * rowSize;
 if (bmpFile.position() != pos) { // Need seek?
 bmpFile.seek(pos);
 buffidx = sizeof(sdbuffer); // Force buffer reload
 }
 for (col = 0; col < w; col++) { // For each column...
 // Time to read more pixel data?
 if (buffidx >= sizeof(sdbuffer)) { // Indeed
 // Push LCD buffer to the display first
 if (lcdidx > 0) {
 tft.pushColors(lcdbuffer, lcdidx, first);
 lcdidx = 0;
 first = false;
 }
 bmpFile.read(sdbuffer, sizeof(sdbuffer));
 buffidx = 0; // Set index to beginning
 }
 // Convert pixel from BMP to TFT format
 b = sdbuffer[buffidx++];
 g = sdbuffer[buffidx++];
 r = sdbuffer[buffidx++];
 lcdbuffer[lcdidx++] = tft.color565(r, g, b);
 } // end pixel
 } // end scanline
 // Write any remaining data to LCD
 if (lcdidx > 0) {
 tft.pushColors(lcdbuffer, lcdidx, first);
 }
 //Serial.print(F("Loaded in "));
 //Serial.print(millis() - startTime);
 //Serial.println(" ms");
 } // end goodBmp
 }
 }
 bmpFile.close();
 //if (!goodBmp) Serial.println(F("BMP format not recognized."));
}
uint16_t read16(File f) {
 uint16_t result;
 ((uint8_t *)&result)[0] = f.read(); // LSB
 ((uint8_t *)&result)[1] = f.read(); // MSB
 return result;
}
uint32_t read32(File f) {
 uint32_t result;
 ((uint8_t *)&result)[0] = f.read(); // LSB
 ((uint8_t *)&result)[1] = f.read();
 ((uint8_t *)&result)[2] = f.read();
 ((uint8_t *)&result)[3] = f.read(); // MSB
 return result;
}
