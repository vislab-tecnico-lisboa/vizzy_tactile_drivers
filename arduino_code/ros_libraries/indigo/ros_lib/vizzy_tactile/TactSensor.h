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
      const char* frame_id;
      geometry_msgs::Vector3 force;

    TactSensor():
      frame_id(""),
      force()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_frame_id = strlen(this->frame_id);
      memcpy(outbuffer + offset, &length_frame_id, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->frame_id, length_frame_id);
      offset += length_frame_id;
      offset += this->force.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_frame_id;
      memcpy(&length_frame_id, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_frame_id; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_frame_id-1]=0;
      this->frame_id = (char *)(inbuffer + offset-1);
      offset += length_frame_id;
      offset += this->force.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "vizzy_tactile/TactSensor"; };
    const char * getMD5(){ return "80c028f08883b83d496126c686672e02"; };

  };

}
#endif