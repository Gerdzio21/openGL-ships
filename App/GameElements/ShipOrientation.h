//
// Created by gerdzio21 on 24.05.2023.
//

#ifndef SHIPS_SHIPORIENTATION_H
#define SHIPS_SHIPORIENTATION_H

enum ShipOrientation{
    Horizontal,
    Vertical
};
static ShipOrientation changeOrientation(ShipOrientation currentOrientation){
    return currentOrientation == Horizontal ? Vertical : Horizontal;
}

#endif //SHIPS_SHIPORIENTATION_H
