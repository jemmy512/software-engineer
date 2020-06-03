
int main() {

    return 0;
}

/**
 * Define the skeleton of an algorithm in an operation, deferring somesteps to
 * subclasses. Template Method lets subclasses redefinecertain steps of an algorithm
 * without changing the algorithm's structure.
 *
 * Functionalities:
 * 1. Reuse: All subclasses can reuse the code of template method provided by parent class.
 * 2. Extension: Framework provides extension points through template method, so framework users can
 *    customize framework functions through the extension points without modifiying the framework.
 *
 * Callbacks and templates:
 * 1. Callbacks do not need to define new subclasses for new functions
 * 2. Callbacks do not need to implement unwanted template functions
 * 3. Callbacks are implemented by composition, transfor one object to another, are objects relationship
 * 4. Templates are implemented by inheritance, subclass overrides parent, are classes relationship */