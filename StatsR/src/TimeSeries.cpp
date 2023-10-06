#include <Rcpp.h>

#include <string>
#include <vector>

#include "../../Common/include/TimeSeries.h"

//' Calculate a simple moving average
//' 
//' @param dates A vector of .
//' @param observations A vector of doubles.
//' @param window An integer representing the window size
//' @export
// [[Rcpp::export]]
std::vector<double> get_moving_average(Rcpp::NumericVector dates, Rcpp::NumericVector observations, int window) {
  
  std::vector<long> _dates = Rcpp::as<std::vector<long> >(dates);
  std::vector<double> _observations = Rcpp::as<std::vector<double> >(observations);
  
  StatisticsLibrary::TimeSeries ts(_dates, _observations);
  
  std::vector<double> results = ts.MovingAverage(window);
  return results;
}

// A wrapper class for time series
class TimeSeries
{
public:
  ~TimeSeries() = default;
  
  TimeSeries(Rcpp::NumericVector dates, Rcpp::NumericVector observations)
    : _ts(Rcpp::as<std::vector<long> >(dates), Rcpp::as<std::vector<double> >(observations) )
  {}
  
  std::vector<double> MovingAverage(int window)
  {
    return _ts.MovingAverage(window);
  }
  
private:
  StatisticsLibrary::TimeSeries _ts;
};

RCPP_MODULE(TS) {
  
  Rcpp::class_<TimeSeries>("TimeSeries")
  .constructor<Rcpp::NumericVector, Rcpp::NumericVector>("Construct a time series object")
  .method("MovingAverage", &TimeSeries::MovingAverage, "Calculate a moving average of size = window")
  ;

}

















