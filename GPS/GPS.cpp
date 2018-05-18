#include "mbed.h"
#include "GPS.h"

GPS::GPS(PinName gpstx,PinName gpsrx): _gps(gpstx,gpsrx)
{
    latitude=0;
    longtitude=0;
    
    gpscmd("314,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0");
    int odr=ODR;
    odr=1000/odr;
    sprintf(buf,"300,%d,0,0,0,0",odr);
    gpscmd(buf);
    
    int baud=GPSBAUD;
    
    for(int i=0;i<100;i++){
        buf[i]=0;
    }
    
    sprintf(buf,"251,%d",baud);
    
    gpscmd(buf);
    gpscmd(buf);
    
    
    _gps.baud(GPSBAUD);
    
    _gps.attach(this,&GPS::getgps);
}

void GPS::gpscmd(char *command)
{
    int len=strlen(command);
    char xordata[len+4];
    sprintf(xordata,"PMTK%s",command);
    
    
    char  xorbuf=0x00;
    for(int i=0;i<len+4;i++){
        xorbuf=xorbuf^xordata[i];
        }
        
    
    char packet[len+8];
    if(xorbuf>0x0f){
        sprintf(packet,"$%s*%x",xordata,xorbuf);
        }
    else {
        sprintf(packet,"$%s*0%x",xordata,xorbuf);
        }
    
    
    _gps.printf(packet);
    _gps.putc(0x0D);
    _gps.putc(0x0A);
}

void GPS::getgps()
{
    if(_gps.getc()=='$'){
        
    int counter;
    char sample=0x00;
    
   
    
    
        
        
        for(counter=0;counter<18;counter++){
         sample=_gps.getc();   
        }
        
        if(sample=='A'){
            
        //初期化
        latitude=0;
        longtitude=0;
        //speed=0;
        //direction=0;
        
            //データ取得
            for(int i=0;i<4;i++){
            point[i]=0;
            }    
        
            int pointnum=0;
            for(counter=0;sample!='\n';counter++){
              sample=_gps.getc();
              buf[counter]=sample;
              
                if(buf[counter]=='.'){
                  point[pointnum]=counter;
                  pointnum++;
                }
                
            }
            
            //緯度計算
            for(counter=1;counter<point[0]-2;counter++){
                
                    float num=1;
                    for(int i=point[0]-counter-3;i>0;i--){
                        num=num*10;
                    }
                    
                    latitude+=(float)num*(buf[counter]-48);
                }
                
            float minute=0;
            
            minute+=(buf[point[0]-2]-48)*10;
            minute+=(buf[point[0]-1]-48);
                       
                for(counter=point[0]+1;counter<point[0]+5;counter++){
                    float num=1;
                    
                    for(int i=counter-point[0];i>0;i--){
                        num=num*0.1f;
                    }
                    
                    minute+=(float)num*(buf[counter]-48);
                }
            
            latitude+=minute/60;
            
            
            //経度計算
            for(counter=point[0]+8;counter<point[1]-2;counter++){
                
                    float num=1;
                    for(int i=point[1]-counter-3;i>0;i--){
                        num=num*10;
                    }
                    
                    longtitude+=(float)num*(buf[counter]-48);
                }
                
            minute=0;
            
            minute+=(buf[point[1]-2]-48)*10;
            minute+=(buf[point[1]-1]-48);
                       
                for(counter=point[1]+1;counter<point[1]+5;counter++){
                    float num=1;
                    
                    for(int i=counter-point[1];i>0;i--){
                        num=num*0.1f;
                    }
                    
                    minute+=(float)num*(buf[counter]-48);
                }
            
            longtitude+=minute/60;
            
/*            
            //速度計算
            for(counter=point[1]+9;counter<point[1];counter++){
        
            float num=1;
                for(int i=point[2]-counter-1;i>0;i--){
                    num=num*10;
                }
            
            speed+=(float)num*(buf[counter]-48);
            }
                
            
            speed+=(buf[point[2]+2]-48)*0.01;
            speed+=(buf[point[2]+1]-48)*0.1;
            
            speed/=0.51444;
            
            //方位計算
            for(counter=point[2]+4;counter<point[3];counter++){
        
            float num=1;
                for(int i=point[3]-counter-1;i>0;i--){
                    num=num*10;
                }
            
            direction+=(float)num*(buf[counter]-48);
            }
                
            
            direction+=(buf[point[3]+2]-48)*0.01;
            direction+=(buf[point[3]+1]-48)*0.1;
*/            
            
                
                result=true;
            }
        
            else{
                result=false;
            }
        
        
        
        
        
    }
}
