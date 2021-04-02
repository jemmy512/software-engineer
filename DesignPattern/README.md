# Creational Patterns

## Singleton
1. Disadvantages:
    1. Unfriendly support for OOP
    2. Hide the dependencies between classes
    3. Poor scalabiliry
    4. Poor testbility
    5. Unsupport constructor with paramters

2. Solution:
    1. Factory Design Pattern
    2. IOC container
    3. Programmer make sure do not creat more than one instance

## Factory
1. Functionality of Factory:
    1. Encapsulate change
    2. Reuseability
    3. Encapsulate complxity of object creation
    4. Control complxity of the use code

2. Simple factory vs factory method:
 * If the Object creation is complex, use factory meothod, encapsulate the complexity into each subfactory; otherwise, use simple factory.

## Builder
1. Usage:
    1. There are many paramters in the contrcutor. Some are mandatory, some are optional. It's error-prone to use the constructor with many parameters.
    2. The parameters has some relationship. With set method, relationship can't validate.
    3. We hope to new a const object

2. Difference with Factory pattern:
    1. Factory create different but related types of objects dentermined by given parameters.
    2. Builder create the same type but complex object which is customized by different parameters.

## Prototype

# Structural Patterns

## Proxy
1. Intent
    1. add functionalities without changing the original class,
    2. decouple the framework code with business code,
    3. the purpose is access control rather than enhancement.

2. Use cases: RPC, Cache, Monitor, Authentication, Rate limit, Transaction, logging

3. Implementation:
    1. implemnet same interface
    2. inheritance

## Bridge
1. Definition
    * Decouple the abstration from it's implement so the two can vary independently.
    * The bridge pattern can also be thought of as two layers of abstraction.
    * When there is only one fixed implementation, this pattern is known as the Pimpl idiom.


## Decorator
The decorator pattern maily solves the complexity problem of the inheritance, and replaces inheritance through composition. It's main role is to add enhancements to the original class.

You can nest mutiple decorator classes to the original class, this requires the decorator classes need to inherit the same interface with the original class.

## Adapter
1. Adapter category:
    1. Class adapter: implemented by inheritance when adapter have many same interfaces with adaptee.
    2. Object adapter: implemented by composing when addapter doesn't have many same interfaces with adaptee.

 2. Scenarios:
    1. Encapsulat interfaces that have defective design
    2. Unify interface design for multiple classes
    3. Replace external dependent systems
    4. Compatible with older versions of the interface
    5. Adapt data in different formats

## Facade
1. Definition
    * Provide a unified interface to a set of interfaces in a subsystem.
    * Facade Pattern defines a higher-level interface that makes the subsystem easier to use.

2. Senario:
    1. Resolve usability issue
    2. Resolve performance issue
    3. Resolve distributed transaction issue

## Composite
1. Definition:
    1. Compose objects into tree structure to represent the part-whole hirarchies.
    2. Composite lets client treat the individual objects and compositions of objects uniformly.

## Flyweight
1. Definition
    * Use sharing to support large numbers of fine-grained objects efficiently.

# Behavioral Patterns

## Observer

## Template
1. Definition
    * Define the skeleton of an algorithm in an operation, deferring some steps to subclasses. Template Method lets subclasses redefine certain steps of an algorithm without changing the algorithm's structure.
2. Functionalities:
    1. Reusability: All subclasses can reuse the code of template method provided by parent class.
    2. Extension: Framework provides extension points through template method, so framework users can customize framework functions through the extension points without modifiying the framework.
3. Callbacks and templates:
    1. Sync callbacks like template while async callbacks like observer
    2. Callbacks do not need to define new subclasses for new functions
    3. Callbacks do not need to implement unwanted template functions
    4. Callbacks are implemented by composition, transfor one object to another, are objects relationship
    5. Templates are implemented by inheritance, subclass overrides parent, are classes relationship

## Strategy
1. Definition
    * Define a family of algorithms, encapsulate each one, and make them interchangeable. Strategy lets the algorithm vary independently from clients that use it.
    * Strategy decouples the definition, creation and usage of a strategy, avoid complexity of each part.
2. Strategy VS Command:
    1. A group Strategies have the same goal, but different implementation, they can interexchange
    2. A group commands have different goals, and they can't interexchange
3. Strategy VS Factory:
    1. Strategy focus on strategies or algorithms, select different strategies according to different scenarios
    2. Factory focus on the creation of objects, regardless of scenarios

## Chain
1. Definition
    * Avoid coupling the sender of a request to its receiver by giving more than one object a chance to handle the request. Chain the receiving objects and pass the request along the chain until an object handles it.
2. Applicability
    * Implement filter, intercepter.
    * Let user add new functionality without change the framework.

## Iterator

## State
1. Definition
    * Allow an object to alter its behavior when its internal state changes. The object will appear to change its class.
2. Three Implementation ways:
    1. branch logic method
    2. look-up table
    3. state mode: avoids judging branch logic by dividing event-triggered state transitions and action execution into different state classes.

## Visitor
1. Definition
    * Allows for one or more operation to be applied to a set of objects at runtime, decoupling the operations from the object structure.
2. Intent
    * The visitor pattern aims at a group of objects inherited the same parent class, or implement the same interface.
    * In different application scenarios, we need to perform a group of unrelated operations on this group of objects, to avoid frequent code changes and classes are not single responsibility, we decouple the objects and operations, extract those operations into separate subdivided classes.
## Memoto
1. Definition
    * Captures and externalizes an object’s internal state so that it can be restored later, all without violating encapsulation.

## Command
1. Definition
    * The command pattern encapsulates a request as an object, thereby letting us parameterize other objects with different requests, queue or log requests, and support undoable operations.
    * Command pattern's primary purpose and application scenario: control the execution of the command, e.g., async, dealy, queue execute, undo, redo, log...
 2.  Strategy VS Command:
    1. Different Strategies have the same goal, but different implementation, they are interchangeable
    2. Different commands have different goals, and they aren't interchangeable
3. Strategy VS Factory:
    1. Strategy focus on strategies or algorithms, select different strategies according to different scenarios
    2. Factory focus on the creation of objects, regardless of scenarios

## Interpreter
1. Definition
    * Interpreter pattern is used to defines a grammatical representation for a language and provides an interpreter to deal with this grammar.
    * The main purpose of the design pattern is to deal with the complexity of the code.
    * The core idea of interpreting pattern is to split the work of parsing classes into various small classes to avoid large and complete classes.
## Mediator
1. Definition
    * Mediator pattern defines a separate (mediator) object that encapsulates the interaction between a set of objects and the objects delegate their interaction to a mediator object instead of interacting with each other directly.
2. Mediator vs Observer
    * The interaction between objects in Observer is one to many; in Mediator is many to many, it's much complex than observer.

## Delegation
1. Definition
    * Delegation is a way to make composition as powerful for reuse as inheritance.
    * In delegation, two objects are involved in handling a request: a receiving object delegates operations to its delegator. This is analogous to subclasses deferring requests to parent classes.
    * But with inheritance, an inherited operation can always refer to the receiving object through the this member variable in C++. To achieve the same effect with delegation, the receiver passes itself to the delegator to let the delegated operation refer to the receiver