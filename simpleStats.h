// simpleStats.h

#ifndef ___SIMPLESTATS__H___
#define ___SIMPLESTATS__H___

class simpleStats 
{
 public:
  simpleStats();
  simpleStats(const &cv::Mat);

  void setImage(const &cv::Mat) const;
  cv::Mat* getImage() const;
  dougle getMean();
  double getMax();
  double getMin();

 private:
    const cv::Mat *refImage;
    double _max;
    bool _isMaxComputed;
    double _min;
    bool _isMinComputed;
    double _mean;
    bool _isMeanComputed;

    void computeMeanMaxMin();
 


    
};
#endif //___SIMPLESTATS__H___
