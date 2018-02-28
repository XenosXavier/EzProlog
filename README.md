### EzProlog: A Simple Prolog Interpreter
This is an example for building _**Prolog term matching**_ with some design patterns in C++. The patterns include _Builder, Composite, Factory Method, Flyweight, Interpreter, Iterator, Proxy, Singleton, and Template Method._ We only implement three operators, matching( = ), conjunction( , ), and disjunction( ; ), in this simple interpreter and try to make our output like [swi-prolog](http://www.swi-prolog.org/). Here are some output examples:

Constant matching
```prolog
-? tom = tom.
true.

-? tom = jerry.
false.
```

Variable matching 
```prolog
-? X = 1.
X = 1.
```

Structure(Compound) matching
```prolog
-? point(X, 1) = point(0, 1).
X = 0.
```

List matching(syntax sugar of structure)
```prolog
-? [tom, jerry] = [H|T].
H = tom,
T = [jerry].
```

Shared variables
```prolog
-? A = s(B), A = C, B = D, A = D.
A = B,
B = C,
C = D,
D = s(D).
```

Conjunction and Disjunction
```prolog
-? X = 1, X = 2.
false.

-? X = 1; X = 2.
X = 1;
X = 2.
```

### Getting Started
Prerequest for Windows 10
* [Traditional Chinese](https://blog.gtwang.org/windows/how-to-get-ubuntu-and-bash-running-on-windows-10/)
* [English](https://www.howtogeek.com/249966/how-to-install-and-use-the-linux-bash-shell-on-windows-10/)


Install GoogleTest for running unit test
* [Windows 10 / Ubuntu](https://www.eriksmistad.no/getting-started-with-google-test-on-ubuntu/)
* [Mac](https://github.com/iat-cener/tonatiuh/wiki/Installing-Google-Test-For-Mac)

Open your terminal or command line and do

```
make test
```

under your project folder and then you should see the following result

![unit test result](https://i.imgur.com/PCzTA0G.png "unit test result")

### The Basics - Goal
A query to the Prolog interpreter consists of one or more goals. For example, in

```prolog
-? X = 1.
X = 1.
```

there is a relational goal "X = 1" which means "is X matchable to 1?". A goal is something that Prolog tries to satisfy. In here, "X = 1" succeeded because the variable X matches any legitimate term before instantiating.

```prolog
-? X = 1, X = 2.
false.
```

there is another example, which contains two relational goals "X = 1" and "X = 2". It means "is X matchable to 1 and 2?". Unfortunately, the Prolog says no by printing "false" because the variable X can't be 1 and 2 at the same time.

```prolog
-? X = 1; X = 2.
X = 1;
X = 2.
```

the final example also contains two relational goals. But it means "is X matchable to 1 or 2?". So the goal can be satisfied by instantiating 1 or 2 to X.

### Data Objects in Prolog
In this example, we reference [iso prolog](http://fsl.cs.illinois.edu/images/9/9c/PrologStandard.pdf) to define the following data objects of prolog:

#### Atom

A series of letters, digits, and/or underscores, beginning with a lowercase letter

```
ex: atom, a_t_o_m, atom123
```

A series of 1 or more characters from the set `#$&*+-./:<->?@^~\` provided it does not begin with `/*` (such atoms are called graphic tokens)

```
ex: :->, @-@?, ^+$*
```

A series of arbitrary characters in single quotes

```
ex: 'This is an atom, LoL'
```

The special atoms [] and {}

```
ex: [], {}
```

#### Number

A series of demical digits.

```
ex: 1, 0.2, -0.3
```

#### Variable

A variable name begin with a captical letter or the underscore mark(_) and consists of letters, digits, and/or underscores.

```
ex: Var, _var, Var123, V_A_R
```

#### Structure

The ordinary way to write a structure is to write the functor, an opening parenthesis, a series of terms separeted by commas, and a closing parenthesis. _**p.s. the functor should be an atom.**_

```
ex: date(feb, 19, 2018), age(tom, X)
```

#### List

List is defined as rightward-nested structures using the operator '.'.

```
ex: [a] = .(a, [])
    [a, b] = .(a, .(b, []))
    [a | b] = .(a, b)
```

### Term Matching Rule
Let S and T be two terms.
* If S and T are constants then they match only if both are the same object.
```prolog
-? tom = tom.
true. (match success)

-? tom = jerry.
false. (match fail)
```
* If one of them is variable then they match only if
    * the variable has not been instantiated, or
    * the instance of variable is equal to the other one
```prolog
-? X = 1.
X = 1. (match success, X has been instantiated to 1)

-? X = 1, X = 2.
false. (match fail, the instance of X is 1 not 2)
```
* If S and T are structures then they match only if
    * both have the same functor,
    * equal arity of arguments, and
    * all corresponding arguments match.
```prolog
-? year(2018) = yEar(2018).
false. (match fail, different functor)

-? date(feb, 19, 2018) = date(feb, 19).
false. (match fail, different arity)

-? date(jan, 19, 2018) = date(feb, 19, 2018).
false. (match fail, 'jan' is not equal to 'feb')

-? date(feb, 19, 2018) = date(feb, 19, 2018).
true. (match success)
```
### Lexical Analysis and Parsing
##### Lexical Analyzer
| lexeme                           | token-name | attribute-value    |
| -------------------------------- | ---------- | ------------------ |
| [Atom definition](#atom)         | Atom       | Symbol of atom     |
| [Number definition](#number)     | Number     | Value of number    |
| [Variable definition](#variable) | Var        | Symbol of variable |

##### Grammar
><_query_> ::= <_disjunction expression_> < _disjunction expression'_> '.'
<_disjunction expression_> ::= <_conjunction expression_> <_disjunction expression'_>
<_disjunction expression'_> ::= ';' <_conjunction expression_> <_disjunction expression'_>^*^
<_conjunction expression_> ::= <_matching expression_> <_conjunction expression'_>
<_conjunction expression'_> ::= ',' <_matching expression_> <_conjunction expression'_>^*^
<_matching expression_> ::= <_term_> '=' <_term_>
<_structure_> ::= <_atom_> '(' <_terms_> ')'
<_terms_> ::= <_term_>^*^  
<_term_> ::= <_atom_> | <_number_> | <_variable_> | <_structure_>
<_atom_> ::= <_lowercase letter_> <_string_> | <_specialchar_>^+^ | '<_string_>'  
<_number_> ::= <_negative_>^?^<_digit_>^+^  
<_variable_> ::= <_uppercase letter_> <_string_>  
<_string_> ::= <_character_>^*^
<_character_> ::= <_digit_> | <_lowercase letter_> | <_uppercase letter_>
<_negative_> ::= -  
<_digit_> ::= [0 - 9]  
<_lowercase letter_> ::= [a - z]  
<_uppercase letter_> ::= [A - Z] | _  
<_specialchar_> ::= # | $ | & | * | + | - | . | / | : | < | - | > | ? | @ | ^ | ~ | \\

##### Bottom-Up Parser
Bottom-up parsing starts from the leaf nodes of a tree and works in upward direction till it reaches the root node. Here, we use a simple query, `A = 1, B = 2, C = 3; D = 4.`, to explain how the parser works in the following figures.

| parse tree                              | build steps                              |
| --------------------------------------- | ---------------------------------------- |
| ![SET](https://i.imgur.com/eaEVVyQ.jpg) | ![OWB](https://i.imgur.com/zlykwCn.jpg ) |

In order to build a right recursive tree like the left one shows. We need some stacks to remember which terms, operators, or expressions has been parsed and pop them up to create other expressions if the priority of new operator is greater than the top of the operator stack. Then the parse steps will just be like the right figure.

### Cycle Detection and Shared Variables
There are two situations may cause cycle when variable matching.
* Instantiate to itself
```prolog
-? X = X.
```

* Instantiate to a structure(compound) which arugments contain itself
```prolog
-? X = s(X).
```

In the first situation, it only occurs when a variable match itself or the last shared variable instantiates to the first one. So we check if there is a shared variable and it is equal to the reference one to avoid cycle.

```c++
Variable* other // which prepares to be an instance
for (; other != nullptr; other = other->instance())
    if (other == this)
        return true; // has cycle
return false;
```

The other one, we use a flag to check if this variable has been visited or not.

```c++
// hasBeenVisited is a bool property of variable
if (hasBeenVisited) {
    // do something when cycle detection
}

hasBeenVisited = true;
// do something on instance
hasBeenVisited = false;
```

In the swi-prolog, all variables are sorted by its address. Here, we use a int property called age to complete the same effect and sort the shared variables when instantiating a new variable to another variable by matching.

### Class Diagram
_Click the following image if you want to see the full version_  

[![class-diagram](https://i.imgur.com/KLAJ3zn.jpg)](https://i.imgur.com/KLAJ3zn.jpg)