#ifndef GPS_H
#define GPS_H
 



//GPS Library for GYSFDMAXB

#define GPSTX PA_9//GPSのTXピン
#define GPSRX PA_10//GPSのRXピン
#define GPSBAUD 9600//GPSのボーレート
#define ODR 10//max 10Hz　更新周期
 
class GPS {
public:
    GPS(PinName gpstx,PinName gpsrx);
    
    void gpscmd(char *command);
    void getgps();
    
    float longtitude;//緯度
    float latitude;//経度
    //float speed;//m/s
    //float direction;//方位
    //上の4つは自動的に更新される この4つを読むことでデータ取得が出来る
    
    bool result;//trueで成功、falseで失敗
    
    char buf[100];

    int point[4];
  
private:  
    Serial _gps;
};
 
#endif