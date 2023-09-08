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
    Field();
    ~Field() = default;
    FieldStatus getFieldStatus();
    void setFieldStatus(FieldStatus newFieldStatus);
    void placeShip(Ship* ship1, int shipSector);
    bool isFree() const;
    Ship* getShip() const;
    int getShipSectorIdx() const;


};


#endif //UNTITLED_FIELD_H
