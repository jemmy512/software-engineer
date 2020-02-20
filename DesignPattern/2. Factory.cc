#include <iostream>

namespace simpleFactory {
    class ConfigFactory {
    public:
        static std::make_shared<IConfigParser> createParser(std::string& fileExtension) {
            if (fileExtension == "json") {
                return std::make_shared<JsonConfigParser>();
            } else if (fileExtension == "xml") {
                return std::make_shared<XmlConfigParser>();
            } else if (fileExtension == "yaml") {
                return std::make_shared<YamlConfigParser>();
            } else if (fileExtension == "properties") {
                return std::make_shared<PropertyConfigParser>();
            }

            return nullptr;
        }
    };
}

namespace factoryMethod {
// Define an interface for creating an object, but let subclasses decide which class to instantiate. 
// Factory Method lets a class defer instantiation to subclasses.

    class IConfigFactory {
    public:
        std::shared_ptr<IConfigParser> createParser() = 0;
    };

    class JsonConfigFacgtory : public IConfigFactory {
    public:
        std::shared_ptr<IConfigParser> createParser() override {
            return std::make_shared<JsonConfigParser>();
        }
    };

    class XmlConfigFacgtory : public IConfigFactory {
    public:
        std::shared_ptr<IConfigParser> createParser() override {
            return std::make_shared<XmlConfigParser>();
        }
    };

    class FactoryContext {
    public:
        static std::shared_ptr<IConfigFactory> getFactory(std::string& fileExtension) {
            return mFactories.at(fileExtension);
        }

    private:
        std::map<std::string, std::make_shared<IConfigFactory>> mFactories;
    };
}

namespace abstractFactory {
// Provide an interface for creating families of related or dependent objects without specifying their concrete classes.

    class IConfigParserFactory {
    public:
        std::shared_ptr<IRuleConfigParser> createRuleConfigParser() = 0;
        std::shared_ptr<ISystemConfigParser> createSystemConfigParser() = 0;
    };

    class JsonConfigParserFactory : public IConfigParserFactory {
    public:
        std::shared_ptr<IRuleConfigParser> createRuleConfigParser() override {
            return std::make_shared<JsonRuleConfigParser>();
        }

        std::shared_ptr<ISystemConfigParser> createSystemConfigParser() override {
            return std::make_shared<JsonSystemConfigParser>();
        }
    };

    class XmlConfigParserFactory : public IConfigParserFactory {
    public:
        std::shared_ptr<IRuleConfigParser> createRuleConfigParser() override {
            return std::make_shared<XmlRuleConfigParser>();
        }

        std::shared_ptr<ISystemConfigParser> createSystemConfigParser() override {
            return std::make_shared<XmlSystemConfigParser>();
        }
    };
}

int main() {

    return 0;
}