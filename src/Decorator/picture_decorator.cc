class Picture {
 public:
  Picture();

  virtual void Draw();
  virtual void Resize();
  // ...
};

class Decorator: public Picture {
 private:
  Picture* _picture;

 public:
  Decorator(Picture* picture) {
    _picture = picture;
  };

  virtual void Draw() {
    _picture->Draw();
  };
  virtual void Resize() {
    _picture->Resize();
  };
  // ...
};

class BorderDecorator: public Decorator {
 private:
  void DrawBorder();
 
 public:
  BorderDecorator(Picture* picture) : Decorator(picture) {
  };

  virtual void Draw() {
    Decorator::Draw();
    DrawBorder();
  };
};

class ShadowDecorator: public Decorator {
 private:
  void AddShadow();
 
 public:
  ShadowDecorator(Picture* picture) : Decorator(picture) {
  };

  virtual void Draw() {
    Decorator::Draw();
    AddShadow();
  };
};

int main() {
  Picture* p = new Picture;
  bool is_border_enabled, is_shadow_enabled;
  cin >> is_border_enabled >> is_shadow_enabled;

  if (is_border_enabled) {
    p = new BorderDecorator(p);
  }

  if (is_shadow_enabled) {
    p = new ShadowDecorator(p);
  }

  execute_client_code(p);
  return 0;
}