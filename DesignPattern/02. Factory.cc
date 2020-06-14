#include <iostream>
#include <map>

class IConfigParser;
class JsonConfigParser;
class XmlConfigParser;
class YamlConfigParser;
class PropertyConfigParser;

namespace simpleFactory {
    class ConfigFactory {
    public:
        static std::shared_ptr<IConfigParser> createParser(std::string& fileExtension) {
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
        virtual std::shared_ptr<IConfigParser> createParser() = 0;
        virtual ~IConfigFactory() = default;
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
        static std::map<std::string, std::shared_ptr<IConfigFactory>> mFactories;
    };

    std::map<std::string, std::shared_ptr<IConfigFactory>> FactoryContext::mFactories = {
        {"json", std::make_shared<JsonConfigFacgtory>()},
        {"xml", std::make_shared<XmlConfigFacgtory>()}
    };
}

namespace abstractFactory {
// Provide an interface for creating families of related or dependent objects without specifying their concrete classes.

    class IConfigParserFactory {
    public:
        virtual std::shared_ptr<IRuleConfigParser> createRuleConfigParser() = 0;
        virtual std::shared_ptr<ISystemConfigParser> createSystemConfigParser() = 0;
        virtual ~IConfigParserFactory() = default;
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