#include "stdafx.h"
#include "Detection.h"


Detection::Detection(int class_id, float confidence, int x, int y, int width, int height): classId(class_id),
                                                                                           confidence(confidence),
                                                                                           x(x),
                                                                                           y(y),
                                                                                           width(width),
                                                                                           height(height)
{
}

Detection::~Detection()
{
}
