#include <stdio.h>
#include <assert.h>

int CheckBatTemp(float temperature)
{
    if(temperature < 0 || temperature > 45){
    printf("Temperature out of range!\n");
    return 0;}
  return 1;
}
int CheckBatSoc(float soc)
{
    if(soc < 20 || soc > 80){
    printf("State of Charge out of range!\n");
    return 0;}
  return 1;
}
int CheckBatChargeRate(float chargeRate)
{
    if(chargeRate > 0.8){
    printf("Charge Rate out of range!\n");
    return 0;}
   return 1;
}
int main() {
  assert(CheckBatTemp(25));
  assert(!CheckBatTemp(50));
  assert(!CheckBatSoc(0));
}
