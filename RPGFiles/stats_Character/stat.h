#ifndef SFMLAPP_STAT_H
#define SFMLAPP_STAT_H
#include "../map.cpp"
class Stat {
    private:
        //Originally intended for use with Health in this game,
        // there is a max value and a current value.
        int maxStat;
        int currentStat;
    public:
        Stat();
        //Constructor that sets the maxStat and currentStat to the passed in value.
        Stat(int stat);
        //Getters and Setters
        int getCurrentStat() const;
        int getMaxStat() const;
        void setCurrentStat(int stat);
        void setMaxStat(int stat);
};


#endif //SFMLAPP_STAT_H
