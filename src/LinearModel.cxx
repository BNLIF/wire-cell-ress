#include "WCPRess/LinearModel.h"

#include <Eigen/Dense>
using namespace Eigen;

WCP::LinearModel::LinearModel()
{}

WCP::LinearModel::~LinearModel()
{}

VectorXd WCP::LinearModel::Predict()
{
    return _X * _beta;
}

double WCP::LinearModel::chi2_base()
{
    return ( _y - Predict() ).squaredNorm();
}


double WCP::LinearModel::MeanResidual()
{
    return ( _y - Predict() ).norm() / _y.size();
}
