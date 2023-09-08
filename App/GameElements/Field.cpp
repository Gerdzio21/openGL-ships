//
// Created by Gerdzio21 on 2023-09-08.
//
#include "Field.h"
Field::Field() {
    fieldStatus = Free;
    ship = nullptr;
    shipSectorIdx = -1;
}

FieldStatus Field::getFieldStatus() {
    return fieldStatus;
}

void Field::placeShip(Ship *ship1, int shipSector) {
    ship = ship1;
    shipSectorIdx = shipSector;
    fieldStatus=OccupiedByShip;
}

void Field::setFieldStatus(FieldStatus newFieldStatus) {
    fieldStatus = newFieldStatus;
}

bool Field::isFree() const {
    return fieldStatus==Free;
}

Ship *Field::getShip() const {
    return ship;
}

int Field::getShipSectorIdx() const {
    return shipSectorIdx;
}
