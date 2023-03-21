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

## Correctness

Fundamentally, contracts are about correctness.  Some people think
it's futile to pursue correctness, but I disagree, for three reasons:

- Simplicity.  The discipline we're talking about actually removes
  loads of needless complexity and uncertainty from the process of
  coding.
  
- joy / possibility.  It's just way more rewarding when you know what
  it means to do your job right.
  
- It's more practical than you might think.

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

-- [Building bug-free O-O software: An Introduction to Design by
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

You may have heard that some languages have integrated features to
support Design by Contract.  That idea started with Bertrand Meyer's
Eiffel language, and includes D, Scala, Kotlin, and Clojure. Others,
like Rust and Python, have libraries that provide a near-native
contract programming experience. If you use one of these languages,
fantastic; leverage those features and libraries.  Among other
benefits, they will allow you to write many contracts in code.  That
said, contracts are still fundamentally documentation, and some
can't—or shouldn't only—be expressed as code.

## Local Reasoning

- Existing slide material.
- This is what we do every day when we read or write code, to the
  degree possible.

## (Class) Invariants

The most important contribution of Design by Contract, over and above
Hoare Logic, was to apply Hoare's idea of “invariants” to classes, or
more generally, user-defined types with encapsulation.

An “invariant” is just a thing that has to be true at particular
places in a program.  This is a really simple example, but you can
probably see how the invariant might be useful for understanding the
meaning of the next line.

	x.sort()
	
	// invariant: x is sorted
	
	let foundY = x.binary_search(y)

Hoare realized that *loops* have invariants that hold before and after
each iteration, and showed how they could be used to prove the
correctness of interesting algorithms.

Even if you don't care about formal proofs, though, invariants turn
out to be useful for casual reasoning about programs.  Meyer's *class
invariants* are just invariants of types that hold at the boundary of
their public APIs. Let me give you an example:



1. that the user should be able to define their own types and 
2. that each instance of such a type has an encapsulation boundary, so
   public APIs are available to any code operating on the instance,
   but access to private APIs is limited to code that implements
   the type.

Almost any modern language you can think of supports user-defined
types with encapsulation, and this combination also drove the most
significant contribution of Design by Contract, over and above Hoare
Logic.

The most significant contribution of 
The main contribution

I want to start with the part of DbC that really *is* related to
object-orientation, because that will give us context for the rest of
the talk.  The most significant thing that Meyer contributed, on top
of Hoare logic, was to extend Hoare's notion of invariants to cover
classes, or more generally, user-defined types with encapsulation.

## Chain together contracts… 
## then show that given a violated precondition you don't know the extent of the damage.

## Don't forget algorithmic complexity



Some languages like Eiffel and D have features for contract
checking, but the baseline requirement for this discipline that
contracts need to be documented.

In design by contract, a function's documentation covers at least three things:

- preconditions (what's required from the caller)
- postconditions (what's done and/or returned by the callee)
- invariants (conditions that the function preserves)

Having these three things allows clients to use it without diving into the function's implementation to see how it works.

It's required for correct software bigger than a few files, and if you correct software at scale, even if you don't use these words, you're using this discipline.

Invariants also extend to types
>> And every type has its own invariant, that's preserved by all operations on that type.
My favorite example is this type that holds two vectors, and the invariant 
>> is that the vectors always have the same length.  Maybe it's a container that presents pairs of x and y as elements, where storing actual pairs could waste lots of memory due to alignment and padding.

An invariant always has to hold for the program to be correct, with one exception: during a mutation.  If we want to add a new pair, we have to grow one of these vectors first, 
>> which breaks the invariant until we've done the other push_back.  
>> That's not a problem because the vectors are private and we encapsulate the invariant inside a mutating method, that appends a pair.  By the time that method returns, everything is back in order.

But let's see what happens in our object graph:

If you want to be able to do any of these things, you need contracts.













-------------------

Hoare focused on *loop invariants*, which hold before and after each
iteration of a loop:

    i = 0
	
	// loop invariant: elements preceding element i are < x.
	while i < a.length && a[i] < x { 
		i += 1
	}

This one says all elements preceding element `i` are less than `x`.
Now you probably don't need to, but if you wanted to prove that after the loop, `i` is
either at the end, or element `i` is the first one that's not less
than `x`… but unless you're doing formal verification, you probably
don't need to work a case like this using loop invariants

Now, you probably do that kind of reasoning in your head.
