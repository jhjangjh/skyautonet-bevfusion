#ifndef TRACKER_H
#define TRACKER_H


#include "opencv2/video/tracking.hpp"

#include "TrackerState.h"


#define STATE_NUM	7


class Tracker {

public:

	int m_time_since_update;
	int m_hits;
	int m_hit_streak;
	int m_id;

	float yaw;
	float height;
	int label;
	float score;

	Tracker(TrackerState state);

	TrackerState predict(void);
	void update(TrackerState state);
	TrackerState getState();


private:

	static int kf_count;

	cv::KalmanFilter kf;

};


#endif