#ifndef SORT_RECT_H
#define SORT_RECT_H


#include "TrackerState.h"


struct SortRect {

    int id;
    float centerX;
    float centerY;
    float width;
    float length;

    float yaw;
    float height;
    int label;
    float score;

    TrackerState toTrackerState(void);
    void fromTrackerState(TrackerState state);
};


#endif