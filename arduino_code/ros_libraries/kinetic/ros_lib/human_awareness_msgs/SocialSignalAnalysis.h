#ifndef _ROS_SERVICE_SocialSignalAnalysis_h
#define _ROS_SERVICE_SocialSignalAnalysis_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "human_awareness_msgs/PersonTracker.h"
#include "geometry_msgs/Vector3.h"
#include "human_awareness_msgs/OpenFaceFeatures.h"

namespace human_awareness_msgs
{

static const char SOCIALSIGNALANALYSIS[] = "human_awareness_msgs/SocialSignalAnalysis";

  class SocialSignalAnalysisRequest : public ros::Msg
  {
    public:
      typedef human_awareness_msgs::PersonTracker _person_tracker_type;
      _person_tracker_type person_tracker;
      typedef geometry_msgs::Vector3 _velocity_offset_type;
      _velocity_offset_type velocity_offset;

    SocialSignalAnalysisRequest():
      person_tracker(),
      velocity_offset()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->person_tracker.serialize(outbuffer + offset);
      offset += this->velocity_offset.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->person_tracker.deserialize(inbuffer + offset);
      offset += this->velocity_offset.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return SOCIALSIGNALANALYSIS; };
    const char * getMD5(){ return "b52e9a1e0826bb41acf932687ee3f30f"; };

  };

  class SocialSignalAnalysisResponse : public ros::Msg
  {
    public:
      typedef float _distance_type;
      _distance_type distance;
      typedef float _gaze_type;
      _gaze_type gaze;
      typedef float _smile_type;
      _smile_type smile;
      typedef float _speed_type;
      _speed_type speed;
      typedef float _distance_salutation_type;
      _distance_salutation_type distance_salutation;
      typedef float _close_salutation_type;
      _close_salutation_type close_salutation;
      typedef float _head_dip_type;
      _head_dip_type head_dip;
      uint32_t openface_features_length;
      typedef human_awareness_msgs::OpenFaceFeatures _openface_features_type;
      _openface_features_type st_openface_features;
      _openface_features_type * openface_features;

    SocialSignalAnalysisResponse():
      distance(0),
      gaze(0),
      smile(0),
      speed(0),
      distance_salutation(0),
      close_salutation(0),
      head_dip(0),
      openface_features_length(0), openface_features(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_distance;
      u_distance.real = this->distance;
      *(outbuffer + offset + 0) = (u_distance.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_distance.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_distance.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_distance.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->distance);
      union {
        float real;
        uint32_t base;
      } u_gaze;
      u_gaze.real = this->gaze;
      *(outbuffer + offset + 0) = (u_gaze.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_gaze.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_gaze.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_gaze.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->gaze);
      union {
        float real;
        uint32_t base;
      } u_smile;
      u_smile.real = this->smile;
      *(outbuffer + offset + 0) = (u_smile.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_smile.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_smile.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_smile.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->smile);
      union {
        float real;
        uint32_t base;
      } u_speed;
      u_speed.real = this->speed;
      *(outbuffer + offset + 0) = (u_speed.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_speed.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_speed.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_speed.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->speed);
      union {
        float real;
        uint32_t base;
      } u_distance_salutation;
      u_distance_salutation.real = this->distance_salutation;
      *(outbuffer + offset + 0) = (u_distance_salutation.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_distance_salutation.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_distance_salutation.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_distance_salutation.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->distance_salutation);
      union {
        float real;
        uint32_t base;
      } u_close_salutation;
      u_close_salutation.real = this->close_salutation;
      *(outbuffer + offset + 0) = (u_close_salutation.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_close_salutation.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_close_salutation.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_close_salutation.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->close_salutation);
      union {
        float real;
        uint32_t base;
      } u_head_dip;
      u_head_dip.real = this->head_dip;
      *(outbuffer + offset + 0) = (u_head_dip.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_head_dip.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_head_dip.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_head_dip.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->head_dip);
      *(outbuffer + offset + 0) = (this->openface_features_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->openface_features_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->openface_features_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->openface_features_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->openface_features_length);
      for( uint32_t i = 0; i < openface_features_length; i++){
      offset += this->openface_features[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_distance;
      u_distance.base = 0;
      u_distance.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_distance.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_distance.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_distance.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->distance = u_distance.real;
      offset += sizeof(this->distance);
      union {
        float real;
        uint32_t base;
      } u_gaze;
      u_gaze.base = 0;
      u_gaze.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_gaze.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_gaze.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_gaze.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->gaze = u_gaze.real;
      offset += sizeof(this->gaze);
      union {
        float real;
        uint32_t base;
      } u_smile;
      u_smile.base = 0;
      u_smile.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_smile.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_smile.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_smile.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->smile = u_smile.real;
      offset += sizeof(this->smile);
      union {
        float real;
        uint32_t base;
      } u_speed;
      u_speed.base = 0;
      u_speed.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_speed.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_speed.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_speed.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->speed = u_speed.real;
      offset += sizeof(this->speed);
      union {
        float real;
        uint32_t base;
      } u_distance_salutation;
      u_distance_salutation.base = 0;
      u_distance_salutation.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_distance_salutation.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_distance_salutation.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_distance_salutation.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->distance_salutation = u_distance_salutation.real;
      offset += sizeof(this->distance_salutation);
      union {
        float real;
        uint32_t base;
      } u_close_salutation;
      u_close_salutation.base = 0;
      u_close_salutation.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_close_salutation.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_close_salutation.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_close_salutation.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->close_salutation = u_close_salutation.real;
      offset += sizeof(this->close_salutation);
      union {
        float real;
        uint32_t base;
      } u_head_dip;
      u_head_dip.base = 0;
      u_head_dip.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_head_dip.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_head_dip.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_head_dip.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->head_dip = u_head_dip.real;
      offset += sizeof(this->head_dip);
      uint32_t openface_features_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      openface_features_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      openface_features_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      openface_features_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->openface_features_length);
      if(openface_features_lengthT > openface_features_length)
        this->openface_features = (human_awareness_msgs::OpenFaceFeatures*)realloc(this->openface_features, openface_features_lengthT * sizeof(human_awareness_msgs::OpenFaceFeatures));
      openface_features_length = openface_features_lengthT;
      for( uint32_t i = 0; i < openface_features_length; i++){
      offset += this->st_openface_features.deserialize(inbuffer + offset);
        memcpy( &(this->openface_features[i]), &(this->st_openface_features), sizeof(human_awareness_msgs::OpenFaceFeatures));
      }
     return offset;
    }

    const char * getType(){ return SOCIALSIGNALANALYSIS; };
    const char * getMD5(){ return "10d9ac6703f2f8c57a8fd91775c03ec0"; };

  };

  class SocialSignalAnalysis {
    public:
    typedef SocialSignalAnalysisRequest Request;
    typedef SocialSignalAnalysisResponse Response;
  };

}
#endif
