#ifndef SRC_IGEOMETRIC_H
#define SRC_IGEOMETRIC_H

class IGeometric
{
public:
	virtual void Translate(double dx, double dy) = 0;
	virtual void Rotate(double angle) = 0;
	virtual void Expand(double coefficient) = 0;
	virtual void Shrink(double coefficient) = 0;
	
	virtual ~IGeometric() {};
};

#endif //SRC_IGEOMETRIC_H
