#include<stdio.h>
int calculateFuel(int fuel, int consumption, int recharge, int solarBonus, int planet, int totalPlanets){
    if (fuel<=0 || planet>totalPlanets)
    {
        return fuel;
    }
    //general fuel maths for eachy planet
    fuel-=consumption+recharge;

    //special case...4th planets
    if (planet%4==0)
    {
        fuel+=solarBonus;
    }
    int result= calculateFuel(fuel,consumption,recharge,solarBonus,planet+1,totalPlanets);
    printf("\nPlanet %d: Fuel Remaining = %d\n",planet,fuel);
    return result;
}
int main()
{
    // plants are the total planets we are working with
    // totalplanets we take one at a time and process
    int fuel=3000000,fuelUsed=15000,gravitationalCharge=5000,SolarRecharge=2500,Planets,Planetvisit=1;
    printf("Enter total planets being visited: ");
    scanf("%d",&Planets);
    int FuelTrack=calculateFuel(fuel,fuelUsed,gravitationalCharge,SolarRecharge,Planetvisit,Planets);
    printf("\nRemaining fuel: %d",FuelTrack);
    if (FuelTrack > 0)
        printf("\nJourney Completed Successfully!\n");
    else
        printf("\nFuel Exhausted Before Reaching Last Planet.\n");

    return 0;
}
