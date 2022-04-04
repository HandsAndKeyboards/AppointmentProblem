#ifndef SRC_LINE_H
#define SRC_LINE_H

#include <QVector3D>

#include "IRenderable.h"

class Line final : public IRenderable
{
	QVector3D from;
	QVector3D to;
	
public:
	Line(const Line &) = delete;
	Line(Line &&) = delete;
	Line() = delete;
	Line & operator=(const Line &) = delete;
	Line & operator=(Line &&) = delete;
	
	Line(const QVector3D & from, const QVector3D & to) : from{from}, to{to} {};
	~Line() final;
	
	void Render(Qt3DCore::QEntity * scene) override;
	void Remove(Qt3DCore::QEntity * scene) override;
};

#endif //SRC_LINE_H
