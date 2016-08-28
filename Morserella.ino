/* Sensorous event at IIT,Kharagpur

Circuit:
 *Arduino Uno
 *2 Servo motors
 *IR Sensor
 *Dual H-Bridge Stepper motor driver
 *Motor IC L293D
 *Supply
 
 created 28 August 2016
 by Shivanjan Chakravorty(The Glitch)
 modified 28 August 2016
 by Shivanjan Chakravorty(The Glitch)
 
 Facebook: @fb/luckysolitaireking
 Github: github.com/Glitchfix
 LinkedIn: in.linkedin.com/in/shivanjan-chakravorty
 E-Mail: schakravorty846@gmail.com
 Phone no.: +91-96-58-965891
*/
int mlA = 5;//Motor 1 Forward for HIGH
int mlB = 6;//Motor 1 Reverse for HIGH
int mrA = 7;//Motor 2 Forward for HIGH
int mrB = 8;//Motor 2 Reverse for HIGH
/*int A0=A0;//Leftmost IR Sensor
int A1=A1;//Left IR Sensor
int A2=A2;//Middle IR Sensor
int A3=A3;//Right IR Sensor
int A4=A3;//Rightmost IR Sensor*/
int senW = 1;//West IR Sensor
int senE= 2;//East IR Sesor
int senS= 3;//South IR Sensor

int senMO=12;//Morse sensor

int x=7;//RUN MODE BUTTON
int i=1;
int ls,l,m,r,rs,w,e,s;
int count=0;

void setup()
{
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(senW, INPUT);
  pinMode(senE, INPUT);
  pinMode(senS, INPUT);
  
  pinMode(mrA, OUTPUT);
  pinMode(mrB, OUTPUT);
  pinMode(mlA, OUTPUT);
  pinMode(mlB, OUTPUT);
}

void loop()
{
  ls=digitalRead(A0);
  l=digitalRead(A1);
  m=digitalRead(A2);
  r=digitalRead(A3);
  rs=digitalRead(A4);
  w=digitalRead(senW);
  e=digitalRead(senE);
  s=digitalRead(senS);
  
  if(m==1&&w==1&&s==1&&w==1)
  {
    int c=0;
    while(c==0)
    {
      c=re_morse();
    }
    travel(c);
  }
  else
  {
    if(ls==0&&l==1&&m==1&&r==0&&rs==0||ls==0&&l==1&&m==0&&r==0&&rs==0)
    {
      left();
    }
    else if(ls==0&&l==0&m==1&&r==1&&rs==0||ls==0&&l==0&m==0&&r==1&&rs==0)
    {
      right();
    }
    else if(ls==1&&l==1&&m==1&&r==0&&rs==0||ls==1&&l==1&&m==0&&r==0&&rs==0||ls==1&&l==0&&m==0&&r==0&&rs==0)
    {
      while((ls!=0&&l!=0&&m!=1&&r!=0&&rs!=0)||(ls!=0&&l!=1&&m!=1&&r!=0&&rs!=0)||(ls!=0&&l!=1&&m!=0&&r!=0&&rs!=0))
      {
        ls=digitalRead(A0);
        l=digitalRead(A1);
        m=digitalRead(A2);
        r=digitalRead(A3);
        rs=digitalRead(A4);
        sleft();
      }
    }
    else if(ls==0&&l==0&&m==1&&r==1&&rs==1||ls==0&&l==0&&m==0&&r==1&&rs==1||ls==0&&l==0&&m==0&&r==0&&rs==1)
    {
      while((ls!=0&&l!=0&&m!=1&&r!=0&&rs!=0)||(ls!=0&&l!=0&&m!=1&&r!=1&&rs!=0)||(ls!=0&&l!=0&&m!=0&&r!=1&&rs!=0))
      {
        ls=digitalRead(A0);
        l=digitalRead(A1);
        m=digitalRead(A2);
        r=digitalRead(A3);
        rs=digitalRead(A4);
        sright();
      }
    }
    else
    {
      fwd();
    }
  }
}

/*Morse*/
int re_morse()
{
  int a[8]={0,0,0,0,0,0,0,0};
  int mo,mx;
  
  for(int indx=0;indx<8;indx++)
  {
    mo=pulseIn(senMO,HIGH);
    a[0]=mo;
  }
  mx=a[0];
  for(int indx=1;indx<8;indx++)
  {
    if(mx<a[indx])
    {
      mx=a[indx];
    }
  }
  if(mx==a[0])
  {
    return 3;
  }
  else if(mx==a[2])
  {
    return 4;
  }
  else
  {
    if(mx==a[1]&&mx==a[5])
    {
      return 1;
    }
    else if(mx==a[1]&&mx==a[4])
    {
      return 2;
    }
    else
    {
      return 0;
    }
  }
}

/*MOVEMENT*/
void fwd()
{
    digitalWrite(mrA, HIGH);
    digitalWrite(mrB, LOW);
    digitalWrite(mlA, HIGH);
    digitalWrite(mlB, LOW);
}
void stop()
{
    digitalWrite(mrA, LOW);
    digitalWrite(mrB, LOW);
    digitalWrite(mlA, LOW);
    digitalWrite(mlB, LOW);
}
void left()
{
    digitalWrite(mrA, LOW);
    digitalWrite(mrB, LOW);
    digitalWrite(mlA, HIGH);
    digitalWrite(mlB, LOW);
}
void sleft()
{
    digitalWrite(mrA, LOW);
    digitalWrite(mrB, HIGH);
    digitalWrite(mlA, HIGH);
    digitalWrite(mlB, LOW);
}
void right()
{
    digitalWrite(mrA, HIGH); 
    digitalWrite(mrB, LOW);
    digitalWrite(mlA, LOW);
    digitalWrite(mlB, LOW);
}
void sright()
{
    digitalWrite(mrA, HIGH); 
    digitalWrite(mrB, LOW);
    digitalWrite(mlA, LOW);
    digitalWrite(mlB, HIGH);
}

void travel(int x)
{
  if(x==1)
  {
    sleft();
    delay(200);
    fwd();
    delay(100);
  }
  else if(x==2)
  {
    sright();
    delay(200);
    fwd();
    delay(100);
  }
  else if(x==3)
  {
    sleft();
    delay(400);
    fwd();
    delay(100);
  }
  else
  {
    fwd();
    delay(150);
  }
}

