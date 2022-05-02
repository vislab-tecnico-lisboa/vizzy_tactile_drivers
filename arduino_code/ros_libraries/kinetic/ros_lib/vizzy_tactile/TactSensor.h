#ifndef _ROS_vizzy_tactile_TactSensor_h
#define _ROS_vizzy_tactile_TactSensor_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/Vector3.h"

namespace vizzy_tactile
{

  class TactSensor : public ros::Msg
  {
    public:
      typedef const char* _frame_id_type;
      _frame_id_type frame_id;
      typedef geometry_msgs::Vector3 _force_type;
      _force_type force;
      typedef geometry_msgs::Vector3 _displacement_type;
      _displacement_type displacement;
      typedef geometry_msgs::Vector3 _field_type;
      _field_type field;

    TactSensor():
      frame_id(""),
      force(),
      displacement(),
      field()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_frame_id = strlen(this->frame_id);
      varToArr(outbuffer + offset, length_frame_id);
      offset += 4;
      memcpy(outbuffer + offset, this->frame_id, length_frame_id);
      offset += length_frame_id;
      offset += this->force.serialize(outbuffer + offset);
      offset += this->displacement.serialize(outbuffer + offset);
      offset += this->field.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_frame_id;
      arrToVar(length_frame_id, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_frame_id; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_frame_id-1]=0;
      this->frame_id = (char *)(inbuffer + offset-1);
      offset += length_frame_id;
      offset += this->force.deserialize(inbuffer + offset);
      offset += this->displacement.deserialize(inbuffer + offset);
      offset += this->field.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "vizzy_tactile/TactSensor"; };
    const char * getMD5(){ return "77f754a6a592e9feea7376d420ae2ebd"; };

  };

}
#endif