

/* the ideal is we use 2 sensor to identify whether the babys are or not in the cradle
 *  Although we can use 2 to measure the frequency of baby motion, but because of the limitation of device, we just need to use one and apply some simple mathematic method but it get acceptable result.
 *  To determine if the baby wakes up
 *  + apply convolution to get better data
 *  + take data into a array of data that called Window
 *  + processing array 
 *  + analys data ( the ideal is just calculate the number of vibration in a time interval and compine with the value of time, we can guess the baby are awake or not)
 *  

*/

#define trig 4
#define echo 3
#define baby_wake 7
#define PIR 6
#define start_servo 5

bool PIR_read=0;
float U[3]={0,0,0}; // threshold filter convolution
float UMean[5]={0,0,0,0,0}; // mean value convolution

const int len = 255; // should be 2^n , example: 2, 4, 8, 16, 32, ...

float Window[len]; // create a window
int stepW = len/2; // step window, means that after 50 times update new data, the array will be putted into 

bool baby_in_cradle = false;

float D;
int count; // number of wave pulse appear in 

void setup() {
  Serial.begin(9600);
  // set up for U
    for (int i=0; i<3; i++)
  {
    U[i]=0.0;
  }
    for (int i=0; i<5; i++)
  {
    UMean[i]=0;
  }
   // set the initial value for Window
    for (int i=0; i<len; i++)
  {
    Window[i]=0.0;
  }

  // put your setup code here, to run once:
  pinMode(baby_wake,OUTPUT); 
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  pinMode(PIR,INPUT);
  pinMode(start_servo,OUTPUT);
  Serial.println("Start");

}

// FUNCTION



// read input from hcsro4 
float ReadDistance()
{
  int distance;           // biến lưu khoảng cách
  digitalWrite(trig,0);   // tắt chân trig
  delayMicroseconds(2);
  digitalWrite(trig,1);   // phát xung từ chân trig
  delayMicroseconds(5);   // xung có độ dài 5 microSeconds // tần số 5Hz
  digitalWrite(trig,0);   // tắt chân trig
  float duration = pulseIn(echo,HIGH); 
  distance = int(duration/2/29.412);
  return distance;
}

// update window 
void updateNewData(){
     D = ReadDistance();
     D = MedianConvolution(D);
     D = MeanConvolution(D);

}
void stepper() 
{
  int i = 0;

  for (int k=0; k<20; k++){ // filter the 35 first data in that disturbed
    updateNewData();
  }

  while (i<len)
  {
//    Serial.println("Start loop");
    updateNewData();
    delayMicroseconds(10000);
//  Serial.println(D);
    Window[i]=D;
    i++;
//    Serial.println(i);
  }
}
void PrintWindow()
{
   for (int i =0; i<len; i++)
  {
    if ((i+1)%10==0){Serial.print(Window[i]); Serial.println(",");}
    else
    {
      Serial.print(Window[i]);
      Serial.print(", ");
    }
  }
}
// convolution for the input data
float MedianConvolution(float distance) // just apply for U[3]
{
  
  for (int i=0; i<2; i++)
  {
    U[i]=U[i+1];
  }
  
  U[2]=distance;
 
  float max = U[1];
  float min = U[2];
  for (int i=0; i<3; i++)
  {
    if (U[i]>max){max=U[i];}
    if (U[i]<min){min=U[i];}
  }
    for (int i=0; i<3; i++)
  {
    if ((U[i]!=max)&&(U[i]!=min))
    {
      return U[i];
    }
  }
}

float MeanConvolution(float d)
{
    
  for (int i=0; i<4; i++)
  {
    UMean[i]=UMean[i+1];
  }
  UMean[4] = d;
  float SUM=0;
    for (int i=0; i<5; i++)
  {
    SUM+=UMean[i];
  }
  return SUM/5;
  
}


// Analysis data 

int counting(int Up_threshold, int Bottom_threshold){
  float Delta;
  int c=0;
  for (int i= 11; i<len; i++)
  {
    Delta = abs(Window[i]-Window[i-1])/Window[i]*100;
    
    if ((Delta<=Up_threshold)&&(Delta>=Bottom_threshold)) { c++; } 
    else if (Window[i]> 90) {
      baby_in_cradle = digitalRead(PIR);  //to ensure the moving object is baby
      if (baby_in_cradle==1){ 
        baby_in_cradle=0;
        digitalWrite(start_servo,LOW);}
      else if (baby_in_cradle==0){
        baby_in_cradle=1;
        digitalWrite(start_servo,HIGH);}
        
      }
  }
  return c/2; 
}

void loop() {

    count =0;
    for (int i=0; i<4; i++)
    {
      stepper();
      PrintWindow();
      count += counting(20,10);
      Serial.println();
      Serial.print("count =");
      Serial.println(count);
      Serial.println();
    }
    Serial.print("count =");
    Serial.println(count);
     
    if (count > 15){ 
     digitalWrite(baby_wake,HIGH);
     delay(1000);
     digitalWrite(baby_wake,LOW);
     }
    delay(5000);
    Serial.println();
    Serial.println();
    

}
