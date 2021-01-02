#include "stat.h"
Stat::Stat(){
    //Default Constructor
}
//Overloaded constructor.
Stat::Stat(int stat){
    maxStat=stat;
    currentStat=stat;
}
//Getters and Setters
int Stat::getCurrentStat() const {
    return currentStat;
}
int Stat::getMaxStat() const{
    return maxStat;
}
void Stat::setMaxStat(int stat){
    maxStat = stat;
}
void Stat::setCurrentStat(int stat) {
    currentStat=stat;
}