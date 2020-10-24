#ifndef __COMMON_LIB_H
#define __COMMON_LIB_H


/* >> HEADERS >> */
/* ========================================================================= */

  #include <iostream>
  #include <chrono>
  #include <thread>
  #include <random>

/* >> CLASSES >> */
/* ========================================================================= */

  // Shink chrono time_point type's signature using type aliasing
  typedef std::chrono::time_point
    <
      std::chrono::high_resolution_clock,
      std::chrono::microseconds
    > TimePoint;
  
  /** Class: Perf
   * --------------------------------------------------
   * > Measures execution time in between class creation-destruction
   * > It is important to have in mind objects lifecycle
   * -------------------------------------------------- */
  class Perf
  {
    private:
      // Time mark of moment the measured task was started
      TimePoint m_startPoint;
      // The mark of moment the measured task was finished
      TimePoint m_endPoint;
      // Measured task label
      char* m_taskLabel;

    public:
      /** Constructor: Perf
       * --------------------------------------------------
       * > Creates current performance mark
       * > and saves the task label which the timer is related to
       * --------------------------------------------------
       * @param taskLabel - mention of a specific unit being measured
       * -------------------------------------------------- */
      Perf(const char*);

      /** Destructor: Perf
       * --------------------------------------------------
       * > Creates new current performance mark
       * > Prints task label
       * > calculates and prints the difference between two marks 
       * -------------------------------------------------- */
      ~Perf();
  };

  /** Class: PseudoR
   * --------------------------------------------------
   * > Implements pseudo-random generator's "functionality"
   * -------------------------------------------------- */
  class PseudoR
  {
    private:
      std::uniform_int_distribution<int> int_distrib;
      std::uniform_real_distribution<double> real_distrib;
      std::mt19937 m_gen;

      void setDefaults();

    public:

      PseudoR();
      PseudoR(int seed);
      PseudoR(int, const int(&)[2]);
      PseudoR(int, const double(&)[2]);
      
      void setSeed(int seed);
      void setIntRange(const int(&)[2]);
      void setRealRange(const double(&)[2]);
      
      int    gen_int();
      double gen_real();
  };


/* >> FUNCTIONS >> */
/* ========================================================================= */

  /** Function: get_delim_str
   * --------------------------------------------------
   * > Prints text passed as argument
   * > And prints delimiter to prettify the general look
   * --------------------------------------------------
   * @param hyphenCount - amount of hyphen symbols to be printed
   *   If passed value is < 30, then ${ hyphenCount } is assigned 30
   * @param sym - the character which will string consist of 
   * --------------------------------------------------
   * @return hyphenString - string, containing ${hyphenCount} hyphens
   * -------------------------------------------------- */
  std::string get_hyphen_str(int, char);

  /** Function: print_header
   * --------------------------------------------------
   * > Prints text passed as argument
   * > And prints delimiter to prettify the general look
   * --------------------------------------------------
   * @param str - string to be printed
   * @param append_to - specifies where to put hyphens
   *   = 0 - print after the string
   *   = 1 - print before the string
   *   = 2 - print before and after the string
   * -------------------------------------------------- */
  void pretty_print(std::string, int);


#endif // __COMMON_LIB
