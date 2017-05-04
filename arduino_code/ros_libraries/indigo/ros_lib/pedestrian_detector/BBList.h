#ifndef _ROS_pedestrian_detector_BBList_h
#define _ROS_pedestrian_detector_BBList_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "pedestrian_detector/BoundingBox.h"

namespace pedestrian_detector
{

  class BBList : public ros::Msg
  {
    public:
      std_msgs::Header header;
      uint8_t bbVector_length;
      pedestrian_detector::BoundingBox st_bbVector;
      pedestrian_detector::BoundingBox * bbVector;

    BBList():
      header(),
      bbVector_length(0), bbVector(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
      *(outbuffer + offset++) = bbVector_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < bbVector_length; i++){
      offset += this->bbVector[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      uint8_t bbVector_lengthT = *(inbuffer + offset++);
      if(bbVector_lengthT > bbVector_length)
        this->bbVector = (pedestrian_detector::BoundingBox*)realloc(this->bbVector, bbVector_lengthT * sizeof(pedestrian_detector::BoundingBox));
      offset += 3;
      bbVector_length = bbVector_lengthT;
      for( uint8_t i = 0; i < bbVector_length; i++){
      offset += this->st_bbVector.deserialize(inbuffer + offset);
        memcpy( &(this->bbVector[i]), &(this->st_bbVector), sizeof(pedestrian_detector::BoundingBox));
      }
     return offset;
    }

    const char * getType(){ return "pedestrian_detector/BBList"; };
    const char * getMD5(){ return "451051af5703a61c3d4949dd71734381"; };

  };

}
#endif