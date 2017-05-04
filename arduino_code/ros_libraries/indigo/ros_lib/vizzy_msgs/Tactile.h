#ifndef _ROS_vizzy_msgs_Tactile_h
#define _ROS_vizzy_msgs_Tactile_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "vizzy_msgs/TacVector.h"

namespace vizzy_msgs
{

  class Tactile : public ros::Msg
  {
    public:
      std_msgs::Header header;
      vizzy_msgs::TacVector sensorsArray[16];

    Tactile():
      header(),
      sensorsArray()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      for( uint8_t i = 0; i < 16; i++){
      offset += this->sensorsArray[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      for( uint8_t i = 0; i < 16; i++){
      offset += this->sensorsArray[i].deserialize(inbuffer + offset);
      }
     return offset;
    }

    const char * getType(){ return "vizzy_msgs/Tactile"; };
    const char * getMD5(){ return "c6f495229c1ca17ef38013481c00069b"; };

  };

}
#endif