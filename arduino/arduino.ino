  #include <Adafruit_NeoPixel.h>
#define MAX_VAL 64  // 0 to 255 for brightness
#define DELAY_TIME 50 
#define DELAY_TIME2 20
 
// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(100, 6, NEO_GRB + NEO_KHZ800);
 
void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  
  Serial.begin(9600);
  Serial.print("Start");
}

String s = "";
String rs = "", gs = "", bs = "";
boolean sf = false, rf = false, gf = false;
void loop() {
  if (Serial.available() > 0) {
    char c = Serial.read();
    Serial.print(c);
    if (c == '\n') {
      if (s == "0") {
        colorWipe(strip.Color(0, 0, 0), DELAY_TIME); // Black
      } else {
        int r = rs.toInt();
        int g = gs.toInt();
        int b = bs.toInt();
        colorWipe(strip.Color(r, g, b), DELAY_TIME);
      }
      
      s = "";
      rs = "";
      gs = "";
      bs = "";
      sf = false;
      rf = false;
      gf = false;
    } else if (c == ',') {
      if (!sf) sf = true;
      else if (!rf) rf = true;
      else if (!gf) gf = true;
    } else {
      if (!sf) s += c;
      else if (!rf) rs += c;
      else if (!gf) gs += c;
      else bs += c;
    }
  }
  
}
 
// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      //strip.show();
      //delay(wait);
  }
  strip.show();
}
