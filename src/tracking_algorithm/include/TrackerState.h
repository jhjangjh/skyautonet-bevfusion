#ifndef TRACKER_STATE_H
#define TRACKER_STATE_H

#define	MEASURE_NUM	4

#include "cv_bridge/cv_bridge.h"


struct TrackerState {

	float centerX;
	float centerY;
	float area;
	float aspectRatio;

	float yaw;
	float height;
	int label;
	float score;

	cv::Mat toMat(void);
	void fromMat(cv::Mat mat);

};


#endif