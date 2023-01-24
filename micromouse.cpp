#define rr 8
#define r 3
#define m 4
#define l 5
#define ll 7

#define l2 6
#define l1 9
#define r1 10
#define r2 11

#define led 13

int SPEED = 220;
int medium = 200;
int RR,R,M,L,LL;


void setup() {
  Serial.begin(9600);
  pinMode(ll,INPUT);
  pinMode(l,INPUT);
  pinMode(m,INPUT);
  pinMode(r,INPUT);
  pinMode(rr,INPUT);

  pinMode(l1, OUTPUT);
  pinMode(l2, OUTPUT);
  pinMode(r1, OUTPUT);
  pinMode(r2, OUTPUT);

  pinMode(led, OUTPUT);
}



void loop() {
  update();
  if(LL==1 && L==1 && M==0 && R==1 && RR==1){
     move();
     digitalWrite(led,HIGH);
  }

  else if(R==0 || L==0){
      digitalWrite(led,LOW);
      move();
      delay(1);
      update();
      
      if(R==0){
        if(RR==1){
          correctRight(medium);
        }
        else if(M==0){
          if(L==1){
              //Right or right&forward turn detectedd
              moveBitForward();
    //          update();
              if(M==0){
                show("Forward path with right turn detected");
                //forward path with right turn
                
              }
              else{
                //only right turn
                show("Only right turn detected");
                
              }
              turnRight();
              
          }
          else{
            //both right and left turns detected, need to check if there is forward path as well
            moveBitForward();
            if(M==0){
              //+ detected
              show("Four way junction detected");
            }
            else{
              //T detected
              show("Right and Left Turn detected");
            }
            turnRight();
          }
      }
    }
  
    else if(L==0){
      if(LL==1){
        correctLeft(medium);
      }
      else if(M==0){
        //Left turn detectedd
        moveBitForward();
        if(M==0){
          show("Forward path with left turn detected");
        }
        else{
          show("Only left turn detected");
          
        }
        turnLeft();  
      }
      
    }
  }
  
  

  delay(1);

}

void moveBitForward(){
//  int a=LL,b=L,c=M,d=R,e=RR;
  show("Moving bit forward");
  move();
//  while(a==LL && b==L && c==M && d==R && e==RR){
//    delay(1);
//    update();
//  }
  delay(800);
  update();
  
}

void moveMore(){
  move();
  delay(200);
}

void show(String msg){
  Serial.println(msg);
}

void printArray(){
//  Serial.print("ll: ");
  Serial.println(LL);
//  Serial.print("l: ");
  Serial.println(L);
//  Serial.print("m: ");
  Serial.println(M);
//  Serial.print("r: ");
  Serial.println(R);
//  Serial.print("rr: ");
  Serial.println(RR);
  Serial.println();
  
  
}
void update(){
  RR = digitalRead(rr);
  R = digitalRead(r);
  M = digitalRead(m);
  L = digitalRead(l);
  LL = digitalRead(ll);
}

void stop(){
  digitalWrite(l1, LOW);
  analogWrite(l2, LOW);
  digitalWrite(r1, LOW);
  digitalWrite(r2, LOW);
  while(1==1){
    delay(100);
  }
}

void move(){
//  Serial.println("Moving ahead");
  digitalWrite(l1, LOW);
  analogWrite(l2, SPEED);
  digitalWrite(r1, LOW);
  analogWrite(r2, SPEED);
}

void correctLeft(int mode){
  
  digitalWrite(l1, LOW);
  digitalWrite(l2, LOW);
  digitalWrite(r1, LOW);
  digitalWrite(r2, mode);
}

void correctRight(int mode){
  digitalWrite(l1, LOW);
  digitalWrite(l2, mode);
  digitalWrite(r1, LOW);
  digitalWrite(r2, LOW);
}

void turnLeft(){
  show("Turning left");
//  moveMore();
  int count=0;
  digitalWrite(l1, SPEED);
  digitalWrite(l2, LOW);
  digitalWrite(r1, LOW);
  digitalWrite(r2, SPEED);
  delay(500);
  while(count<300){
    update();
    if(LL==1 && L==1 && M==0 && R==1 && RR==1){
      break;
    }
//    count++;
    delay(1);
  }
}

void turnRight(){
  show("Turning right");
//  moveMore();
  int count=0;
  digitalWrite(l1, LOW);
  digitalWrite(l2, SPEED);
  digitalWrite(r1, SPEED);
  digitalWrite(r2, LOW);
  delay(500);
  while(count<300){
    update();
    if(LL==1 && L==1 && M==0 && R==1 && RR==1){
      break;
    }
    delay(1);
  }
}
