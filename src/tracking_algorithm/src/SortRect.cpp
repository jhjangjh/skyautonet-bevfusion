#include "SortRect.h"


TrackerState SortRect::toTrackerState(void) {

    TrackerState state;
    state.centerX = centerX;
    state.centerY = centerY;
    state.area = width * length;
    state.aspectRatio = width / length;

    state.yaw = yaw;
    state.height = height;
    state.label = label;
    state.score = score;
    
    return state;
}

void SortRect::fromTrackerState(TrackerState state) {

    centerX = state.centerX;
    centerY = state.centerY;
    
    yaw = state.yaw;
    height = state.height;
    label = state.label;
    score = state.score;

    if(state.area > 0) {
        width = sqrt(state.area * state.aspectRatio);
        length = state.area / width;
    }
    else {
        width = 0;
        length = 0;
    }

}