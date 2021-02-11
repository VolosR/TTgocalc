#include <TFT_eSPI.h> 
#include <SPI.h>
#include "7seg.h"
#include "orbitron.h"

TFT_eSPI tft = TFT_eSPI(); 

#define TFT_GREY 0x5AEB 
#define left 0
#define right 35

#define darkblue 0x22AE
#define c1 0x02CD
#define c2 0xE280
#define c3 0x6005
#define back TFT_WHITE

/*
#define darkblue 0x22AE
#define c1 0x026A
#define c2 0xBAC0
#define c3 0x6005
#define back 0xAFDF
*/
const int pwmFreq = 5000;
const int pwmResolution = 8;
const int pwmLedChannelTFT = 0;

int n=4;
int m=4;
int posX[16];
int posY[16];

int fromTop=96;
int fromLeft=5;
int boxW=29;
int boxH=32;
int space=3;

float n1=0;
float n2=0;
String num="";

int v=0;
int h=0;

int vt=0;
int ht=0;

int pres=0;
int pres2=0;
bool both=0;

int operation=0; //+1 -2 *3 3/ 

char buttons[4][4]={{'7','8','9','/'},{'4','5','6','*'},{'1','2','3','-'},{'0','.','=','+'}};
short colors[4][4]={{c1,c1,c1,c3},{c1,c1,c1,c3},{c1,c1,c1,c3},{c1,c3,c3,c3}};

void setup(void) {
  tft.init();
  tft.fillScreen(TFT_BLACK);
  tft.setRotation(0);
  tft.fillRoundRect(0,0,134,239,8,back);

      pinMode(left, INPUT_PULLUP);
      pinMode(right, INPUT_PULLUP);

  ledcSetup(pwmLedChannelTFT, pwmFreq, pwmResolution);
  ledcAttachPin(TFT_BL, pwmLedChannelTFT);
  ledcWrite(pwmLedChannelTFT, 100);
  initDraw();
  
}

void loop() {
  
 checkButtons();
}

void initDraw()
{
  tft.fillRect(84,8,8,15,0x52AA);
  tft.fillRect(94,8,8,15,0x52AA);
  tft.fillRect(104,8,8,15,0x52AA);
  tft.fillRect(114,8,8,15,0x52AA);
  
  tft.setTextColor(TFT_BLACK,back);
  tft.setFreeFont(&Orbitron_Bold_18);
  tft.setCursor(8,22);
  tft.print("CASIO");
  tft.setFreeFont(&FreeMonoBold9pt7b);
  tft.drawString("CALCULATOR",8,72,2);
  tft.fillRoundRect(5,30,124,40,7,darkblue);
    tft.setFreeFont(&FreeMonoBold12pt7b);
   
    
  for(int i=0;i<n;i++){
  posY[i]=fromTop+(boxH*i)+(space*i);
  for(int j=0;j<m;j++)
    { 
      
      tft.setTextColor(TFT_WHITE,colors[j][i]);
      posX[j]=fromLeft+(boxW*j)+(space*j);
      
      tft.fillRoundRect(posX[j],posY[i],boxW,boxH,3,colors[i][j]);
     
      tft.setCursor(posX[j]+7,posY[i]+22);
       tft.print(buttons[i][j]);
      
      
    }}
    tft.setTextColor(TFT_WHITE,c2);
    tft.fillRoundRect(posX[0],posY[0],boxW,boxH,3,c2);
    tft.setCursor(posX[0]+7,posY[0]+22);
    tft.print(buttons[0][0]);
}


void checkButtons()
     {
      if(digitalRead(left)==0){
      if(pres==0)
            {
              pres=1;
              delay(40);
              if(digitalRead(right)==0){
                 both=1;}
                 else {
              v++;
              if(v==4)
              v=0;
             tft.setFreeFont(&FreeMonoBold12pt7b);
              tft.fillRoundRect(posX[ht],posY[vt],boxW,boxH,3,colors[vt][ht]);
              tft.setCursor(posX[ht]+7,posY[vt]+22);
              tft.print(buttons[vt][ht]);
              tft.fillRoundRect(posX[h],posY[v],boxW,boxH,3,c2);
              tft.setCursor(posX[h]+7,posY[v]+22);
              tft.print(buttons[v][h]);
              vt=v;
              ht=h;
              
              delay(150);
            }}}else {pres=0;}

             if(digitalRead(right)==0){
            if(pres2==0)
             {
              pres2=1;
              delay(40);
                 if(digitalRead(left)==0){
                 both=1;}
                 else {
             
              h++;
              if(h==4)
              h=0;
               tft.setFreeFont(&FreeMonoBold12pt7b);
              tft.fillRoundRect(posX[ht],posY[vt],boxW,boxH,3,colors[vt][ht]);
              tft.setCursor(posX[ht]+7,posY[vt]+22);
              tft.print(buttons[vt][ht]);
              tft.fillRoundRect(posX[h],posY[v],boxW,boxH,3,c2);
              tft.setCursor(posX[h]+7,posY[v]+22);
              tft.print(buttons[v][h]);
              vt=v;
              ht=h;
              
              delay(150);
            }}}else {pres2=0;}


            if(both==1)
            {
              if(buttons[v][h]=='0' || buttons[v][h]=='1' || buttons[v][h]=='2' || buttons[v][h]=='3' || buttons[v][h]=='4' || buttons[v][h]=='5' || buttons[v][h]=='6' || buttons[v][h]=='7' || buttons[v][h]=='8' ||  buttons[v][h]=='9' || buttons[v][h]=='.' )
              num=num+String(buttons[v][h]);
              
              if(buttons[v][h]=='+') {operation=1; n1=num.toFloat(); num="";}
              if(buttons[v][h]=='-') {operation=2; n1=num.toFloat(); num="";}
              if(buttons[v][h]=='*') {operation=3; n1=num.toFloat(); num="";}
              if(buttons[v][h]=='/') {operation=4; n1=num.toFloat(); num="";}
              
              
              
              if(buttons[v][h]=='=') {

               if(operation==1)
               {float r=n1+num.toFloat(); num=String(r); n1=num.toFloat();
               int p=r*10.00;
               if(p%10==0)
               num=String(p/10);
               }

                if(operation==2)
               {float r=n1-num.toFloat(); num=String(r); n1=num.toFloat();
                int p=r*10.00;
               if(p%10==0)
               num=String(p/10);}

                if(operation==3)
               {float r=n1*num.toFloat(); num=String(r); n1=num.toFloat();
                int p=r*10.00;
               if(p%10==0)
               num=String(p/10);}

                if(operation==4)
               {float r=n1/num.toFloat(); num=String(r); n1=num.toFloat();
                int p=r*10.00;
               if(p%10==0)
               num=String(p/10);}

              
              

              }

                
                draw();
                both=0;
               delay(200);
              }
      
     }


     void draw()
     {
      tft.setFreeFont(&DSEG7_Classic_Bold_24);
      tft.setTextColor(TFT_WHITE,darkblue);
      tft.fillRoundRect(5,30,124,40,7,darkblue);
      tft.setCursor(10,62);
      tft.print(num);
    
     }
