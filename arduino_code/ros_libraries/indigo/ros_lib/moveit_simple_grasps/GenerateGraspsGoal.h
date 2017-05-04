#ifndef _ROS_moveit_simple_grasps_GenerateGraspsGoal_h
#define _ROS_moveit_simple_grasps_GenerateGraspsGoal_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/Pose.h"
#include "moveit_simple_grasps/GraspGeneratorOptions.h"

namespace moveit_simple_grasps
{

  class GenerateGraspsGoal : public ros::Msg
  {
    public:
      geometry_msgs::Pose pose;
      float width;
      uint8_t options_length;
      moveit_simple_grasps::GraspGeneratorOptions st_options;
      moveit_simple_grasps::GraspGeneratorOptions * options;

    GenerateGraspsGoal():
      pose(),
      width(0),
      options_length(0), options(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->pose.serialize(outbuffer + offset);
      offset += serializeAvrFloat64(outbuffer + offset, this->width);
      *(outbuffer + offset++) = options_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < options_length; i++){
      offset += this->options[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->pose.deserialize(inbuffer + offset);
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->width));
      uint8_t options_lengthT = *(inbuffer + offset++);
      if(options_lengthT > options_length)
        this->options = (moveit_simple_grasps::GraspGeneratorOptions*)realloc(this->options, options_lengthT * sizeof(moveit_simple_grasps::GraspGeneratorOptions));
      offset += 3;
      options_length = options_lengthT;
      for( uint8_t i = 0; i < options_length; i++){
      offset += this->st_options.deserialize(inbuffer + offset);
        memcpy( &(this->options[i]), &(this->st_options), sizeof(moveit_simple_grasps::GraspGeneratorOptions));
      }
     return offset;
    }

    const char * getType(){ return "moveit_simple_grasps/GenerateGraspsGoal"; };
    const char * getMD5(){ return "162875df5b62e9fb4be6d2aa5a67176d"; };

  };

}
#endif