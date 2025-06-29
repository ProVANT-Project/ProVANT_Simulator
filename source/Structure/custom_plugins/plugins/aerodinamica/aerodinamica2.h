/*
 * This file is part of the ProVANT simulator project.
 * Licensed under the terms of the MIT open source license. More details at
 * https://github.com/Guiraffo/ProVANT-Simulator/blob/master/LICENSE.md
 */
/**
 * @file aerodinamica2.h
 * @brief This file contains the declaration of a Gazebo model plugin that
 * simulate aerodinamics.
 *
 * @author Jonatan Campos
 * @author Júnio Eduardo de Morais Aquino
 */

#ifndef PROVANT_AERODINAMICA_H
#define PROVANT_AERODINAMICA_H

#include <gazebo/common/Events.hh>
#include <gazebo/common/Plugin.hh>
#include <gazebo/physics/physics.hh>

#include <ros/ros.h>
#include <std_msgs/Float64.h>

#include <eigen3/Eigen/Eigen>

#include <MatlabData.h>

namespace gazebo
{
class Aerodinamica2 : public ModelPlugin
{
public:
  Aerodinamica2();
  virtual ~Aerodinamica2();
  void Load(physics::ModelPtr _model, sdf::ElementPtr _sdf) override;
  void CallbackFR(std_msgs::Float64);
  void CallbackFL(std_msgs::Float64);
  void CallbackFElev(std_msgs::Float64);
  void CallbackFRud(std_msgs::Float64);

protected:
  // adicionada função callback para atualizar a força da fuselagem:
  virtual void Update();

private:
  // adiciona funções auxiliares para atualizar a aerodinâmica:
  double getAlpha(double wb, double wa, double ub, double ua);
  double getBeta(double vb, double va, double ub, double ua);
  double getAirxy(double wb, double wa, double ub, double ua);
  double getAirxz(double vb, double va, double ub, double ua);
  double c_r(double Dr);
  double c_e(double De);

  std::string path;
  ros::NodeHandle node_handle_;

  physics::WorldPtr world;
  physics::LinkPtr linkFr;
  physics::LinkPtr linkFl;
  physics::LinkPtr linkE;
  physics::LinkPtr linkR;
  physics::LinkPtr link;
  physics::JointPtr JointFl;
  physics::JointPtr JointFr;

  std::string topic_Fr;
  std::string topic_Fl;
  std::string topic_Elev;
  std::string topic_Rud;

  ros::Subscriber motor_subscriberFL_;
  ros::Subscriber motor_subscriberFR_;
  ros::Subscriber motor_subscriberFElev_;
  ros::Subscriber motor_subscriberFRud_;

  std::string NameOfLinkFr_;
  std::string NameOfLinkFl_;
  std::string NameOfLinkBody_;
  std::string NameOfJointFl_;
  std::string NameOfJointFr_;

  boost::mutex lock;
  event::ConnectionPtr updateConnection;
  // Tempo Aerodinamica2 %Passo integracao Gazebo
  double T;

    MatlabData Wind;

  // velocidades lineares decompostas do vento e corpo
  double ua, va, wa, ub, vb, wb, phi, theta, psi;  //, x, y, z;
  double RudderDeflection;
  double ElevatorDeflection;
  // ângulo de ataque e derrapagem
  double Alpha, Beta, Ho, sf, sh, sv;  //, kt, b;
  double Vxz, Vxy, Fr, Fl;
  double VetCDv[63] = { 0.0071,  -0.11395, 0.10658, 0.45137,  0.711,    0.85029,  0.98929,  1.1324,   1.2382,
                        1.3224,  1.3995,   1.4579,  1.5009,   1.5443,   1.581,    1.5978,   1.5993,   1.5894,
                        1.5642,  1.5276,   1.4894,  1.4474,   1.3927,   1.3111,   1.222,    1.1889,   1.0564,
                        0.67454, 0.30154,  0.11121, 0.024927, 0.010853, 0.012969, 0.035073, 0.13043,  0.35371,
                        0.74531, 1.0998,   1.1925,  1.2344,   1.327,    1.4034,   1.4551,   1.4959,   1.5341,
                        1.5695,  1.592,    1.5998,  1.5963,   1.5761,   1.537,    1.494,    1.4497,   1.3875,
                        1.3087,  1.2227,   1.1104,  0.96413,  0.82972,  0.67893,  0.39398,  0.054892, -0.1234 };

  double VetCLv[63] = { 0,        0.3994,   0.55274,  0.58755,  0.62718,  0.70302,  0.76193,  0.7903,    0.79189,
                        0.75553,  0.68102,  0.59354,  0.49502,  0.36827,  0.23541,  0.114,    -0.061171, -0.30075,
                        -0.49385, -0.61787, -0.73228, -0.84611, -0.94327, -1.0036,  -1.0128,  -0.97063,  -0.92622,
                        -0.99894, -1.0372,  -0.74074, -0.43079, -0.12844, 0.18012,  0.48016,  0.79568,   1.0575,
                        0.97331,  0.92997,  0.98023,  1.0149,   0.99685,  0.92894,  0.82764,  0.71268,   0.59908,
                        0.46781,  0.26059,  0.024942, -0.13593, -0.25643, -0.39112, -0.51329, -0.60848,  -0.69516,
                        -0.76483, -0.79388, -0.78733, -0.75437, -0.69013, -0.61666, -0.58454, -0.53872,  -0.35292 };

  double VetCDf[63] = { 0.025,   0.065452, 0.16654,  0.26951,  0.37366,   0.52852,   0.73279,  0.92854,  1.1099,
                        1.2652,  1.4051,   1.5216,   1.6162,   1.694,     1.7517,    1.7846,   1.8024,   1.7931,
                        1.7549,  1.6829,   1.5829,   1.4625,   1.318,     1.1666,    0.99974,  0.80772,  0.60564,
                        0.42784, 0.2875,   0.023346, 0.012045, 0.0068935, 0.0072707, 0.013511, 0.017643, 0.30916,
                        0.45295, 0.63915,  0.8418,   1.0291,   1.193,     1.3428,    1.4847,   1.6012,   1.6972,
                        1.7637,  1.7964,   1.8013,   1.7799,   1.7438,    1.6823,    1.601,    1.5045,   1.3823,
                        1.2406,  1.0812,   0.8966,   0.69802,  0.49702,   0.35513,   0.25209,  0.14907,  0.051889 };

  double VetCLf[63] = { 0,        0.74461,  0.81047,  0.64392,   0.70064,  0.8229,   0.90449,  0.94542,  0.94146,
                        0.89219,  0.79445,  0.6682,   0.5406,    0.3852,   0.21348,  0.043238, -0.11908, -0.29265,
                        -0.4615,  -0.62107, -0.75584, -0.88146,  -0.98183, -1.0626,  -1.0791,  -1.082,   -0.90438,
                        -0.92431, -0.65444, -0.91363, -0.89073,  -0.26214, 0.36812,  0.9726,   0.74113,  0.69509,
                        0.97793,  0.92464,  1.0841,   1.0828,    1.0509,   0.96642,  0.86173,  0.73431,  0.59556,
                        0.43358,  0.26364,  0.090584, -0.070567, -0.24276, -0.41334, -0.56309, -0.68936, -0.81442,
                        -0.90355, -0.94545, -0.94099, -0.89544,  -0.80124, -0.68545, -0.65111, -0.83993, -0.67012 };
  //      		double VetCLf[63] =
  //					{0,0.74461,   0.81047,  0.64392,   0.70064,    0.8229,   0.90449,  0.94542,
  //                       0.94146,   0.89219,  0.79445,    0.6682,    0.5406,    0.3852,  0.21348,
  //                      0.043238,  -0.11908, -0.29265,   -0.4615,  -0.62107,  -0.75584, -0.88146,
  //                      -0.98195,   -1.0618,   -1.083,   -1.0583,   -0.8989,  -0.92432, -0.65444,
  //                      -0.91363,  -0.89073, -0.26214,   0.36812,    0.9726,   0.74113,  0.69509,
  //                       0.97789,   0.91181,   1.0676,    1.0854,    1.0505,   0.96643,  0.86174,
  //                        0.7343,   0.59556,  0.43358,   0.26364,  0.090584, -0.070567, -0.24276,
  //                      -0.41334,  -0.56309, -0.68936,  -0.81442,  -0.90355,  -0.94545, -0.94099,
  //                      -0.89544,  -0.80124, -0.68545,  -0.65111,  -0.83993, -0.67012};

  double VetCDh[63] = { 0.01,    -0.014686, 0.039606, 0.14179,  0.26115,  0.37536,  0.4718,   0.55138,  0.62136,
                        0.68835, 0.75304,   0.80588,  0.84351,  0.86966,  0.89079,  0.91094,  0.92141,  0.91636,
                        0.89982, 0.87552,   0.84549,  0.8076,   0.75908,  0.70106,  0.63335,  0.55213,  0.45149,
                        0.33068, 0.18957,   0.086203, 0.035775, 0.010921, 0.013072, 0.042734, 0.098476, 0.21631,
                        0.42069, 0.60983,   0.75792,  0.85157,  0.92049,  0.98952,  1.0572,   1.1133,   1.1518,
                        1.1738,  1.1892,    1.1993,   1.1997,   1.1876,   1.1619,   1.1241,   1.0777,   1.0276,
                        0.96749, 0.88554,   0.7838,   0.66984,  0.55251,  0.41773,  0.22878,  0.033737, -0.062168 };

  double VetCLh[63] = { 0,        0.59164,  0.69735,  0.61673,  0.63814,  0.80205, 0.92648,  0.98066,   1.0012,
                        0.97829,  0.90569,  0.80394,  0.68694,  0.55683,  0.3929,  0.17536,  -0.074495, -0.32313,
                        -0.53312, -0.69313, -0.81462, -0.90425, -0.96773, -1.016,  -1.0475,  -1.0422,   -1.0261,
                        -0.9924,  -0.92609, -0.98447, -0.58049, -0.17426, 0.23549, 0.6446,   0.99882,   0.8849,
                        0.97275,  1.0499,   1.0893,   1.1125,   1.0981,   1.0053,  0.86342,  0.71528,   0.56377,
                        0.40394,  0.22927,  0.027647, -0.20726, -0.42502, -0.5818, -0.70695, -0.82204,  -0.92071,
                        -0.98601, -1.0002,  -0.97439, -0.91178, -0.77285, -0.6198, -0.63052, -0.70076,  -0.5343 };

  // forças aerodinâmicas
  //			ignition::math::Vector3d Ff, Fh, Fv;
  ignition::math::Pose3d pose;
  Eigen::MatrixXd R_IB, wind_I, wind_B;
  Eigen::VectorXd DBf;
  Eigen::VectorXd DBh;
  Eigen::VectorXd DBv;
};
}  // namespace gazebo

#endif  // PROVANT_AERODINAMICA_H
