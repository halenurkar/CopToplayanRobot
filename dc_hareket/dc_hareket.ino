  #include <VarSpeedServo.h> 
VarSpeedServo myservo;    // create servo object to control a servo 
VarSpeedServo lservo;
VarSpeedServo rservo;

#define echoPin 7 
#define trigPin 6 
 
#define MotorR1 9
#define MotorR2 10
#define MotorRE 3  
#define MotorL1 11
#define MotorL2 12
#define MotorLE 5
int sure=0, uzaklik=0; //süre ve uzaklık diye iki değişken tanımlıyoruz.
 char r;
void setup() {
  myservo.attach(2);  // attaches the servo on pin 9 to the servo object
  lservo.attach(4);
  rservo.attach(13);

  // ultrasonik sensör Trig pininden ses dalgaları gönderdiği için OUTPUT (Çıkış),
  // bu dalgaları Echo pini ile geri aldığı için INPUT (Giriş) olarak tanımlanır.
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);

  pinMode(MotorL1, OUTPUT);
  pinMode(MotorL2, OUTPUT);
  pinMode(MotorLE, OUTPUT); //Motorlarımızı çıkış olarak tanımlıyoruz.
  pinMode(MotorR1, OUTPUT);
  pinMode(MotorR2, OUTPUT);
  pinMode(MotorRE, OUTPUT);


  Serial.begin(9600);

}

void loop() {


 // digitalWrite(trigPin, LOW); //sensör pasif hale getirildi
 // delayMicroseconds(5);
  digitalWrite(trigPin, HIGH); //Sensore ses dalgasının üretmesi için emir verildi
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW); //Yeni dalgaların üretilmemesi için trig pini LOW konumuna getirildi

  sure = pulseIn(echoPin, HIGH); //ses dalgasının geri dönmesi için geçen sure ölçülüyor
  uzaklik = sure / 29.1 / 2; //ölçülen süre uzaklığa çevriliyor

  //Serial.println(uzaklik);
   int h=0;
  if (uzaklik < 17) // Uzaklık 17'den küçük ise,
  {
    dur();
    delay(3000); 
    // h=1;
    //Serial.println(h);
      r=Serial.read();
      Serial.println(r);
   // delay(100);

      if(Serial.available())
        {
          r=Serial.read();
            if(r==1)
             {
               //delay(100);
               servo();
               delay(5000); 
              }
          
         }
    
     // Serial.println('1');
     
      
      //delay(3000);
     
    
    geri();  // 150 ms geri git
    delay(150);
    sag();  // 250 ms sağa dön
    delay(250);
   

 //  dur();
  }
  else {  // değil ise
   // h=0;
   // Serial.println(h);
    ileri(); // ileri git
  }

}

void servo(){
   //  dur();
  //  delay(2000);
    myservo.write(100, 30, true); // move to 180 degrees, use a speed of 30, wait until move is complete
    myservo.write(0, 30, true);

    delay(1000);
  
    lservo.write(90, 60, true);
    rservo.write(0, 60, true);
 //  delay(50);
   
     lservo.write(0, 60, true);
     rservo.write(90, 60, true);
    
   // delay(50);
    myservo.write(0, 70, true);
    myservo.write(100, 70, true);
     
   /*  dur();
    delay(3000); 
    geri();  // 150 ms geri git
    delay(150);
    sag();  // 250 ms sağa dön
    delay(250); 
  */
  
  }

void ileri(){  // Robotun ileri yönde hareketi için fonksiyon tanımlıyoruz.

  digitalWrite(MotorR1, HIGH); // Sağ motorun ileri hareketi aktif
  digitalWrite(MotorR2, LOW); // Sağ motorun geri hareketi pasif
  analogWrite(MotorRE, 120); // Sağ motorun hızı 120

  digitalWrite(MotorL1, LOW); // Sol motorun ileri hareketi aktif
  digitalWrite(MotorL2, HIGH); // Sol motorun geri hareketi pasif
  analogWrite(MotorLE, 120); // Sol motorun hızı 120
  
  
}


void sol(){ // Robotun sağa dönme hareketi için fonksiyon tanımlıyoruz.

  digitalWrite(MotorR1, HIGH); // Sağ motorun ileri hareketi aktif
  digitalWrite(MotorR2, LOW); // Sağ motorun geri hareketi pasif
  analogWrite(MotorRE, 0); // Sağ motorun hızı 0 (Motor duruyor)

  digitalWrite(MotorL1, HIGH); // Sol motorun ileri hareketi aktif
  digitalWrite(MotorL2, LOW); // Sol motorun geri hareketi pasif
  analogWrite(MotorLE, 150); // Sol motorun hızı 150
  
  
}


void sag(){ // Robotun sola dönme hareketi için fonksiyon tanımlıyoruz.

  digitalWrite(MotorL1, LOW); 
  digitalWrite(MotorL2, HIGH); 
  analogWrite(MotorLE, 150); 

  digitalWrite(MotorR1, LOW); 
  digitalWrite(MotorR2, HIGH); 
  analogWrite(MotorRE, 0);
  
  
}

void dur(){ // Robotun geri yönde hareketi için fonksiyon tanımlıyoruz.

  digitalWrite(MotorR1, LOW); // Sağ motorun ileri hareketi pasif
  digitalWrite(MotorR2, LOW); 
  analogWrite(MotorRE, 0); // Sağ motorun hızı 0

  digitalWrite(MotorL1, LOW); // Sol motorun ileri hareketi pasif
  digitalWrite(MotorL2, LOW); // Sol motorun geri hareketi aktif
  analogWrite(MotorLE, 0); // Sol motorun hızı 150
  
}


void geri(){ // Robotun geri yönde hareketi için fonksiyon tanımlıyoruz.

  digitalWrite(MotorR1, LOW); // Sağ motorun ileri hareketi pasif
  digitalWrite(MotorR2, HIGH); // Sağ motorun geri hareketi aktif
  analogWrite(MotorRE, 150); // Sağ motorun hızı 150

  digitalWrite(MotorL1, HIGH); // Sol motorun ileri hareketi pasif
  digitalWrite(MotorL2, LOW); // Sol motorun geri hareketi aktif
  analogWrite(MotorLE, 150); // Sol motorun hızı 150
  
}
