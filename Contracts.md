# Contracts

What's holding your program together?  Can we do better than duct tape
and good intentions?

## Introduction

Thank you to STLab team and to our group of content previewers,
especially Laura Savino, who spent many hours with me talking about
this material.

This is the first in a series of Better Code seminars from the
Software Technology Lab, which are aimed at elevating the quality of
programming everywhere. We're rolling this episode out first because
in many ways, it's the foundation for everything else.

Contracts are the connective tissue of solid software.  You really
can't build software at scale without them.  If you *are* building
large software systems, I promise you, you're using contracts, even if
you don't use that word for them, and it will be well worth your time
to take a deeper look at these ideas.

Because we have practitioners here from many language backgrounds, I'm
writing most examples in no particular language. Hopefully, they
should be easily read as pseudocode, but if you have questions, please
ask and I'll try to clear them up.  Also speaking of languages, I'm
going to refer to English a lot, and please consider that a shorthand
for “whatever human languages you use to communicate about software,”
which is just too long to repeat.

### Agenda

- Part 1
  - Correctness
  - Local Reasoning
  - Design by Contract
  - What's in a Contract
  - A Story with a Moral

- Part 2
  - Good style
  - Contract Checking
  - Offensive Programming
  - What to do in Existing Codebases
  - Conclusion

## Correctness

Fundamentally, contracts are about correctness.  Some people think
it's futile to pursue correctness, but I disagree, for three reasons:

- It's more practical than you might think.

- Simplicity: One of the reasons it's practical.  The discipline we're
  talking about actually removes loads of needless complexity and
  uncertainty from your code and from the process of coding.
  
- joy / possibility.  It's just way more rewarding when you know what
  it means to do your job right. <!-- rephrase -->
  

> **Note: Strong Contracts Simplify Code**

I want to be clear, though, when I talk about correctness, I don't
mean some kind of elaborate formal proof. I mean achieving correctness
through the sort of everyday thinking that we do while programming:

    var names = [ "Sean", "Laura", "Dave", "Crusty" ]
	
	names.sort()
	
	for i in 0...3 { print(names[i]) }

How do I know that last line is OK?  “I started with four names, and
sorting rearranges items without changing the length, so I can still
access all four items.”

Not to overly aggrandize what we do every day, but that's just a
informal proof. So regular programming is on the same continuum as
formally proving correctness and from time-to-time when you really
need to get confidence that you understand some code, or that you've
fixed a bug, it's OK to slide into a more formal mode. Not as an
academic exercise, but because it's practical and useful.

## Local Reasoning

That kind of everyday thinking only works if we can reason locally

> Local reasoning is the idea that the reader can make sense of the
> code directly in front of them, without going on a journey
> discovering how the code works.
> 
> —Nathan Gitter
> (https://medium.com/@nathangitter/local-reasoning-in-swift-6782e459d)

My brain has limited capacity. And I've found a lot of other peoples'
brains are limited too. Not yours of course, but a lot of peoples'
are. People like us can't keep the whole program in our heads. Of
course local reasoning goes beyond programming; it's how humans deal
with complexity: we break complicated problems into parts that we can
think about in isolation so that we can reason about the whole.

In fact, local reasoning is so fundamental that most of our
programming best practices are there just to enable it.  It's why we
make data members private, why we break programs into components like
functions, types, and modules, and we try to keep them small.

> Best practices that exist to support local reasoning
> 
> - Using private data members
> - Keeping functions small
> - Creating components
> - Avoiding global variables
> - Avoiding pointers
> - Building/using libraries
> - Following the single-responsibility principle
> - Documentation (spoiler alert)

## What's a Contract?

When I say “Contract” I mean something very specific.  In the mid
1980s, Bertrand Meyer took Tony Hoare's work on formal verification of
programs, known as Hoare Logic, and shaped it into a practical
discipline for software engineering, called “Design By Contract” or
DbC.

He describes the core idea this way (emphasis mine):

> …a software system is viewed as a set of communicating
> **components** whose **interaction** is based on precisely defined
> **specifications** of the **mutual obligations** — contracts.
>
> —[Building bug-free O-O software: An Introduction to Design by
Contract™](https://www.eiffel.com/values/design-by-contract/introduction/)

So contracts describe the rules that govern how one piece of software
talks to another. In other words, they're relationships.  Thinking in
terms of relationships is one of the themes of Better Code, and we'll
be pointing relationships out as they come up.

Meyer breaks DbC down into three main components called preconditions,
postconditions, and invariants.

If you go back and look at Meyers' writings, you'll see he mentions
object-oriented programming all the time (this was the 80's after
all), and his idea of a “component” is a class instance, but his
system generalizes perfectly well to any modern programming
paradigm, because M. Meyer was onto something deep and fundamental.

So I'm going to present what we think of as a modern generalization of
DbC.

### Spoiler Alert: It's Documentation

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
you've been to any of my talks you know that I don't agree. First of
all, it's a prerequisite for correctness.  Correctness is always with
respect to a specification, so undocumented software is neither
correct nor incorrect.

In fact, I don't review code; I review contracts.  If you ask me for a
code review and there's anything without a contract, I'm going to send
it back, because there's no way to make a judgement about its
correctness.

So yes, this is a talk about documentation. While it is true that
there are lots of counterproductive approaches to documentation, I'm
going to show you one that is practical *and*—if you give the process
the attention it deserves—can help you improve the code of your APIs.

#### Documentation and local reasoning

I also want to point out that documentation is essential for local
reasoning.  It's the reason I don't need to be a condensed matter
physicist to program a computer.

Here's what I mean. As programmers, we're working on what my friend
Sam Lazarus calls “a tower of abstraction” that stretches through the
libraries and programming language we use, the operating system, and
into the hardware, which ultimately rests on the laws of physics.

So what keeps us from recursing down to the limits of known physics
when we think about how our programs work?

The answer is documentation.  We can use libraries and our programming
language without digging into their implementations because there's a
solid spec.  The compiler backend engineers can do their jobs because
the hardware manufacturers document the architecture and instruction
sets. The hardware designers succeed because the physicists document
the laws of physics.  That's the tower, and you're a part of it.  The
bad news, of course, is that you're not at the top of the
tower. Someone else, or future-you, is going to have to build on the
code you're writing.  We're all library builders here.

#### Put it in comments

Lastly, I want to say, this documentation should go in your code,
because:

1. That puts the two things that should correspond—documentation and
   implementation—next to one another, so you can see when they don't
   match up. People sometimes complain that docs go out of date, but
   that's kinda the point: without the ability to see that
   inconsistency, there's no way to know that there's a bug.

2. Using comments makes it reasonable to combine the activities of
   coding and documentation, which—believe it or not—are mutually
   supportive.

But if we're going to integrate documentation into our programming so
tightly, we need to make sure it's neither intrusive for the
maintainer to read nor burdensome for the author to write.  Ideally,
it should help both of them, and in Part 2, I'll show you how to do
just that.

But just to give you an idea that this is practical, this component
has what I consider minimal but complete contract documentation for
each declaration.

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
  public subscript(i: Int) -> (First, Second) {
    (first[i], second[i])
  }

  /// The length.
  public var count: Int { first.count }

  /// Adds `x` to the end.
  public mutating func append(_ x: (First, Second)) {
    first.append(x.0)
    second.append(x.1)
  }
}
```

This one's in Swift, but you can do it in any language.  I wrote the
same component in Python, TypeScript, and C++.  Now, not every
contract is as simple as these are, but simplicity is a goal.  In
fact, if you can't write a terse, simple, but _complete_ contract for
anything, there's a good chance it's badly designed.  More on all this
later.

#### Aside: Language / Library Support ####

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
Clojure. Other languages, like Rust and Python, have contract
libraries that provide a near-native contract programming experience.

If you use one of these languages, fantastic; absolutely leverage
those features and libraries.  That may reduce the amount of pure
documentation you need to write. That said, contracts are still
fundamentally documentation. They need to appear in the API
description used by clients, like web pages... There are some that
really ought to be expressed in English, and some others that are
actually impossible to express as code. Examples to follow.

<!-- Where are the examples -->

### Preconditions / postconditions ###

- Directly from Hoare logic, but DbC added an ethos of blame.

<!-- phrasing -->

A contract is a two sided arrangement between a client and a callee (server).

- A contract binds the client to pass a valid combination of arguments
  (precondition), and binds the callee to correctly provide the
  documented result (postconditions).

- Postcondition describes /relationship/ between initial state+arguments
  and final state+return value.

#### The Ethos of Blame

- If preconditions don't hold, THAT'S A BUG.  The client is at fault,
  and callee is not required to make any promises.

- If preconditions hold, no error is reported*, and postconditions not
  fulfilled THAT'S A BUG, the callee is at fault.

We'll talk about errors next, but errors are NOT BUGs.
Being able to say which code is at fault is extremely powerful! You
know what to fix; you know who should do the work.  It's simplifying
and clarifying.

Don't be afraid of having lots of preconditions. You should only
promise results for inputs that make sense. Weak preconditions
propagate nonsense—garbage in, garbage out.

##### Errors ####

- Not a bug

- An error is a postcondition failure where there's nobody at fault.
  - Example: resource exhaustion
  - Example: callee deserializing invalid data from disk

- We don't include error effects in the postcondition.

### Invariants ###

An “invariant” in Hoare Logic is just a thing that has to be true at
particular places in a program.  For example,

	grades.sort_descending()
	// Invariant: grades is sorted in descending order.
	grades.reverse_in_place()
	// Invariant: grades is sorted in ascending order.
	let found = grades.binary_search(50)

When we get to the last line, we've established the invariant that
grades is always in ascending order.  That's powerful because
`binary_search` has a *precondition* that the elements to search are
sorted ascending.

The most important contribution of Design by Contract was to apply
Hoare's idea of “invariants” to user-defined types that have an 
encapsulation boundary (public/private parts).

Meyer's *class invariant* (or *type invariant*), is just a
formalization of what we mean when we talk about instances
being “in a good state.”

> in a good state ≅ invariant is upheld

More specifically, it's a condition that holds whenever a type
interacts with clients.  My favorite example is this type that holds a
pair of private arrays, but whose public interface is more like an
array of pairs.  The invariant for this type is that the private
arrays have the same length.

<!-- picture -->

You can probably write this type in any language; I've coded it in
Swift, Python, TypeScript, and C++.

It's important to realize that to be a class invariant, the condition
only needs to hold at the public interface boundary; it's perfectly
fine to violate the condition when no clients can observe it.  In
fact, it's necessary:

<!-- grab language from slides.  -->

The beauty of having public and private access control is that it
doesn't take much attention to uphold a class invariant.  The
condition needs to be established the constructor, and every mutating
operation with access to private parts needs to be sure to preserve,
or re-establish it.  But aside from that, you're golden.  Obviously
non-mutating operations don't change anything and can't disturb the
invariant.  Even mutating operations are in the clear so long as they
only use the type's public interface.

#### The Tower of Invariants

The tower of abstraction mentioned earlier comes with a tower of
invariants.  The invariants of the type with the two arrays in it are
built on—and depend on—the invariants of the individual arrays, and
you could embed this type into some other data structure with its own
invariant.

In fact, you can think of the entire state of your program as one big
datastructure with its own invariants, and formalize what it means for
the program to “be in a good state” that way.  For example, 

- you might have a database of employees, each with
  - an ID of its own
  - a manager ID (Shantanu gets to be his own manager)

It's an invariant of your program that a manager ID can't just be
random; it has to identify an employee in the database—that's part of
what it means for the program to be in a good state, and all through
the program you have code to ensure it's upheld.  It would be a great
idea to identify and documenting that whole-program invariant.

An even better idea is to use *encapsulate* the invariant in a type,
and document _that_.  So instead of using a Database type directly,
maybe create an EmployeeDatabase type with a private Database, whose
public API always upholds that invariant.  Now you can remove that
logic from the rest of your code.

Upholding invariants is the _entire purpose_ of encapsulation, so use
it whenever you can!

#### Strength and Weakness (possibly leave for part 2)
- show weakening private invariant complicates implementation
- show weakening public invariant (length > 0) complicates clients
  and weakens semantics of whole type.

X0 X1 X2 X3
Y0 Y1 Y2

### Arbitrary Damage

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

# ---------- END OF PART 1 ---------
## Quick Review

In part I we introduced a discipline called Design by Contract: a way
of documenting code so that you can reason locally its meaning and
correctness. You do this by completely describing three elements:
an operation's preconditions (the things a client must ensure),
postconditions (the effects and result value of the operation), and
invariants: properties that are preserved.

For example, the operation that removes and returns an element from a
dynamic array might have this contract.

```swift
/// A resizable random-access collection of `T`s.
///
/// - Invariant: `count >= 0`
struct DynamicArray<T> {
  // Private invariant: `capacity >= count`
  
  /// Removes and returns the last element.
  ///
  /// - Precondition: `self` is non-empty.
  /// - Postcondition: The length is one less than before the call.
  /// - Invariant: the values of the remaining elements.
  public mutating func popLast() -> T { ... }

  /// The `i`th element.
  ///
  /// - Precondition: `i >= 0 && i < count`
  public subscript(i: Int) -> T { ... }
  
  /// The length.
  public var count: Int { ... }

  /// The number of elements that can be stored before storage is
  /// reallocated.
  private var capacity: Int { ... }
}
```

We also talked about *type invariants*, which describe conditions that
always hold at the boundary between a type and its clients.  For
example, this type has a publicly-visible invariant that its length is
always non-negative.  That's useful information for clients because it
tells them what kinds of things they can do with this value.

It also has an invariant that's only visible to the implementor, that
its private capacity is always at least as great as its count.

<description of the example>

Today, we're going to talk about 
- How errors fit into the picture
- How to write contracts well 
- How to reinforce your code and find bugs by _checking_ contracts
- What to do in existing codebases.

## Another example

This is a method of Arrays that sorts the elements according to some
comparison predicate `areInIncreasingOrder`.

```swift
extension Array {
  /// Sorts the elements so that `areInIncreasingOrder(self[i+1],
  /// self[i])` is false for for each `i` where 0 <= `i` < `count` - 1.
  ///
  /// - Precondition: `areInIncreasingOrder` is a strict weak ordering
  ///   over the elements of `self`.
  /// - Complexity: at most N log N comparisons, where N is the number
  ///   of elements.
  mutating func sort<T>(areInIncreasingOrder: (T, T)->Bool) { ... }
```

The summary gives the postcondition is no two adjacent elements
are out-of-order according to the predicate.

Two things to notice: first, there's an explicit precondition that
isn't implied by the summary.  I'm not going to get into detail about
what it means to be a strict weak ordering here, but for one stark
example, that means it has to be stable for any pair of argument
values. If it returns random booleans, we can't claim anything about
what it will return for adjacent elements after sorting.

Second, I've documented the performance of this method.  Time and
space complexity have to be part of the contract if you want your
clients to be able to reason locally about the performance of their
own code.  You haven't seen complexity documented in this talk up to
now because I have a policy that if the complexity of an operation is
constant, it doesn't need to be documented.

I want to mention one other thing: everything you see in these
function signatures is implicitly part of the function's contract, for
example, the signature says the predicate must operate on arguments of
type T, and return a `Bool`, so we didn't have to spell that out as a
precondition.  Because this is a statically typed language, it just so
happens that those things are going to be enforced by the compiler,
but if you're programming in a totally dynamic language, like
Javascript, or Python without type hints, you're at a disadvantage: if
you want to practice this discipline you need to make sure that
information is all implied or explicit.

Okay, now let's see what happens when errors are involved.

## Contracts and errors

In part I we described an error as a no-fault, recoverable
postcondition failure.

That means neither the client nor the operation have any reasonable
way to guarantee that the postcondition can be satisfied, but the
client might have a reasonable way to recover and continue running.
For example, you can't guarantee you'll be able to deserialize a
document from disk if the data turns out to be corrupted, but you can
report the corruption to the user and continue running.

Anyway, because mutations are postconditions, errors have some
interesting implications for mutation.

Let's update our sorting function to deal with a comparison that can
report errors.  Maybe the comparison needs to allocate space on disk or something.

```swift
extension Array {
  /// Sorts the elements so that `areInIncreasingOrder(self[i+1],
  /// self[i])` is false for for each `i` where 0 <= `i` < `count` - 1.
  ///
  /// - Precondition: `areInIncreasingOrder` is a strict weak ordering
  ///   over the elements of `self`.
  /// - Complexity: at most N log N comparisons, where N is the number
  ///   of elements.
  mutating func sort<T>(
    areInIncreasingOrder: (T, T) throws->Bool) rethrows { ... }
```

In Swift, if something is going to throw, you have to declare that
fact explicitly, because whether something can report errors is an
important part of its contract.  We'll get to why that is in a moment,
but in the meantime, if you're stuck with a language like C++ or
Python that doesn't make you put error information in the signature,
you have to find another way to document it for client coders.
In those cases I normally have a policy that by default, anything can
report an error, and say that operations that will never report errors
must document that fact.

The simplest kind of contract around errors is the one we just
described: “this operation will not report errors.”  It means the
postcondition will always be fulfilled as long as the preconditions
are met. I call that the nothrow guarantee, but if you don't use
exceptions feel free to call it the “nofail guarantee.”

### Contracts for error-reporting operations

Because we said an error is a recoverable postcondition failure, the
postcondition doesn't tell you anything about the the state of the
program when an error is reported.  But if you really don't know
*anything* about the state of the program, you probably can't recover.
Fortunately, we can assume by default that the only mutations in case
of an error are to things that the operation would mutate in case of success.

So in the case of `sort`, we know the array was mutated… somehow, but
we don't know much more than that.  Is there anything more we can
reasonably guarantee?

Well, it's _possible_ that our clients could do something with the
array if they know that the array is still a permutation of the
original elements, just rearranged.  OK, I just led you down the
garden path: I actually want to caution you against the line of
thinking that goes, “it's *conceivable* that some unknown client may
have a use for this feature or guarantee, so I'm going to give it to
them.”

1. It's very hard to retract once it's given, because you may break
   code.
2. The guarantee complicates your contract: it needs to be described;
   potential clients need to read and understand it.
3. The guarantee is likely to complicate your implementation and your
   tests.
4. Making needless guarantees may constrain the implementation in ways
   that rule out the most efficient implementation, now or in the
   future.
   
In general, describing a partially mutated state is complex, probably
not useful, and may be impossible. So clients need to assume values
under mutation have arbitrary meaningless values after an error is
reported.

This is not some new thing. In general, it's a BUG to operate on a
partially mutated value. In fact, that's usually the problem you
encounter when there's a data race in your program: a value is
observed when its invariants are broken.

### Partial Mutations? What About Type Invariants?

I told you that you can lean on invariants for reasoning, so you might
find the idea of an interrupted, partial mutation alarming, because
that could leave invariants broken.  That collection of pairs offers a
good example, if appending an element to a vector can fail, as in C++:

```c++
class PairVector<X, Y> {
  vector<X> xs;
  vector<Y> ys;
 public:
  /// Adds `p` to the end.
  void push_back(std::pair<X, Y> p) {
    xs.push_back(p.first);
    ys.push_back(p.second); // <=== here
  }
  ...
}
```

Now I realize that lots of modern programming languages treat
out-of-memory as something that can't happen, so if you use one of
those languages, imagine that the private arrays in this thing are a
different type, `DiskVector`, that's backed by storage on disk, and we
can run out of disk space trying to grow them.

So if an error occurs trying to do the second append, as coded, we're
left with a broken invariant, because the length of `xs` is one
greater than the length of `ys`.

### The Basic Guarantee

So how could we uphold the invariant? There are a number of strategies.
Here's one totally legit way.

```c++
class PairVector<X, Y> {
  vector<X> xs;
  vector<Y> ys;
 public:
  /// Adds `p` to the end.
  void push_back(std::pair<X, Y> p) {
    try {
	  xs.push_back(p.first);
	  ys.push_back(p.second);
	}
	catch(...) { xs.clear(); ys.clear(); throw; }
  }
  ...
}
```

If anything fails, we just discard all the elements.  This is
what we call the Basic Error Guarantee: it says that all invariants
are upheld and nothing is leaked.

This is a nice place to land because the instance of `PairVector` is
still in a good state, and its operations still function as normal.
On the other hand, even if the invariant is upheld, from the client's
perspective this is still a partially mutated object with unknown
contents, and we really shouldn't be doing anything with it.  We'll
come back to that.

### The Nothrow/nofail guarantee

By the way, we need to know something in order for this method to give
the basic guarantee: it only works if `clear()` can't fail—if it gives
the nothrow or nofail guarantee.  Remember I said that whether an
error can occur is part of an operation's contract?  It's crucial
information because error *recovery* needs to use operations that
can't themselves report errors.

### The Strong Guarantee

It turns out that `push_back` can give a stronger guarantee than the
basic one if we recover this way:

```c++
class PairVector<X, Y> {
  vector<X> xs;
  vector<Y> ys;
 public:
  /// Adds `p` to the end.
  ///
  /// - If an exception is thrown, there are no effects.
  void push_back(std::pair<X, Y> p) {
    xs.push_back(p.first);
    try { ys.push_back(p.second); }
	catch(...) { xs.pop_back(); throw; }
  }
  ...
}
```

If the second `push_back` fails, we just undo the first one and the
`PairVector` is unchanged.  The strong guarantee that an operation
either succeeds or has no effects is actually useful to clients in
practice, unlike most statements describing partial mutations.

In fact, we're taking advantage of the strong guarantee from
`vector`'s own `push_back` method here: it's why no recovery is needed
if the first `push_back` fails, and we're able to say that the catch
block restores the state of the `PairVector` because we know that if
we get there, `ys` is unchanged.

### Which guarantee?

So could that `sort` method give the strong guarantee?  Well, we could
always do something like this:

```swift
  mutating func sort<T>(
    areInIncreasingOrder: (T, T) throws->Bool) rethrows
  {
      var tentative = self                             // copy self
      try tentative.actuallySort(areInIncreasingOrder) // sort the copy
      swap(&self, &tentative)                          // swap if no fail
  }
```

This approach leaves `self` unmodified if `actuallySort` fails.  But
it's super expensive: it allocates memory, and incurs O(N) space and
time overhead.  Since we're not sure every client of `sort` needs the
strong guarantee, we shouldn't force them to accept this expense.  On
the other hand, the strong guarantee makes sense for `PairVector`'s
`push_back` because it's achievable without loss of efficiency. It
even falls out of maintaining invariants in the most natural way.

### The Other Way Around

What you've seen so far is basically the theory of error handling that
I developed back in 1998 for the C++ standard library, with every
operation being required to give at least the Basic Guarantee.  It's a
tried and true way to approach thinking about errors and correctness.
But I'd be remiss if I didn't describe Sean's 2022 alternative to the
basic guarantee, which he calls “error handling the other way around.”
It's based on the insight that an unknown partially-mutated value is
meaningless, so any operations you do on it, other than destruction
and maybe assignment, represent a bug—also known as nonsense.

Sean's thesis is that when an operation can't efficiently give the
strong guarantee, maybe upholding invariants is a waste of effort,
because further operations on the value are nonsense and there's no
point in trying to produce a sensible result. It's the client's
obligation to discard any partially mutated value via destruction or
assignment, so all we really need to do is leave the partially-mutated
object in a destructible and assignable state.

If you work on a desktop application with undo, it's effectively
saving a snapshot of the document before every mutation, so your
program is very likely set up to discard partial mutations.

In my 1998 theory of error handling, type invariants are required to
hold after every public operation, whether an error is reported or
not.  If we do error handling “the other way around,” they're only
required to hold if the operation is successful or if it gives the
strong guarantee.  Whichever policy you choose—you got it—document
that.

## Good contract style
<!-- ** Implementation comments indicate a missing refactor -->

### Other elements of contracts ###

<!-- phrasing -->
- Function Signatures
- Cost in time / memory.
  Exact operation counts can be more useful than Big O complexity.
- Conventions (document these!)
- Names
  - Name means something; should reflect the postcondition.  Respect
    the name, or change it.
  - sort with a random comparison is not a shuffle.  At worst, isolate
    it as a hack in a well-named operation.

<!-- phrasing -->
- Names 
  - Think about how the API plays out at the use-site.  Things are
    declared once but used many times.
  - In particular, don’t repeat type info. Don't call an array "array."
  - Express the most specific abstraction being represented.
  - Yes, use a thesaurus!
    Example: Position vs identity vs iterator

- Omit needless words
  - Don't say "An abstraction that…", "A type representing," etc.
  - Don't say anything that is evident from the declaration by itself! "Returns an int that…"
  - Don't say "the specified;" use parameter names.
  - Terseness is supported by having a central document for conventions.
  - Don't talk about self.
  - Constructors can be documented *as* the created instance.
  - Subscripts are a generalization of parameters and can be
    documented *as* the acccessed property.
  - Be willing to use implied preconditions
	“Returns the `i`th element” => `i` must be in range.

- Use a summary sentence fragment.
  - Say what a non-mutating function returns
  - Say what a void-returning mutating function does
  - Other functions: choose based on the primary role.  Usually what
    it does, and incidentally what it returns. An exception might be a
    cache function.
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

- A precondition check is not a crash.  Don't blame the checker.
- A sanity check is the problem of the asserter.

DbC can also be used to _reinforce_ your code and help you discover
bugs during testing.

In a project with more than a couple participants, these checks are
super-valuable.

- Checks must not have significant side-effects
- Checks must not change complexity of operation


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



### Offensive Programming #####
don't accept any nonsense, never forgive

It should be a precondition that your inputs aren't nonsense.  You
can't do the job you're promising to do otherwise.

	func do_foo(x: Bar) {
	  if (is_bad_value(x)) {
		return
	  } 
	  // *actually* do foo.
	}

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

and hide bugs. Usually they create execution paths that are never
tested and may be buggy.

> **Note: Strong Contracts Simplify Code**


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

* Fight Cynicism!

* It's hard but it's worth it.

  Don’t make other people write your contracts.  So inefficient

* Magic Feedback loop with design
  - Contract too complicated? Fix the API!
  - Contract's english description will tell you what to call the API.

* If you've secretly been fooling around with Hoare logic but were
  embarrassed to tell anyone—maybe you have a little impostor
  syndrome—it's OKAY; as a programmer you've earned the
  right.

# -------- ADD TO PART 2 ---------

- Example of contracts that benefit from additional English expression
- Example of uncheckable contracts
- Don't be afraid of having lots of preconditions. You should only
  promise results for inputs that make sense. Weak preconditions
  propagate nonsense—garbage in, garbage out.
- We don't include error effects in the postcondition. (style)

- Error Reporting
  - Returning error or optional
	- good when immediate client has a response
	- awkward for constructors

  - Throwing exception
	- Simplifies client logic when the immediate client can't do anything about it
	- Makes return value available/simple (no encoding failure)
	- Supports construction failure with strong invariants.


# -------- CUT -------
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

