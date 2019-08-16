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
    color BtnColr;
    
    button(int X, int Y, int H, int W, bool ColrTog, color Colr){
        x = X;  //set positions
        y = Y;
        h = H;
        w = W;
        //set color if need color
        if(ColrTog == false){
            if(buttonState == true){BtnColr = Colr;}
            else{BtnColr = color::transparent;}
        }
       else{
           BtnColr = Colr;
       }
      //show button
      Brain.Screen.drawRectangle(x, y, w, h, BtnColr);
    }
    
    ~button(){
      //delete button if done
        Brain.Screen.clearScreen();
    }
    
    bool buttonState;
    bool togState = false;

    void wait(int milliseconds){
      //wait for time
      this_thread::sleep_for(milliseconds);
    }
    
    void update(){
      //check if button is being pressed or not
        if((Brain.Screen.xPosition() >= x && Brain.Screen.xPosition() <= x+w) &&
           (Brain.Screen.yPosition() >= y && Brain.Screen.yPosition() <= y+h)){
            
            buttonState = true;
        }
        else{
            buttonState = false;
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
        if(ColrTog == false){
            if(buttonState == true){BtnColr = Colr;}
            else{BtnColr = color::transparent;}
        }
       else{
           BtnColr = Colr;
       }
        
        Brain.Screen.drawRectangle(x, y, w, h, BtnColr);
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
        if((Brain.Screen.xPosition() >= x && Brain.Screen.xPosition() <= x+w) &&
           (Brain.Screen.yPosition() >= y && Brain.Screen.yPosition() <= y+h) &&
           Brain.Screen.pressing()){
            
            buttonState = true;
        }
        else{
            buttonState = false;
        }            
    }
    
    void waitforRelease(){
        while((Brain.Screen.xPosition() >= x && Brain.Screen.xPosition() <= x+w) &&
           (Brain.Screen.yPosition() >= y && Brain.Screen.yPosition() <= y+h)&&
           Brain.Screen.pressing()) {wait(10);}
    }
};
