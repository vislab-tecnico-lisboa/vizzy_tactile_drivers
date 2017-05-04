#ifndef _ROS_pedestrian_detector_Features_h
#define _ROS_pedestrian_detector_Features_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace pedestrian_detector
{

  class Features : public ros::Msg
  {
    public:
      uint8_t features_length;
      float st_features;
      float * features;

    Features():
      features_length(0), features(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset++) = features_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < features_length; i++){
      union {
        float real;
        uint32_t base;
      } u_featuresi;
      u_featuresi.real = this->features[i];
      *(outbuffer + offset + 0) = (u_featuresi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_featuresi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_featuresi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_featuresi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->features[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint8_t features_lengthT = *(inbuffer + offset++);
      if(features_lengthT > features_length)
        this->features = (float*)realloc(this->features, features_lengthT * sizeof(float));
      offset += 3;
      features_length = features_lengthT;
      for( uint8_t i = 0; i < features_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_features;
      u_st_features.base = 0;
      u_st_features.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_features.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_features.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_features.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_features = u_st_features.real;
      offset += sizeof(this->st_features);
        memcpy( &(this->features[i]), &(this->st_features), sizeof(float));
      }
     return offset;
    }

    const char * getType(){ return "pedestrian_detector/Features"; };
    const char * getMD5(){ return "1eff39aaa9756f3221a187400752fb2e"; };

  };

}
#endif