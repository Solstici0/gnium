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
        Gnium(int mode, int type) {
            Mode = mode;  // 0 -> testing, 1-> compite
            Type = type;  // 0 -> 5-wheels, 1 -> classic 
        }

    public:
        int Mode;  // compiting or testing mode
        int Type;  // type of car (5-wheels or classic)

    void run_lap(int lap_n) {
        /*! @fn run 1 lap 
         *
         *  @param lap_n lap number
         *  @retuns TODO (wis) lap_stuct lap structure or class 
         */
        if (lap_n == 0) {
            // first lap --> train
            train();
        }
        else if (lap_n > 0 and lap_n < 3) {
            // second and third lap --> run as a motherfucker
            run_trained();
        }
        else {
            // more than 3 laps?!
            // TODO (wis) include some exception
        }
    }

    void train() {
        /*! @fn TODO (wis) training protocol for 1st lap
         */
    }

    void run_trained() {
        /*! @fn TODO (wis) run after training protocol 
         */
    }

    void test() {
        /*! TODO (wis) test protocol 
         */
    }
};
