#ifndef WIRECELLRESS_GAUSSPROCESS_H
#define WIRECELLRESS_GAUSSPROCESS_H

#include <vector>
#include <tuple>
#include <Eigen/Dense>

namespace WCP {
  class GaussProcess{
  public:
    GaussProcess(int flag_kernel = 1);
    ~GaussProcess();

    void set_parameters(std::vector<double>& pars);
    double get_parameter(int i);

    void set_measurements(std::vector<std::tuple<double,double,double> >& data);
    
    std::vector<double> cal_conditional_mean(std::vector<double>& vec_x);
    std::vector<double> cal_conditional_variance(std::vector<double>& vec_x);
    
  private:
    int flag_kernel;
    std::vector<double> vec_pars;
    double sigma(double x1, double x2);
    
    int flag_cal_kernel;
    void cal_kernel();
    Eigen::MatrixXd mat_sigma;
    Eigen::MatrixXd inv_mat_sigma;

    
    std::vector<double> vec_data_x;
    std::vector<double> vec_data_y;
    std::vector<double> vec_data_dy;

   
  };
}


#endif
