#include "WCPRess/GaussProcess.h"
#include <cmath>

using namespace WCP;

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
    value = exp(-pow(x1-x2,2)/2./pow(vec_pars.at(0),2)) * vec_pars.at(1);
  }
  return value;
}

void GaussProcess::cal_kernel(){
  if (flag_cal_kernel==0){
    flag_cal_kernel = 1;

    mat_sigma.resize(vec_data_x.size(),vec_data_x.size());
    for (size_t i=0;i!=vec_data_x.size();i++){
      for (size_t j=0;j!=vec_data_x.size();j++){
	mat_sigma(i,j) = sigma(vec_data_x.at(i),vec_data_x.at(j));
	if (i==j);
	mat_sigma(i,j) += pow(vec_data_dy.at(i),2);
      }
    }
    inv_mat_sigma = mat_sigma.inverse();
    
  }
}


std::vector<double> GaussProcess::cal_conditional_mean(std::vector<double>& vec_x){
  Eigen::VectorXd vec_Y(vec_data_y.size());
  for (size_t i = 0; i!=vec_data_y.size(); i++){
    vec_Y(i) = vec_data_y.at(i);
  }

  cal_kernel();

  Eigen::MatrixXd mat_pred(vec_x.size(),vec_data_y.size());
  for (size_t i=0;i!=vec_x.size();i++){
    for (size_t j=0;j!=vec_data_x.size();j++){
      mat_pred(i,j) = sigma(vec_x.at(i),vec_data_x.at(j));
    }
  }

  Eigen::VectorXd vec_res = mat_pred * inv_mat_sigma * vec_Y;

  std::vector<double> results;
  for (size_t i=0;i!=vec_x.size();i++){
    results.push_back(vec_res(i));
  }
  return results;
  
}

std::vector<double> GaussProcess::cal_conditional_variance(std::vector<double>& vec_x){
  Eigen::MatrixXd sigma_new(vec_x.size(),vec_x.size());
  for (size_t i=0;i!=vec_x.size();i++){
    for (size_t j=0;j!=vec_x.size();j++){
      sigma_new(i,j) = sigma(vec_x.at(i),vec_x.at(j));
    }
  }

  Eigen::MatrixXd mat_pred(vec_x.size(),vec_data_y.size());
  for (size_t i=0;i!=vec_x.size();i++){
    for (size_t j=0;j!=vec_data_x.size();j++){
      mat_pred(i,j) = sigma(vec_x.at(i),vec_data_x.at(j));
    }
  }

  Eigen::MatrixXd mat_pred_T = mat_pred.transpose();
  cal_kernel();

  sigma_new = sigma_new - mat_pred * inv_mat_sigma * mat_pred_T;
  
  
  std::vector<double> results;
  for (size_t i=0;i!=vec_x.size();i++){
    results.push_back(sigma_new(i,i));
  }
  return results;
}
