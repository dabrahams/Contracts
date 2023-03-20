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
system generalizes perfectly well to any programming paradigm. That's
a strong indication that he was onto something deep and fundamental.

So I'm going to present what we think of as a modern generalization
of DbC.

## Real Talk: It's Documentation

Looking back at Meyers' description, you might notice the words
“precisely defined specification,” which means contracts are
documentation.

If you're like a lot of programmers I know, your eyes are rolling back
in your head. You can find all kinds of reasons on the web that
documentation is supposedly a waste of time, but if you've been to any
of my talks you know that I don't agree. The only people who really
believe that are working alone on throw-away code.  Living with your
own code for a little while can cure you of this ailment.

Some languages, starting with Bertrand Meyer's Eiffel, and including
D, Scala, Kotlin, and Clojure, have integrated features to support
Design by Contract, and others, like Rust and Python, have libraries
that provide a near-native experience. If you use one of these
languages, that's fantastic; leverage those features and libraries.
Among other benefits, it will allow you to write many contracts as
code.  That said, contracts are still fundamentally documentation, and
some can't—or shouldn't only—be expressed as code.

So yes, this is a talk about documentation.

## Correctness


Besides
which, I'm going to show you how to make it livable.

## Chain together contracts… then show that given a violated
## precondition you don't know the extent of the damage.

It's a way of describing the
rules that govern how the parts of your system interact.

We're going to present Meyer's

Then he incorporated support for
it into his own


refined came up with a discipline called Design by
Contract, that 



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













