# Report
**Topic:** Interpreter implementation: elements of declarative and functional styles

**Course:** Programming Languages: Principles and Paradigms

**Student:** Tarasevych Daria.

---

## 1. Introduction:
Purpose of work is to gain experience in programming using multi-paradigm programming and preparing my own declarative `language` that supports basic elements of the functional style.

## 2. Architectural Design & Paradigms:
* **Tokenization (`Tokenization.cpp`):**
The Tokenization class performs lexical scanning over user string inputs. It categorizes text sequences into typed Token structures containing explicit TokensType enumerations (e.g., Number, Operator, Variable, FunctionName, KeywordVar, KeywordDef, LeftCurly, RightCurly). 
It handles unary operators (such as negative numbers).
*  **Parsing (`ShuntingYard.cpp`):**
ShuntingYard class implements Shunting-Yard algorithm. It converts standard infix expressions into Postfix / Reverse Polish Notation (RPN). Operator stacks are used to reorder arithmetic operations according to standard math rules (*, / taking precedence over +, -).
Custom functions and user-defined identifier calls are dynamically shifted onto the operator stack when followed by a left parenthesis (, ensuring correct argument evaluation order in postfix streams.
* **Evaluation (`Evaluator.cpp`):**
The Evaluator processes postfix RPN token streams using a LIFO execution stack. Numbers are pushed directly onto the stack, while binary operators (+, -, *, /) and built-in functions (abs, max, min, pow) pop their required operands, evaluate results, and push outcomes back.
For user-defined functions, the evaluator manages local scope execution by mapping arguments to parameters and recursively processing the function's internal RPN representation.
* Environment & State Scoping (`Environment.cpp`):
Program state is managed via symbol tables backed by fast $O(1)$ lookup hash maps (std::unordered_map). Variables are strictly immutable once declared; re-assignment attempts throw explicit runtime exceptions.
Custom functions (FunctionSymbol) store parameter signature vectors alongside parsed RPN token lists. During function invocation, isolated temporary Environment instances (tempEnv) are spawned to enforce scoped variable evaluation without polluting global memory.

## 3. Classes description:

* Token.h: enum class TokensType, struct Token
* Tokenization.cpp / Tokenization.h: std::vector<Token> Tokenization::tokenize(const std::string& input)
* ShuntingYard.cpp / ShuntingYard.h: getPrecedence(const std::string& op), parseToRPN(const std::vector<Token> &tokens)
* Environment.cpp / Environment.h: struct FunctionSymbol, std::unordered_map<std::string, double> variables;, std::unordered_map<std::string, FunctionSymbol> functions;, setVariable(const std::string& name, double value), getVariable (const std::string& name), setFunction(const FunctionSymbol& func), hasFunction(const std::string& name)
* Evaluator.cpp / Evaluator.h: evaluate(const std::vector<Token>& rpnTokens, const Environment& env)
* main.cpp: 'program manager'

## 4. Testing:
**Test Case 1: Immutable Variable Assignment & Mathematical Evaluation**

- Actions: Declare var a = 10 $\rightarrow$ Declare var b = 5 $\rightarrow$ Evaluate a + b * 2 $\rightarrow$ Attempt var a = 20.

- Expected Output: `20` and `Error: Variable: a is immutable and cannot be reassigned!`

- Screenshots:
<img width="488" height="137" alt="Знімок екрана 2026-07-14 о 22 58 02" src="https://github.com/user-attachments/assets/8c14c9d1-e9e3-403f-80ed-68fcb7ecdd07" />

**Test Case 2: Built-in Mathematical Functions & Nested Precedence**

- Actions: Evaluate expression mixing nested functions and standard operators: max(10, 20) + abs(-5) * min(4, 2).

- Expected Output: 30

- Screenshots:
<img width="488" height="52" alt="Знімок екрана 2026-07-14 о 23 04 20" src="https://github.com/user-attachments/assets/6273a28e-5624-46ab-a272-5abc83f0ecfd" />

**Test Case 3: Custom Function Definition (User-defined functions (def))**

- Actions: Define custom single-parameter function def doubleIt(x) { x * 2 } $\rightarrow$ Call doubleIt(5) $\rightarrow$ Define multi-parameter function def addSq(a, b) { pow(a, 2) + pow(b, 2) } $\rightarrow$ Call addSq(3, 4).

- Expected Output: 10 and 25

- Screenshots:
<img width="488" height="137" alt="Знімок екрана 2026-07-14 о 23 08 54" src="https://github.com/user-attachments/assets/db66ebba-7d83-4c1d-8d7d-1800c417aaec" />

**Test Case 4: Error Handling & Boundary Condition Validation**

- Actions: Trigger division by zero 10 / 0 $\rightarrow$ Call function with missing arguments doubleIt() $\rightarrow$ Access undeclared variable x + 1.

- Screenshots:
<img width="488" height="269" alt="Знімок екрана 2026-07-14 о 23 12 34" src="https://github.com/user-attachments/assets/663baaea-2de2-4b0b-8f05-4be244ac90df" />

**Test Case 5: Higher-order integral(f, a, b)**

- Actions: Define custom single-parameter function def parabola(x) { x * x } $\rightarrow$ Call integral(parabola, 0, 6)

- Screenshots:
<img width="412" height="70" alt="Знімок екрана 2026-07-15 о 14 24 42" src="https://github.com/user-attachments/assets/966282f4-f017-4a3b-a6ca-d93e9bf001a8" />


## 5. Conclusion:
The developed project successfully fulfills the assignment requirements by implementing a simple C++ interpreter that supports elements of declarative and functional paradigms. 
The system reliably evaluates arithmetic expressions, built-in functions (pow, abs, max, min), and user-defined functions. 
Furthermore, by enforcing variable immutability (disallowing re-assignment after a var declaration), the interpreter maintains a core functional programming principle. 
Overall, the project demonstrates practical experience in building custom declarative 'languages' that supports basic elements of the functional style.
