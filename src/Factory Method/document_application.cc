/**
 * src: https://refactoring.guru/design-patterns/factory-method/cpp/example
 * replaced [Product, Creator] with [Document, Application]
 */

class Document {
 public:
  virtual ~Document() {}
  virtual std::string Operation() const = 0;
};

class DrawingDocument : public Document {
 public:
  std::string Operation() const override {
    return "{Result of the DrawingDocument}";
  }
};
class WritingDocument : public Document {
 public:
  std::string Operation() const override {
    return "{Result of the WritingDocument}";
  }
};

class Application {
 public:
  virtual ~Application(){};
  virtual Document* FactoryMethod() const = 0;

  std::string SomeOperation() const {
    Document* document = this->FactoryMethod();
    std::string result = "The same creator(application)'s code has just worked with " + document->Operation();
    delete document;
    return result;
  }
};

class DrawingApplication : public Application {
 public:
  Document* FactoryMethod() const override {
    return new DrawingDocument();
  }
};

class WritingApplication : public Application {
 public:
  Document* FactoryMethod() const override {
    return new WritingDocument();
  }
};

void ClientCode(const Application& application) {
  std::cout << "Client: I'm not aware of the application's class, but it still works.\n"
            << application.SomeOperation() << std::endl;
}

int main() {
  std::cout << "App: Launched with the ConcreteApplication1.\n";
  Application* application1 = new DrawingApplication();
  ClientCode(*application1);
  std::cout << std::endl;
  std::cout << "App: Launched with the ConcreteApplication2.\n";
  Application* application2 = new WritingApplication();
  ClientCode(*application2);

  delete application1;
  delete application2;
  return 0;
}