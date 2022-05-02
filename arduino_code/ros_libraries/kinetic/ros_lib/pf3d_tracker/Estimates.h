#ifndef _ROS_pf3d_tracker_Estimates_h
#define _ROS_pf3d_tracker_Estimates_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "geometry_msgs/PointStamped.h"

namespace pf3d_tracker
{

  class Estimates : public ros::Msg
  {
    public:
      typedef geometry_msgs::PointStamped _mean_type;
      _mean_type mean;
      typedef float _likelihood_type;
      _likelihood_type likelihood;
      typedef bool _seeingBall_type;
      _seeingBall_type seeingBall;
      typedef float _meanU_type;
      _meanU_type meanU;
      typedef float _meanV_type;
      _meanV_type meanV;

    Estimates():
      mean(),
      likelihood(0),
      seeingBall(0),
      meanU(0),
      meanV(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->mean.serialize(outbuffer + offset);
      offset += serializeAvrFloat64(outbuffer + offset, this->likelihood);
      union {
        bool real;
        uint8_t base;
      } u_seeingBall;
      u_seeingBall.real = this->seeingBall;
      *(outbuffer + offset + 0) = (u_seeingBall.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->seeingBall);
      offset += serializeAvrFloat64(outbuffer + offset, this->meanU);
      offset += serializeAvrFloat64(outbuffer + offset, this->meanV);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->mean.deserialize(inbuffer + offset);
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->likelihood));
      union {
        bool real;
        uint8_t base;
      } u_seeingBall;
      u_seeingBall.base = 0;
      u_seeingBall.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->seeingBall = u_seeingBall.real;
      offset += sizeof(this->seeingBall);
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->meanU));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->meanV));
     return offset;
    }

    const char * getType(){ return "pf3d_tracker/Estimates"; };
    const char * getMD5(){ return "f0daa77a09640e42e9bdadbfeb180186"; };

  };

}
#endif