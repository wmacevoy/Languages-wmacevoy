# Exam 1 Notes

## Models of Computation

 - VonNeumann Architecture (Classical Computation)
   CPU, RAM, Process Layout (Text, Globals, Heap, Stack (down)).
   Main Event for Programming Languages
 - Neural Network
   Directed graph of weighted edges with a transfer funcion.
   - Leading nodes (no edges going in) are inputs and given data.
   - sum weights of all nodes leading to that node, and then pass
    that value through the transfer function
      T(sum (weights*inputs to that node))
   - ML amounts to designing the graph and optimizing the weights.
  - Probabalistc Classical & NN
    - x = 3 with prob .7 and 82 with prob .3 ...
    - Quantum Computer

- Categories of Languages

  Procedural
  Functional
  Constraints / Logic
  Object Oriented

- Many are combinations of these.

- When is procedural programming style a good idea?

- Why is functional programming style popular in web applications?

- What is the basic syntax of CSS?

- What is the purpose of HTML.  What kind of language is it?

- Why is SQL a logic/contraints language?

- Why are logic languages used for user interfaces?

- Why are general purpose languages used to write machine learning
  models?

- Convert this procedural program into functional style:

  double sum_powers(int a, int b, int p) {
     double sum = 0;
     for (int i = a; i <= b; ++i) {
        sum += pow(i,p);
     };
     return a;
  }

  - Why do side effects break functional programming style?