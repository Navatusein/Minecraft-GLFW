#pragma once

#include "NotCopyable.h"
#include "NotMovable.h"

class Singleton : public NotMovable, public NotCopyable {
};