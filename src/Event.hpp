#pragma once

class Event{
public:
    virtual void percept() const noexcept = 0;
    virtual bool die() const noexcept = 0;
    virtual bool reward() const noexcept = 0;
};