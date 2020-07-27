class Picture {
 public:
  Picture();

  virtual void Draw();
  virtual void Resize();
  // ...
};

class BorderPicture : public Picture {
 private:
  void DrawBorder();
 
 public:
  BorderPicture();

  virtual void Draw() {
    Picture::draw();
    DrawBorder();
  };
};

class ShadowPicture : public Picture {
 private:
  void AddShadow();
 
 public:
  ShadowPicture();

  virtual void Draw() {
    Picture::Draw();
    AddShadow();
  };
};

class BorderShadowPicture : public BorderPicture, public ShadowPicture {
 public:
  BorderShadowPicture();

  virtual void Draw() {
    Picture::Draw();
    BorderPicture::DrawBorder();
    ShadowPicture::AddShadow();
  };
};

int main() {
  Picture* p = new Picture;
  bool is_border_enabled, is_shadow_enabled;
  cin >> is_border_enabled >> is_shadow_enabled;

  if (is_border_enabled && is_shadow_enabled) {
    p = new BorderShadowPicture;
  } else if (is_border_enabled) {
    p = new BorderPicture;
  } else if (is_shadow_enabled) {
    p = new ShadowPicture;
  } else {
    p = new Picture;
  }

  execute_client_code(p);
  return 0;
}