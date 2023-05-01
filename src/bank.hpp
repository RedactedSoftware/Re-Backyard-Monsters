#pragma once
namespace Bank {
    //When we save and load the game, preserve this.
    inline int twigs = 0;
    inline int pebbles = 0;
    inline int putty = 0;
    inline int goo = 0;

    inline void cash(int cashedAmount, int type) {
        type = type + cashedAmount;
    }

    inline bool spend(int spentAmount, int type) {
        if (type - spentAmount < 0)
            return false;
        type = type - spentAmount;
        return true;
    }

    //TODO work on this later.
    inline int calculateMaxCapacity() {

    }
}