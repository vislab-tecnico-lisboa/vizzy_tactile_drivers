
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

    float Fx;
    float Fy;
    float Fz;
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

                //Auto calibration: calculation of the b value of the linear regression curve.
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
                    
                        //Sensors channel 2: palm left
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
                        } //Sensors channel 0: little finger
                        else if (s.id == 0 && s.type == 11){
                            s.val_in = s.z;
                            s.b = -0.002372*s.val_in;
                            std::cout << "sensor 0, b: " << s.b << std::endl;
                        } else if (s.id == 1 && s.type == 14){
                            s.val_in = s.x;
                            s.b = 0.008411*s.val_in;
                            std::cout << "sensor 1, b: " << s.b << std::endl;
                        } else if (s.id == 2 && s.type == 14){
                            s.val_in = s.y;
                            s.b = -0.05343*s.val_in;
                            std::cout << "sensor 2, b: " << s.b << std::endl;
                        } else if (s.id == 3 && s.type == 11){
                            s.val_in = s.z;
                            s.b = -0.00419*s.val_in;
                            std::cout << "sensor 3, b: " << s.b << std::endl;
                        } //Sensors channel 1: index 
                        else if (s.id == 5 && s.type == 11){
                            s.val_in = s.z;
                            s.b = 0.04706*s.val_in;
                            std::cout << "sensor 5 (11), b: " << s.b << std::endl;
                        } else if (s.id == 5 && s.type == 14){
                            s.val_in = s.z;
                            s.b = 0.005986*s.val_in;
                            std::cout << "sensor 5 (14), b: " << s.b << std::endl;
                        } else if (s.id == 6 && s.type == 11){
                            s.val_in = s.y;
                            s.b = -0.0001542*s.val_in;
                            std::cout << "sensor 6, b: " << s.b << std::endl;
                        } //Sensors channel 3: palm right
                        else if ((s.id == 12 ||  s.id == 13)  && s.type == 11){
                            s.val_in = s.z;
                            s.b = 0.01831*s.val_in;
                            std::cout << "sensor 12 (11), b: " << s.b << std::endl;
                        } else if ((s.id == 12 || s.id == 15) && s.type == 14){
                            s.val_in = s.x;
                            s.b = 0.0633*s.val_in;
                            std::cout << "sensor 12 (14), b: " << s.b << std::endl;
                        } else if (s.id == 14 && s.type == 11){
                            s.val_in = s.y;
                            s.b = 0.007156*s.val_in;
                            std::cout << "sensor 14 (11), b: " << s.b << std::endl;
                        } else if (s.id == 14 && s.type == 14){
                            s.val_in = s.x;
                            s.b = 0.003408*s.val_in;
                            std::cout << "sensor 14 (14), b: " << s.b << std::endl;
                        } //Sensors channel 4: middle finger
                        else if (s.id == 16 && s.type == 14){
                            s.val_in = s.z;
                            s.b = 0.001228*s.val_in;
                            std::cout << "sensor 16, b: " << s.b << std::endl;
                        } else if (s.id == 18 && s.type == 11){
                            s.val_in = s.z;
                            s.b = 0.003735*s.val_in;
                            std::cout << "sensor 18, b: " << s.b << std::endl;
                        } else if (s.id == 19 && s.type == 11){
                            s.val_in = s.z;
                            s.b = 0.01776*s.val_in;
                            std::cout << "sensor 19 (11), b: " << s.b << std::endl;
                        } else if (s.id == 19 && s.type == 14){
                            s.val_in = s.z;
                            s.b = 0.007641*s.val_in;
                            std::cout << "sensor 19 (14), b: " << s.b << std::endl;
                        } //Sensors channel 5: thumb
                        else if (s.id == 21 && s.type == 11){
                            s.val_in = s.x;
                            s.b = -0.004517*s.val_in;
                            std::cout << "sensor 21, b: " << s.b << std::endl;
                        } else if (s.id == 22 && s.type == 11){
                            s.val_in = s.z;
                            s.b = 0.004503*s.val_in;
                            std::cout << "sensor 22, b: " << s.b << std::endl;
                        } else if (s.id == 23 && s.type == 11){
                            s.val_in = s.z;
                            s.b = 0.01071*s.val_in;
                            std::cout << "sensor 23 (11), b: " << s.b << std::endl;
                        } else{
                                std::cout << "Sensor ignorado" << std::endl;
                                std::cout << "s.id" << s.id << std::endl;
                                std::cout << "s.type" << s.type << std::endl;
                        }
                        
                        sensor_array.push_back(s);

                        }
                
                    is_calib = true;
                 }

                    
                //Calculation of forces sensed
                int idx = 0;
                for(auto &sensor_msg: msg->sensorsArray){
                    
                    //Sensors channel 2: palm left
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
                    } //Sensors channel 0: little finger
                    else if(sensor_array[idx].id == 0 && sensor_array[idx].type == 11){ //sensor 11
                        sensor_array[idx].Fz = 0.002372*sensor_msg.z+sensor_array[idx].b;
                        sensor_array[idx].Fx = 0;
                        sensor_array[idx].Fy = 0;
                        std::cout << "sensor 0, Fz: " << sensor_array[idx].Fz << std::endl;
                    } else if(sensor_array[idx].id == 1 && sensor_array[idx].type == 14){ //sensor 14
                        sensor_array[idx].Fz = -0.008411*sensor_msg.x+sensor_array[idx].b;
                        sensor_array[idx].Fx = 0;
                        sensor_array[idx].Fy = 0;
                        std::cout << "sensor 1, Fz: " << sensor_array[idx].Fz << std::endl;
                    } else if (sensor_array[idx].id == 2 && sensor_array[idx].type == 14){
                        sensor_array[idx].Fz = 0.05343*sensor_msg.y+sensor_array[idx].b;
                        sensor_array[idx].Fx = 0;
                        sensor_array[idx].Fy = 0;
                        std::cout << "sensor 2, Fz: " << sensor_array[idx].Fz << std::endl;
                    } else if (sensor_array[idx].id == 3 && sensor_array[idx].type == 11){
                        sensor_array[idx].Fz = 0.00419*sensor_msg.z+sensor_array[idx].b;
                        sensor_array[idx].Fx = 0;
                        sensor_array[idx].Fy = 0;
                        std::cout << "sensor 3, Fz: " << sensor_array[idx].Fz << std::endl;
                    } //Sensors channel 1: index 
                    else if(sensor_array[idx].id == 5 && sensor_array[idx].type == 11){ //sensor 11
                        sensor_array[idx].Fz = -0.004706*sensor_msg.z+sensor_array[idx].b;
                        sensor_array[idx].Fx = 0;
                        sensor_array[idx].Fy = 0;
                        std::cout << "sensor 5 (11), Fz: " << sensor_array[idx].Fz << std::endl;
                    } else if(sensor_array[idx].id == 5 && sensor_array[idx].type == 14){ //sensor 14
                        sensor_array[idx].Fz = -0.005986*sensor_msg.z+sensor_array[idx].b;
                        sensor_array[idx].Fx = 0;
                        sensor_array[idx].Fy = 0;
                        std::cout << "sensor 5 (14), Fz: " << sensor_array[idx].Fz << std::endl;
                    } else if (sensor_array[idx].id == 6 && sensor_array[idx].type == 11){
                        sensor_array[idx].Fz = 0.001542*sensor_msg.y+sensor_array[idx].b;
                        sensor_array[idx].Fx = 0;
                        sensor_array[idx].Fy = 0;
                        std::cout << "sensor 6, Fz: " << sensor_array[idx].Fz << std::endl;
                    } //Sensors channel 3: palm right 
                    else if((sensor_array[idx].id == 12 || sensor_array[idx].id ==13)&& sensor_array[idx].type == 11){ //sensor 11
                        sensor_array[idx].Fz = -0.01831*sensor_msg.z+sensor_array[idx].b;
                        sensor_array[idx].Fx = 0;
                        sensor_array[idx].Fy = 0;
                        std::cout << "sensor 12 (11), Fz: " << sensor_array[idx].Fz << std::endl;
                    } else if((sensor_array[idx].id == 12 || sensor_array[idx].id == 15) && sensor_array[idx].type == 14){ //sensor 14
                        sensor_array[idx].Fz = -0.0633*sensor_msg.x+sensor_array[idx].b;
                        sensor_array[idx].Fx = 0;
                        sensor_array[idx].Fy = 0;
                        std::cout << "sensor 12 (14), Fz: " << sensor_array[idx].Fz << std::endl;
                    } else if (sensor_array[idx].id == 14 && sensor_array[idx].type == 11){
                        sensor_array[idx].Fz = -0.007156*sensor_msg.x+sensor_array[idx].b;
                        sensor_array[idx].Fx = 0;
                        sensor_array[idx].Fy = 0;
                        std::cout << "sensor 14 (11), Fz: " << sensor_array[idx].Fz << std::endl;
                    } else if (sensor_array[idx].id == 14 && sensor_array[idx].type == 14){
                        sensor_array[idx].Fz = -0.003408*sensor_msg.x+sensor_array[idx].b;
                        sensor_array[idx].Fx = 0;
                        sensor_array[idx].Fy = 0;
                        std::cout << "sensor 14 (14), Fz: " << sensor_array[idx].Fz << std::endl;
                    } //Sensors channel 4: middle finger
                    else if(sensor_array[idx].id == 16 && sensor_array[idx].type == 14){ //sensor 11
                        sensor_array[idx].Fz = -0.001228*sensor_msg.z+sensor_array[idx].b;
                        sensor_array[idx].Fx = 0;
                        sensor_array[idx].Fy = 0;
                        std::cout << "sensor 16, Fz: " << sensor_array[idx].Fz << std::endl;
                    } else if(sensor_array[idx].id == 18 && sensor_array[idx].type == 11){ //sensor 14
                        sensor_array[idx].Fz = -0.003735*sensor_msg.z+sensor_array[idx].b;
                        sensor_array[idx].Fx = 0;
                        sensor_array[idx].Fy = 0;
                        std::cout << "sensor 18, Fz: " << sensor_array[idx].Fz << std::endl;
                    } else if (sensor_array[idx].id == 19 && sensor_array[idx].type == 11){
                        sensor_array[idx].Fz = -0.01776*sensor_msg.z+sensor_array[idx].b;
                        sensor_array[idx].Fx = 0;
                        sensor_array[idx].Fy = 0;
                        std::cout << "sensor 19 (11), Fz: " << sensor_array[idx].Fz << std::endl;
                    } else if (sensor_array[idx].id == 19 && sensor_array[idx].type == 14){
                        sensor_array[idx].Fz = -0.007641*sensor_msg.z+sensor_array[idx].b;
                        sensor_array[idx].Fx = 0;
                        sensor_array[idx].Fy = 0;
                        std::cout << "sensor 19 (14), Fz: " << sensor_array[idx].Fz << std::endl;
                    } //Sensors channel 5: thumb
                    else if(sensor_array[idx].id == 21 && sensor_array[idx].type == 11){ //sensor 11
                        sensor_array[idx].Fz = 0.004517*sensor_msg.x+sensor_array[idx].b;
                        sensor_array[idx].Fx = 0;
                        sensor_array[idx].Fy = 0;
                        std::cout << "sensor 21, Fz: " << sensor_array[idx].Fz << std::endl;
                    } else if(sensor_array[idx].id == 22 && sensor_array[idx].type == 11){ //sensor 14
                        sensor_array[idx].Fz = -0.004503*sensor_msg.z+sensor_array[idx].b;
                        sensor_array[idx].Fx = 0;
                        sensor_array[idx].Fy = 0;
                        std::cout << "sensor 22, Fz: " << sensor_array[idx].Fz << std::endl;
                    } else if (sensor_array[idx].id == 23 && sensor_array[idx].type == 11){
                        sensor_array[idx].Fz = -0.01071*sensor_msg.z+sensor_array[idx].b;
                        sensor_array[idx].Fx = 0;
                        sensor_array[idx].Fy = 0;
                        std::cout << "sensor 23, Fz: " << sensor_array[idx].Fz << std::endl;
                    } else{
                        std::cout << "Sensor ignorado 2" << std::endl;
                        std::cout << "id: " << sensor_array[idx].id << std::endl;
                        std::cout << "type: " << sensor_array[idx].type << std::endl;

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
