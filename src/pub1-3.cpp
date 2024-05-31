// #include "rclcpp/rclcpp.hpp"
// #include <geometry_msgs/msg/twist.hpp>
// #include <signal.h>
// #include <termios.h>
// #include <stdio.h>
// #include <memory.h>
// #include <unistd.h>


// #define KEYCODE_R 0x43 
// #define KEYCODE_L 0x44
// #define KEYCODE_U 0x41
// #define KEYCODE_D 0x42
// #define KEYCODE_Q 0x71

// class TeleopTurtle
// {
// public:
//   TeleopTurtle(std::shared_ptr<rclcpp::Node> nh);
//   void keyLoop();

// private:

  
//   std::shared_ptr<rclcpp::Node> nh_;
//   double linear_, angular_, l_scale_, a_scale_;
//   rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr twist_pub_;
  
// };

// TeleopTurtle::TeleopTurtle(std::shared_ptr<rclcpp::Node> nh):
//   nh_(nh),
//   linear_(0),
//   angular_(0),
//   l_scale_(2.0),
//   a_scale_(2.0)
// {
// //   nh_.param("scale_angular", a_scale_, a_scale_);
// //   nh_.param("scale_linear", l_scale_, l_scale_);

//   twist_pub_ = nh_->create_publisher<geometry_msgs::msg::Twist>("turtle1/cmd_vel", 1);
// }

// int kfd = 0;
// struct termios cooked, raw;

// void quit(int sig)
// {
//   (void)sig;
//   tcsetattr(kfd, TCSANOW, &cooked);
// //   ros::shutdown();
//   rclcpp::shutdown();
//   exit(0);
// }


// int main(int argc, char** argv)
// {
// //   ros::init(argc, argv, "teleop_turtle");
//   rclcpp::init(argc, argv);
//   auto node = rclcpp::Node::make_shared("teleop_turtle");
//   TeleopTurtle teleop_turtle(node);

//   signal(SIGINT,quit);

//   teleop_turtle.keyLoop();
  
//   return(0);
// }


// void TeleopTurtle::keyLoop()
// {
//   char c;
//   bool dirty=false;


//   // get the console in raw mode                                                              
//   tcgetattr(kfd, &cooked);
//   memcpy(&raw, &cooked, sizeof(struct termios));
//   raw.c_lflag &=~ (ICANON | ECHO);
//   // Setting a new line, then end of file                         
//   raw.c_cc[VEOL] = 1;
//   raw.c_cc[VEOF] = 2;
//   tcsetattr(kfd, TCSANOW, &raw);

//   puts("Reading from keyboard");
//   puts("---------------------------");
//   puts("Use arrow keys to move the turtle.");


//   for(;;)
//   {
//     // get the next event from the keyboard  
//     if(::read(kfd, &c, 1) < 0)
//     {
//       perror("read():");
//       exit(-1);
//     }

//     linear_=angular_=0;
//     // ROS_DEBUG("value: 0x%02X\n", c);
  
//     switch(c)
//     {
//       case KEYCODE_L:
//         std::cout << "LEFT" << std::endl;
//         angular_ = 1.0;
//         dirty = true;
//         break;
//       case KEYCODE_R:
//         // ROS_DEBUG("RIGHT");
//         std::cout << "RIGHT" << std::endl;
//         angular_ = -1.0;
//         dirty = true;
//         break;
//       case KEYCODE_U:
//         // ROS_DEBUG("UP");
//         std::cout << "UP" << std::endl;
//         linear_ = 1.0;
//         dirty = true;
//         break;
//       case KEYCODE_D:
//         // ROS_DEBUG("DOWN");
//         std::cout << "DOWN" << std::endl;
//         linear_ = -1.0;
//         dirty = true;
//         break;
//     }

//     geometry_msgs::msg::Twist twist;
//     twist.angular.z = a_scale_*angular_;
//     twist.linear.x = l_scale_*linear_;
//     if(dirty ==true)
//     {
//       twist_pub_->publish(twist);    
//       dirty=false;
//     }
//   }

//   return;
// }
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/vector3.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include <memory>

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<rclcpp::Node>("node_pub1_3");
    auto qos_profile = rclcpp::QoS(rclcpp::KeepLast(10));
    auto mypub = node->create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", qos_profile);
    char key;
    while(rclcpp::ok())
    {
        geometry_msgs::msg::Twist message;
        std::cin >> key;
        switch (key)
        {
            case 'f': 
                message.linear.x = 1; 
                break;
            case 'b': 
                message.linear.x = -1; 
                break;
            case 'l': 
                message.angular.z = 1.5708; 
                break;
            case 'r': 
                message.angular.z = -1.5708; 
                break;
            default: 
                RCLCPP_INFO(node->get_logger(), "bad input"); 
                continue;
        }
        mypub->publish(message);
        RCLCPP_INFO(node->get_logger(), "msg sent");
        //rclcpp::spin_some(node);
        //loop_rate.sleep(); //반복주파수에서 남은 시간 만큼 sleep
    }
    rclcpp::shutdown();
    return 0;
}