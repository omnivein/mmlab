#ifndef __LAB1_MODULE_H
#define __LAB1_MODULE_H

  #include <common.hxx>
  #include <vector>
  #include <cstdlib>
  #include <cmath>
  #include <fstream>
  #include <unistd.h>
  #include <mutex>

  #define PI 3.14159265
  // App's entry point


/* >> CLASSES >> */
/* ========================================================================= */
  
  class GuardedStream
  {
    // provides control of mutual use for this class
    std::mutex m_mutex;
    // output stream
    std::ofstream fstream; 

    public:
    /** Constructor: Perf
       * --------------------------------------------------
       * > Opens member file stream
       * -------------------------------------------------- */
      GuardedStream();

      /** Constructor: Perf
       * --------------------------------------------------
       * > Closes member file stream
       * -------------------------------------------------- */
      ~GuardedStream();

      // Locks member mutex
      void lock();
      //Unlocks member mutex
      void unlock();


      /** Operator Overloading: << 
       * --------------------------------------------------
       * > Overloads class' operator <<
       * > to provide easier passing data to the function
       * --------------------------------------------------
       * @param data - data of any type to be written to the output stream
       * --------------------------------------------------
       * @returns GuardedStream& - reference to current class
       * -------------------------------------------------- */
      template <class DataAny>
      GuardedStream& operator<<(DataAny data);
      
  };


/* >> FUNCTIONS >> */
/* ========================================================================= */
  // L1 module's entry point
  void lab1_main();

  /** Functions: f1_calculations, f2_calculations
   * --------------------------------------------------
   * > Calculates function with provided arguments
   * > writes results to the file
   * --------------------------------------------------
   * @param argX - vector with arguments for the function
   * @param fstream - reference to the shared resource GuardedStream
   * --------------------------------------------------
   * @returns void
   * -------------------------------------------------- */
  void f1_calculations(std::vector<float>, GuardedStream& fstream);
  void f2_calculations(std::vector<float>, GuardedStream& fstream);

#endif