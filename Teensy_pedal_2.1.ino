float mapf(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

float MaxFuzz[17] = { -1.000, -1.000, -1.000, -1.000, -1.000, -1.000, -1.000, -1.000, 0.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000, 1.000 };
float MinFuzz[17] = { -1.000, -0.875, -0.750, -0.625, -0.500, -0.375, -0.250, -0.125, 0.000, 0.125, 0.250, 0.375, 0.500, 0.625, 0.750, 0.875, 1.000 };
int bCount = 0;
bool LbState = 0;

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S            i2s1;           //xy=78,181
AudioAmplifier           amp1;           //xy=196,181
AudioSynthWaveformSine   sine1;          //xy=196,219
AudioEffectMultiply      multiply1;      //xy=351,198
AudioEffectFreeverb      freeverb1;      //xy=352,230
AudioEffectDigitalCombine combine1;       //xy=353,262
AudioEffectWaveshaper    waveshape1;     //xy=363,166
AudioMixer4              mixer1; //xy=510,214
AudioFilterStateVariable filter2;        //xy=656,221
AudioFilterStateVariable filter3;        //xy=656,267
AudioFilterStateVariable filter1;        //xy=657,175
AudioMixer4              mixer2;         //xy=793,228
AudioAmplifier           amp2; //xy=913,228
AudioOutputI2S           i2s2;           //xy=1031,228
AudioConnection          patchCord1(i2s1, 0, amp1, 0);
AudioConnection          patchCord2(amp1, waveshape1);
AudioConnection          patchCord3(amp1, freeverb1);
AudioConnection          patchCord4(amp1, 0, multiply1, 0);
AudioConnection          patchCord5(amp1, 0, combine1, 0);
AudioConnection          patchCord6(sine1, 0, multiply1, 1);
AudioConnection          patchCord7(sine1, 0, combine1, 1);
AudioConnection          patchCord8(multiply1, 0, mixer1, 1);
AudioConnection          patchCord9(freeverb1, 0, mixer1, 2);
AudioConnection          patchCord10(combine1, 0, mixer1, 3);
AudioConnection          patchCord11(waveshape1, 0, mixer1, 0);
AudioConnection          patchCord12(mixer1, 0, filter1, 0);
AudioConnection          patchCord13(mixer1, 0, filter2, 0);
AudioConnection          patchCord14(mixer1, 0, filter3, 0);
AudioConnection          patchCord15(filter2, 1, mixer2, 1);
AudioConnection          patchCord16(filter3, 2, mixer2, 2);
AudioConnection          patchCord17(filter1, 0, mixer2, 0);
AudioConnection          patchCord18(mixer2, amp2);
AudioConnection          patchCord19(amp2, 0, i2s2, 0);
AudioControlSGTL5000     sgtl5000_1;     //xy=517,154
// GUItool: end automatically generated code

const int myInput = AUDIO_INPUT_LINEIN;

void setup() {
  AudioMemory(1024);
  sgtl5000_1.enable();
  sgtl5000_1.inputSelect(myInput);
  sgtl5000_1.volume(1);
  Serial.begin(9600);
}

void loop() {
  float vol = mapf(analogRead(15), 0, 1023, 0, 2);
  float low = mapf(analogRead(14), 0, 1023, 0, 1);
  float mid = mapf(analogRead(16), 0, 1023, 0, 1);
  float hi = mapf(analogRead(17), 0, 1023, 0, 1);
  float var = mapf(analogRead(22), 0, 1023, 0, 1);

  amp1.gain(vol);
  amp2.gain(vol);

  filter1.frequency(200); 
  mixer2.gain(0, low);     

  filter2.frequency(1000); 
  mixer2.gain(1, mid);    

  filter3.frequency(3000); 
  mixer2.gain(2, hi);     

  Serial.print(" ║ ");
  Serial.print("Volume: ");
  Serial.print(vol);
  Serial.print(" ║ ");
  Serial.print("Bass: ");
  Serial.print(low);
  Serial.print(" ║ ");
  Serial.print("Middle: ");
  Serial.print(mid);
  Serial.print(" ║ ");
  Serial.print("Trebble: ");
  Serial.print(hi);
  Serial.print(" ║ ");
  Serial.print("Variable: ");
  Serial.print(var);
  Serial.print(" ║ ");
  Serial.print("Mode:");
  Serial.print(bCount);
  Serial.print(" ║ ");

  /*bool bState = digitalRead(2);          
    if(bState != LbState){
      bCount++;   
    }*/
  bCount = 0;

  switch (bCount) {
    case 0:  // Fuzz // Fuzz // Fuzz // Fuzz // Fuzz // Fuzz // Fuzz // Fuzz // Fuzz // Fuzz // Fuzz // Fuzz // Fuzz // Fuzz // Fuzz // Fuzz // Fuzz // Fuzz // Fuzz //
      mixer1.gain(0, 1);
      mixer1.gain(1, 0);
      mixer1.gain(2, 0);
      mixer1.gain(3, 0);

      float Fuzz[17];
      Serial.print("Fuzz: ");

      for (int i = 0; i < 17; i++) {
        Fuzz[i] = mapf(var, 0, 1, MinFuzz[i], MaxFuzz[i]);
        Serial.print(Fuzz[i]);
        Serial.print(" ");
      }
      
      waveshape1.shape(Fuzz, 17);
      Serial.println("║ ");

    break;
    
    case 1:  // Vibrato // Vibrato // Vibrato // Vibrato // Vibrato // Vibrato // Vibrato // Vibrato // Vibrato // Vibrato // Vibrato // Vibrato // Vibrato // Vibrato // 
      mixer1.gain(0, 0);
      mixer1.gain(1, 1);
      mixer1.gain(2, 0);
      mixer1.gain(3, 0);

      sine1.amplitude(0.25);
      sine1.frequency(var * 10);
      Serial.println(" ║ ");

    break;

    case 2: // Delay // Delay // Delay // Delay // Delay // Delay // Delay // Delay // Delay // Delay // Delay // Delay // Delay // Delay // Delay // Delay // Delay 
    mixer1.gain(0, 0);
    mixer1.gain(1, 0);
    mixer1.gain(2, 1);
    mixer1.gain(3, 0);

    delay1.delay(0, 0);
    delay1.delay(0, var * 500);
    delay1.delay(1, var * 1000);
    delay1.delay(2, var * 1500);

    Serial.print("Delay: "); Serial.print(var * 500); Serial.println(" ║ ");

    case 3: // Boolean // Boolean // Boolean // Boolean // Boolean // Boolean // Boolean // Boolean // Boolean // Boolean // Boolean // Boolean // Boolean // Boolean //
      mixer1.gain(0, 0);
      mixer1.gain(1, 0);
      mixer1.gain(2, 0);
      mixer1.gain(3, 1);

      setCombineMode(AudioEffectDigitalCombine::XOR);
      sine1.amplitude(1);
      sine1.frequency(var * 50);
  
      Serial.println(" ║ ");

    break;
  }


}