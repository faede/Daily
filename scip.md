# SCIP
## Chapter 1 Building Abstractions with Procedures

lisp

```
The language
was conceived by John McCarthy and is based on his paper "Recursive
Functions of Symbolic Expressions and Their Computation by Machine"
(McCarthy 1960).
```

The most significant of these features is the fact that Lisp descriptions of processes, called procedures,
can themselves be represented and manipulated as Lisp data. The importance of this is that there are powerful program-design techniques that rely on the ability to blur the traditional distinction between "passive" data and "active" processes.



Poerful language has thtree mechanisms

* primitibe  expression , which represent the simplest entites
* means of combination 
* means of abstraction

Prefix notation has several advantages, however. 

One of them is that it can accommodate procedures that may take an arbitrary number of arguments .

`(+ 12 12 2 1 3)`

A second advantage of prefix notation is that it extends in a straightforward
way to allow combinations to be *nested*, that is, to have combinations
whose elements are themselves combinations:



names things with `define` -- special foms.

`(define size 2)`

• To evaluate a combination, do the following:
  1 . Evaluate the subexpressions of the combination.

2. Apply the procedure that is the value of the leftmost subexpression
(the operator) to the arguments that are the values of the other subexpressions
(the operands).



compound procedure

"To square something, multiply it by itself." This is expressed
in our language as
`(define (square x) ( * x x) )`

`(define (<name> <formal parameters>) <body> )`



substitution model



* normal-order evaluation
* applicative-order evaluation

It can be shown that, for procedure
applications that can be modeled using substitution (including all
the procedures in the first two chapters of this book) and that yield legitimate
values, normal-order and applicative-order evaluation produce
the same value.

lisp use applicative-order evaluation

### 1.1.6+

(define		( abs x)
	( cond	 (( > x 0 ) x )
				   (( = x 0 ) 0 )
				   (( < x 0 )  ( - x ) ) ) )
The general form of a conditional expression is

```scheme
(cond (<p1> <e1>)
	 		(<p2> <e2>)
	 		...
	 		(<pn> <en>))
```

(define		( abs x)
	( cond	 (( < x 0 ) -x )
				   (else x )))

```scheme
(define ( abs x )
		( if (< x 0 )
				 ( - x )
				 x))
```

`( if ( predicate ) ( consequent ) ( alternative ) )`

and or not 

`( and  <e1> ... <en > )`

exe 1.6



This principle-that the meaning of a procedure should be independent
of the parameter names used by its author-seems on the surface to be
self-evident, but its consequences are profound.

#### recursive

When we describe a procedure as recursive, we are referring to
the syntactic fact that the procedure definition refers (either directly or
indirectly) to the procedure itself. But when we describe a process as
following a pattern that is, say, *linearly recursive*, we are speaking about
how the process evolves, not about the syntax of how a procedure is written.
It may seem disturbing that we refer to a *recursive procedure* such
as fact - iter as generating an iterative process





Tail recursion has long been known as a compiler optimization trick. A coherent semantic basis for tail recursion was provided by Carl Hewitt ( 1 977), who explained it in terms of the "message-passing" model of computation that we shall discuss in chapter 3. Inspired by this, Gerald Jay Sussman and Guy Lewis Steele Jr. (see Steele 1 975) constructed a *tail-recursive* interpreter for Scheme.



tree-recursive

Fib 

```scheme
(define (fib n )
	cond ((= n 0) 0)
			 ((= n 1) 1)
			 (else (+ (fib (- n 1))
			 					(fib (- n 2)))))
```



the number of times the procedure will compute ( f ib 1) or
( fib 0) (the number of leaves in the above tree, in general) is precisely
Fib(n + 1 ) .

```scheme
(define (fib n) 
	(fib-iter 1 0 n)
)    
(define (fib-iter a b count)
           (if (= count 0)
		b
		(fib-iter (+ a b) a (- count 1 ))))
```



Counting Coins

How many different ways can we make change of $ 1 .00, given half-dollars, quarters, dimes, nickels, and pennies? More generally, can we write a procedure to compute the number of ways to change any given amount of money?

```
The number of ways to change amount a using n kinds of coins equals
• the number of ways to change amount a using all but the first kind of
coin, plus
• the number of ways to change amount a - d using all n kinds of coins,
where d is the denomination of the first kind of coin.
```

```
• If a is exactly 0, we should count that as 1 way to make change.
• If a is less than 0, we should count that as ° ways to make change.
• If n is 0, we should count that as ° ways to make change.
```



```scheme
(define (count-change amount)
	(cc amount 5))
	
(define ( cc amount kinds-of-coins)
	(cond ((= amount 0) 1)
	      ((or (< amount 0 ) (= kinds-of-coins 0 )) 0 )
	      (else (+ (cc amount
			   (- kinds-of-coins 1 ))
		       (cc (- amount 
				(first-denomination kinds-of-coins)) 
			   kinds-of-coins)))))
(define (first-denomination kinds-of-coins)
	(cond ((= kinds-of-coins 1) 1)
 				((= kinds-of-coins 2) 5)
 				((= kinds-of-coins 3) 10 )
 				((= kinds-of-coins 4) 25 )
 				((= kinds-of-coins 5) 50)))
```



One approach to coping with redundant computations is to arrange matters so that we automatically construct a table of values as they are computed. Each time we are asked to apply the procedure to some argument, we first look to see if the value is already stored in the table, in which case we avoid performing the redundant computation. This strategy, known as *tabulation* or *memoization*, can be implemented in a straightforward way. Tabulation can sometimes be used to transform processes that require an exponential number of steps (such as count -change) into processes whose space and time requirements grow linearly with the input.



Fast-Exp

```scheme
(define (fast-expt b n)
  (cond ((= n 0) 1)
        ((even? n)(square (fast-expt b (/ n 2))))
        (else (* b (fast-expt b (- n 1))))))

(define (even? n)
  (= (remainder n 2) 0))
```



Fast-Fib

There is a clever algorithm for computing the Fibonacci numbers in a logarithmic
number of steps. Recall the transformation of the state variables a and b in
the f ib-iter process of section 1.2.2: $a \leftarrow  a +b$ and $b \leftarrow  a$. Call this transformation
T, and observe that applying T over and over again n times, starting with
1 and 0, produces the pair Fib(n+1) and Fib(n) . In other words, the Fibonacci
numbers are produced by applying $T^n$, the nth power of the transformation T,
starting with the pair (1, 0) . 

Now consider T to be the special case of p = 0 and q = 1 in a family of transformations $ T_{pq}$ , where $ T_{pq}$  transforms the pair (a , b) according to $a \leftarrow bq + aq + ap $ and $ b \leftarrow bp + aq $. Show that if we apply such a transformation $ T_{pq}$ twice, the effect is the same as using a single transformation $ T_{p'q'}$of the same form, and compute p' and q' in terms of p and q . This gives us an explicit way to square these transformations, and thus we can compute $T^n$ using successive squaring, as in the fast-expt procedure. Put this all together to complete the following procedure, which runs in a logarithmic number of steps:

```scheme
(define (fib n)
   (fib-iter 1 0 0 1 n))

(define (fib-iter a b p q count)
  (cond ((= count 0) b)
        ((even? count)
         (fib-iter a
                   b
                   (+ (* q q) (* 2 (* q p)) )
                   (+ (* q q) (* p p))
                   (/ count 2)))
        (else (fib-iter (+ (* b q) (* a q) (* a p))
                        (+ (* b q) (* a q))
                        p
                        q
                        (- count 1)))))
```

show:

 $a \leftarrow bq + aq + ap $

$a \leftarrow (bp + aq)q + (bq + aq + ap)q + (bq + aq + ap)p$

=>

$q' = q^2 + 2pq$

$p'=p^2+q^2$

so as b



Greatest Common Divisors



GCD(a, b) = GCD(b, r)      *Euclid's Algorithm*

Lame’  Theorem :

If Euclid's Algorithm requires k steps to compute the GCD of some pair, then the smaller number in the pair must be greater than or equal to the kth Fibonacci number.



Test for Primality

1. Searching for divisors

2. The Fermat test

The 0 (log n) primality test is based on a result from number theory known as Fermat's Little Theorem.
Fermat's Little Theorem:

If n is a prime number and a is any positive integer less than n, then a raised to the nth power is congruent to a modulo n .

(Two numbers are said to be *congruent modulo n*  if they both have the
same remainder when divided by n . The remainder of a number a when
divided by n is also referred to as the *remainder of a modulo* n, or simply
as a modulo n .)

If n is not prime, then, in general, most of the numbers a < n will not satisfy the above relation. This leads to the following algorithm for testing primality: Given a number n, pick a random number a < n and compute the remainder of an modulo n . If the result is not equal to a, then n is certainly not prime. If it is a, then chances are good that n is prime. Now pick another random number a and test it with the same method. If it also satisfies the equation, then we can be even more confident that n is prime. By trying more and more values of a , we can increase our confidence in the result. This algorithm is known as the Fermat test. To implement the Fermat test, we need a procedure that computes the exponential of a number modulo another number:

There do exist numbers that fool the Fermat test: numbers n that are not prime and yet have the property that an is congruent to a modulo n for all integers a < n

```
47Numbers that fool the Fermat test are called Carmichael numbers, and little is known about them other than that they are extremely rare. There are 255 Carmichael numbers below 100,000,000. The smallest few are 561, 1 1 05, 1 729, 2465, 282 1 , and 660 1 . In testing primality of very large numbers chosen at random, the chance of stumbling upon a value that fools the Fermat test is less than the chance that cosmic radiation will cause the computer to make an error in carrying out a "correct" algorithm. Considering an algorithm to be inadequate for the first reason but not for the second illustrates the difference between mathematics and engineering.
```





Procedures that manipulate procedures are called higher-order procedures. 

```scheme
(define (sum term a next b)
  (if (> a b)
      0
      (+ (term a)
         (sum term (next a) next b))))
```

so we can define sum-cubes

```scheme
(define (inc n )(+ n 1))

(sum cube a inc b)
```



```scheme
(define (identity x) x)
(define (sum-integers a b)
	(sum identity a inc b))

(sum-integers 1 10)

```



#### 1.3.2 lambda

```scheme
(define (pi-sum a b)
  (sum (lambda (x) (/ 1.0 (* x (+ x 2))))
       a
       (lambda (x) (+ x 4))
       b))
```

In general, lambda is used to create procedures in the same way as define , except that no name is specified for the procedure:

```(lambda (<formal-parameters>) <body> )```

#### using let to create locate varibles

$f(x,y)=x(1+xy)^2+y(1-y)+(1+xy)(1-y)$

$a=1+xy$

$b=1-y$

$f(x,y)=xa^2+yb+ab$



we can use aux produrces such as

```scheme
(define (f x y)
  (define (f-helper a b)
    (+ (* x (square a))
       (* y b)
       (* a b)))
  (f-helper (+ 1 (* x y))
            (- 1 y)))
```

or lambda,

or let:

```scheme
(define (f x y)
  (let ((a (+ 1 (* x y)))
        (b (- 1 y)))
    (+ (* x (square a))
       (* y b)
       (* a b))))
```

 

general 

```scheme
(let ((<var1> <exp1>)
      (<var2> <exp2>)
      .
      .
      .
      (<varn> <expn>))
  <body>)
```



A let expression is simply syntactic sugar for the underlying lambda application.



Elements with the fewest restrictions are said to have first-class status.

• They may be named by variables.

• They may be passed as arguments to procedures.

• They may be returned as the results of procedures.

• They may be included in data structures.



Lisp, unlike other common programming languages, awards procedures full first-class status. This poses challenges for efficient implementation, but the resulting gain in expressive power is enormous

### 2 Building Abstractions with Data

the means it provides for building abstractions by combining data obj ects to form compound data.