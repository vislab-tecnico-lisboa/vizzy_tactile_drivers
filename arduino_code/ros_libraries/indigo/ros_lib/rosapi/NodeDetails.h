#ifndef _ROS_SERVICE_NodeDetails_h
#define _ROS_SERVICE_NodeDetails_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace rosapi
{

static const char NODEDETAILS[] = "rosapi/NodeDetails";

  class NodeDetailsRequest : public ros::Msg
  {
    public:
      const char* node;

    NodeDetailsRequest():
      node("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      uint32_t length_node = strlen(this->node);
      memcpy(outbuffer + offset, &length_node, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->node, length_node);
      offset += length_node;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t length_node;
      memcpy(&length_node, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_node; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_node-1]=0;
      this->node = (char *)(inbuffer + offset-1);
      offset += length_node;
     return offset;
    }

    const char * getType(){ return NODEDETAILS; };
    const char * getMD5(){ return "a94c40e70a4b82863e6e52ec16732447"; };

  };

  class NodeDetailsResponse : public ros::Msg
  {
    public:
      uint8_t subscribing_length;
      char* st_subscribing;
      char* * subscribing;
      uint8_t publishing_length;
      char* st_publishing;
      char* * publishing;
      uint8_t services_length;
      char* st_services;
      char* * services;

    NodeDetailsResponse():
      subscribing_length(0), subscribing(NULL),
      publishing_length(0), publishing(NULL),
      services_length(0), services(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset++) = subscribing_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < subscribing_length; i++){
      uint32_t length_subscribingi = strlen(this->subscribing[i]);
      memcpy(outbuffer + offset, &length_subscribingi, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->subscribing[i], length_subscribingi);
      offset += length_subscribingi;
      }
      *(outbuffer + offset++) = publishing_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < publishing_length; i++){
      uint32_t length_publishingi = strlen(this->publishing[i]);
      memcpy(outbuffer + offset, &length_publishingi, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->publishing[i], length_publishingi);
      offset += length_publishingi;
      }
      *(outbuffer + offset++) = services_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < services_length; i++){
      uint32_t length_servicesi = strlen(this->services[i]);
      memcpy(outbuffer + offset, &length_servicesi, sizeof(uint32_t));
      offset += 4;
      memcpy(outbuffer + offset, this->services[i], length_servicesi);
      offset += length_servicesi;
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint8_t subscribing_lengthT = *(inbuffer + offset++);
      if(subscribing_lengthT > subscribing_length)
        this->subscribing = (char**)realloc(this->subscribing, subscribing_lengthT * sizeof(char*));
      offset += 3;
      subscribing_length = subscribing_lengthT;
      for( uint8_t i = 0; i < subscribing_length; i++){
      uint32_t length_st_subscribing;
      memcpy(&length_st_subscribing, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_subscribing; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_subscribing-1]=0;
      this->st_subscribing = (char *)(inbuffer + offset-1);
      offset += length_st_subscribing;
        memcpy( &(this->subscribing[i]), &(this->st_subscribing), sizeof(char*));
      }
      uint8_t publishing_lengthT = *(inbuffer + offset++);
      if(publishing_lengthT > publishing_length)
        this->publishing = (char**)realloc(this->publishing, publishing_lengthT * sizeof(char*));
      offset += 3;
      publishing_length = publishing_lengthT;
      for( uint8_t i = 0; i < publishing_length; i++){
      uint32_t length_st_publishing;
      memcpy(&length_st_publishing, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_publishing; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_publishing-1]=0;
      this->st_publishing = (char *)(inbuffer + offset-1);
      offset += length_st_publishing;
        memcpy( &(this->publishing[i]), &(this->st_publishing), sizeof(char*));
      }
      uint8_t services_lengthT = *(inbuffer + offset++);
      if(services_lengthT > services_length)
        this->services = (char**)realloc(this->services, services_lengthT * sizeof(char*));
      offset += 3;
      services_length = services_lengthT;
      for( uint8_t i = 0; i < services_length; i++){
      uint32_t length_st_services;
      memcpy(&length_st_services, (inbuffer + offset), sizeof(uint32_t));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_services; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_services-1]=0;
      this->st_services = (char *)(inbuffer + offset-1);
      offset += length_st_services;
        memcpy( &(this->services[i]), &(this->st_services), sizeof(char*));
      }
     return offset;
    }

    const char * getType(){ return NODEDETAILS; };
    const char * getMD5(){ return "3da1cb16c6ec5885ad291735b6244a48"; };

  };

  class NodeDetails {
    public:
    typedef NodeDetailsRequest Request;
    typedef NodeDetailsResponse Response;
  };

}
#endif
