#ifndef _ROS_pedestrian_detector_DetectionList_h
#define _ROS_pedestrian_detector_DetectionList_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "pedestrian_detector/BoundingBox.h"
#include "pedestrian_detector/Features.h"
#include "sensor_msgs/Image.h"

namespace pedestrian_detector
{

  class DetectionList : public ros::Msg
  {
    public:
      std_msgs::Header header;
      uint8_t bbVector_length;
      pedestrian_detector::BoundingBox st_bbVector;
      pedestrian_detector::BoundingBox * bbVector;
      uint8_t headsVector_length;
      pedestrian_detector::BoundingBox st_headsVector;
      pedestrian_detector::BoundingBox * headsVector;
      uint8_t featuresVector_length;
      pedestrian_detector::Features st_featuresVector;
      pedestrian_detector::Features * featuresVector;
      sensor_msgs::Image im;

    DetectionList():
      header(),
      bbVector_length(0), bbVector(NULL),
      headsVector_length(0), headsVector(NULL),
      featuresVector_length(0), featuresVector(NULL),
      im()
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
      *(outbuffer + offset++) = headsVector_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < headsVector_length; i++){
      offset += this->headsVector[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset++) = featuresVector_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < featuresVector_length; i++){
      offset += this->featuresVector[i].serialize(outbuffer + offset);
      }
      offset += this->im.serialize(outbuffer + offset);
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
      uint8_t headsVector_lengthT = *(inbuffer + offset++);
      if(headsVector_lengthT > headsVector_length)
        this->headsVector = (pedestrian_detector::BoundingBox*)realloc(this->headsVector, headsVector_lengthT * sizeof(pedestrian_detector::BoundingBox));
      offset += 3;
      headsVector_length = headsVector_lengthT;
      for( uint8_t i = 0; i < headsVector_length; i++){
      offset += this->st_headsVector.deserialize(inbuffer + offset);
        memcpy( &(this->headsVector[i]), &(this->st_headsVector), sizeof(pedestrian_detector::BoundingBox));
      }
      uint8_t featuresVector_lengthT = *(inbuffer + offset++);
      if(featuresVector_lengthT > featuresVector_length)
        this->featuresVector = (pedestrian_detector::Features*)realloc(this->featuresVector, featuresVector_lengthT * sizeof(pedestrian_detector::Features));
      offset += 3;
      featuresVector_length = featuresVector_lengthT;
      for( uint8_t i = 0; i < featuresVector_length; i++){
      offset += this->st_featuresVector.deserialize(inbuffer + offset);
        memcpy( &(this->featuresVector[i]), &(this->st_featuresVector), sizeof(pedestrian_detector::Features));
      }
      offset += this->im.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "pedestrian_detector/DetectionList"; };
    const char * getMD5(){ return "32a9d6bec4073df954e13aa34f2ef4fb"; };

  };

}
#endif