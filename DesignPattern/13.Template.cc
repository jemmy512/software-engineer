class HttpServlet {
public:
     void service(HttpServletRequest req, HttpServletResponse resp) {
        String method = req.getMethod();

        if (method.equals(METHOD_GET)) {
            doGet(req, resp);
        } else if (method.equals(METHOD_HEAD)) {
            doHead(req, resp);
        } else if (method.equals(METHOD_POST)) {
            doPost(req, resp);
        } else if (method.equals(METHOD_PUT)) {
            doPut(req, resp);
        } else if (method.equals(METHOD_DELETE)) {
            doDelete(req, resp);
        } else if (method.equals(METHOD_OPTIONS)) {
            doOptions(req,resp);
        } else if (method.equals(METHOD_TRACE)) {
            doTrace(req,resp);
        } else {
            String errMsg = "http.method_not_implemented";
            resp.sendError(HttpServletResponse.SC_NOT_IMPLEMENTED, errMsg);
        }
    }
};

class HelloServlet : public HttpServlet {
protected:
    void doGet(HttpServletRequest req, HttpServletResponse resp) override {
        this->doPost(req, resp);
    }

protected:
    void doPost(HttpServletRequest req, HttpServletResponse resp) override {
        resp.getWriter().write("Hello World.");
    }
};

int main() {

    return 0;
}

/**
 * Define the skeleton of an algorithm in an operation, deferring somesteps to subclasses.
 * Template Method lets subclasses redefine certain steps of an algorithm
 * without changing the algorithm's structure.
 *
 * Functionalities:
 * 1. Reuse: All subclasses can reuse the code of template method provided by parent class.
 * 2. Extension: Framework provides extension points through template method, so framework users can
 *    customize framework functions through the extension points without modifiying the framework.
 *
 * Callbacks and templates:
 * 0. Sync callbacks like template while async callbacks like observer
 * 1. Callbacks do not need to define new subclasses for new functions
 * 2. Callbacks do not need to implement unwanted template functions
 * 3. Callbacks are implemented by composition, transfor one object to another, are objects relationship
 * 4. Templates are implemented by inheritance, subclass overrides parent, are classes relationship */