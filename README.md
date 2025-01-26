## BrailleScript

### Goals

The goal of **BrailleScript** is to simplify or reduce common everyday programming tasks and problems. **BrailleScript** get its name from its operators, which are reminiscent of the Braille language for the visually impaired. There are no keywords, yielding concise syntax that strives for readability and simplicity.

**BrailleScript** in its current state is simply an expression evaluator, not a full-featured language implementation. This will change as progress is made, so keep an eye out if this project interests you. Oh, and expect a ```.bs``` file extension for LSP and linting support.

## Statements:

* ```#``` : **Single-line comment**
* ```:```: **Assignment**
* ```:>``` : **Function definition**
* ```.:``` : **if**
* ```:.``` : **then**
* ```..``` : **else**
* ```::``` : **end**
* ```.;``` : **for**
* ```;.``` : **do**
* ```;;``` : **while**
* ```:>>``` : **continue**
* ```<<:``` : **break**
* ```@``` : **return**

## Unary Operators:

* ```+A``` : **Unary Plus**
* ```-A``` : **Unary Minus / Negate**
* ```!A``` : **Unary Not**
* ```~A``` : **Unary Bitwise Not**

## Binary Operators:

* ```A + B``` : **Add**
* ```A - B``` : **Subtract**
* ```A * B``` : **Multiply**
* ```A / B``` : **Divide**
* ```A % B``` : **Modulo**
* ```A ** B``` : **Power**
* ```A & B``` : **Bitwise and**
* ```A | B``` : **Bitwise or**
* ```A ^ B``` : **Bitwise exclusive or**
* ```A << B``` : **Bitwise left shift**
* ```A >> B``` : **Bitwise right shift**
* ```A == B``` : **Equality**
* ```A != B``` : **Inequality**
* ```A < B``` : **Less than**
* ```A <= B``` : **Less than or equal**
* ```A > B``` : **Greater than**
* ```A >= B``` : **Greater than or equal**
* ```A && B``` : **Logical and**
* ```A || B``` : **Logical or**
* ```A += B``` : **Add equal**
* ```A -= B``` : **Subtract equal**
* ```A *= B``` : **Multiply equal**
* ```A /= B``` : **Divide equal**
* ```A %= B``` : **Modulo equal**
* ```A &= B``` : **Bitwise and equal**
* ```A |= B``` : **Bitwise or equal**
* ```A ^= B``` : **Bitwise exclusive or equal**
* ```A <<= B``` : **Left shift equal**
* ```A >>= B``` : **Right shift equal**

## Code Examples:

### Assignment

```bs
x: 10
y: 20
```

### If, then, else, end

```bs
.: x > y :.
	log( "x greater" )
..
	log( "y greater" )
::
```

## For

```bs
# Counts from 1 to 10.

.; i: 1, 10 ;.
	log( i )
::
```

```bs
# Counts from 1 to 10 by increments of 2

.; i: 1, 10, 2 ;.
	log( i )
::
```

## While

```bs
# Counts from 10 to 0, decrementing by 1

x: 10

;; x > 0 ;.
	log( x )
	x -= 1
::
```

## Do While
```bs
# Right shifts 'x' until it becomes 0.
# 'bits' counts the number bits shifted.

x: 128
bits: 0

;.
	x >>= 1
	bits += 1
;; x > 0

log( bits )
```

## Continue
```
# Counts to 50, continuing past even numbers.

.; i: 0, 50 ;.
	.: i % 2 != 0 :. :>> ::
	log( i )
::
```

## Break
```
# Count from 10 to 20, but break when we hit 15.

.; i: 10, 20 ;.
	.: i == 15 :. <<: ::
::
```

## Functions
```bs
# There are 2 ways to define a function.

add:>( x, y )
	@x + y
::

:> sub( x, y )
	@x - y
::

# There may be support for double-colon definitions as well, since it looks a bit more appealing:

mul::>( x, y )
	@x * y
::

```