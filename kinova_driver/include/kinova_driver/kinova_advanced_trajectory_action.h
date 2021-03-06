/**
 *
 *  File: kinova_advanced_trajectory_action.h
 *  Desc: Action server for kinova arm who take a list of trajectory point as an input.
 *  Auth: Mathieu Lauret
 *
 *  Copyright (c) 2016, Mathieu Lauret
 *  All Rights Reserved
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the copyright holder nor the names of its contributors
 *       may be used to endorse or promote products derived from this
 *       software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * history:
 *  23/08/16 : First Creation
 */
#ifndef KINOVAADVANCEDTRAJECTORYACTIONSERVER_H
#define KINOVAADVANCEDTRAJECTORYACTIONSERVER_H


#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <tf/tf.h>
#include <tf/transform_listener.h>

#include <kinova_msgs/Arm_KinovaTrajectoryListAction.h>

#include <string>
#include "kinova_driver/kinova_comm.h"

namespace kinova
{

    class KinovaAdvancedTrajectoryActionServer
    {

         public:
            KinovaAdvancedTrajectoryActionServer(KinovaComm &, const ros::NodeHandle &n, const std::string &kinova_robotType);
            ~KinovaAdvancedTrajectoryActionServer();

            void actionCallback(const kinova_msgs::Arm_KinovaTrajectoryListGoalConstPtr &);

         private:
            ros::NodeHandle node_handle_;
            std::string kinova_robotType_;
            KinovaComm &arm_comm_;
            actionlib::SimpleActionServer<kinova_msgs::Arm_KinovaTrajectoryListAction> action_server_;
            tf::TransformListener listener;

            ros::Time last_nonstall_time_;
            kinova::KinovaPose last_nonstall_pose_;

            std::string link_base_frame_;

            // Parameters
            double stall_interval_seconds_;
            double stall_threshold_;
            double rate_hz_;
            float position_tolerance_;
            float EulerAngle_tolerance_;
            std::string tf_prefix_;
    };

}  // namespace kinova

#endif // KINOVAADVANCEDTRAJECTORYACTIONSERVER_H
