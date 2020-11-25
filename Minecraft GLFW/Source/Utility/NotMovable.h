#pragma once

class NotMovable {
public:
    NotMovable(NotMovable&&) = delete;
    NotMovable& operator=(NotMovable&&) = delete;

protected:
    NotMovable() = default;
};