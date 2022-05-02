#ifndef _ROS_segway_rmp_SegwayStatusStamped_h
#define _ROS_segway_rmp_SegwayStatusStamped_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "segway_rmp/SegwayStatus.h"

namespace segway_rmp
{

  class SegwayStatusStamped : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      typedef segway_rmp::SegwayStatus _segway_type;
      _segway_type segway;

    SegwayStatusStamped():
      header(),
      segway()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      offset += this->segway.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      offset += this->segway.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "segway_rmp/SegwayStatusStamped"; };
    const char * getMD5(){ return "f11247ac7dcf2a8717603cc53878eec2"; };

  };

}
#endif