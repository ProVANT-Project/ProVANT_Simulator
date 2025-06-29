/*
 * This file is part of the ProVANT simulator project.
 * Licensed under the terms of the MIT open source license. More details at
 * https://github.com/Guiraffo/ProVANT-Simulator/blob/master/LICENSE.md
 */
/**
 * @file routines.cpp
 * @brief This file contains the implementation of the routines class.
 *
 * @author Brenner Santana Rego
 */

#include "vant2load_franklin/routines.h"

#include <cmath>
#include <random>

void routines::generate_Trajectory(int k, double Ts, int which_trajectory, Eigen::MatrixXd& csiref,
                                   Eigen::MatrixXd& csirefdot, Eigen::MatrixXd& csirefddot)
{
  // k = Time instant k
  double t = k * Ts;

  double x;
  double y;
  double z;
  double xdot;
  double ydot;
  double zdot;
  double xddot;
  double yddot;
  double zddot;

  // Parameters for trajectory 1
  double trajectoryRadius = 2;
  double trajectoryHeight = 4 * trajectoryRadius;
  double trajTime = 40;

  // double pi = M_PI;
  double pi = 3.14159265358979323846;

  switch (which_trajectory)
  {
    case 0:  // Hovering
      x = 0;
      y = 0;
      z = 0 + 1;
      xdot = 0;
      ydot = 0;
      zdot = 0;
      xddot = 0;
      yddot = 0;
      zddot = 0;

      break;

    case 1:  // Trajetoria artigo SBAI c/ Arthur
      x = trajectoryRadius * cos(t * 2 * pi / trajTime);
      xdot = -trajectoryRadius * (2 * pi / trajTime) * sin(t * 2 * pi / trajTime);
      xddot = -trajectoryRadius * (2 * pi / trajTime) * (2 * pi / trajTime) * cos(t * 2 * pi / trajTime);

      y = trajectoryRadius * sin(t * 2 * pi / trajTime);
      ydot = trajectoryRadius * (2 * pi / trajTime) * cos(t * 2 * pi / trajTime);
      yddot = -trajectoryRadius * (2 * pi / trajTime) * (2 * pi / trajTime) * sin(t * 2 * pi / trajTime);

      z = trajectoryHeight + 1 - trajectoryHeight * cos(t * 2 * pi / trajTime);
      zdot = trajectoryHeight * (2 * pi / trajTime) * sin(t * 2 * pi / trajTime);
      zddot = trajectoryHeight * (2 * pi / trajTime) * (2 * pi / trajTime) * cos(t * 2 * pi / trajTime);

      break;

    case 2:  // Second trajectory from Rego's Master thesis
      x = 0;
      y = 0;
      z = 0;
      xdot = 0;
      ydot = 0;
      zdot = 0;
      xddot = 0;
      yddot = 0;
      zddot = 0;

      if (t < 10)  // Region 1
      {
        x = 0.01 * (pow(t, 2.0)) * cos(pi * t / 4);
        y = sin(pi * t / 20) * sin(pi * t / 4);
        z = 2.5 - 2.5 * cos(pi * t / 10) + 1;

        xdot = 0.02 * t * cos(pi * t / 4) - 0.01 * (pow(t, 2.0)) * (pi / 4) * sin(pi * t / 4);
        ydot = (pi / 20) * cos(pi * t / 20) * sin(pi * t / 4) + (pi / 4) * sin(pi * t / 20) * cos(pi * t / 4);
        zdot = 2.5 * (pi / 10) * sin(pi * t / 10);

        xddot = 0.02 * cos(pi * t / 4) - 0.02 * t * (pi / 4) * sin(pi * t / 4) -
                (0.02 * t * (pi / 4) * sin(pi * t / 4) + 0.01 * (pow(t, 2.0)) * (pi / 4) * (pi / 4) * cos(pi * t / 4));
        yddot = -(pi / 20) * (pi / 20) * sin(pi * t / 20) * sin(pi * t / 4) +
                (pi / 20) * (pi / 4) * cos(pi * t / 20) * cos(pi * t / 4) +
                ((pi / 4) * (pi / 20) * cos(pi * t / 20) * cos(pi * t / 4) -
                 (pi / 4) * (pi / 4) * sin(pi * t / 20) * sin(pi * t / 4));
        zddot = 2.5 * (pi / 10) * (pi / 10) * cos(pi * t / 10);
      }
      else if (10 <= t && t < 19)  // Region 2
      {
        x = -(pi / 4) * (t - 10);
        y = 1;
        z = 5 + 1;

        xdot = -pi / 4;
        ydot = 0;
        zdot = 0;

        xddot = 0;
        yddot = 0;
        zddot = 0;
      }
      else if (19 <= t && t < 20)  // Region 3
      {
        x = -(9 * pi / 4) - 0.5 * sin((pi / 2) * (t - 19));
        y = 1.5 - 0.5 * cos((pi / 2) * (t - 19));
        z = 5 + 1;

        xdot = -(pi / 4) * cos((pi / 2) * (t - 19));
        ydot = (pi / 4) * sin((pi / 2) * (t - 19));
        zdot = 0;

        xddot = (pi / 4) * (pi / 2) * sin((pi / 2) * (t - 19));
        yddot = (pi / 4) * (pi / 2) * cos((pi / 2) * (t - 19));
        zddot = 0;
      }
      else if (20 <= t && t < 29)  // Region 4
      {
        x = -(9 * pi / 4) - 0.5;
        y = 1.5 + (pi / 4) * (t - 20);
        z = 5 + 1;

        xdot = 0;
        ydot = pi / 4;
        zdot = 0;

        xddot = 0;
        yddot = 0;
        zddot = 0;
      }
      else if (29 <= t && t < 30)  // Region 5
      {
        x = -(9 * pi / 4) - 0.5 * cos((pi / 2) * (t - 29));
        y = 1.5 + (9 * pi / 4) + 0.5 * sin((pi / 2) * (t - 29));
        z = 5 + 1;

        xdot = (pi / 4) * sin((pi / 2) * (t - 29));
        ydot = (pi / 4) * cos((pi / 2) * (t - 29));
        zdot = 0;

        xddot = (pi / 4) * (pi / 2) * cos((pi / 2) * (t - 29));
        yddot = -(pi / 4) * (pi / 2) * sin((pi / 2) * (t - 29));
        zddot = 0;
      }
      else if (30 <= t && t < 40)  // Region 6
      {
        x = -(9 * pi / 4) + (pi / 4) * (t - 30);
        y = 2 + (9 * pi / 4);
        z = 5 + 1;

        xdot = pi / 4;
        ydot = 0;
        zdot = 0;

        xddot = 0;
        yddot = 0;
        zddot = 0;
      }
      else if (40 <= t && t < 50)  // Region 7
      {
        x = -(pi / 80) * (pow(t, 2.0)) + (5 * pi / 4) * t - (119 * pi / 4);
        y = 2 + (9 * pi / 4);
        z = 2.5 + 2.5 * cos((pi / 10) * (t - 40)) + 1;

        xdot = -(pi / 40) * t + (5 * pi / 4);
        ydot = 0;
        zdot = -2.5 * (pi / 10) * sin((pi / 10) * (t - 40));

        xddot = -pi / 40;
        yddot = 0;
        zddot = -2.5 * (pi / 10) * (pi / 10) * cos((pi / 10) * (t - 40));
      }
      else if (t >= 50)  // Stop
      {
        x = 4.7124;
        y = 9.0686;
        z = 0 + 1;

        xdot = 0;
        ydot = 0;
        zdot = 0;

        xddot = 0;
        yddot = 0;
        zddot = 0;
      }

      break;

    default:

      x = 0;
      y = 0;
      z = 0;
      xdot = 0;
      ydot = 0;
      zdot = 0;
      xddot = 0;
      yddot = 0;
      zddot = 0;

      break;
  }

  csiref << x, y, z;
  csirefdot << xdot, ydot, zdot;
  csirefddot << xddot, yddot, zddot;
}

Eigen::MatrixXd routines::generate_Disturbances(int k, double Ts, int which_disturbance)
{
  // k = Time instant k
  double t = k * Ts;

  double dtrbX = 0;
  double dtrbY = 0;
  double dtrbZ = 0;

  // Parameters for disturbances 1
  double finaltime = 50;  // In seconds
  double dtrbMag = 0.1;   // In Newtons

  switch (which_disturbance)
  {
    case 0:  // No disturbances
      dtrbX = 0;
      dtrbY = 0;
      dtrbZ = 0;

      break;

    case 1:  // Disturbances from Rego's Master thesis, second trajectory
      dtrbX = 0;
      dtrbY = 0;
      dtrbZ = 0;

      if ((finaltime / 8) <= t && t < (finaltime / 2 + finaltime / 8))
      {
        dtrbX = dtrbMag;
      }
      else if ((finaltime / 4) <= t && t < (finaltime / 2 + finaltime / 4))
      {
        dtrbY = dtrbMag;
      }
      else if ((finaltime / 4 + finaltime / 8) <= t && t < (finaltime / 2 + finaltime / 4 + finaltime / 8))
      {
        dtrbZ = dtrbMag;
      }
      else
      {
        dtrbX = 0;
        dtrbY = 0;
        dtrbZ = 0;
      }

      break;

    default:
      dtrbX = 0;
      dtrbY = 0;
      dtrbZ = 0;

      break;
  }

  Eigen::MatrixXd dtrb(3, 1);
  dtrb << dtrbX, dtrbY, dtrbZ;
  return dtrb;
}

double routines::first_order_filter(double in_prev, double in)
{
  double A = 0.976285709757909;
  double B = 0.011857145121045;
  double C = 2;

  double out = C * (A * in_prev / C + B * in);

  return out;
}

void routines::generate_Measurement(int k, double Ts, simulator_msgs::Sensor mainbody,
                                    simulator_msgs::Sensor rightpropeller, simulator_msgs::Sensor leftpropeller,
                                    simulator_msgs::Sensor load, simulator_msgs::Sensor rightservo,
                                    simulator_msgs::Sensor leftservo, simulator_msgs::Sensor rodx,
                                    simulator_msgs::Sensor rody, std::vector<double>& y, std::vector<int>& I)
{
  // double noise;
  double pi = 3.14159265358979323846;

  double dA1Bx = 0;
  double dA1By = 0;
  double dA1Bz = 0.119;

  // Sampling rates (in seconds)
  double T_GPS = 0.120;
  double T_Barometer = 0.012;
  double T_IMU = 0.012;
  double T_Camera = 0.024;
  double T_Servos = 0.012;

  // Sampling multiples
  int T_GPS_multiple = T_GPS / Ts;
  int T_Barometer_multiple = T_Barometer / Ts;
  int T_IMU_multiple = T_IMU / Ts;
  int T_Camera_multiple = T_Camera / Ts;
  int T_Servos_multiple = T_Servos / Ts;

  // Random number generators
  static std::default_random_engine gen00(rand());
  static std::default_random_engine gen01(rand());
  static std::default_random_engine gen02(rand());
  static std::default_random_engine gen03(rand());
  static std::default_random_engine gen04(rand());
  static std::default_random_engine gen05(rand());
  static std::default_random_engine gen06(rand());
  static std::default_random_engine gen07(rand());
  static std::default_random_engine gen08(rand());
  static std::default_random_engine gen09(rand());
  static std::default_random_engine gen10(rand());
  static std::default_random_engine gen11(rand());
  static std::default_random_engine gen12(rand());
  static std::default_random_engine gen13(rand());
  static std::default_random_engine gen14(rand());
  static std::default_random_engine gen15(rand());  // One generator for each sensor, each one with a different seed

  std::normal_distribution<double> GPS_x(0, 0.05);                   // sigma = 0.05 m
  std::normal_distribution<double> GPS_y(0, 0.05);                   // sigma = 0.05 m
  std::normal_distribution<double> Barometer(0, 0.17);               // sigma = 0.17 m
  std::normal_distribution<double> IMU_phi(0, (0.05 * pi / 180));    // sigma = (0.05*pi/180) rad
  std::normal_distribution<double> IMU_theta(0, (0.05 * pi / 180));  // sigma = (0.05*pi/180) rad
  std::normal_distribution<double> IMU_psii(0, (0.05 * pi / 180));   // sigma = (0.05*pi/180) rad
  std::normal_distribution<double> IMU_p(0, 0.005519215703220);      // sigma = 0.005519215703220 rad/s
  std::normal_distribution<double> IMU_q(0, 0.005519215703220);      // sigma = 0.005519215703220 rad/s
  std::normal_distribution<double> IMU_r(0, 0.005519215703220);      // sigma = 0.005519215703220 rad/s
  std::uniform_real_distribution<double> Camera_x(-0.005, 0.005);    // resolution = 0.5 cm
  std::uniform_real_distribution<double> Camera_y(-0.005, 0.005);    // resolution = 0.5 cm
  std::uniform_real_distribution<double> Camera_z(-0.02, 0.02);      // resolution = 2 cm
  std::uniform_real_distribution<double> Servos_aR(-(0.325 * pi / 180),
                                                   (0.325 * pi / 180));  // resolution = 0.325 deg
  std::uniform_real_distribution<double> Servos_aL(-(0.325 * pi / 180),
                                                   (0.325 * pi / 180));  // resolution = 0.325 deg
  std::uniform_real_distribution<double> Servos_daR(-(29.09 * pi / 180),
                                                    (29.09 * pi / 180));  // resolution = 29.09 deg/s
  std::uniform_real_distribution<double> Servos_daL(-(29.09 * pi / 180),
                                                    (29.09 * pi / 180));  // resolution = 29.09 deg/s

  // Get sensor data plus noise (indexes from UniversalLinkSensor.cpp and UniversalJointSensor.cpp)
  // GPS
  double xB = mainbody.values.at(24) + GPS_x(gen00);
  double yB = mainbody.values.at(25) + GPS_y(gen01);

  // Barometer
  double zB = mainbody.values.at(26) + Barometer(gen02);

  // IMU
  double phiB = mainbody.values.at(27) + IMU_phi(gen03);
  double thetaB = mainbody.values.at(28) + IMU_theta(gen04);
  ;
  double psiiB = mainbody.values.at(29) + IMU_psii(gen05);
  ;
  std::vector<double> pqr = wIIL2pqr(mainbody.values.at(39), mainbody.values.at(40), mainbody.values.at(41),
                                     mainbody.values.at(27), mainbody.values.at(28), mainbody.values.at(29));
  double p = pqr.at(0) + IMU_p(gen06);
  double q = pqr.at(1) + IMU_q(gen07);
  double r = pqr.at(2) + IMU_r(gen08);

  double gamma1 = rodx.values.at(0);
  double gamma2 = rody.values.at(0);

  Eigen::MatrixXd RLB(3, 3);
  RLB = rotx(-gamma1) * roty(-gamma2);

  double l = 0.5;
  Eigen::MatrixXd dLA1(3, 1);
  dLA1 << 0, 0, l;

  Eigen::MatrixXd dA1A1L(3, 1);
  dA1A1L = -RLB.transpose() * dLA1;
  double dA1A1L_x = dA1A1L(0) + Camera_x(gen09);
  double dA1A1L_y = dA1A1L(1) + Camera_y(gen10);
  double dA1A1L_z = dA1A1L(2) + Camera_z(gen11);

  // Servos
  double aR = rightservo.values.at(0) + Servos_aR(gen12);
  double aL = leftservo.values.at(0) + Servos_aL(gen13);
  double aRdot = rightservo.values.at(1) + Servos_daR(gen14);
  double aLdot = leftservo.values.at(1) + Servos_daL(gen15);

  if (k == 0)  // Initial instant time, all sensors are available
  {
    y.push_back(xB);
    I.push_back(0);
    y.push_back(yB);
    I.push_back(1);
    y.push_back(zB);
    I.push_back(2);
    y.push_back(phiB);
    I.push_back(3);
    y.push_back(thetaB);
    I.push_back(4);
    y.push_back(psiiB);
    I.push_back(5);
    y.push_back(p);
    I.push_back(6);
    y.push_back(q);
    I.push_back(7);
    y.push_back(r);
    I.push_back(8);
    y.push_back(dA1A1L_x);
    I.push_back(9);
    y.push_back(dA1A1L_y);
    I.push_back(10);
    y.push_back(dA1A1L_z);
    I.push_back(11);
    y.push_back(aR);
    I.push_back(12);
    y.push_back(aL);
    I.push_back(13);
    y.push_back(aRdot);
    I.push_back(14);
    y.push_back(aLdot);
    I.push_back(15);
  }
  else
  {
    if ((k % T_GPS_multiple) == 0)  // If the GPS is available
    {
      y.push_back(xB);
      I.push_back(0);
      y.push_back(yB);
      I.push_back(1);
    }

    if ((k % T_Barometer_multiple) == 0)  // If the Barometer is available
    {
      y.push_back(zB);
      I.push_back(2);
    }

    if ((k % T_IMU_multiple) == 0)  // If the IMU is available
    {
      y.push_back(phiB);
      I.push_back(3);
      y.push_back(thetaB);
      I.push_back(4);
      y.push_back(psiiB);
      I.push_back(5);
      y.push_back(p);
      I.push_back(6);
      y.push_back(q);
      I.push_back(7);
      y.push_back(r);
      I.push_back(8);
    }

    if ((k % T_Camera_multiple) == 0)  // If the Camera is available
    {
      y.push_back(dA1A1L_x);
      I.push_back(9);
      y.push_back(dA1A1L_y);
      I.push_back(10);
      y.push_back(dA1A1L_z);
      I.push_back(11);
    }

    if ((k % T_Servos_multiple) == 0)  // If the Servos sensors are available
    {
      y.push_back(aR);
      I.push_back(12);
      y.push_back(aL);
      I.push_back(13);
      y.push_back(aRdot);
      I.push_back(14);
      y.push_back(aLdot);
      I.push_back(15);
    }
  }
}

void routines::generate_Measurement_clean(int k, double Ts, simulator_msgs::Sensor mainbody,
                                          simulator_msgs::Sensor rightpropeller, simulator_msgs::Sensor leftpropeller,
                                          simulator_msgs::Sensor load, simulator_msgs::Sensor rightservo,
                                          simulator_msgs::Sensor leftservo, simulator_msgs::Sensor rodx,
                                          simulator_msgs::Sensor rody, std::vector<double>& y, std::vector<int>& I)
{
  double pi = 3.14159265358979323846;

  double dA1Bx = 0;
  double dA1By = 0;
  double dA1Bz = 0.119;

  // Sampling rates (in seconds)
  double T_GPS = 0.120;
  double T_Barometer = 0.012;
  double T_IMU = 0.012;
  double T_Camera = 0.024;
  double T_Servos = 0.012;

  // Sampling multiples
  int T_GPS_multiple = T_GPS / Ts;
  int T_Barometer_multiple = T_Barometer / Ts;
  int T_IMU_multiple = T_IMU / Ts;
  int T_Camera_multiple = T_Camera / Ts;
  int T_Servos_multiple = T_Servos / Ts;

  // Get sensor data (indexes from UniversalLinkSensor.cpp and UniversalJointSensor.cpp)
  // GPS
  double xB = mainbody.values.at(24);
  double yB = mainbody.values.at(25);

  // Barometer
  double zB = mainbody.values.at(26);

  // IMU
  double phiB = mainbody.values.at(27);
  double thetaB = mainbody.values.at(28);
  double psiiB = mainbody.values.at(29);
  std::vector<double> pqr = routines::wIIL2pqr(mainbody.values.at(39), mainbody.values.at(40), mainbody.values.at(41),
                                               mainbody.values.at(27), mainbody.values.at(28), mainbody.values.at(29));
  double p = pqr.at(0);
  double q = pqr.at(1);
  double r = pqr.at(2);

  double gamma1 = rodx.values.at(0);
  double gamma2 = rody.values.at(0);

  Eigen::MatrixXd RLB(3, 3);
  RLB = routines::rotx(-gamma1) * routines::roty(-gamma2);

  double l = 0.5;
  Eigen::MatrixXd dLA1(3, 1);
  dLA1 << 0, 0, l;

  Eigen::MatrixXd dA1A1L(3, 1);
  dA1A1L = -RLB.transpose() * dLA1;
  double dA1A1L_x = dA1A1L(0);
  double dA1A1L_y = dA1A1L(1);
  double dA1A1L_z = dA1A1L(2);

  // Servos
  double aR = rightservo.values.at(0);
  double aL = leftservo.values.at(0);
  double aRdot = rightservo.values.at(1);
  double aLdot = leftservo.values.at(1);

  if (k == 0)  // Initial instant time, all sensors are available
  {
    y.push_back(xB);
    I.push_back(0);
    y.push_back(yB);
    I.push_back(1);
    y.push_back(zB);
    I.push_back(2);
    y.push_back(phiB);
    I.push_back(3);
    y.push_back(thetaB);
    I.push_back(4);
    y.push_back(psiiB);
    I.push_back(5);
    y.push_back(p);
    I.push_back(6);
    y.push_back(q);
    I.push_back(7);
    y.push_back(r);
    I.push_back(8);
    y.push_back(dA1A1L_x);
    I.push_back(9);
    y.push_back(dA1A1L_y);
    I.push_back(10);
    y.push_back(dA1A1L_z);
    I.push_back(11);
    y.push_back(aR);
    I.push_back(12);
    y.push_back(aL);
    I.push_back(13);
    y.push_back(aRdot);
    I.push_back(14);
    y.push_back(aLdot);
    I.push_back(15);
  }
  else
  {
    if ((k % T_GPS_multiple) == 0)  // If the GPS is available
    {
      y.push_back(xB);
      I.push_back(0);
      y.push_back(yB);
      I.push_back(1);
    }

    if ((k % T_Barometer_multiple) == 0)  // If the Barometer is available
    {
      y.push_back(zB);
      I.push_back(2);
    }

    if ((k % T_IMU_multiple) == 0)  // If the IMU is available
    {
      y.push_back(phiB);
      I.push_back(3);
      y.push_back(thetaB);
      I.push_back(4);
      y.push_back(psiiB);
      I.push_back(5);
      y.push_back(p);
      I.push_back(6);
      y.push_back(q);
      I.push_back(7);
      y.push_back(r);
      I.push_back(8);
    }

    if ((k % T_Camera_multiple) == 0)  // If the Camera is available
    {
      y.push_back(dA1A1L_x);
      I.push_back(9);
      y.push_back(dA1A1L_y);
      I.push_back(10);
      y.push_back(dA1A1L_z);
      I.push_back(11);
    }

    if ((k % T_Servos_multiple) == 0)  // If the Servos sensors are available
    {
      y.push_back(aR);
      I.push_back(12);
      y.push_back(aL);
      I.push_back(13);
      y.push_back(aRdot);
      I.push_back(14);
      y.push_back(aLdot);
      I.push_back(15);
    }
  }
}

std::vector<double> routines::wIIB2EtaDot(double in_a, double in_b, double in_c, double phi, double theta, double psii)
{
  std::vector<double> out;
  out.push_back((in_a * cos(psii) + in_b * sin(psii)) / cos(theta));
  out.push_back(in_b * cos(psii) - in_a * sin(psii));
  out.push_back(in_c + in_a * cos(psii) * tan(theta) + in_b * sin(psii) * tan(theta));
  return out;
}

std::vector<double> routines::pqr2EtaDot(double in_a, double in_b, double in_c, double phi, double theta, double psii)
{
  std::vector<double> out;
  out.push_back(in_a + in_c * cos(phi) * tan(theta) + in_b * sin(phi) * tan(theta));
  out.push_back(in_b * cos(phi) - in_c * sin(phi));
  out.push_back((in_c * cos(phi)) / cos(theta) + (in_b * sin(phi)) / cos(theta));
  return out;
}

std::vector<double> routines::wIIL2pqr(double in_a, double in_b, double in_c, double phi, double theta, double psii)
{
  // Converts wIIB to pqr
  std::vector<double> out;

  Eigen::MatrixXd RIB(3, 3);

  RIB = rotz(psii) * roty(theta) * rotx(phi);

  Eigen::MatrixXd wIIB(3, 1);

  wIIB << in_a, in_b, in_c;

  Eigen::MatrixXd pqr(3, 1);

  pqr = RIB.transpose() * wIIB;

  out.push_back(pqr(0));
  out.push_back(pqr(1));
  out.push_back(pqr(2));

  return out;
}

Eigen::MatrixXd routines::rotx(double angle)
{
  // Rotation about x axis

  Eigen::MatrixXd out(3, 3);

  out << 1, 0, 0, 0, cos(angle), -sin(angle), 0, sin(angle), cos(angle);

  return out;
}

Eigen::MatrixXd routines::roty(double angle)
{
  // Rotation about y axis

  Eigen::MatrixXd out(3, 3);

  out << cos(angle), 0, sin(angle), 0, 1, 0, -sin(angle), 0, cos(angle);

  return out;
}

Eigen::MatrixXd routines::rotz(double angle)
{
  // Rotation about z axis

  Eigen::MatrixXd out(3, 3);

  out << cos(angle), -sin(angle), 0, sin(angle), cos(angle), 0, 0, 0, 1;

  return out;
}

Eigen::MatrixXd routines::get_LKFconfidencelimits(Eigen::MatrixXd Pxx)
{
  Eigen::MatrixXd Confidence(46, 1);

  for (int i = 0; i < 23; i++)
  {
    Confidence(2 * i) = -3 * sqrt(Pxx(i, i));
    Confidence(2 * i + 1) = 3 * sqrt(Pxx(i, i));
  }

  return Confidence;
}

Eigen::MatrixXd routines::get_ZSEconfidencelimits(Eigen::MatrixXd XG)
{
  Eigen::MatrixXd Confidence(46, 1);

  for (int i = 0; i < 23; i++)
  {
    Confidence(2 * i) = -XG.block(i, 0, 1, XG.cols()).cwiseAbs().sum();
    Confidence(2 * i + 1) = XG.block(i, 0, 1, XG.cols()).cwiseAbs().sum();  // Sum of absolute values of i-th line of XG
  }

  return Confidence;
}

double routines::get_ZSEfrobnorm(Eigen::MatrixXd XG)
{
  double frobnorm = sqrt((XG * XG.transpose()).trace());

  return frobnorm;
}
