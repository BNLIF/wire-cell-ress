#include "WireCellRess/GaussProcess.h"
#include <cmath>

using namespace WireCell;

GaussProcess::GaussProcess(int flag_kernel)
  : flag_kernel(flag_kernel)
  , flag_cal_kernel(0)
{
}

GaussProcess::~GaussProcess(){
}

void GaussProcess::set_parameters(std::vector<double>& pars){
  vec_pars.clear();
  vec_pars = pars;
}

double GaussProcess::get_parameter(int i){
  if (i<vec_pars.size()){
    return vec_pars.at(i);
  }else{
    return 0;
  }
}

void GaussProcess::set_measurements(std::vector<std::tuple<double,double,double> >& data){
  vec_data_x.clear();
  vec_data_y.clear();
  vec_data_dy.clear();
  
  for (auto it = data.begin(); it!=data.end(); it++){
    vec_data_x.push_back(std::get<0>(*it));
    vec_data_y.push_back(std::get<1>(*it));
    vec_data_dy.push_back(std::get<2>(*it));
  }
}

double GaussProcess::sigma(double x1,double x2){
  double value = 0;
  if (flag_kernel == 1){
    value = exp(-pow(x1-x2,2)/2./pow(vec_pars.at(0),2));
  }
  return value;
}

void GaussProcess::cal_kernel(){
  if (flag_cal_kernel==0){
    flag_cal_kernel = 1;
  }
}
