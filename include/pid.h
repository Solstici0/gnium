/*! @file pid.h
 * defines pid controller namespace
*/

namespace pid {
  class Pid;
}

class pid::Pid {
    /*! @class Pid
    * creates pid object
    */
    public:
        // Constructor
        Pid(float kp = 10., float ki = 0., float kd = 0.,
            int target_array[3] = {} ) {
            Kp = kp;
            ki = ki;
            Kd = kd;
            Ta = target_array;
        }
    public:
        float Kp; // proportional constant
        float Ki; // integral constant
        float Kd; // derivative constant
        int* Ta; // target array (perfect position over trace)

  // TODO: code correction signal
  //float correction_signal(int* sensor_array) {
  //e_p = sensor_array - pid::Pid::Ta;
  //e_i += e_p * dt;  // e_i(0) = 0
  //e_d = (e_p - e_prev); / dt
  //float correction_signal = pid::Pid::Kp*e_p + pid::Pid::Ki*e_i +
  // pid::Pid::Kd*e_d;
  //e_prev = e_p
  //return correction_signal
  // TODO: define dt. Coulde be like this:
  // time_now = read_time_function()
  // dt = time_now - time_before
  // time_before = time_now
  //}

  //}
};
