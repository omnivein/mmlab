#include <L1/L1.hxx>


GuardedStream::GuardedStream()
{
  fstream.open("shared_results.txt", std::ios::out);
}
GuardedStream::~GuardedStream() { fstream.close(); }

void GuardedStream::lock() { this->m_mutex.lock(); }
void GuardedStream::unlock() { this->m_mutex.unlock(); }

template <class DataAny>
GuardedStream& GuardedStream::operator<<(DataAny data)
{
  this->fstream << data;
  return *this;
}

void lab1_main()
{
  Perf lab1Perf("LAB 1");  // Start performance measuring

  // Create shared resource stream guard
  GuardedStream fstream;

  // Initialize randomizer
  PseudoR Rand(4324, { 0.0, 1080.0 });

  // List of angles measured in degrees for function 1
  std::vector<float> xargsF;
  
  // Fill array with pseudo-random values
  int fillCounter = 0;
  while( fillCounter++ <= 10000 )
  {
    xargsF.push_back( Rand.gen_real() );
  }

/******************************************************************************
 * [ 1 ] st Method to use threads
 ******************************************************************************
 */
  // Creating threads and passing reference parameter arguments
  std::thread fn1_worker(f1_calculations, xargsF, std::ref(fstream));
  std::thread fn2_worker(f2_calculations, xargsF, std::ref(fstream));

  fn1_worker.join();
  fn2_worker.join();

  // Detaching child threads and waiting some time in main thread
  // fn1_worker.detach();
  // fn2_worker.detach();
  // usleep(1000000);
}

void f1_calculations(std::vector<float> argX, GuardedStream& fstream)
{
  pretty_print("Thread 1... started", 1);
  Perf perf("Function [1]"); // Start performance measuring

  fstream.lock();

  // File will contain calculation results
  // std::ofstream fs_fn1Results("fn1_results.txt", std::ios::out);
  
  std::vector<float>::iterator cur_it = argX.begin();
  std::vector<float>::iterator end_it = argX.end();

  // Walking through all the function's arguments and saving the results
  while( cur_it++ != end_it )
  {
    // Convert angle to radians and calc the function
    fstream << "THREAD: " << std::this_thread::get_id() << " ### "
      << "X (angle) = " << *cur_it << " | "
      << "cos(2x) = " << cos( 2 * ( PI * (*cur_it) / 180 ) ) << "\n";
  }

  fstream.unlock();
  // fs_fn1Results.close();
  // End performance measuring on object destruction
}
void f2_calculations(std::vector<float> argX, GuardedStream& fstream)
{
  pretty_print("Thread 2... started", 1);
  Perf perf("Function [2]");

  // // Using mutex to protect shared resource
  fstream.lock();

  // // Creating new file stream 
  // std::ofstream fs_fn2Results("fn2_results.txt", std::ios::out)

  std::vector<float>::iterator cur_it = argX.begin();
  std::vector<float>::iterator end_it = argX.end();
  
  while( cur_it++ != end_it )
  {
    // The cbrt is the cubic root
    // fs_fn2Results
    fstream << "THREAD: " << std::this_thread::get_id() << " ### "
      << "X  = " << *cur_it << " | "
      << "y(x) = (3-_/1-x) = "
      << cbrt(1.0 - (*cur_it) ) << "\n";
  }

  // // Releasing lock on shared resource 
  fstream.unlock();
  // // fs_fn2Results.close();
}