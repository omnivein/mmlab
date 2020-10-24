#include <common.hxx>

/* >> Performance >> */
/* ========================================================================= */

// Capturing the execution's start time a current scope
Perf::Perf(const char* taskLabel)
{
  m_taskLabel = (char*)taskLabel;
  std::cout << "\nTask |>> " << m_taskLabel << " <<| started\n";
  m_startPoint = std::chrono::time_point_cast<std::chrono::microseconds>(
    std::chrono::high_resolution_clock::now()
  );
}
// Capturing the execution's end time of a current scope
Perf::~Perf()
{
  // Get end time point
  TimePoint endPoint = std::chrono::time_point_cast<std::chrono::microseconds>(
    std::chrono::high_resolution_clock::now()
  );
  
  // Get time point value
  unsigned long startTime = m_startPoint.time_since_epoch().count();
  unsigned long endTime = endPoint.time_since_epoch().count();

  // Calculate the difference between task's start and finish time
  unsigned long duration = endTime - startTime;
  double msDuration = duration * 0.001;

  // Spew some info about what heck's goin' on
  std::cout << "\nTask |>> "
    << this->m_taskLabel
    << " <<| finished and took: "
    << msDuration << " ms\n\n";
}

/* >> Class: PseudoR >> */
/* ========================================================================= */
// PRIVATE
  void PseudoR::setDefaults()
  {
    this->setSeed(599572); // Default seed
    this->setIntRange({ 0, 10 }); // Default int range
    this->setRealRange({ 0.0, 10.0 }); // Default real range
  }

// PUBLIC
  PseudoR::PseudoR()
  {
    this->setDefaults();
  }

  PseudoR::PseudoR(int seed)
  {
    this->setSeed(seed);
  };

  PseudoR::PseudoR(int seed, const int(&range)[2])
  {
    this->setSeed(seed);
    this->setIntRange(range);
  }

  PseudoR::PseudoR(int seed, const double(&range)[2])
  {
    this->setSeed(seed);
    this->setRealRange(range);
  }

  void PseudoR::setSeed(int seed) { this->m_gen.seed(seed); }
  void PseudoR::setIntRange(const int(&range)[2])
  {
    this->int_distrib.param(
      std::uniform_int_distribution<int>(range[0], range[1]).param()
    );
  }

  void PseudoR::setRealRange(const double(&range)[2])
  {
    this->real_distrib.param(
      std::uniform_real_distribution<double>(range[0], range[1]).param()
    );
  }

  int    PseudoR::gen_int()  { return this->int_distrib(this->m_gen); }
  double PseudoR::gen_real() { return this->real_distrib(this->m_gen); }


/* >> Functions: pretty printing >> */
/* ========================================================================= */

// Print specified amount of hyphens
std::string get_delim_str(int hyphenCount, char sym)
{
  // Minimum amount of printed hyphens: 30
  hyphenCount = hyphenCount > 30 ? hyphenCount : 30;
  std::string hyphenString;
  int c = 1;
  
  while ( c++ <= hyphenCount ){ hyphenString.append((std::string (1,sym))); }

  return hyphenString;
}

// Pretty print
void pretty_print(std::string str, int append_to)
{
  int strlen = str.length();
  int counter = 1;

  std::string hyphens = get_delim_str(strlen, '-');
  
  /* Coerce invalid values to default value (1) - print after
   * 0 - print before
   * 1 - print after 
   * 2 - print both */
  append_to = (append_to > 2) ? 1 : append_to;

  // Print only before or both
  if ( append_to ^ 1 ) { std::cout << "\n" << hyphens; }

  // "\n" works faster than std::endl
  std::cout << "\n" << str << "\n";

  // When has value 1 or 2
  if ( append_to & 0x03 ) { std::cout << hyphens << "\n"; }
}