template <class Item>
class List {
 public:
  List(long size = DEFAULT_LIST_CAPACITY); // 생성자
  long Count() const; // 리스트의 현재 길이
  Item& Get(long index) const; // n번째 아이템을 반환
  // ...
};

template <class Item>
class Iterator {
 public:
  virtual void First() = 0;
  virtual void Next() = 0;
  virtual bool IsDone() const = 0;
  virtual Item CurrentItem() const = 0;

 protected:
  Iterator();
};

// 구현 1. ListIterator: 정방향 순회
template <class Item>
class ListIterator : public Iterator <Item> {
 public:
  // 실제 구현: 리스트 포인터를 저장해서 특정 index의 아이템을 반환
  ListIterator(const List<Item>* aList) {
    _list = aList;
    _current = 0;
  }
  virtual void First() {
    _current = 0;
  }
  virtual void Next() {
    _current++;
  }
  virtual bool IsDone() const {
    return _current >= _list->Count();
  }
  virtual Item CurrentItem() const {
    if (IsDone()) {
      throw IteratorOutOfBounds;
    }
    return _list->Get(_current);
  }

 private:
  const List<Item>* _list;
  long _current;
};

// 구현 2. ReverseIterator: 역방향 순회
template <class Item>
class ReverseIterator : public Iterator <Item> {
 public:
  ReverseIterator(const List<Item>* aList) {
    _list = aList;
    _current = _list->count();
  }
  virtual void First() {
    _current = _list->count();
  }
  virtual void Next() {
    _current--;
  }
  virtual bool IsDone() const {
    return _current <= 0;
  }
  virtual Item CurrentItem() const {
    if (IsDone()) {
      throw IteratorOutOfBounds;
    }
    return _list->Get(_current);
  }

 private:
  const List<Item>* _list;
  long _current;
};

// 클라이언트에서 이러테이터 사용하기
void PrintEmployees(Iterator <Employee*>& i) {
  for (i.First(); !i.IsDone(); i.Next()) {
    i.CurrentItem()->Print();
  }
}

List <Employee*>* employees;
// ...
ListIterator <Employee*> forward(employees);
ReverseListIterator <Employee*> backward(employees);

PrintEmployees(forward);
PrintEmployees(backward);