 class Counter {

private:

  int count;  

public:

  Counter(int value){
    count = value;
  }

  ~Counter(){
    // destructor  
  }
  
  void inc(){
    count++;  
  }
  
  int getValue(){
    return count;
  }

};

int a = 1;
Counter* c1;
Counter* c3;

int co = 0;

void setup(){
   int x1 = 3;
   int x2 = 4;
   Counter c(10);

   Serial.begin(9600); 
   c1 = new Counter(20);
   c3 = new Counter(30);

   c = *c1;
   
   while(!Serial){};
   Serial.println("DUMP");
   
   Serial.println(" &a => " + String((unsigned long) &a));
   Serial.println(" &c => " + String((unsigned long) &c));
   Serial.println(" &c1 => " + String ((unsigned long) &c1));

   Serial.println(" &x1 => " + String((unsigned long) &x1));
   Serial.println(" &x2 => " + String((unsigned long) &x2));

   Serial.println(" c1 => " + String((unsigned long) c1));
   Serial.println(" c2 => " + String((unsigned long) c3));
}


void loop(){
}
