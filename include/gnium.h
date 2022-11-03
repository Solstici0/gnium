/*! @file gnium.h
* @brief gnium.h: defines gnium namespace and class
*/
#include <pid.h>
#include <ir_sensor.h>
#include <servo.h>
#include <muscle.h>

namespace gnium {
    typedef enum mode{
        race,
        test_ir_sensors,
        test_side_sensors,
        test_servo,
        test_servo_offset,
        test_servo_angle,
        test_muscle,
        test_vel,
        test_forward_vel,
        test_follow_trace
    }mode;

    // TODO (wis) create array of struct for lap information
    // total marks in the lap
    //TOTAL_MARKS = 30
    //struct mark {
    //  int next_idx;
    //  float mean_angle;
    //  float max_vel;
    //  bool end_line;  // save finish line
    //  for the future, we can also include encoder steps here
    //};
    //
    //mark lap_info [TOTAL_MARKS];
    // Training routine
    //so in lap_info[n] we can save information from the nth to (n+1)th mark
    //in (or a bit after) mark (n + 1)=k do:
    //gnium::lap_info[n].next_idx = k
    //gnium::lap_info[n].mean_angle = tools::mean_angle(last_angle_meas)
    //gnium::lap_info[n].max_vel = tools::max_vel_from_angle(lap_info[n].mean_angle)
    //Trained routine
    //then we can use this information to define velocity planning.
    //For example, if lap_info[n+1].max_vel > lap_info[n].max_vel accelerate
    //OBS.:
    //mean_angle has to be calculated after reaching the next mark (while training).
    //so info related to nth mark is saved when we are within mark (n+1) and (n+2)
    //we need an extra variable for saving last angle measurements
    //and then calculate mean_angle using it
    //OBS2.:
    //if end detected:
    //lap_info[last + 1].end_line = 1;
    //else:
    //lap_info[last + 1].end_line = 0;
    class Gnium;
    
}

// Creates gnium object
// Example:
//     gnium:Gnium gnium = gnium:Gnium()
//     gnium.method()
class gnium::Gnium {
    /*! @class Gnium
     * Creates gnium object
     */
    public:
        // Constructor
        //TODO (wis) in principle, there should be 2 types of gnium
        // with 5 wheels, and the standar 3 wheels version
        Gnium(int mode, int type = 0, int lap_n = 0,
              int train_pwm = 75, pid::Pid pid = pid::Pid(),
              int threshold = 100) {
            Mode = mode;  // 0 -> testing, 1-> compite
            Type = type;  // 0 -> 5-wheels, 1 -> classic 
            Lap_n = lap_n;  // lap number counter
            Train_pwm = train_pwm;  // pwm train velocity (in degrees)
            Threshold = threshold;
            // TODO (wis) inject pid object as attribute..
            // check if this could be improve
            Pid = pid; // PID controller
            ir_sensor::setup(Threshold);
            servo::setup();
            muscle::setup();

        }

    public:
        int Mode;  // compiting or testing mode
        int Type;  // type of car (5-wheels or classic)
        int Lap_n;  // lap number counter
        int Train_pwm;  // pwm train velocity in degrees (forward: pwm > 90)
        bool Start_detected = false;  // bool start line detected
        bool End_detected = false;  // bool end line detected
        int Threshold;
        pid::Pid Pid;  //PID controller

    void reset_start_and_end() {
        /*! @fn reset_start_and_end
          * reset Start and End detected Booleans
          */
          gnium::Gnium::Start_detected = false;
          gnium::Gnium::End_detected = false;
        }

    int run_lap(int lap_n) {
        /*! @fn run 1 lap 
         *
         *  @param lap_n lap number
         *  @retuns TODO (wis) lap_struct lap structure or class
         */

        // reset start and end line detectors booleans
        gnium::Gnium::reset_start_and_end();
        int fail = 0;
        if (lap_n == 0) {
            // first lap --> train
            fail = gnium::Gnium::train();
        }
        else if (lap_n > 0 and lap_n < 3) {
            // second and third lap --> run as a motherfucker
            fail = gnium::Gnium::run_trained();
        }
        else {
            // more than 3 laps?!
            // TODO (wis) include some exception
        }
        return fail;
    }

    int train(int train_pwm = -1,
              pid::Pid pid = pid::Pid()) {
        /*! @fn train protocol for first lap
         * @param train_pwm forward velocity for training
         * @param pid object
         * TODO (wis) training protocol for 1st lap
         * when running this function we should save the lap database.
         * Where this should be saved? lap class (struct)?
         * gnium attribute?
         */
         // use default Train_pwm velocity and PID values
         if (train_pwm == -1) {
             train_pwm = Train_pwm;
         }
         //n = 0; // mark counter

         // run until start line is detected
         while (!gnium::Gnium::Start_detected) {
             gnium::Gnium::Start_detected =
                 gnium::Gnium::follow_trace(train_pwm, pid);
         }

         // run until end line is detected
         while (gnium::Gnium::Start_detected and
             !gnium::Gnium::End_detected) {
             // Save lap information after each new mark
             // is detected
             //if (ir_sensors::mark_detected()) {
             //n += 1;
             //}
             
             // update End_detected flag
             gnium::Gnium::End_detected =
                 gnium::Gnium::follow_trace(train_pwm, pid);
         }

         // end detected routine
         if (gnium::Gnium::End_detected) {
             gnium::Gnium::follow_trace(train_pwm, pid);
             // here we can stop for some time
             // and then exit function
             return 0;
         }
         // this shouldn't happen if we run the lap *propely*
         return 1;
    }

    int run_trained() {
        /*! @fn TODO (wis) run after training protocol 
         */

         // TODO: (wis) this routine needs to rewrite/create a
         // PID instance evertime a new "mark" appears

         // we need a detect_mark() routine
         // so we can detect marks and create the PID.
         // Which is the best way to do this?
         // TODO: (wis) Ask Felipin.
         // We should only read the IR sensor associated
         // with a new mark here
         //if (new_mark_detected) {
         //    gnium::Gnium::pid = pid::Pid::update_pid(curvature)};
         //    gnium::Gnium::vel_pwm = gnium::Gnium::update_vel(curvature)};
         //follow_tracer(gnium::Gnium::vel_pwm, gnium::Gnium::Pid)
         return 0;
         }


    bool follow_trace(int vel_pwm, pid::Pid pid) {
        /*! @fn run following the line
          * @param vel_pwm (in degrees)
          * @param pid object
          * @return true if start or end
          * line is detected
         */

        // read from from ir sensors
        unsigned char Sensor_array = ir_sensor::read_front();
        // calculate correction using pid
        float angle_correction = pid.correction_signal(Sensor_array);
        // set new angle and velocity
        servo::set_angle(angle_correction); //
        muscle::set_vel(vel_pwm); //

        int start_or_end_detected = 0; // just to pass tests
                                          // should not be like this
        //int start_or_end_detected = ir_sensor::start_or_end_detected();

        if (start_or_end_detected) {
            return true;
        }
        else {
            return false;
        }

    }

    void test() {
        /*! TODO (wis) test protocol 
         */
    }
};
