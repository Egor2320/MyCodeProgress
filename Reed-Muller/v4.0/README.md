# added:
##-new tests (testAll() and testRandom())
##-now its only possible to apply a function to a std::string
##-when applying, the apply() functions check whether a string is valid, if string is less than needed, we add zeroes to the end, if it's bigger - throw an InvalidPadding exception (custom one)
##-also have a custom exception in class Test (when it runs testAll() and gets function and truth table of different sizes, it throws a InvalidFormat exception)
##-now projects supports Doxygen documentation, the comments will transform to a document
