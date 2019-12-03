using namespace vex;
using namespace std;

/***********************
 Button 
***********************/
class button {
    private:
    
    public:
    //position of the button on screen
    int x = 0;
    int y = 0;
    int h = 0;
    int w = 0;
    bool BtnTog;
    bool colrTog;
    color BtnColr;
    
    button(int X, int Y, int H, int W, bool ColrTog, color Colr){
        x = X;  //set positions
        y = Y;
        h = H;
        w = W;
        BtnColr = Colr;
        colrTog = ColrTog;
    }
    
    ~button(){
      //delete button if done
        Brain.Screen.clearScreen();
    }
    
    bool buttonState = false;
    bool togState = false;

    void wait(int milliseconds){
      //wait for time
      this_thread::sleep_for(milliseconds);
    }
    
    void update(){
      Brain.Screen.drawRectangle(x, y, w, h, BtnColr);
      //show button

      //check if button is being pressed or not
      if(Brain.Screen.pressing()){
        if((Brain.Screen.xPosition() >= x && Brain.Screen.xPosition() <= x+w) &&
          (Brain.Screen.yPosition() >= y && Brain.Screen.yPosition() <= y+h)){

          buttonState = true;
        }
        else{
          
          buttonState = false;
        } 
      }
      if(buttonState){
        if(BtnColr == color::blue){Brain.Screen.drawCircle(x+(w/2), y+(h/2), 20, color::cyan);}
        else if(BtnColr == color::green){Brain.Screen.drawCircle(x+(w/2), y+(h/2), 20, color::blue);}
        else if(BtnColr == color::red){Brain.Screen.drawCircle(x+(w/2), y+(h/2), 20, color::orange);}
        else if(BtnColr == color::purple){Brain.Screen.drawCircle(x+(w/2), y+(h/2), 20, color::purple);}
      }  
      else{
        Brain.Screen.drawCircle(x+(w/2), y+(h/2), 20, color::white);
      }      
    }
    
    void waitforRelease(){
      //wait for button to be released
      while((Brain.Screen.xPosition() >= x && Brain.Screen.xPosition() <= x+w) &&
      (Brain.Screen.yPosition() >= y && Brain.Screen.yPosition() <= y+h)) {wait(10);}
    }
};

/***********************
Push Button 
***********************/
class Pushbutton {
    private:
    
    public:
    int x = 0;
    int y = 0;
    int h = 0;
    int w = 0;
    color BtnColr;
    
    Pushbutton(int X, int Y, int H, int W, bool ColrTog, color Colr){
      x = X;
      y = Y;
      h = H;
      w = W;
      
      BtnColr = Colr;
    }
    
    ~Pushbutton(){
        Brain.Screen.clearScreen();
    }
    
    bool buttonState;
    bool togState = false;

    void wait(int milliseconds){
      //wait for time
      this_thread::sleep_for(milliseconds);
    }
    
    void update(){

      Brain.Screen.drawRectangle(x, y, w, h, BtnColr);

      if((Brain.Screen.xPosition() >= x && Brain.Screen.xPosition() <= x+w) &&
        (Brain.Screen.yPosition() >= y && Brain.Screen.yPosition() <= y+h) &&
        Brain.Screen.pressing()){
        if(BtnColr == color::blue){Brain.Screen.drawCircle(x+(w/2), y+(h/2), 20, color::cyan);}
        else if(BtnColr == color::green){Brain.Screen.drawCircle(x+(w/2), y+(h/2), 20, color::blue);}
        else if(BtnColr == color::red){Brain.Screen.drawCircle(x+(w/2), y+(h/2), 20, color::orange);}
        buttonState = true;
      }
      else{
        Brain.Screen.drawCircle(x+(w/2), y+(h/2), 20, color::white);
        buttonState = false;
      }            
    }
    
    void waitforRelease(){
        while((Brain.Screen.xPosition() >= x && Brain.Screen.xPosition() <= x+w) &&
           (Brain.Screen.yPosition() >= y && Brain.Screen.yPosition() <= y+h)&&
           Brain.Screen.pressing()) {wait(10);}
    }
};


class Togglebutton {
    private:
    
    public:
    //position of the button on screen
    int x = 0;
    int y = 0;
    int h = 0;
    int w = 0;
    bool BtnTog = false;
    color BtnColr;
    
    Togglebutton(int X, int Y, int H, int W, bool ColrTog, color Colr){
        x = X;  //set positions
        y = Y;
        h = H;
        w = W;
        BtnColr = Colr;
    }
    
    ~Togglebutton(){
      //delete button if done
        Brain.Screen.clearScreen();
    }
    
    bool buttonState = false;
    bool togState = false;
    bool butStat = false;

    void wait(int milliseconds){
      //wait for time
      this_thread::sleep_for(milliseconds);
    }
    
    void update(){
      Brain.Screen.drawRectangle(x, y, w, h, BtnColr);
      
      //show button

      if((Brain.Screen.xPosition() >= x && Brain.Screen.xPosition() <= x+w) &&
      (Brain.Screen.yPosition() >= y && Brain.Screen.yPosition() <= y+h) && 
      Brain.Screen.pressing()){
        butStat = true;
      }
      else{
        butStat = false;
      }

      //check if button is being pressed or not
      if(butStat && !BtnTog){
        BtnTog = true;
        while(isPressing()){wait(10);}
      }
      else if(butStat && BtnTog){  
        BtnTog = false; 
        while(isPressing()){wait(10);}    
      } 

      if(BtnTog){
        buttonState = true;
        Brain.Screen.drawCircle(x+(w/2), y+(h/2), 20, color::white);
      }
      else{
        buttonState = false;
        Brain.Screen.drawCircle(x+(w/2), y+(h/2), 20, color::black);
      }        
    }

    bool isPressing(){
      return (Brain.Screen.xPosition() >= x && Brain.Screen.xPosition() <= x+w) &&
      (Brain.Screen.yPosition() >= y && Brain.Screen.yPosition() <= y+h) && 
      Brain.Screen.pressing();
    }
    
    void waitforRelease(){
      //wait for button to be released
      while((Brain.Screen.xPosition() >= x && Brain.Screen.xPosition() <= x+w) &&
      (Brain.Screen.yPosition() >= y && Brain.Screen.yPosition() <= y+h)) {wait(10);}
    }
};


class slider{
  public:
  int X, Y; //X and Y position of the slider
  int Xnew; //New X center position (when min exists)
  int Width, Height, widthMem;  //dimension of slide bar
  float Scalar, Min;  //minimum value and maximum value

  int circleX, circleY, circleR;  //circle position and dimension
  int fingerX,fingerY;  //finger x and y position
  int fingerToCircleDist; //find distance from finger to circle

  int slidePos;     //slides output value
  float slidePct;   //slide percent based on postion
  float slideEr;    //slide error

  bool isMin;       //if the mimimum exists

  slider(int x, int y, int width, int height, float max, bool minExists = false, float min = 0){
    X = x;  //set values
    Y = y;
    Height = height;
    Min = min;
    Scalar = max;

    if(minExists){
      //change width and circle start bc of min
      Xnew = (min/Scalar)*(width/2);
      Width = (width/2)+Xnew;
      widthMem = width;
      circleX = Xnew+X;
      isMin = true;
    }
    else{Width = width;circleX = (Width/2)+X;isMin=false;}

    //circle start position
    circleY = (Height/2)+Y;
    circleR = 10;
  }

  ~slider(){
    Brain.Screen.clearScreen();
  }

  void update(){
    fingerX = Brain.Screen.xPosition(); //set finger position 
    fingerY = Brain.Screen.yPosition();

    //change slider output 
    if(!isMin){slideEr = (circleX-((Width/2)+X));slidePct = slideEr/(Width/2);}
    else{slideEr= (circleX-(Xnew+X));slidePct = slideEr/(widthMem/2);}
    slidePos = slidePct*Scalar;

    //draw slider component
    Brain.Screen.drawRectangle(X,Y,Width,Height,color::blue);
    Brain.Screen.drawCircle(circleX,circleY,circleR,color::white);
    Brain.Screen.printAt((Width/2)+X-5,circleY+25,"%d",slidePos);

    //find finger to circle distance
    fingerToCircleDist = sqrt(pow(fingerX-circleX,2)+pow(fingerY-circleY,2));

    //check if finger is touching the circle
    if(fingerToCircleDist <= circleR+20 && Brain.Screen.pressing()){
      circleX = fingerX;
    }
    else if(fingerY >= Y && fingerY <= Y+Height && 
    fingerX >= X && fingerX <= X+Width && Brain.Screen.pressing()){
      circleX = fingerX;
    }

    //keep the slider in its slider bar
    if(circleX >= X+Width){circleX = X+Width;}
    else if(circleX <= X){circleX = X;}
  }

  void reset(){
    slideEr = 0;
    slidePct = 0;
    slidePos = 0;

    if(isMin){
      //change width and circle start bc of min
      Xnew = (Min/Scalar)*(widthMem/2);
      circleX = Xnew+X;
    }
    else{circleX = (Width/2)+X;}

    //circle start position
    circleY = (Height/2)+Y;
    circleR = 10;
  }

  int getSliderVal(){
    return slidePos;  //output value of slider
  }
};
