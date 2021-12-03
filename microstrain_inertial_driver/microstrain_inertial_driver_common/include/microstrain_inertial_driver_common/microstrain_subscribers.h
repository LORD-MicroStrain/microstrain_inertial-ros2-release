/////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Parker-Lord GX5-Series Driver Definition File
//
// Copyright (c) 2017, Brian Bingham
// Copyright (c)  2020, Parker Hannifin Corp
//
// This code is licensed under MIT license (see LICENSE file for details)
//
/////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef MICROSTRAIN_INERTIAL_DRIVER_COMMON_MICROSTRAIN_SUBSCRIBERS_H
#define MICROSTRAIN_INERTIAL_DRIVER_COMMON_MICROSTRAIN_SUBSCRIBERS_H

#include "microstrain_inertial_driver_common/microstrain_defs.h"
#include "microstrain_inertial_driver_common/microstrain_ros_funcs.h"
#include "microstrain_inertial_driver_common/microstrain_config.h"

namespace microstrain
{

/**
 * Contains subscribers and the functions they call
 */
class MicrostrainSubscribers
{
public:
  /**
   * \brief Default Constructor
   */
  MicrostrainSubscribers() = default;

  /**
   * \brief Constructs this class with a reference to the node, and a config object
   * \param node  Reference to a node that will be saved to this class and used to log and interact with ROS
   * \param config Reference to the config object that will be saved to this class and used to determine whether or not to enable the subscriptions
   */
  MicrostrainSubscribers(RosNodeType* node, MicrostrainConfig* config);

  /**
   * \brief Activates the subscribers. After this function is called, the subscriptions will be ready to receive messages
   * \return true if activation was successful and false if activation failed
   */
  bool activate();

  /**
   * \brief Callback that will start the velZupt task to send the velZupt command at 5 hz
   * \param state  If the state is true, the task will be started, if the state is false, the task will be stopped
   */
  void velZuptCallback(const BoolMsg& state);

  /**
   * \brief Sends the velZupt command. Meant to be called in a loop
   */
  void velZupt();

  /**
   * \brief Callback that will start the angZupt task to send the angZupt command at 5 hz
   * \param state  If the state is true, the task will be started, if the state is false, the task will be stopped
   */
  void angZuptCallback(const BoolMsg& state);

  /**
   * \brief Sends the angZupt command. Meant to be called in a loop
   */
  void angZupt();

  /**
   * \brief Accepts external GPS time to set time on the device
   * \param time  Message containing external GPS time
   */
  void external_gps_time_callback(const TimeReferenceMsg& time);

  // ZUPT subscribers
  BoolSubType filter_vel_state_sub_;
  BoolSubType filter_ang_state_sub_;

  // External GNSS subscriber
  TimeReferenceSubType external_gps_time_sub_;

private:
  // Node Information
  RosNodeType* node_;
  MicrostrainConfig* config_;

  bool vel_still_;
  bool ang_still_;

  RosTimerType vel_zupt_timer_;
  RosTimerType ang_zupt_timer_;
};  // struct MicrostrainPublishers

}  // namespace microstrain

#endif  // MICROSTRAIN_INERTIAL_DRIVER_COMMON_MICROSTRAIN_SUBSCRIBERS_H
