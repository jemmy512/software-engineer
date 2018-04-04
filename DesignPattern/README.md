SOLID Principle Of Object-Oriented Programming:
    SRP The Singole Responsiblity Principle
    OCP The Open Closed Principle
    LSP The Liskov Substitution Principle
    ISP The Interafce Segregation Principle
    DIP The Dependency Inversion Principle\
    
********************************** 4 Elementary of TCP Sockets  **************************************************
1. Strategy Patter
    Defines a series algorithms which doing the same work but defferent in the implementation. All the algorithms
        can be called by the same function, deduced the 

********************************** Decorator  ********************************************************************
    Adding extern functionality to an object dynamically.
Advantages:
    Simplefy the original class.
    
********************************** Proxy *************************************************************************
    Provide a proxy for another object to control the this object.
Usage:
    1. Remote Proxy. Provide local proxy for an object in different address space.
    2. Virtual Proxy. Storage an object which takes long time to initialize.
    3. Security Proxy. Control access to real object.
    
********************************** Factory Method ****************************************************************
    Define a interface to create object, subOjbect determines which class to initialize. Delay the object
        initialization to subObject.
    