#ifndef _ROS_moveit_msgs_PickupResult_h
#define _ROS_moveit_msgs_PickupResult_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "moveit_msgs/MoveItErrorCodes.h"
#include "moveit_msgs/RobotState.h"
#include "moveit_msgs/RobotTrajectory.h"
#include "moveit_msgs/Grasp.h"

namespace moveit_msgs
{

  class PickupResult : public ros::Msg
  {
    public:
      typedef moveit_msgs::MoveItErrorCodes _error_code_type;
      _error_code_type error_code;
      typedef moveit_msgs::RobotState _trajectory_start_type;
      _trajectory_start_type trajectory_start;
      uint32_t trajectory_stages_length;
      typedef moveit_msgs::RobotTrajectory _trajectory_stages_type;
      _trajectory_stages_type st_trajectory_stages;
      _trajectory_stages_type * trajectory_stages;
      uint32_t trajectory_descriptions_length;
      typedef char* _trajectory_descriptions_type;
      _trajectory_descriptions_type st_trajectory_descriptions;
      _trajectory_descriptions_type * trajectory_descriptions;
      typedef moveit_msgs::Grasp _grasp_type;
      _grasp_type grasp;

    PickupResult():
      error_code(),
      trajectory_start(),
      trajectory_stages_length(0), trajectory_stages(NULL),
      trajectory_descriptions_length(0), trajectory_descriptions(NULL),
      grasp()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->error_code.serialize(outbuffer + offset);
      offset += this->trajectory_start.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->trajectory_stages_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->trajectory_stages_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->trajectory_stages_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->trajectory_stages_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->trajectory_stages_length);
      for( uint32_t i = 0; i < trajectory_stages_length; i++){
      offset += this->trajectory_stages[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset + 0) = (this->trajectory_descriptions_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->trajectory_descriptions_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->trajectory_descriptions_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->trajectory_descriptions_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->trajectory_descriptions_length);
      for( uint32_t i = 0; i < trajectory_descriptions_length; i++){
      uint32_t length_trajectory_descriptionsi = strlen(this->trajectory_descriptions[i]);
      varToArr(outbuffer + offset, length_trajectory_descriptionsi);
      offset += 4;
      memcpy(outbuffer + offset, this->trajectory_descriptions[i], length_trajectory_descriptionsi);
      offset += length_trajectory_descriptionsi;
      }
      offset += this->grasp.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->error_code.deserialize(inbuffer + offset);
      offset += this->trajectory_start.deserialize(inbuffer + offset);
      uint32_t trajectory_stages_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      trajectory_stages_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      trajectory_stages_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      trajectory_stages_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->trajectory_stages_length);
      if(trajectory_stages_lengthT > trajectory_stages_length)
        this->trajectory_stages = (moveit_msgs::RobotTrajectory*)realloc(this->trajectory_stages, trajectory_stages_lengthT * sizeof(moveit_msgs::RobotTrajectory));
      trajectory_stages_length = trajectory_stages_lengthT;
      for( uint32_t i = 0; i < trajectory_stages_length; i++){
      offset += this->st_trajectory_stages.deserialize(inbuffer + offset);
        memcpy( &(this->trajectory_stages[i]), &(this->st_trajectory_stages), sizeof(moveit_msgs::RobotTrajectory));
      }
      uint32_t trajectory_descriptions_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      trajectory_descriptions_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      trajectory_descriptions_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      trajectory_descriptions_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->trajectory_descriptions_length);
      if(trajectory_descriptions_lengthT > trajectory_descriptions_length)
        this->trajectory_descriptions = (char**)realloc(this->trajectory_descriptions, trajectory_descriptions_lengthT * sizeof(char*));
      trajectory_descriptions_length = trajectory_descriptions_lengthT;
      for( uint32_t i = 0; i < trajectory_descriptions_length; i++){
      uint32_t length_st_trajectory_descriptions;
      arrToVar(length_st_trajectory_descriptions, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_trajectory_descriptions; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_trajectory_descriptions-1]=0;
      this->st_trajectory_descriptions = (char *)(inbuffer + offset-1);
      offset += length_st_trajectory_descriptions;
        memcpy( &(this->trajectory_descriptions[i]), &(this->st_trajectory_descriptions), sizeof(char*));
      }
      offset += this->grasp.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "moveit_msgs/PickupResult"; };
    const char * getMD5(){ return "23c6d8bf0580f4bc8f7a8e1f59b4b6b7"; };

  };

}
#endif