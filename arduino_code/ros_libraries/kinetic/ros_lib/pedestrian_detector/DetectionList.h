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
      typedef std_msgs::Header _header_type;
      _header_type header;
      uint32_t bbVector_length;
      typedef pedestrian_detector::BoundingBox _bbVector_type;
      _bbVector_type st_bbVector;
      _bbVector_type * bbVector;
      uint32_t headsVector_length;
      typedef pedestrian_detector::BoundingBox _headsVector_type;
      _headsVector_type st_headsVector;
      _headsVector_type * headsVector;
      uint32_t featuresVector_length;
      typedef pedestrian_detector::Features _featuresVector_type;
      _featuresVector_type st_featuresVector;
      _featuresVector_type * featuresVector;
      typedef sensor_msgs::Image _im_type;
      _im_type im;

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
      *(outbuffer + offset + 0) = (this->bbVector_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->bbVector_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->bbVector_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->bbVector_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->bbVector_length);
      for( uint32_t i = 0; i < bbVector_length; i++){
      offset += this->bbVector[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset + 0) = (this->headsVector_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->headsVector_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->headsVector_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->headsVector_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->headsVector_length);
      for( uint32_t i = 0; i < headsVector_length; i++){
      offset += this->headsVector[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset + 0) = (this->featuresVector_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->featuresVector_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->featuresVector_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->featuresVector_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->featuresVector_length);
      for( uint32_t i = 0; i < featuresVector_length; i++){
      offset += this->featuresVector[i].serialize(outbuffer + offset);
      }
      offset += this->im.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->header.deserialize(inbuffer + offset);
      uint32_t bbVector_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      bbVector_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      bbVector_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      bbVector_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->bbVector_length);
      if(bbVector_lengthT > bbVector_length)
        this->bbVector = (pedestrian_detector::BoundingBox*)realloc(this->bbVector, bbVector_lengthT * sizeof(pedestrian_detector::BoundingBox));
      bbVector_length = bbVector_lengthT;
      for( uint32_t i = 0; i < bbVector_length; i++){
      offset += this->st_bbVector.deserialize(inbuffer + offset);
        memcpy( &(this->bbVector[i]), &(this->st_bbVector), sizeof(pedestrian_detector::BoundingBox));
      }
      uint32_t headsVector_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      headsVector_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      headsVector_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      headsVector_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->headsVector_length);
      if(headsVector_lengthT > headsVector_length)
        this->headsVector = (pedestrian_detector::BoundingBox*)realloc(this->headsVector, headsVector_lengthT * sizeof(pedestrian_detector::BoundingBox));
      headsVector_length = headsVector_lengthT;
      for( uint32_t i = 0; i < headsVector_length; i++){
      offset += this->st_headsVector.deserialize(inbuffer + offset);
        memcpy( &(this->headsVector[i]), &(this->st_headsVector), sizeof(pedestrian_detector::BoundingBox));
      }
      uint32_t featuresVector_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      featuresVector_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      featuresVector_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      featuresVector_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->featuresVector_length);
      if(featuresVector_lengthT > featuresVector_length)
        this->featuresVector = (pedestrian_detector::Features*)realloc(this->featuresVector, featuresVector_lengthT * sizeof(pedestrian_detector::Features));
      featuresVector_length = featuresVector_lengthT;
      for( uint32_t i = 0; i < featuresVector_length; i++){
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