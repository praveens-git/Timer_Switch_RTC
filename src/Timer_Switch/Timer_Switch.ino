/* Schematics - easyeda.com/praveen.elumalai/timer_switch
   github - github.com/praveens-git/Timer_Switch_RTC/
   
   pin13 - OUTPUT to Relay.
   pin12 - button (optional).
   
   before starting Every thing check whether the day and time is correct.
*/

#include <Wire.h>
#include <RTC.h>

static DS3231 RTC;

int curr_hr, curr_min, curr_sec = 0;

int RunTime = 3; // Please Mention it in Minutes
char Time1[5] = "14:59";
char Time2[5] = "10:20";
char Time3[5] = "14:40";
char Time4[5] = "14:50";

int eh, em = 0;

int t1h, t2h, t3h, t4h, t1m, t2m, t3m, t4m;

const int out = 13;
const int btn = 12;

bool btn_state = false;

void setup()
{
  pinMode(out, OUTPUT);
  pinMode(btn, INPUT_PULLUP);
  digitalWrite(out, LOW);
  Serial.begin(9600);
  RTC.begin();
  getTime();
  getTimers();
  Serial.print(curr_hr);
  Serial.print(":");
  Serial.print(curr_min);
  Serial.print(":");
  Serial.println(curr_sec);
  Serial.println(RTC.isRunning());
}

void getTime() {
  curr_hr = int(RTC.getHours());
  curr_min = int(RTC.getMinutes());
  curr_sec = int(RTC.getSeconds());
}

void getTimers() {
  t1h = (((Time1[0]-'0') * 10) + (Time1[1]-'0'));
  t2h = (((Time2[0]-'0') * 10) + (Time2[1]-'0'));
  t3h = (((Time3[0]-'0') * 10) + (Time3[1]-'0'));
  t4h = (((Time4[0]-'0') * 10) + (Time4[1]-'0'));
  t1m = (((Time1[3]-'0') * 10) + (Time1[4]-'0'));
  t2m = (((Time2[3]-'0') * 10) + (Time2[4]-'0'));
  t3m = (((Time3[3]-'0') * 10) + (Time3[4]-'0'));
  t4m = (((Time4[3]-'0') * 10) + (Time4[4]-'0'));
  Serial.print(t1h);
  Serial.print(" ");
  Serial.print(t2h);
  Serial.print(" ");
  Serial.print(t3h);
  Serial.print(" ");
  Serial.print(t4h);
  Serial.print(" ");
  Serial.print(t1m);
  Serial.print(" ");
  Serial.print(t2m);
  Serial.print(" ");
  Serial.print(t3m);
  Serial.print(" ");
  Serial.println(t4m);

}

void calcEnd() {
  em = curr_min + RunTime;
  eh = curr_hr;
  if (em > 60) {
    em = em - 60;
    eh = eh + 1;
  }
}

void StartDevice() {
  digitalWrite(out, HIGH);
  calcEnd();
  Serial.print(curr_hr);
  Serial.print(":");
  Serial.println(curr_min);
  bool Run = true;
  while (Run) {
    getTime();
    if ((curr_hr == eh) && (curr_min == em)) {
      digitalWrite(out, LOW);
      Run = false;
    }
    delay(500);
  }
  Serial.print(curr_hr);
  Serial.print(":");
  Serial.println(curr_min);
}

void loop() {
  getTime();
  btn_state = !digitalRead(btn);
  if ((curr_hr == t1h) || (curr_hr == t2h) || (curr_hr == t3h) || (curr_hr == t4h) || btn_state) {
    if ((curr_min == t1m) || (curr_min == t2m) || (curr_min == t3m) || (curr_min == t4m) || btn_state) {
      btn_state = false;
      StartDevice();
    }
  }
  delay(500);
}
