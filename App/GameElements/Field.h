//
// Created by gerdzio21 on 13.08.2023.
//

#ifndef UNTITLED_FIELD_H
#define UNTITLED_FIELD_H

#include "Ships/Ship.h"

enum FieldStatus {
    OccupiedByShip,
    SurroundsShip,
    Free,
    Hit,
    Missed
};
class Field {
private:
    FieldStatus fieldStatus;
    Ship* ship;
    int shipSectorIdx;
public:
    Field(){
        fieldStatus = Free;
        ship = nullptr;
        shipSectorIdx = -1;
    }
    ~Field() = default;
    FieldStatus getFieldStatus(){
        return fieldStatus;
    }
    void setFieldStatus(FieldStatus newFieldStatus){
        fieldStatus = newFieldStatus;
    }
    void placeShip(Ship* ship1, int shipSector){
        ship = ship1;
        shipSectorIdx = shipSector;
        fieldStatus=OccupiedByShip;
    }
    bool isFree() const {
        return fieldStatus==Free;
    }
    Ship* getShip() const {
        return ship;
    }
    int getShipSectorIdx() const {
        return shipSectorIdx;
    }


};


#endif //UNTITLED_FIELD_H
