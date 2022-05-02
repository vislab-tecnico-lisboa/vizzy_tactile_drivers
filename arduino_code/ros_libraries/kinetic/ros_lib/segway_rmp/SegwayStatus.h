#ifndef _ROS_segway_rmp_SegwayStatus_h
#define _ROS_segway_rmp_SegwayStatus_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace segway_rmp
{

  class SegwayStatus : public ros::Msg
  {
    public:
      typedef float _pitch_angle_type;
      _pitch_angle_type pitch_angle;
      typedef float _pitch_rate_type;
      _pitch_rate_type pitch_rate;
      typedef float _roll_angle_type;
      _roll_angle_type roll_angle;
      typedef float _roll_rate_type;
      _roll_rate_type roll_rate;
      typedef float _left_wheel_velocity_type;
      _left_wheel_velocity_type left_wheel_velocity;
      typedef float _right_wheel_velocity_type;
      _right_wheel_velocity_type right_wheel_velocity;
      typedef float _yaw_rate_type;
      _yaw_rate_type yaw_rate;
      typedef float _servo_frames_type;
      _servo_frames_type servo_frames;
      typedef float _left_wheel_displacement_type;
      _left_wheel_displacement_type left_wheel_displacement;
      typedef float _right_wheel_displacement_type;
      _right_wheel_displacement_type right_wheel_displacement;
      typedef float _forward_displacement_type;
      _forward_displacement_type forward_displacement;
      typedef float _yaw_displacement_type;
      _yaw_displacement_type yaw_displacement;
      typedef float _left_motor_torque_type;
      _left_motor_torque_type left_motor_torque;
      typedef float _right_motor_torque_type;
      _right_motor_torque_type right_motor_torque;
      typedef int8_t _operation_mode_type;
      _operation_mode_type operation_mode;
      typedef int8_t _gain_schedule_type;
      _gain_schedule_type gain_schedule;
      typedef float _ui_battery_type;
      _ui_battery_type ui_battery;
      typedef float _powerbase_battery_type;
      _powerbase_battery_type powerbase_battery;
      typedef bool _motors_enabled_type;
      _motors_enabled_type motors_enabled;
      enum { LIGHT = 1 };
      enum { TALL = 2 };
      enum { HEAVY = 3 };
      enum { BALANCE = 1 };
      enum { TRACTOR = 2 };
      enum { POWER_DOWN = 3 };

    SegwayStatus():
      pitch_angle(0),
      pitch_rate(0),
      roll_angle(0),
      roll_rate(0),
      left_wheel_velocity(0),
      right_wheel_velocity(0),
      yaw_rate(0),
      servo_frames(0),
      left_wheel_displacement(0),
      right_wheel_displacement(0),
      forward_displacement(0),
      yaw_displacement(0),
      left_motor_torque(0),
      right_motor_torque(0),
      operation_mode(0),
      gain_schedule(0),
      ui_battery(0),
      powerbase_battery(0),
      motors_enabled(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_pitch_angle;
      u_pitch_angle.real = this->pitch_angle;
      *(outbuffer + offset + 0) = (u_pitch_angle.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_pitch_angle.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_pitch_angle.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_pitch_angle.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->pitch_angle);
      union {
        float real;
        uint32_t base;
      } u_pitch_rate;
      u_pitch_rate.real = this->pitch_rate;
      *(outbuffer + offset + 0) = (u_pitch_rate.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_pitch_rate.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_pitch_rate.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_pitch_rate.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->pitch_rate);
      union {
        float real;
        uint32_t base;
      } u_roll_angle;
      u_roll_angle.real = this->roll_angle;
      *(outbuffer + offset + 0) = (u_roll_angle.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_roll_angle.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_roll_angle.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_roll_angle.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->roll_angle);
      union {
        float real;
        uint32_t base;
      } u_roll_rate;
      u_roll_rate.real = this->roll_rate;
      *(outbuffer + offset + 0) = (u_roll_rate.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_roll_rate.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_roll_rate.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_roll_rate.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->roll_rate);
      union {
        float real;
        uint32_t base;
      } u_left_wheel_velocity;
      u_left_wheel_velocity.real = this->left_wheel_velocity;
      *(outbuffer + offset + 0) = (u_left_wheel_velocity.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_left_wheel_velocity.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_left_wheel_velocity.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_left_wheel_velocity.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->left_wheel_velocity);
      union {
        float real;
        uint32_t base;
      } u_right_wheel_velocity;
      u_right_wheel_velocity.real = this->right_wheel_velocity;
      *(outbuffer + offset + 0) = (u_right_wheel_velocity.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_right_wheel_velocity.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_right_wheel_velocity.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_right_wheel_velocity.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->right_wheel_velocity);
      union {
        float real;
        uint32_t base;
      } u_yaw_rate;
      u_yaw_rate.real = this->yaw_rate;
      *(outbuffer + offset + 0) = (u_yaw_rate.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_yaw_rate.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_yaw_rate.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_yaw_rate.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->yaw_rate);
      union {
        float real;
        uint32_t base;
      } u_servo_frames;
      u_servo_frames.real = this->servo_frames;
      *(outbuffer + offset + 0) = (u_servo_frames.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_servo_frames.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_servo_frames.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_servo_frames.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->servo_frames);
      union {
        float real;
        uint32_t base;
      } u_left_wheel_displacement;
      u_left_wheel_displacement.real = this->left_wheel_displacement;
      *(outbuffer + offset + 0) = (u_left_wheel_displacement.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_left_wheel_displacement.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_left_wheel_displacement.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_left_wheel_displacement.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->left_wheel_displacement);
      union {
        float real;
        uint32_t base;
      } u_right_wheel_displacement;
      u_right_wheel_displacement.real = this->right_wheel_displacement;
      *(outbuffer + offset + 0) = (u_right_wheel_displacement.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_right_wheel_displacement.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_right_wheel_displacement.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_right_wheel_displacement.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->right_wheel_displacement);
      union {
        float real;
        uint32_t base;
      } u_forward_displacement;
      u_forward_displacement.real = this->forward_displacement;
      *(outbuffer + offset + 0) = (u_forward_displacement.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_forward_displacement.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_forward_displacement.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_forward_displacement.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->forward_displacement);
      union {
        float real;
        uint32_t base;
      } u_yaw_displacement;
      u_yaw_displacement.real = this->yaw_displacement;
      *(outbuffer + offset + 0) = (u_yaw_displacement.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_yaw_displacement.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_yaw_displacement.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_yaw_displacement.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->yaw_displacement);
      union {
        float real;
        uint32_t base;
      } u_left_motor_torque;
      u_left_motor_torque.real = this->left_motor_torque;
      *(outbuffer + offset + 0) = (u_left_motor_torque.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_left_motor_torque.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_left_motor_torque.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_left_motor_torque.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->left_motor_torque);
      union {
        float real;
        uint32_t base;
      } u_right_motor_torque;
      u_right_motor_torque.real = this->right_motor_torque;
      *(outbuffer + offset + 0) = (u_right_motor_torque.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_right_motor_torque.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_right_motor_torque.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_right_motor_torque.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->right_motor_torque);
      union {
        int8_t real;
        uint8_t base;
      } u_operation_mode;
      u_operation_mode.real = this->operation_mode;
      *(outbuffer + offset + 0) = (u_operation_mode.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->operation_mode);
      union {
        int8_t real;
        uint8_t base;
      } u_gain_schedule;
      u_gain_schedule.real = this->gain_schedule;
      *(outbuffer + offset + 0) = (u_gain_schedule.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->gain_schedule);
      union {
        float real;
        uint32_t base;
      } u_ui_battery;
      u_ui_battery.real = this->ui_battery;
      *(outbuffer + offset + 0) = (u_ui_battery.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_ui_battery.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_ui_battery.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_ui_battery.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->ui_battery);
      union {
        float real;
        uint32_t base;
      } u_powerbase_battery;
      u_powerbase_battery.real = this->powerbase_battery;
      *(outbuffer + offset + 0) = (u_powerbase_battery.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_powerbase_battery.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_powerbase_battery.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_powerbase_battery.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->powerbase_battery);
      union {
        bool real;
        uint8_t base;
      } u_motors_enabled;
      u_motors_enabled.real = this->motors_enabled;
      *(outbuffer + offset + 0) = (u_motors_enabled.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->motors_enabled);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_pitch_angle;
      u_pitch_angle.base = 0;
      u_pitch_angle.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_pitch_angle.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_pitch_angle.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_pitch_angle.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->pitch_angle = u_pitch_angle.real;
      offset += sizeof(this->pitch_angle);
      union {
        float real;
        uint32_t base;
      } u_pitch_rate;
      u_pitch_rate.base = 0;
      u_pitch_rate.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_pitch_rate.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_pitch_rate.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_pitch_rate.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->pitch_rate = u_pitch_rate.real;
      offset += sizeof(this->pitch_rate);
      union {
        float real;
        uint32_t base;
      } u_roll_angle;
      u_roll_angle.base = 0;
      u_roll_angle.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_roll_angle.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_roll_angle.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_roll_angle.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->roll_angle = u_roll_angle.real;
      offset += sizeof(this->roll_angle);
      union {
        float real;
        uint32_t base;
      } u_roll_rate;
      u_roll_rate.base = 0;
      u_roll_rate.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_roll_rate.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_roll_rate.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_roll_rate.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->roll_rate = u_roll_rate.real;
      offset += sizeof(this->roll_rate);
      union {
        float real;
        uint32_t base;
      } u_left_wheel_velocity;
      u_left_wheel_velocity.base = 0;
      u_left_wheel_velocity.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_left_wheel_velocity.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_left_wheel_velocity.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_left_wheel_velocity.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->left_wheel_velocity = u_left_wheel_velocity.real;
      offset += sizeof(this->left_wheel_velocity);
      union {
        float real;
        uint32_t base;
      } u_right_wheel_velocity;
      u_right_wheel_velocity.base = 0;
      u_right_wheel_velocity.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_right_wheel_velocity.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_right_wheel_velocity.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_right_wheel_velocity.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->right_wheel_velocity = u_right_wheel_velocity.real;
      offset += sizeof(this->right_wheel_velocity);
      union {
        float real;
        uint32_t base;
      } u_yaw_rate;
      u_yaw_rate.base = 0;
      u_yaw_rate.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_yaw_rate.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_yaw_rate.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_yaw_rate.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->yaw_rate = u_yaw_rate.real;
      offset += sizeof(this->yaw_rate);
      union {
        float real;
        uint32_t base;
      } u_servo_frames;
      u_servo_frames.base = 0;
      u_servo_frames.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_servo_frames.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_servo_frames.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_servo_frames.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->servo_frames = u_servo_frames.real;
      offset += sizeof(this->servo_frames);
      union {
        float real;
        uint32_t base;
      } u_left_wheel_displacement;
      u_left_wheel_displacement.base = 0;
      u_left_wheel_displacement.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_left_wheel_displacement.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_left_wheel_displacement.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_left_wheel_displacement.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->left_wheel_displacement = u_left_wheel_displacement.real;
      offset += sizeof(this->left_wheel_displacement);
      union {
        float real;
        uint32_t base;
      } u_right_wheel_displacement;
      u_right_wheel_displacement.base = 0;
      u_right_wheel_displacement.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_right_wheel_displacement.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_right_wheel_displacement.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_right_wheel_displacement.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->right_wheel_displacement = u_right_wheel_displacement.real;
      offset += sizeof(this->right_wheel_displacement);
      union {
        float real;
        uint32_t base;
      } u_forward_displacement;
      u_forward_displacement.base = 0;
      u_forward_displacement.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_forward_displacement.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_forward_displacement.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_forward_displacement.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->forward_displacement = u_forward_displacement.real;
      offset += sizeof(this->forward_displacement);
      union {
        float real;
        uint32_t base;
      } u_yaw_displacement;
      u_yaw_displacement.base = 0;
      u_yaw_displacement.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_yaw_displacement.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_yaw_displacement.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_yaw_displacement.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->yaw_displacement = u_yaw_displacement.real;
      offset += sizeof(this->yaw_displacement);
      union {
        float real;
        uint32_t base;
      } u_left_motor_torque;
      u_left_motor_torque.base = 0;
      u_left_motor_torque.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_left_motor_torque.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_left_motor_torque.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_left_motor_torque.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->left_motor_torque = u_left_motor_torque.real;
      offset += sizeof(this->left_motor_torque);
      union {
        float real;
        uint32_t base;
      } u_right_motor_torque;
      u_right_motor_torque.base = 0;
      u_right_motor_torque.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_right_motor_torque.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_right_motor_torque.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_right_motor_torque.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->right_motor_torque = u_right_motor_torque.real;
      offset += sizeof(this->right_motor_torque);
      union {
        int8_t real;
        uint8_t base;
      } u_operation_mode;
      u_operation_mode.base = 0;
      u_operation_mode.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->operation_mode = u_operation_mode.real;
      offset += sizeof(this->operation_mode);
      union {
        int8_t real;
        uint8_t base;
      } u_gain_schedule;
      u_gain_schedule.base = 0;
      u_gain_schedule.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->gain_schedule = u_gain_schedule.real;
      offset += sizeof(this->gain_schedule);
      union {
        float real;
        uint32_t base;
      } u_ui_battery;
      u_ui_battery.base = 0;
      u_ui_battery.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_ui_battery.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_ui_battery.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_ui_battery.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->ui_battery = u_ui_battery.real;
      offset += sizeof(this->ui_battery);
      union {
        float real;
        uint32_t base;
      } u_powerbase_battery;
      u_powerbase_battery.base = 0;
      u_powerbase_battery.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_powerbase_battery.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_powerbase_battery.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_powerbase_battery.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->powerbase_battery = u_powerbase_battery.real;
      offset += sizeof(this->powerbase_battery);
      union {
        bool real;
        uint8_t base;
      } u_motors_enabled;
      u_motors_enabled.base = 0;
      u_motors_enabled.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->motors_enabled = u_motors_enabled.real;
      offset += sizeof(this->motors_enabled);
     return offset;
    }

    const char * getType(){ return "segway_rmp/SegwayStatus"; };
    const char * getMD5(){ return "658b68a87a84c7483fa3f522de0a2f66"; };

  };

}
#endif