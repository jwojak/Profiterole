#include "simpleStats.h"

simpleStats::SimpleStats()
{
  _max = 0.0;
  _min = 0.0;
  _mean = 0.0;
  _isMaxComputed = false;
  _isMinComputed = false;
  _isMeanComputed = false;
  refImage = NULL;
}

simpleStats::SimpleStats( const &cv::Mat cvMat) cont
{
  _max = 0.0;
  _min = 0.0;
  _mean = 0.0;
  _isMaxComputed = false;
  _isMinComputed = false;
  _isMeanComputed = false;
  refImage = cvMat;
}

double simpleStat::getMin()
{
  if(_isMinComputed)
    return _min;
  else
    {
      computeMeanMaxMin();
      return getMin();
    }
}

double simpleStat::getMax()
{
  if(_isMaxComputed)
    return _max;
  else
    {
      computeMeanMaxMin();
      return getMax();
    }
}

double simpleStat::getMean()
{
  if(_isMeanComputed)
    return _mean;
  else
    {
      computeMeanMaxMin;
      return getMean();
    }

}

void simpleStat::computeMeanMaxMin()
{
  
  _isMeanComputed = true;
  _isMinComputed = true;
  _isMaxComputed = true;
}
