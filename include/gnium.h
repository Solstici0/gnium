/*! @file gnium.h
* @brief gnium.h: defines gnium namespace and class
*/

namespace gnium {
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
        Gnium(int mode, int type = 0, int lap_n = 0, int train_pwm = 10) {
            Mode = mode;  // 0 -> testing, 1-> compite
            Type = type;  // 0 -> 5-wheels, 1 -> classic 
            Lap_n = lap_n;  // lap number counter
            Train_pwm = train_pwm;  // pwm train velocity
        }

    public:
        int Mode;  // compiting or testing mode
        int Type;  // type of car (5-wheels or classic)
        int Lap_n;  // lap number counter
        int Train_pwm;  // pwm train velocity
        bool Start_detected = false;  // bool start line detected
        bool End_detected = false;  // bool end line detected

    void reset_start_and_end() {
        /*!< @fn reset_start_and_end
          * reset Start and End detected Booleans
          */
          gnium::Gnium::Start_detected = false;
          gnium::Gnium::End_detected = false;
        }

    int run_lap(int lap_n) {
        /*! @fn run 1 lap 
         *
         *  @param lap_n lap number
         *  @retuns TODO (wis) lap_stuct lap structure or class 
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

    int train(int train_pwm = -1) {
        /*! @fn train protocol for first lap
         * @param train_pwm forward velocity for training
         * TODO @param pid should be a vector of 3 elements
         * TODO (wis) training protocol for 1st lap
         * when running this function we should save the lap database.
         * Where this should be saved? lap class (struct)?
         * gnium attribute?
         */

         // use default Train_pwm velocity if its not defined
         if (train_pwm == -1) {
             train_pwm = gnium::Gnium::Train_pwm;
         }

         // run until start line is detected
         while (!gnium::Gnium::Start_detected) {
             gnium::Gnium::Start_detected =
                 gnium::Gnium::follow_trace(train_pwm);
         }

         // run until end line is detected
         while (gnium::Gnium::Start_detected and
             !gnium::Gnium::End_detected) {
             gnium::Gnium::End_detected =
                 gnium::Gnium::follow_trace(train_pwm);
         }

         // end detected routine
         if (gnium::Gnium::End_detected) {
             gnium::Gnium::follow_trace(train_pwm);
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
         return 0;
         }


    bool follow_trace(int vel_pwm) {
        /*! @fn run following the line
          * @param vel_pwm
          * TODO @param pid
          * @return true if start or end
          * line is detected
         */

        // read information from IR sensors
        // and update start_or_end_is_detected
        // this should be a variable from another namespace
        // communication.h? ir_sensors.h?

        // write information to motors
        // here we should use pid::measure_error_and_correct
        // and inside that function we should use communication
        // namespace directly
        int start_or_end_is_detected = 0; // just to pass tests
                                          // should not be like this
        if (start_or_end_is_detected) {
            return true;
        }
        else {
            return false;
        }
    }

    // IDEA: TODO
    // this should be more efficiente if we only have one
    // function for detecting stop or start line
    // So the idea is to merger stop_after_end_detected and
    // run_until_start_detected

    void test() {
        /*! TODO (wis) test protocol 
         */
    }
};
