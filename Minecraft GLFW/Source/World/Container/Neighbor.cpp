#include "Neighbor.h"

Neighbor::Neighbor() {
}

Neighbor::Neighbor(Chunk* Top, Chunk* Bottom, Chunk* XFront, Chunk* XRear, Chunk* ZFront, Chunk* ZRear) : Top(Top), Bottom(Bottom), XFront(XFront), XRear(XRear), ZFront(ZFront), ZRear(ZRear) {
}
