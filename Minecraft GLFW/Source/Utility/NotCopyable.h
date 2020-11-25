#pragma once

class NotCopyable {
public:
    NotCopyable() = default;
    NotCopyable(const NotCopyable&) = delete;
    NotCopyable& operator=(const NotCopyable&) = delete;
};