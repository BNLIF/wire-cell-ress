#include "WCPRess/GaussProcess.h"

#include <iostream>
using namespace std;
using namespace WCP;

int main(int argc, char* argv[])
{
  GaussProcess gp(1);
  
  std::vector<double> pars;
  pars.push_back(0.5);
  pars.push_back(1);
  gp.set_parameters(pars);

  std::vector<std::tuple<double,double,double> > data;
  data.push_back(std::make_tuple(1,  0.3,0.1));
  data.push_back(std::make_tuple(1.5,0.2,0.05));
  data.push_back(std::make_tuple(2,  0,0.2));
  data.push_back(std::make_tuple(4,  -0.3,0.005));
  data.push_back(std::make_tuple(4.5,-0.4,0.1));
  data.push_back(std::make_tuple(5,  0.2,0.2));
  data.push_back(std::make_tuple(5.5,0.3,0.05));
  data.push_back(std::make_tuple(8,  -0.2,0.01));
  data.push_back(std::make_tuple(9,  -0.3,0.1));
  data.push_back(std::make_tuple(10, -0.1,0.01));

  gp.set_measurements(data);

  std::vector<double> vec_x;
  vec_x.push_back(1.3);
  vec_x.push_back(2.5);
  vec_x.push_back(3.7);

  std::vector<double> vec_y = gp.cal_conditional_mean(vec_x);
  std::vector<double> vec_var_y = gp.cal_conditional_variance(vec_x);
  for (size_t i=0;i!=vec_y.size();i++){
    std::cout << vec_x.at(i) << " "<< vec_y.at(i) << " " << vec_var_y.at(i) << std::endl;
  }

  
  return 0;
}
