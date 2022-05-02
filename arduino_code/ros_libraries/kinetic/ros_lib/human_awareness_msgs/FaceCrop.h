#ifndef _ROS_human_awareness_msgs_FaceCrop_h
#define _ROS_human_awareness_msgs_FaceCrop_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "sensor_msgs/RegionOfInterest.h"
#include "sensor_msgs/CompressedImage.h"

namespace human_awareness_msgs
{

  class FaceCrop : public ros::Msg
  {
    public:
      typedef const char* _camera_info_topic_type;
      _camera_info_topic_type camera_info_topic;
      typedef sensor_msgs::RegionOfInterest _bounding_box_type;
      _bounding_box_type bounding_box;
      typedef sensor_msgs::CompressedImage _crop_compressed_type;
      _crop_compressed_type crop_compressed;

    FaceCrop():
      camera_info_topic(""),
      bounding_box(),
      crop_compressed()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_camera_info_topic = strlen(this->camera_info_topic);
      varToArr(outbuffer + offset, length_camera_info_topic);
      offset += 4;
      memcpy(outbuffer + offset, this->camera_info_topic, length_camera_info_topic);
      offset += length_camera_info_topic;
      offset += this->bounding_box.serialize(outbuffer + offset);
      offset += this->crop_compressed.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_camera_info_topic;
      arrToVar(length_camera_info_topic, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_camera_info_topic; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_camera_info_topic-1]=0;
      this->camera_info_topic = (char *)(inbuffer + offset-1);
      offset += length_camera_info_topic;
      offset += this->bounding_box.deserialize(inbuffer + offset);
      offset += this->crop_compressed.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "human_awareness_msgs/FaceCrop"; };
    const char * getMD5(){ return "eaeede2a706322edd2f5ca44f711d99d"; };

  };

}
#endif