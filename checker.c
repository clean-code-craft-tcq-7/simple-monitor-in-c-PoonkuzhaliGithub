#include <stdio.h>
#include <assert.h>

typedef struct
{
    int TempBreachAlerter;
    int SOCBreachAlerter;
    int ChargeRateBreachAlerter;
    int TempWarningAlerter;
    int SOCWarningAlerter;
    int ChargeRateWarningAlerter;
}BMS_s;

BMS_s BatteryCheck_s ={0, 0,0,0,0,0};

  _Bool CheckHighTempWarningRange(float temperature)
  {
      if((42.75<= temperature )&&(temperature<=45))
      {
          return 1;
      }
      else
      {
          return 0;
      }
  }
  _Bool CheckLowTempWarningRange(float temperature)
  {
      if((0<= temperature)&&(temperature <=2.25))
      {
          return 1;
      }
      else
      {
          return 0;
      }
  }
   _Bool CheckTempInWarningRange(float temperature)
  {
      if((CheckHighTempWarningRange(temperature) == 1) ||(CheckLowTempWarningRange(temperature)==1))
      {
          return 1;
      }
      else
      {
        return 0;  
      }
  }
   _Bool CheckTempInRange(float temperature)
  {
      if(temperature < 0|| temperature > 45)
      {
          return 0;
      }
      else
      {
        return 1;  
      }
  }
  _Bool CheckHighSOCWarningRange(float soc)
  {
      if((10<= soc )&&(soc<=24))
      {
          return 1;
      }
      else
      {
          return 0;
      }
      
  }
  _Bool CheckLowSOCWarningRange(float soc)
  {
      if((76<= soc)&&(soc <=80))
      {
          return 1;
      }
      else
      {
          return 0;
      }
  }
_Bool CheckSOCInWarningRange(float soc)
  {
      if((CheckHighSOCWarningRange(soc) == 1) ||(CheckLowSOCWarningRange(soc)==1))
      {
          return 1;
      }
      else
      {
        return 0;  
      }
  }
  _Bool CheckSOCInRange(float soc)
  {
      if(soc < 20 || soc > 80)
      {
          return 0;
      }
      else
      {
        return 1;  
      }
      
  }
    _Bool CheckChargeRateInWarningRange(float chargeRate)
  {
      if((0.76<=chargeRate)&&(chargeRate<= 0.8))
      {
          return 1;
      }
      else
      {
        return 0;  
      }
  }
_Bool CheckChargeRateInRange(float chargeRate)
  {
      if(chargeRate > 0.8)
      {
          return 0;
      }
      else
      {
        return 1;  
      }
  }
   void TempWarningAlerter(void)
   {
       BatteryCheck_s.TempWarningAlerter ++;
       printf("Warning :Temperature nearing out of range !\n");
   }
  void TempAlerter(void)
  {
     BatteryCheck_s.TempBreachAlerter++;
     printf("Error:Temperature out of range !\n");
  }
  void ChargeRateWarningAlerter(void)
   {
       BatteryCheck_s.ChargeRateWarningAlerter ++;
       printf("Warning :ChargeRate nearing out of range !\n");
   }
  void SOCAlerter(void)
  {
     BatteryCheck_s.SOCBreachAlerter++;
     printf("Error:SOC out of range !\n");
  }
  void SOCWarningAlerter(void)
   {
       BatteryCheck_s.SOCWarningAlerter ++;
       printf("Warning: SOC nearing out of range !\n");
   }
  void ChargeRateAlerter(void)
  {
     BatteryCheck_s.ChargeRateBreachAlerter++;
     printf("Error:ChargeRate out of range !\n");
  }
  void BatteryTempIsOk(float temperature)
  {
      if(CheckTempInWarningRange(temperature) == 1)
     {
         TempWarningAlerter();
     }
     else if(CheckTempInRange(temperature) == 0)
     {
       TempAlerter();
     }
     else{   }
  }
  void BatterySOCIsOk(float soc)
  {
     if(CheckSOCInWarningRange(soc) == 1)
     {
         SOCWarningAlerter();
     }
     else if(CheckSOCInRange(soc) == 0)
     {
       SOCAlerter();
     }
     else{   }
  }
 void BatteryChargeRateIsOk(float chargeRate)
  {
     if(CheckChargeRateInWarningRange(chargeRate) == 1)
     {
         ChargeRateWarningAlerter();
     }
     else if(CheckChargeRateInRange(chargeRate) == 0)
     {
       ChargeRateAlerter();
     }
     else
     {

     }
  }
  float GetTempInFarenheit(float temperature,char tempunit)
  {
      float temp;
      if(tempunit == 'C')
      {
          temp = ((temperature * 9/5) + 32);
      }
      else
      {
          temp = temperature;
      }
      return temp;
  }
  
void BatteryIsOk(float temperature, float soc, float chargeRate ,char tempunit) 
{
    float temp;
     temp = GetTempInFarenheit(temperature,tempunit);
     BatteryTempIsOk(temp);
     BatterySOCIsOk(soc);
     BatteryChargeRateIsOk(chargeRate);
}
 
int main() {
    BatteryIsOk(-3.8, 70, 0.7,'C');
    assert(BatteryCheck_s.TempBreachAlerter == 0);
    assert(BatteryCheck_s.SOCBreachAlerter == 0);
    assert(BatteryCheck_s.ChargeRateBreachAlerter == 0);
    
    BatteryIsOk(46, 81, 1.0,'F');
    assert(BatteryCheck_s.TempBreachAlerter == 1);
    assert(BatteryCheck_s.SOCBreachAlerter == 1);
    assert(BatteryCheck_s.ChargeRateBreachAlerter == 1);
    
    BatteryIsOk(-1, 9, 0.9,'F');
    assert(BatteryCheck_s.TempBreachAlerter == 2);
    assert(BatteryCheck_s.SOCBreachAlerter == 2);
    assert(BatteryCheck_s.ChargeRateBreachAlerter == 2);
    
    BatteryIsOk(1, 22, 0.78,'F');
    assert(BatteryCheck_s.TempWarningAlerter == 1);
    assert(BatteryCheck_s.SOCWarningAlerter == 1);
    assert(BatteryCheck_s.ChargeRateWarningAlerter == 1);
    
    BatteryIsOk(44, 77, 0.79,'F');
    assert(BatteryCheck_s.TempWarningAlerter == 2);
    assert(BatteryCheck_s.SOCWarningAlerter == 2);
    assert(BatteryCheck_s.ChargeRateWarningAlerter == 2);
    
    BatteryIsOk(6.6, 77, 0.79,'C');
    assert(BatteryCheck_s.TempWarningAlerter == 3);
    assert(BatteryCheck_s.SOCWarningAlerter == 3);
    assert(BatteryCheck_s.ChargeRateWarningAlerter == 3);
}
