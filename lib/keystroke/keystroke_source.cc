#include "keystroke_source.h"
#include "keystroke_consumer.h"

void KeystrokeSource::notifyAll(){ Subject<Keystroke,KeystrokeSource>::notifyAll(this); }

