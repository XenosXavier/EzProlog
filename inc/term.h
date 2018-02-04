#ifndef TERM_H
#define TERM_H
#include <string>
using std::string;

/**
 * [Composite Pattern - Component]
 * The abstract class of prolog data objects.
 * It provides some interfaces for term.
 */
class Structure;
class Variable;
class Term
{
public:
  // Returns the symbol of term.
  virtual string symbol() const = 0;

  // Returns the value of term.
  virtual string value() = 0;

  // Match with another term.
  virtual bool match(Term *term) = 0;

  // Get Structure, default is nullptr.
  virtual Structure *getStructure();

  // Get Variable, default is nullptr.
  virtual Variable *getVariable();

private:
};

#endif
