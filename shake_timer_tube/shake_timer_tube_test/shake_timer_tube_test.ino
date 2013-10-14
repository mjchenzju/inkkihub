int a = 1;
int b = 2;
int c = 3;
int d = 4;
int e = 5;
int f = 6;
int g = 7;
int p = 8;

int d4 = 9;
int d3 = 10;
int d2 = 11;
int d1 = 12;

long n = 0;
int x = 100;

int del = 55;

void setup(){
	pinMode(d1, OUTPUT);
	pinMode(d2, OUTPUT);
	pinMode(d3, OUTPUT);
	pinMode(d4, OUTPUT);
	pinMode(a, OUTPUT);
	pinMode(b, OUTPUT);
	pinMode(c, OUTPUT);
	pinMode(d, OUTPUT);
	pinMode(e, OUTPUT);
	pinMode(f, OUTPUT);
	pinMode(g, OUTPUT);
	pinMode(p, OUTPUT);
}

void loop(){
    digitalWrite(d1, HIGH);
    nine();
    digitalWrite(d1, LOW);
    clearLEDs();
    digitalWrite(d2, HIGH);
    zero();
    digitalWrite(d2, LOW);
    clearLEDs();
    digitalWrite(d3, HIGH); 
    seven();
    digitalWrite(d3, LOW);
    clearLEDs();
    digitalWrite(d4, HIGH);
    eight();
    digitalWrite(d4, LOW);
    clearLEDs();
}

void clearLEDs(){
	digitalWrite(a, HIGH);  
	digitalWrite(b, HIGH);   
	digitalWrite(c, HIGH);    
	digitalWrite(d, HIGH);    
	digitalWrite(e, HIGH);  
	digitalWrite(f, HIGH);    
	digitalWrite(g, HIGH); 
    digitalWrite(p, HIGH);
}

void zero(){
	digitalWrite(a, LOW);  
	digitalWrite(b, LOW);   
	digitalWrite(c, LOW);    
	digitalWrite(d, LOW);    
	digitalWrite(e, LOW);  
	digitalWrite(f, LOW);    
	digitalWrite(g, HIGH); 
}

void one(){
	digitalWrite(a, HIGH);  
	digitalWrite(b, LOW);   
	digitalWrite(c, LOW);    
	digitalWrite(d, HIGH);    
	digitalWrite(e, HIGH);  
	digitalWrite(f, HIGH);    
	digitalWrite(g, HIGH); 
}

void two(){
	digitalWrite(a, LOW);  
	digitalWrite(b, LOW);   
	digitalWrite(c, HIGH);    
	digitalWrite(d, LOW);    
	digitalWrite(e, LOW);  
	digitalWrite(f, HIGH);    
	digitalWrite(g, LOW); 
}

void three(){
	digitalWrite(a, LOW);  
	digitalWrite(b, LOW);   
	digitalWrite(c, LOW);    
	digitalWrite(d, LOW);    
	digitalWrite(e, HIGH);  
	digitalWrite(f, HIGH);    
	digitalWrite(g, LOW); 	
}

void four(){
	digitalWrite(a, HIGH);  
	digitalWrite(b, LOW);   
	digitalWrite(c, LOW);    
	digitalWrite(d, HIGH);    
	digitalWrite(e, HIGH);  
	digitalWrite(f, LOW);    
	digitalWrite(g, LOW); 	
}

void five(){
	digitalWrite(a, LOW);  
	digitalWrite(b, HIGH);   
	digitalWrite(c, LOW);    
	digitalWrite(d, LOW);    
	digitalWrite(e, HIGH);  
	digitalWrite(f, LOW);    
	digitalWrite(g, LOW); 		
}

void six(){
	digitalWrite(a, LOW);  
	digitalWrite(b, HIGH);   
	digitalWrite(c, LOW);    
	digitalWrite(d, LOW);    
	digitalWrite(e, LOW);  
	digitalWrite(f, LOW);    
	digitalWrite(g, LOW); 		
}

void seven(){
	digitalWrite(a, LOW);  
	digitalWrite(b, LOW);   
	digitalWrite(c, LOW);    
	digitalWrite(d, HIGH);    
	digitalWrite(e, HIGH);  
	digitalWrite(f, HIGH);    
	digitalWrite(g, HIGH); 		
}

void eight(){
	digitalWrite(a, LOW);  
	digitalWrite(b, LOW);   
	digitalWrite(c, LOW);    
	digitalWrite(d, LOW);    
	digitalWrite(e, LOW);  
	digitalWrite(f, LOW);    
	digitalWrite(g, LOW); 
}

void nine(){
	digitalWrite(a, LOW);  
	digitalWrite(b, LOW);   
	digitalWrite(c, LOW);    
	digitalWrite(d, LOW);    
	digitalWrite(e, HIGH);  
	digitalWrite(f, LOW);    
	digitalWrite(g, LOW); 
}
