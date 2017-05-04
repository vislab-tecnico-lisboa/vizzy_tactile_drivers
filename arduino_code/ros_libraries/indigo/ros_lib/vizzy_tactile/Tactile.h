#ifndef _ROS_vizzy_tactile_Tactile_h
#define _ROS_vizzy_tactile_Tactile_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "vizzy_tactile/TacVector.h"

namespace vizzy_tactile
{

  class Tactile : public ros::Msg
  {
    public:
      std_msgs::Header header;
      vizzy_tactile::TacVector sensorsArray[16];

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

    const char * getType(){ return "vizzy_tactile/Tactile"; };
    const char * getMD5(){ return "c6f495229c1ca17ef38013481c00069b"; };

  };

}
#endif