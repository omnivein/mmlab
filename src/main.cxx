#include <common.hxx> // Contains common functions & libraries
#include <l1/l1.hxx>    // Lab 1 module
#include <map>



int main(int argc, char** argv)
{
  // Author info
  pretty_print(
    "- (c) Created and maintained by "
    "@omnivein (aka Stanislav Pavlyshynets) -"
    , 2
  );

  // Create name-function mapping for futher invokation
  std::map<std::string, void (*)()> nameMap =
  {
    { "lab1", lab1_main }
  };
 
  // Start module specified as app argument
  if (argc >= 2 && nameMap.count( argv[1] ))
  {
    pretty_print( std::string("Now on the air: ") + argv[1], 1);
    nameMap[ argv[1] ]();
    std::cout << "\nThe end of the ether! Bye! \n";
  }

  return 0;
}