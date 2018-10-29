/*
 * Localizer.h
 *
 *  Created on: Jul 23, 2018
 *      Author: sujiwo
 */

#ifndef LOCALIZER_H_
#define LOCALIZER_H_


#include <opencv2/opencv.hpp>
#include <Eigen/Eigen>

#include "VMap.h"
#include "optimizer.h"
#include "Frame.h"
#include "ImageDatabase.h"


class Localizer
{
public:

	Localizer(VMap*, bool emptyMask=false);

	virtual ~Localizer();

	/*
	 * Entry point to Place Recognition Routine
	 */
	kfid detect (cv::Mat &frmImg);

	void setCameraParameter (const CameraPinholeParams &c)
	{ localizerCamera = c; }

	void setCameraParameterFromId (int cameraId);

	const CameraPinholeParams& getCamera() const
	{ return localizerCamera; }

	void setMask(const cv::Mat &mm)
	{ locMask = mm.clone(); }

	cv::Mat getMask() const
	{ return locMask; }

	cv::Ptr<cv::FeatureDetector> getFeatureDetector() const
	{ return featureDetector; }

protected:
	VMap *sourceMap;
	ImageDatabase *imgDb;

	cv::Ptr<cv::FeatureDetector> featureDetector;

	CameraPinholeParams localizerCamera;

	cv::Mat locMask;

	float projectionCheck (const Frame &frame, const kfid &keyframe) const;

	int SearchBoW (const KeyFrame &kf, Frame &fi, vector<pair<mpid,kpid>> &mapPtMatchPairs, const float matchNNRatio=0.6);

	void debug_KF_F_Matching (const KeyFrame &keyframe, const Frame &frame, const vector<pair<mpid,kpid>> &mapPtMatchPairs);
};

#endif /* LOCALIZER_H_ */
