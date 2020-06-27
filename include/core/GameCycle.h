//
// Created by DamarIndra on 24-Jun-20.
//

#ifndef DOLANAN_GAMECYCLE_H
#define DOLANAN_GAMECYCLE_H

#include <SFML/Window/Event.hpp>

class GameCycle{

public:
    virtual void Initialization();

    virtual void Start();

    virtual void Update();

    virtual void FixedUpdate();

    virtual void LateUpdate();

    virtual void Input(sf::Event event);

    virtual void Draw();
};

#endif //DOLANAN_GAMECYCLE_H
