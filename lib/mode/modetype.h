#ifndef MODE_MODETYPE_H
#define MODE_MODETYPE_H

// vim mode enum
// search "mode" is for /,?
// Ex is for ":"
enum class ModeType {
  Normal, Ex, Insert, Replace, Search
};

#endif