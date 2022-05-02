
#include "ros/ros.h"
#include "vizzy_tactile/TacVector.h"
#include "vizzy_tactile/Tactile.h"
#include "vizzy_tactile/TactSensorArray.h"
#include "vizzy_tactile/TactSensor.h"

class Sensor{
    public:

    int id;
    int type;
    int x;
    int y;
    int z;

    int d = 1;
    int val_in;

    float b;

    int Fx;
    int Fy;
    int Fz;
};


class SensorComputer
{
    public:
        ros::NodeHandle nh_;
        std::vector<Sensor> sensor_array;
        ros::Publisher pub_;
        ros::Subscriber sub_;

        bool is_calib = false;

        SensorComputer(ros::NodeHandle nh) : nh_(nh)
        {
            pub_ = nh_.advertise<vizzy_tactile::TactSensorArray>("forces",1);
            sub_ = nh_.subscribe<vizzy_tactile::Tactile>("tactile", 1, &SensorComputer::callback, this);
            
        }


        void callback(const vizzy_tactile::Tactile::ConstPtr& msg)
        {

            
                if(!is_calib)
                 {
                    for(auto &sensor_msg: msg->sensorsArray){
                        
                        std::cout << sensor_msg << std::endl;

                        Sensor s;
                        s.id = sensor_msg.id;
                        s.type = sensor_msg.type;
                        s.x = sensor_msg.x;
                        s.y = sensor_msg.y;
                        s.z = sensor_msg.z;

                        if(s.id == 8 && s.type == 11){   //sensor 8   
                            s.val_in = s.y;
                            s.b = -0.005616*s.val_in;
                            std::cout << "sensor 8, b: " << s.b << std::endl;
                        } else if(s.id == 11 && s.type == 11){ //sensor 11
                            s.val_in = s.x;
                            s.b = 0.009252*s.val_in;
                            std::cout << "sensor 11 (11), b: " << s.b << std::endl;
                        } else if(s.id == 10 && s.type == 14){ //sensor 14
                            s.val_in = s.x;
                            s.b = -0.005203*s.val_in;
                            std::cout << "sensor 10, b: " << s.b << std::endl;
                        } else if (s.id == 11 && s.type == 14){
                            s.val_in = s.x;
                            s.b = 0.003944*s.val_in;
                            std::cout << "sensor 11 (14), b: " << s.b << std::endl;
                        }else{
                                std::cout << "Sensor ignorado" << std::endl;
                        }

                        sensor_array.push_back(s);

                        }
                
                    is_calib = true;
                 }

                    
                int idx = 0;
                for(auto &sensor_msg: msg->sensorsArray){

                    if(sensor_array[idx].id == 8 && sensor_array[idx].type == 11){   //sensor 8   
                        sensor_array[idx].Fz = 0.005617*sensor_msg.y+sensor_array[idx].b;
                        sensor_array[idx].Fx = 0;
                        sensor_array[idx].Fy = 0;
                        std::cout << "sensor 8, Fz: " << sensor_array[idx].Fz << std::endl;
                    } else if(sensor_array[idx].id == 11 && sensor_array[idx].type == 11){ //sensor 11
                        sensor_array[idx].Fz = -0.009252*sensor_msg.x+sensor_array[idx].b;
                        sensor_array[idx].Fx = 0;
                        sensor_array[idx].Fy = 0;
                        std::cout << "sensor 11 (11), Fz: " << sensor_array[idx].Fz << std::endl;
                    } else if(sensor_array[idx].id == 10 && sensor_array[idx].type == 14){ //sensor 14
                        sensor_array[idx].Fz = 0.0005203*sensor_msg.x+sensor_array[idx].b;
                        sensor_array[idx].Fx = 0;
                        sensor_array[idx].Fy = 0;
                        std::cout << "sensor 10, Fz: " << sensor_array[idx].Fz << std::endl;
                    } else if (sensor_array[idx].id == 11 && sensor_array[idx].type == 14){
                        sensor_array[idx].Fz = -0.003944*sensor_msg.x+sensor_array[idx].b;
                        sensor_array[idx].Fx = 0;
                        sensor_array[idx].Fy = 0;
                        std::cout << "sensor 11 (14), Fz: " << sensor_array[idx].Fz << std::endl;
                    }else{
                        std::cout << "Sensor ignorado" << std::endl;
                    }

                    idx++;
                }


                vizzy_tactile::TactSensorArray sensor_array_msg;

                for(auto &my_sensor: sensor_array)
                {   
                    vizzy_tactile::TactSensor message;
                    std::stringstream ss;
                    ss <<  my_sensor.id << "_" << my_sensor.type;
                    message.frame_id=ss.str();
                    message.force.z = my_sensor.Fz;
                    sensor_array_msg.sensorArray.push_back(message);
                }

                pub_.publish(sensor_array_msg);
        }

};


int main(int argc, char **argv){

    ros::init(argc, argv, "forces_calculation");

    ros::NodeHandle nh;   

    SensorComputer sc(nh);

    ros::spin();

    return 0;
}
