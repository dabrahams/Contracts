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
writing most of these examples in no particular language. Hopefully,
they should be easily read as pseudocode, but if you have questions, please ask and I'll try to clear them up.  Also speaking of languages, I'm going to refer to English a lot, and please consider that a shorthand for “whatever human languages you use to communicate about software,” which is just too long to repeat.

## Correctness

Fundamentally, contracts are about correctness.  Some people think
it's futile to pursue correctness, but I disagree, for three reasons:

- Simplicity.  The discipline we're talking about actually removes
  loads of needless complexity and uncertainty from the process of
  coding.
  
- joy / possibility.  It's just way more rewarding when you know what
  it means to do your job right.
  
- It's more practical than you might think.

I want to be clear, though, when I talk about correctness, I don't
mean some kind of elaborate formal proof. I mean achieving correctness
through the sort of everyday thinking that we do every day while
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
it's OK to slide into a more formal mode. Not as an academic exercise, but because it's practical and useful. That doesn't make you an impostor; as a programmer you've earned the right.

<!-- consider saving that last idea for the Outro. -->

## Local Reasoning

That kind of everyday thinking only works if we can reason locally...

<!-- insert existing material here. -->

## What's a Contract?

When I say “Contract” I mean something very specific.  In the mid
1980s, Bertrand Meyer, who has to be the coolest cat in Object
Oriented Programming, took Tony Hoare's work on formal verification of
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
either. First of all, correctness is always with respect to a
specification, so undocumented software is neither correct nor
incorrect.

So yes, this is a talk about documentation. While it is true that
there are lots of counterproductive approaches to documentation, I'm
going to show you one that is practical *and*—if you give the process
the attention it deserves—can help you improve the code of your APIs.

I also want to point out that documentation is essential for local
reasoning.  It's the reason I don't need to be a condensed matter
physicist to program a computer.

<!-- insert existing material about documentation/local reasoning
here. -->

## Language / Library Support

You may have heard that some languages have features to support Design by Contract.  In general, that means you can write *parts* of your contracts as code, and get some checking at runtime to make sure they're upheld:

	class Array<T> {
	
	  /// Returns the `i`th element.
	  @requires(i >= 0 && i < self.length) // <=== Here
      fun getNth(i: Integer) -> T
	  ...
    }

The idea started with Bertrand Meyer's own Eiffel language, and was
picked up by many others, including D, Scala, Kotlin, and
Clojure. Others languages, like Rust and Python, have contract
libraries that provide a near-native contract programming experience.

If you use one of these languages, fantastic; absolutely leverage
those features and libraries.  That may reduce the amount of pure documentation you need to write. That said, contracts are still
fundamentally documentation. There are some that really ought to be expressed in English (or your favorite).
expressed as code.

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
correctness of interesting algorithms.  This is just to give you a flavor.  Don't worry if you don't get it; it won't be on the test.

    i = 0
	
	// Loop invariant: if J < i, a[J] != x
	while (i < a.length && a[i] != x) { 
		i += 1
	}
	
	// a[i] is the first element == x, or 
	//   no such element exists and i == a.length
	
This one says all elements preceding element `i` are not equal to `x`.
Combining that loop invariant with the fact that `i` is incremented by 1 each iteration, lets you prove the loop either finds the first x, or leaves i equal to a.length.  For a simple loop like this, you probably don't need to do a proof, but if you're interested, it's a good exercise.

## Class Invariants

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

<!-- show all four implementations -->

There are four basic operations: create an empty instance, get the nth
pair, get the length, and append a new pair.  The invariant for this
type is that the private arrays always have the same length.

If you're the type author, the invariant is basically a “contract with
yourself.” The invariant, or parts of it, could also be publicly
visible.  So if we made the private arrays publicly readable we could
promise the user that their lengths will always match.



# -------------------- Stuff to incorporate ------------------------
## Chain together contracts… 
then show that given a violated precondition you don't know the extent of the damage.

## Don't forget algorithmic complexity
## Deal with failing constructors/exceptions, null.
## Encode program invariants in a type 
(e.g. parent is an element in the database of people)
## 

## Arbitrary damage
You own a supercar, a $7M Bugatti Divo, and you've got a contract with an ultra-exclusive "car butler" who takes care of all the maintenance, including refueling.  The contract, of course, says the butler is only going to use ultra-premium gas.  You also have a contract with the state that says you have to keep this thing's emissions within certain smog limits.  Well at some point the butler puts regular gas for a Prius in there, and of course this starts eating away at the valves and piston heads.  You never really push the car too hard, so you don't notice any difference in performance, but finally you have it taken for its smog checkup and it fails.  You've broken the precondition for the smog test, due to an earlier unnoticed bug (regular gas in supercar).  You take the car back to the dealer and they tell you the damage from regular gas is too extensive and now the car is valued at only $2M, practically worthless.

## 
