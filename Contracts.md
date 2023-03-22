# Contracts

What's holding your program together?  Can we do better than duct tape
and good intentions?

## Introduction

This is the first in a series of Better Code seminars from the
Software Technology Lab, which are aimed at elevating the quality of
programming everywhere. We're rolling this episode out first because
in many ways, it's the foundation for everything else.

Contracts are the connective tissue of solid software.  You really
can't build software at scale without them.  If you *are* building
large software systems, I promise you, you're using contracts, even if
you don't use that word for them, and it will be well worth your time
to take a deeper look at the ideas.

Because we have practitioners here from many language backgrounds, I'm
writing most examples in no particular language. Hopefully, they
should be easily read as pseudocode, but if you have questions, please
ask and I'll try to clear them up.  Also speaking of languages, I'm
going to refer to English a lot, and please consider that a shorthand
for “whatever human languages you use to communicate about software,”
which is just too long to repeat.

## Correctness

Fundamentally, contracts are about correctness.  Some people think
it's futile to pursue correctness, but I disagree, for three reasons:

- Simplicity.  The discipline we're talking about actually removes
  loads of needless complexity and uncertainty from the process of
  coding.
  
- joy / possibility.  It's just way more rewarding when you know what
  it means to do your job right.
  
- It's more practical than you might think.

### Additionally: Strong Contracts Simplify Code

I want to be clear, though, when I talk about correctness, I don't
mean some kind of elaborate formal proof. I mean achieving correctness
through the sort of everyday thinking that we do while
programming:

    var names = [ "Sean", "Laura", "Dave", "Crusty" ]
	
	names.sort()
	
	for i in 0...3 { print(names[i]) }

“I started with four names, and sorting rearranges items without
changing the length, so I can still access all four items.”

Not to overly aggrandize what we do every day, but that's just a
little proof. So regular programming is on the same continuum as
proving correctness and from time-to-time when you really need to get
confidence that you understand some code, or that you've fixed a bug,
it's OK to slide into a more formal mode. Not as an academic exercise,
but because it's practical and useful. 

## Local Reasoning

That kind of everyday thinking only works if we can reason locally...

<!-- insert existing material here. -->

## What's a Contract?

When I say “Contract” I mean something very specific.  In the mid
1980s, Bertrand Meyer took Tony Hoare's work on formal verification of
programs, known as Hoare Logic, and shaped it into a practical
discipline for software engineering, called “Design By Contract” or
(DbC).

He describes the core idea this way (emphasis mine):

> …a software system is viewed as a set of communicating
> **components** whose **interaction** is based on precisely defined
> **specifications** of the **mutual obligations** — contracts.
>
> —[Building bug-free O-O software: An Introduction to Design by
Contract™](https://www.eiffel.com/values/design-by-contract/introduction/)

So contracts describe the rules that govern how one piece of software
talks to another. In other words, they're relationships.  Now I know
as engineers, a lot of us aren't exactly great at relationships, but
hopefully this series will make us all a little better. Thinking in
terms of relationships is one of the themes of Better Code, and we'll
be pointing them out as they come up.

If you go back and look at Meyers' writings, you'll see he mentions
object-oriented programming all the time (this was the 80's after
all), and his idea of a “component” is a class instance, but his
system generalizes perfectly well to any modern programming
paradigm, because M. Meyer was onto something deep and fundamental.

So I'm going to present what we think of as a modern generalization of
DbC.

## Real Talk: It's Documentation

> …a software system is viewed as a set of communicating
> components whose interaction is based on precisely defined
> **specifications** of the mutual obligations — contracts.
>
> —[Building bug-free O-O software: An Introduction to Design by
Contract™](https://www.eiffel.com/values/design-by-contract/introduction/)

Looking back at Meyers' definition, you might notice he says contracts
are “precisely defined specifications,” which is just a fancy word for
documentation.

Now, lots of people think documentation is a waste of time, but if
you've been to any of my talks you know that I don't agree with that
either. First of all, it's a prerequisite for correctness.
Correctness is always with respect to a specification, so undocumented
software is neither correct nor incorrect.  

In fact, I don't review code; I review contracts.  If you ask me for a
code review and there's anything without a contract, I'm going to send
it back, because there's no way to make a judgement about its
correctness.

So yes, this is a talk about documentation. While it is true that
there are lots of counterproductive approaches to documentation, I'm
going to show you one that is practical *and*—if you give the process
the attention it deserves—can help you improve the code of your APIs.

### Documentation and local reasoning

I also want to point out that documentation is essential for local
reasoning.  It's the reason I don't need to be a condensed matter
physicist to program a computer.

<!-- insert existing material about documentation/local reasoning
here. -->

### Put it in comments

Lastly, I want to say, this documentation should go in your code,
because:

1. That puts the two things that should correspond—documentation and
   implementation—next to one another, so you can see when they don't
   match up. People sometimes complain that docs go out of date, but
   that's kinda the point: without the ability to see that
   inconsistency, there's no way to know that there's a bug.

2. That makes it reasonable to combine the activities of coding and
   documentation, which—believe it or not—are mutually supportive.

But if we're going to integrate documentation into our programming so
tightly, we need to make sure it's neither intrusive for the
maintainer to read nor burdensome for the author to write.  Ideally,
it should help both of them, and I'll show you how to do just that.

<!-- ** Implementation comments indicate a missing refactor -->

## Language / Library Support

You may have heard that some languages have features to support Design
by Contract.  In general, that means you can write *parts* of your
contracts as code, and get some checking at runtime to make sure
they're upheld:

	class Array<T> {
	
	  /// Returns the `i`th element.
	  @requires(i >= 0 && i < self.length) // <=== CONTRACT
      fun getNth(i: Integer) -> T
	  ...
    }

The idea started with Bertrand Meyer's own Eiffel language, and was
picked up by many others, including D, Scala, Kotlin, and
Clojure. Others languages, like Rust and Python, have contract
libraries that provide a near-native contract programming experience.

If you use one of these languages, fantastic; absolutely leverage
those features and libraries.  That may reduce the amount of pure
documentation you need to write. That said, contracts are still
fundamentally documentation. There are some that really ought to be
expressed in English, and some others that are actually impossible to
express as code. Examples to follow.

## Preconditions / postconditions

- Directly from Hoare logic, but DbC added an ethos of blame.

<!-- phrasing -->
- There is a client and a callee (server).

- A contract binds the client to pass a valid combination of arguments
  (precondition), and binds the callee to correctly provide the result
  (postconditions).

- If preconditions don't hold, THAT'S A BUG.  The client is at fault, and callee is
  not required to make any promises.

- If preconditions hold… and postconditions not fulfilled THAT'S A
  BUG, the callee is at fault.  <!-- amend this later -->

- Being able to say which code is at fault is extremely powerful!

- Postcondition describes /relationship/ between initial state+arguments
  and final state+return value.

## Error Handling
- An error is a postcondition failure.  Update the statement

  - If preconditions hold, no error reported, and postconditions not
    fulfilled and, the callee is at fault.

** Throwing exception
- Makes return value available/simple (no encoding failure)
- Supports construction failure.
- Simplifies postcondition
- Simplifies client logic when the immediate client can't do anything about it

** Returning error
- good when immediate client has a response

### Choosing preconditions:
<!-- phrasing -->
- Impractical precondition: user input to parser is valid
- Impractical precondition: changes complexity of operation
- Weak preconditions propagate nonsense, create untested paths

## Offensive programming: don't accept nonsense inputs
<!-- phrasing -->
- Partial functions are a thing

Your language acknowledges this (integer multiplication, array
indexing); you should too.

- it's a poor engineering tradeoff to make code check for errors in its own usage.
- Example: indexing out of bounds allowed
- You're not doing the client any favors — it complicates postconditions/results
- What your thing *is* becomes fuzzy
- There's room for judgement: stack top/pop could have preconditions.
  Should they?  depends on how clients will use it.

### Arbitrary Damage Stories

You're an idle billionaire.  You own a supercar, a $7M Bugatti Divo.  
and you've got a contract with an ultra-exclusive "car butler" who
takes care of all the maintenance, including refueling. Now one day you

The contract, of course, says the butler is only
going to use ultra-premium gas.  You also have a contract with the
state that says you have to keep this thing's emissions within certain
smog limits.  Well at some point the butler puts regular gas for a
Prius in there, and of course this starts eating away at the valves
and piston heads.  You never really push the car too hard, so you
don't notice any difference in performance, but finally you have it
taken for its smog checkup and it fails.  You've broken the
precondition for the smog test, due to an earlier unnoticed bug
(regular gas in supercar).  You take the car back to the dealer and
they tell you the damage from regular gas is too extensive and now the
car is valued at only $2M, practically worthless.

- best effort butler drives the car home anyway and tells you you're all set.  Then you destroy the car.

<!-- Deal with resource exhaustion as recoverable in the following -->

Laura: I wonder if the "reasonable fallback" behavior can illustrate damage here, too -- like, the gas station within a 30-mile drive of the mansion didn't have ultra premium, so the butler picked the highest value available
2:27
and the way to mitigate damage (like, the embarrassment of showing up at the fancy car party with no gas) is to report the failure at the point of failure AND stop
2:28
like, clearly the butler shouldn't just walk off into the desert leaving the keys in the car if the right gas isn't available


## Invariants

The most important contribution of Design by Contract, over and above
Hoare Logic, was to apply Hoare's idea of “invariants” to classes, or
more generally, user-defined types with a public/private boundary.

An “invariant” is just a thing that has to be true at particular
places in a program.  This is a really simple example, but you can
probably see how the invariant might be useful for understanding the
meaning of the next line.

	x.sort()
                                	// <= Invariant: x is sorted
	let foundY = x.binary_search(y) // Therefore this is legal.

Hoare realized that *loops* have invariants that hold before and after
each iteration, and showed how they could be used to prove the
correctness of interesting algorithms.  This is just to give you a
flavor.  Don't worry if you don't get it; it won't be on the test.

    i = 0
	
	// Loop invariant: if J < i, a[J] != x
	while (i < a.length && a[i] != x) { 
		i += 1
	}
	
	// a[i] is the first element == x, or 
	//   no such element exists and i == a.length
	
This one says all elements preceding element `i` are not equal to `x`.
Combining that loop invariant with the fact that `i` is incremented by
1 each iteration, lets you prove the loop either finds the first x, or
leaves i equal to a.length.  For a simple loop like this, you probably
don't need to do a proof, but if you're interested, it's a good
exercise.

### Class Invariants

A *class invariant* or *type invariant* is a condition that is
established by the type's constructor and upheld by all of its
publicly-accessible APIs.  This is just what we mean when we
informally talk about the thing being “in a good state.”

> in a good state ≅ invariant is upheld

My favorite example is this type that holds a pair of private arrays,
but its public interface is more like an array of pairs.

<!-- picture -->

You can probably write this type in any language; I've coded it in
Swift, Python, TypeScript, and C++.

There are four basic operations: create an empty instance, get the nth
pair, get the length, and append a new pair.  The invariant for this
type is that the private arrays always have the same length.

<!-- show all four implementations -->

Maintaining that invariant is what I need to do in order to 
Knowing the invariant allows us to implement the length function by
returning the length of the first array.

<!-- make this example work -->

```swift
/// A random-access collection of `(First, Second)` pairs.
struct PairArray<First, Second> {
  /// The first part of each element.
  private var first: [First] = []

  /// The second part of each element.
  private var second: [Second] = []

  /// An empty instance.
  public init() {}

  /// The `i`th element.
  public subscript(i: Int) -> (First, Second)

  /// The length.
  public func length() -> Int

  /// Adds x to the end.
  public mutating func append(_ x: (First, Second))
}
```

<!-- show weakened private invariant -->

<!-- show pimpl/resource -->

<!-- ordering -->
If you're the type author, the invariant is basically a “contract with
yourself.” The invariant, or parts of it, could also be publicly
visible.  So if we made the private arrays publicly readable we could
promise the user that their lengths will always match.


<!-- the purpose of public/private is to uphold invariants -->
So Encode program invariants in a type 
(e.g. parent is an element in the database of people)
<!-- no mutation, no need to think about it. -->


## Other elements of contracts
<!-- phrasing -->
- Function Signatures
- Cost in time / memory.
  Exact operation counts can be more useful than Big O complexity.
- Conventions (document these!)
- Names
  - Name means something; should reflect the postcondition.  Respect
    the name, or change it.
  - sort with a random comparison is not a shuffle.  At worst, isolate it as a hack in a well-named operation.

## How to write good contracts
<!-- phrasing -->
- Names 
  - Think about how the API plays out at the use-site.  Things are
    declared once but used many times.
  - In particular, don’t repeat type info. Don't call an array "array."
  - Express the most specific abstraction being represented.
  - Yes, use a thesaurus!
    Example: Position vs identity vs iterator

- A lot of people are afraid of being overwhelmed by documentation.
  - You can find all kinds of reasons on the web that documentation is
    supposedly a waste of time.
  - If you've been to any of my talks you know that I don't agree.
  - Living with your own code for 3-5 years will change your mind about that.

- Omit needless words
  - Don't say "An abstraction that…", "A type representing," etc.
  - Don't say anything that is evident from the declaration by itself! "Returns an int that…"
  - Don't say "the specified;" use parameter names.
  - Terseness is supported by having a central document for conventions.
  - Don't talk about self.
  - Constructors can be documented *as* the created instance.
  - Subscripts are a generalization of parameters and can be
    documented *as* the acccessed property.

- Use a summary sentence fragment.
  - Say what a non-mutating function returns
  - Say what a void-returning mutating function does
  - Other functions: choose based on the primary role.  Usually what
    it does, and incidentally what it returns. An exception might be a cache function.
  - Say what a type is.
- To support local reasoning, the contract ≠ implementation
- Hold your feet to the fire for meaningfulness
  - ChatGPT documentation
  - Beware copilot
- Don't depend on an understanding of words in the name unless they're well defined:

  This is OK in a vector type because negation is a well-defined computation:

  #+begin_src c++
    // Returns the negation of *this.
  Vec2 negated() const {
  #+end_src

  But this is not:

  #+begin_src c++
  // Returns the value of *this after swizzling,
  Vec2 swizzled() const {
  #+end_src

  consider "Actualize"

## Checking
<!-- phrasing -->
In a project with more than a couple participants, these checks are super-valuable.

- Checks must not have significant side-effects


- Contracts are part of the interface so assertions in the body are not enough.
- Untestable precondition: comparison function is stable.

- For reusable code, bottleneck your response
  - You might just want to terminate
  - You might want to take emergency shutdown measures
  - You might… want to throw an exception… but beware.
  - You might want to do something different in testing from what you do in shipping code.

- Assertions 
can be ignored when reasoning about program semantics
As long as they don't have side-effects and they stop the program.
They don't induce control flow.

- Checking after UB doesn't work:
this ==  NULL doesn't work.
Checking that pointer is in range doesn't work.
Checking that your signed ints didn't overflow doesn't work.

## What to do in existing codebases

Think globally, act locally

### New code
Create an island of correctness.  Brook no nonsense.

### Maintenance
* Write a contract for existing things.
- state any preconditions that can be considered satisfied by all clients
- promise only the postconditions that all clients depend on.

```
 * The behavior of this class is unknown. Its specification is
 * whatever the callers have come to rely on in the decade+ it's
 * existed.
```

** Write the thing that was supposed to be there and begin using it
- Attempt to remove the old thing
- Otherwise, deprecate it
- It's going away; don't use it!

### Debugging

** The only way to get control of a misbehaving system is to establish
what the contracts are.  If someone else has to do that, huge cost!

** Dealing with Hyrum's law
With a sufficient number of users of an API, it does not matter what
you promise in the contract: all observable behaviours of your system
will be depended on by somebody.
-- Hyrum Wright

- Not "contracts don't matter."
- An observation about social programming dynamics as # clients grows.
- “As a practical matter, if you change anything observable about a widely-used API, some client will break”
- Effect of contract:
  - discourage depending on things you might want to change
  - as consequence, break fewer clients
  - gives you grounds for indemnity!

## Outro

<!-- phrasing -->
* It's hard but it's worth it.

  Don’t make other people write your contracts.  So inefficient

* Magic Feedback loop with design
  - Contract too complicated? Fix the API!
  - Contract's english description will tell you what to call the API.

* If you've secretly been fooling around with Hoare logic but were
  embarrassed to tell anyone—maybe you have a little impostor
  syndrome—it's OKAY; as a programmer you've earned the
  right.



