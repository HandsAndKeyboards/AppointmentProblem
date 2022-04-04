#ifndef SRC_AXIS_H
#define SRC_AXIS_H

#include "IRenderable.h"
#include "Line.h"
#include "SegmentPoint.h"

class Axis final : public IRenderable
{
	std::shared_ptr<Line> line;
	std::shared_ptr<Line> arrowFirstPart;
	std::shared_ptr<Line> arrowSecondPart;
	std::vector<SegmentPoint> segmentPoints;
	uint32_t segmentPointsDistance;
	
	void addSegmentPoints(const std::vector<std::string> & segmentPointsLabels);
	
public:
	Axis(const Axis &) = delete;
	Axis(Axis &&) = delete;
	Axis() = delete;
	Axis & operator=(const Axis &) = delete;
	Axis & operator=(Axis &&) = delete;
	
	Axis(const QVector3D & from, const QVector3D & to, const std::vector<std::string> & segmentPointsLabels);
	~Axis() final;
	
	void SetSegmentPointsDistance(uint32_t distance);
	
	void Render(Qt3DCore::QEntity * scene) override;
	void Remove(Qt3DCore::QEntity * scene) override;
};

#endif //SRC_AXIS_H
