/**
 *      _____
 *     /  _  \
 *    / _/ \  \
 *   / / \_/   \
 *  /  \_/  _   \  ___  _    ___   ___   ____   ____   ___   _____  _   _
 *  \  / \_/ \  / /  _\| |  | __| / _ \ | ++ \ | ++ \ / _ \ |_   _|| | | |
 *   \ \_/ \_/ /  | |  | |  | ++ | |_| || ++ / | ++_/| |_| |  | |  | +-+ |
 *    \  \_/  /   | |_ | |_ | ++ |  _  || |\ \ | |   |  _  |  | |  | +-+ |
 *     \_____/    \___/|___||___||_| |_||_| \_\|_|   |_| |_|  |_|  |_| |_|
 *             ROBOTICS™
 *
 *  File: kinova_comm.h
 *  Desc: Class for moving/querying kinova arm.
 *  Auth: Alex Bencz, Jeff Schmidt
 *
 *  Copyright (c) 2013, Clearpath Robotics, Inc.
 *  All Rights Reserved
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Clearpath Robotics, Inc. nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL CLEARPATH ROBOTICS, INC. BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Please send comments, questions, or patches to skynet@clearpathrobotics.com
 *
 */

#ifndef KINOVA_DRIVER_KINOVA_COMM_H
#define KINOVA_DRIVER_KINOVA_COMM_H

#include <boost/thread/recursive_mutex.hpp>

#include <kinova/KinovaTypes.h>

#include <kinova_driver/kinova_ros_types.h>
#include "kinova_driver/kinova_api.h"


namespace kinova
{

class KinovaComm
{
 public:
    KinovaComm(const ros::NodeHandle& node_handle,
             boost::recursive_mutex& api_mutex,
             const bool is_movement_on_start);
    ~KinovaComm();

    void stopAPI();
    void startAPI();
    bool isStopped();
    void startForceControl();
    void stopForceControl();
    int robotType() const;
    void getQuickStatus(QuickStatus &quick_status);
    void getConfig(ClientConfigurations &config);
    void setConfig(const ClientConfigurations &config);
    void printConfig(const ClientConfigurations &config);
    void getControlType(int &controlType); //joint or cartesian control
    void getGeneralInformations(GeneralInformations &general_info);
    void getSensorsInfo(SensorsInfo &sensor_Info); //voltage, current, temperatue and accelerometers
    void getForcesInfo(ForcesInfo &force_Info); // joint torque and end-effector wrench
    void getGripperStatus(Gripper &gripper_status); // most complete information of each fingers, including model, motion, force, limits, etc.

    void setAngularControl();
    void getAngularCommand(AngularPosition &angular_command);
    void getJointAngles(KinovaAngles &angles);
    void setJointAngles(const KinovaAngles &angles, int timeout = 0, bool push = true);
    void getJointVelocities(KinovaAngles &vels);
    void setJointVelocities(const AngularInfo& joint_vel);
    void getJointAccelerations(AngularAcceleration &joint_acc);
    void getJointTorques(KinovaAngles &tqs);
    void getJointCurrent(AngularPosition &anguler_current);
    void setJointTorqueMinMax(AngularInfo &min, AngularInfo &max);
    void printAngles(const KinovaAngles &angles);

    void setCartesianControl();
    void getCartesianCommand(CartesianPosition &cartesian_command);
    void getCartesianPosition(KinovaPose &position);
    void setCartesianPosition(const KinovaPose &position, int timeout = 0, bool push = true);
    void setCartesianPosition(const TrajectoryPoint &position, int timeout = 0, bool push = true);
    void setCartesianPosition(const std::vector<TrajectoryPoint> &positions, int timeout = 0, bool push = true);
    void setCartesianVelocities(const CartesianInfo &velocities);
    float getMaxTranslationVelocity(void);
    void setMaxTranslationVelocity(const float &max_trans_vel);
    float getMaxOrientationVelocity(void);
    void setMaxOrientationVelocity(const float &max_orient_vel);
    void getCartesianForce(KinovaPose &position);
    void setCartesianForceMinMax(const CartesianInfo &min, const CartesianInfo& max);
    void setCartesianInertiaDamping(const CartesianInfo &inertia, const CartesianInfo& damping);
    void printPosition(const KinovaPose &position);

    void getUserCommand(UserPosition &user_position);
    void getGlobalTrajectoryInfo(TrajectoryFIFO &trajectoryFIFO);
    void eraseAllTrajectories(void);

    int numFingers() const;
    void getFingerPositions(FingerAngles &fingers);
    void setFingerPositions(const FingerAngles &fingers, int timeout = 0, bool push = true);
    void printFingers(const FingersPosition &fingers);

    void homeArm(void);
    bool isHomed(void);
    void initFingers(void);
    void setEndEffectorOffset(unsigned int status, float x, float y, float z);
    void getEndEffectorOffset(unsigned int &status, float &x, float &y, float &z);

 private:
    boost::recursive_mutex& api_mutex_;
    kinova::KinovaAPI kinova_api_;
    bool is_software_stop_;
    int num_fingers_;
    int robot_type_;
    int motion_command_type_;

};

}  // namespace kinova
#endif  // KINOVA_DRIVER_KINOVA_COMM_H
